#include "Block.h"

#include <iostream>

using std::cout;
using std::endl;

void Block::PrintInfo()
{
	cout << "Broken " << m_broken << ", Texture rect left " << m_textureRect.left << ", texture rect top " << m_textureRect.top << ", Color " << m_colorName << endl;
}

Block::Block(sf::Vector2f position, sf::Vector2f dimensions, BlockColors::ColorName colorName, BlockTypes::Type type, sf::Texture* texture)
{
	m_colorName = colorName;
	m_type = type;

	if (m_type == BlockTypes::Bomb)
		m_textureRect.top = 32;
	else if (m_type == BlockTypes::Zig_Zag)
		m_textureRect.top = 64;
	else
		m_textureRect.top = 0;


	m_textureRect.left = 0;
	m_textureRect.height = 32;
	m_textureRect.width = 32;

	m_shape.setFillColor(BlockColors::enumToSFColor[m_colorName]);
	m_shape.setSize(dimensions);
	m_shape.setPosition(position);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(0);
	m_shape.setTexture(texture);
	m_shape.setTextureRect(m_textureRect);

	m_visible = true;
}

void Block::Reset()
{
	auto it = BlockColors::enumToSFColor.begin();
	std::advance(it, rand() % (BlockColors::enumToSFColor.size()-1));
	m_colorName = it->first;

	m_type = BlockTypes::Type::Regular;
	m_textureRect.top = 0;

	//Randomize type
	int typeRandom = rand() % 100;
	if (typeRandom > 90 && typeRandom < 95)
	{
		m_colorName = BlockColors::ColorName::White;
		m_type = BlockTypes::Type::Bomb;
		m_textureRect.top = 32;
	}
	else if (typeRandom > 95)
	{
		m_colorName = BlockColors::ColorName::White;
		m_type = BlockTypes::Type::Zig_Zag;
		m_textureRect.top = 64;
	}

	m_textureRect.left = 0;
	m_textureRect.height = 32;
	m_textureRect.width = 32;
	m_counter = 0;

	m_shape.setFillColor(BlockColors::enumToSFColor[m_colorName]);
	m_shape.setTextureRect(m_textureRect);

	m_visible = true;
	m_processed = false;
	m_broken = false;
}

bool Block::Update(float dt)
{
	bool result = false;
	
	//If block isn't broken, nothing to update
	if (!m_broken)
		return result;

	//If it is, increase counter
	m_counter++;
	result = true;
	//If enough frames have passed, progress animaiton
	if (m_counter == FRAME_DELAY)
	{
		//Animation steps are fixed, can be changed later.
		m_textureRect.left += 32;

		if (m_textureRect.left >= 128)
		{
			m_visible = false;
			m_textureRect.left = 0;
			m_broken = false;
			result = false;
		}
		else
		{
			result = true;
		}
		m_counter = 0;
		m_shape.setTextureRect(m_textureRect);
		
	}
	return result;
}

void Block::Draw(sf::RenderWindow& rw)
{
	if (m_visible)
		rw.draw(m_shape);
}

void Block::Break()
{
	m_broken = true;
}

BlockColors::ColorName Block::GetColorName() const
{
	return m_colorName;
}
void Block::SetColorName(BlockColors::ColorName colorName)
{
	m_colorName = colorName;
	m_shape.setFillColor(BlockColors::enumToSFColor[colorName]);
}

sf::Vector2f Block::GetPoisiton() const
{
	return m_shape.getPosition();
}
void Block::SetPosition(sf::Vector2f newPosition)
{
	m_shape.setPosition(newPosition);
}

void Block::SetVisible(bool visible)
{
	m_visible = visible;
}
bool Block::GetVisible() const
{
	return m_visible;
}

bool Block::GetProcessed() const
{
	return m_processed;
}
void Block::SetProcessed(bool value)
{
	m_processed = value;
}

bool Block::GetBroken() const
{
	return m_broken;
}
void Block::SetBroken(bool value)
{
	m_broken = value;
}

BlockTypes::Type Block::GetType() const
{
	return m_type;

}
void Block::SetType(BlockTypes::Type type)
{
	m_type = type;
}

sf::IntRect Block::GetTextureRect() const
{
	return m_textureRect;
}
void Block::SetTextureRect(sf::IntRect rect)
{
	m_textureRect = rect;
	m_shape.setTextureRect(rect);
}