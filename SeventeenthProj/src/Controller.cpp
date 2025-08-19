#include "Controller.h"

bool Controller::gameFinished = false;

// Opening file
Controller::Controller()
	: m_window(sf::VideoMode(WindowWidth, WindowHeight), "Mushroom Game", sf::Style::Fullscreen),
	  m_transitionScreen(sf::Vector2f(WindowWidth, WindowHeight)),
	  m_teleportSound(Resources::instance().sound(Resources::Portal_Sound)),
	  m_view(sf::FloatRect(sf::Vector2f(0.f,0.f), sf::Vector2f(WindowWidth, WindowHeight))),
	  m_GUIview(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(WindowWidth, WindowHeight))),
	  cursor(Resources::instance().texture(Resources::Cursor))
{
	m_window.setFramerateLimit(60);	
	m_window.setMouseCursorVisible(false);
	m_window.setView(m_view);
	m_transitionScreen.setFillColor(sf::Color::Transparent);
}
//----------------------------------------------------
void Controller::run()
{
	spawn(Map::MushroomTown);

	while (m_window.isOpen() && !gameFinished)
	{
		draw();
		handleEvents();
		updateGameObjects();
		updateView();
		updateInfo();
	}
}
//----------------------------------------------------
void Controller::finishGame()
{
	gameFinished = true;
}
//----------------------------------------------------
void Controller::draw()
{
	m_window.clear();
	if (auto debugSpriteSheet = 0) // use 1 to debug animation data
	{
		displayAll(m_window, Resources::instance().animationData(Resources::BlueSnail));
	}
	else
	{
		m_window.draw(*Map::instance().background());
		m_window.draw(*Map::instance().map());

		for (auto& unmovable : Map::instance().unmovables())
			unmovable->draw(m_window);

		for (auto& monster : Map::instance().monsters())
			monster->draw(m_window);

		for (auto& npc : Map::instance().npcs())
			npc->draw(m_window);

		Map::instance().player()->draw(m_window);

		for (auto& portal : Map::instance().portals())
			portal->draw(m_window);

		Info::instance().drawInfo(m_window);

		// GUIview helps us keep GUIs in place while moving
		m_window.setView(m_GUIview);
		Info::instance().drawGUI(m_window);
		m_window.draw(cursor);
		m_window.draw(m_transitionScreen);
		m_window.setView(m_view);
	}
	m_window.display();
}
//----------------------------------------------------
void Controller::handleEvents()
{
	cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));

	for (auto event = sf::Event{}; m_window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				m_window.close();

			if (event.key.code == sf::Keyboard::Up)
				checkPortals();
			break;
		case sf::Event::MouseButtonReleased:
			if (Map::instance().player()->getData().respawn)
			{
				fadeIn();
				Map::instance().player()->respawn();
				updateView();
				fadeOut();
				gameClock.restart();
			}
			break;
		case sf::Event::MouseButtonPressed:
			for (auto& npc : Map::instance().npcs())
				if (npc->wasClicked(m_window))
					Info::instance().showDialogue(npc->dialogue(), npc->name(), npc->sprite());
		}			
	}
}
//----------------------------------------------------
void Controller::updateGameObjects()
{
	const auto delta = gameClock.restart();

	// movement + collision
	Map::instance().player()->update(delta);
	Map::instance().player()->updatePhysics();
	handleCollisions(*Map::instance().player());
	
	for (auto& monster : Map::instance().monsters())
	{
		monster->update(delta);
		handleCollisions(*monster);
		monster->updatePhysics();
	}
	
	for (auto& portal : Map::instance().portals())
		portal->update(delta);

	for (auto& npc : Map::instance().npcs())
		npc->update(delta);

	Map::instance().respawn();
}
//----------------------------------------------------
void Controller::updateInfo()
{
	Info::instance().update(Map::instance().player()->getData());
}
//----------------------------------------------------
void Controller::handleCollisions(gameObject& gameObject)
{
	// check collision with player
	if (gameObject.collidesWith(Map::instance().player()->getGlobalBounds()))
		gameObject.handleCollision(*Map::instance().player());

	// check collision with unmovables
	for (auto& unmovable : Map::instance().unmovables())
		if (gameObject.collidesWith(unmovable->getGlobalBounds()))
			gameObject.handleCollision(*unmovable);
}
//----------------------------------------------------
void Controller::spawn(const int& mapID)
{
	m_teleportSound.play();

	// transition screen
	readFile(mapID);

	// so we don't fall off the map
	for (auto& monster : Map::instance().monsters())
		for (int i = 0; i < 5; i++)
			handleCollisions(*monster);

	for (int i = 0; i < 5; i++)
		handleCollisions(*Map::instance().player());

	fadeOut();

	gameClock.restart();	// unfreeze clock
}
//----------------------------------------------------
void Controller::changeMap(const int& mapID, const int& exitPortal)
{
	// make sure we wait before teleporting again
	teleportTime.restart();
		
	fadeIn();			// transition screen

	readFile(mapID);

	// spawn in exit portal
	if (exitPortal > -1)
		Map::instance().player()->setPosition(Map::instance().portals()[exitPortal]->getPosition() - sf::Vector2f(0.f, 80.f));

	fadeOut();				// transition screen

	gameClock.restart();	// unpause the game
}
//----------------------------------------------------
void Controller::fadeIn()
{
	bool fadingIn = true;
	m_transitionScreen.setFillColor(sf::Color::Transparent); // Start with a black screen

	float alpha = 0.f; // Initial alpha value for fading

	while (fadingIn)
	{
		// Apply the alpha value to the screen
		alpha += 5.0f;								// speed of the fade
		sf::Color screenColor = m_transitionScreen.getFillColor();
		screenColor.a = static_cast<sf::Uint8>(alpha);
		m_transitionScreen.setFillColor(screenColor);
		draw();
		updateInfo();

		if (alpha == 255.f)
			fadingIn = false;
	}
}
//----------------------------------------------------
void Controller::fadeOut()
{
	bool fadingOut = true;
	m_transitionScreen.setFillColor(sf::Color::Black); // Start with a black screen

	float alpha = 255.f; // Initial alpha value for fading

	updateView();

	while (fadingOut)
	{
		// Apply the alpha value to the screen
		alpha -= 5.0f;								// speed of the fade
		sf::Color screenColor = m_transitionScreen.getFillColor();
		screenColor.a = static_cast<sf::Uint8>(alpha);
		m_transitionScreen.setFillColor(screenColor);
		draw();

		if (alpha == 0.f)
			fadingOut = false;
	}
}
//----------------------------------------------------
void Controller::checkPortals()
{
	// when player is on a portal he can change map
	for (auto& portal : Map::instance().portals())
	{
		if (teleportTime.getElapsedTime().asSeconds() > TimeBetweenTeleports &&
			portal->destination() != -1 &&
		   !Map::instance().player()->isDead() &&
			Map::instance().player()->collidesWith(portal->getGlobalBounds()) &&
			Map::instance().player()->getGlobalBounds().left > portal->getGlobalBounds().left &&
			Map::instance().player()->getGlobalBounds().left < portal->getGlobalBounds().left + Map::instance().player()->getGlobalBounds().width &&
			Map::instance().player()->getGlobalBounds().top > portal->getGlobalBounds().top + Map::instance().player()->getGlobalBounds().height)
		{
			m_teleportSound.play();
			changeMap(portal->destination(), portal->exitPortal());
		}
	}
}
void Controller::updateView()
{
	const sf::Vector2f playerCenter(Map::instance().player()->getGlobalBounds().left + Map::instance().player()->getGlobalBounds().width / 2.f,
		                            Map::instance().player()->getGlobalBounds().top + Map::instance().player()->getGlobalBounds().height / 2.f);

	if (playerCenter.x > WindowWidth / 2.f && playerCenter.x < Map::instance().map()->getGlobalBounds().width - WindowWidth / 2.f &&
		!Map::instance().player()->isAttacking())
	{
		m_view.setCenter(playerCenter.x, m_view.getCenter().y);
		m_window.setView(m_view);
		Map::instance().background()->setPosition(playerCenter.x, Map::instance().background()->getPosition().y);
	}
	if (playerCenter.y < Map::instance().map()->getGlobalBounds().height - WindowHeight / 2.f &&
		!Map::instance().player()->isJumping())
	{
		m_view.setCenter(m_view.getCenter().x, playerCenter.y);
		m_window.setView(m_view);
		Map::instance().background()->setPosition(Map::instance().background()->getPosition().x, playerCenter.y);
	}

	// fix view if position doesn't fall within the categories above
	if (playerCenter.x < WindowWidth / 2.f)
	{
		m_view.setCenter(WindowWidth / 2.f, m_view.getCenter().y);
		m_window.setView(m_view);
		Map::instance().background()->setPosition(WindowWidth / 2.f, Map::instance().background()->getPosition().y);
	}
	if (playerCenter.x > Map::instance().map()->getGlobalBounds().width - WindowWidth / 2.f)
	{
		m_view.setCenter((Map::instance().map()->getGlobalBounds().width - WindowWidth / 2.f), m_view.getCenter().y);
		m_window.setView(m_view);
		Map::instance().background()->setPosition((Map::instance().map()->getGlobalBounds().width - WindowWidth / 2.f), Map::instance().background()->getPosition().y);
		
	}
	if (playerCenter.y > Map::instance().map()->getGlobalBounds().height - WindowWidth / 4.f)
	{
		m_view.setCenter(m_view.getCenter().x, Map::instance().map()->getGlobalBounds().height - WindowHeight / 2.f);
		m_window.setView(m_view);
		Map::instance().background()->setPosition(Map::instance().background()->getPosition().x, Map::instance().map()->getGlobalBounds().height - WindowHeight / 2.f);
	}
}
//----------------------------------------------------
Controller::~Controller()
{
}