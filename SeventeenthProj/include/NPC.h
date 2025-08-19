#pragma once

#include "animatedObject.h"

class NPC : public animatedObject
{
public:
	using staticObject::handleCollision;

	// Constructor
	NPC(const sf::Vector2f& position, const Resources::Objects& object, const std::string& name);

	// Functions
	virtual void update(const sf::Time delta) override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual Resources::Objects dialogue() const;
	virtual sf::Text name() const;
	virtual std::shared_ptr<sf::Sprite> sprite() const;
	virtual bool wasClicked(sf::RenderWindow& window);

	// Collision Handlers
	void handleCollision(gameObject& gameObject) {};
	virtual void handleCollision(Player& movingObject) {};
	virtual void handleCollision(Monster& monster) {};

	virtual ~NPC() = default;

private:
	Resources::Objects m_dialogue;
	sf::Font infoFont;
	sf::Text m_name;
	sf::RectangleShape m_nameBackground;
};