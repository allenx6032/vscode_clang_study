#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <random>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

//Namespace for sblock types
namespace BlockTypes
{
	enum Type
	{
		Regular = 0,
		Bomb = 1,
		Zig_Zag = 2,
	};
}

//Namespace for possible colors
namespace BlockColors
{
	//Enum of available colors
	enum ColorName
	{
		Red = 0,
		Green = 1,
		//Magenta = 2,
		White = 3,
	};

	//Map for finding color by ColorName
	static std::map<ColorName, sf::Color> enumToSFColor =
	{
		{ ColorName::Red, sf::Color::Red },
		{ ColorName::Green, sf::Color::Green },
		//{ ColorName::Magenta, sf::Color::Magenta},
		{ ColorName::White, sf::Color::White},
	};
}

class Block
{
public:
	//Block requires name of its color and dimensions
	Block(sf::Vector2f position, sf::Vector2f dimensions, BlockColors::ColorName colorName, BlockTypes::Type type,sf::Texture* texture = 0);

	//Resets block with new color
	void Reset();
	//Update the block
	bool Update(float dt);
	//Draw this block
	void Draw(sf::RenderWindow& rw);

	//"Breaks" the block
	void Break();

	//Returns blocks color
	BlockColors::ColorName GetColorName() const;
	//Sets blocks color
	void SetColorName(BlockColors::ColorName colorName);

	//Get current position of block
	sf::Vector2f GetPoisiton() const;
	//Set poistion of block
	void SetPosition(sf::Vector2f newPosition);

	//Toggle block visibility
	void SetVisible(bool visible);
	//Returns visibility
	bool GetVisible() const;

	//Returns value of processed
	bool GetProcessed() const;
	//Sets value of processed
	void SetProcessed(bool value);

	//Returns value of broken
	bool GetBroken() const;
	//Sets value of broken
	void SetBroken(bool value);

	//Returns type of block
	BlockTypes::Type GetType() const;
	//Set block type
	void SetType(BlockTypes::Type type);

	//Get Texture rect
	sf::IntRect GetTextureRect() const;
	//Set Texutre rect
	void SetTextureRect(sf::IntRect rect);

	//For testing
	void PrintInfo();

private:

	//Constants for animaiton
	//Number of frames in animation
	static const int NUMBER_OF_FRAMES = 3;
	//Number of updates between frames changes
	static const int FRAME_DELAY = 10;
	//Counter for number of update calls
	int m_counter = 0;

	//Name of this blocks color
	BlockColors::ColorName m_colorName;
	//Block type
	BlockTypes::Type m_type;

	//Rectangle specifying area of spritesheet to draw
	sf::IntRect m_textureRect;

	//Shape for rendering
	sf::RectangleShape m_shape;

	//Flag for broken/unbroken
	bool m_broken = false;
	//Flag for visibility
	bool m_visible;
	//Flag for checking if block has been processed, must be reset after each move is calculated
	bool m_processed = false;
};

#endif

