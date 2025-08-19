#include "MonsterInfo.h"
#include "Resources.h"

MonsterInfo::MonsterInfo(const Data& data)
{
	init(name, 13);
	init(nameBackground, sf::Color(0.f, 0.f, 0.f, 199.f), sf::Vector2f(40.f, 9.f));

	init(level, 11);
	init(levelBackground, sf::Color(0.f, 0.f, 0.f, 199.f), sf::Vector2f(40.f, 7.f));

	init(HPbar,         sf::Color(67, 233, 22), sf::Vector2f(48.f, 5.f));
	init(HPbackground1, sf::Color::White, sf::Vector2f(50.f, 7.f));
	init(HPbackground2, sf::Color::Black, sf::Vector2f(48.f, 5.f));	
}

void MonsterInfo::update(const Data& data, const sf::Vector2f& location, const sf::FloatRect& boundingRectangle)
{
	const float bottom = location.y + boundingRectangle.height;

	HPbar.setSize(sf::Vector2f(48.f * (data.HP / static_cast<float>(data.MaxHP)), 5.f));
	HPbar.setPosition(location - sf::Vector2f(22.f, 50.f));
	HPbackground1.setPosition(location - sf::Vector2f(23.f, 51.f));
	HPbackground2.setPosition(location - sf::Vector2f(22.f, 50.f));
	name.setPosition(boundingRectangle.left + boundingRectangle.width / 4.f, bottom + 1.f);
	nameBackground.setPosition(boundingRectangle.left + boundingRectangle.width / 4.f, bottom);
	level.setPosition(sf::Vector2f(nameBackground.getGlobalBounds().left - level.getString().getSize() * 5.8f, bottom + 2.f));
	levelBackground.setPosition(sf::Vector2f(nameBackground.getGlobalBounds().left - level.getString().getSize() * 5.8f, bottom + 2.f));
}

void MonsterInfo::draw(sf::RenderWindow& window)
{
	window.draw(nameBackground);
	window.draw(name);
	
	window.draw(levelBackground);
	window.draw(level);

	window.draw(HPbackground1);
	window.draw(HPbackground2);
	window.draw(HPbar);
}

void MonsterInfo::setName(const std::string& newName)
{
	name.setString(newName);
	nameBackground.setSize(sf::Vector2f(name.getGlobalBounds().width * 1.04f, 16.f));
}

void MonsterInfo::setLevel(const int& newLevel)
{
	if (newLevel == 0)
	{
		level.setString("");
		levelBackground.setSize(sf::Vector2f(0.f, 0.f));
	}
	else
	{
		level.setString("Lv, " + std::to_string(newLevel));
		levelBackground.setSize(sf::Vector2f(level.getGlobalBounds().width * 1.12f, 13.f));
	}
}

void MonsterInfo::init(sf::Text& text, const int& size)
{
	text.setFont(Resources::instance().font());
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(size);
}

void MonsterInfo::init(sf::RectangleShape& bar, const sf::Color& color, 
	            const sf::Vector2f& size)
{
	bar.setFillColor(color);
	bar.setSize(size);
}