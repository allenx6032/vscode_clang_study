#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <vector>
#include <memory>

#include "Block.h"

class LevelManager
{
private:
	typedef std::vector<sf::Vector2i>(*MatchFunction)(std::vector<std::vector<std::shared_ptr<Block>>>&, sf::Vector2i);

public:
	LevelManager(int boardHeight, int boardWidth, int boardTop);

	void Update(float dt);

	void HandleClick(sf::Vector2i mouseCoordinates);
	void Draw(sf::RenderWindow& rw);
	
	int GetScore();

private:
	//Determines if another click can be accepted
	bool m_readyForClick = true;

	//Contains spritesheet for blocks
	sf::Texture m_blockTexture;
	//Dimensions of blocks
	const int BLOCK_WIDTH = 32;
	const int BLOCK_HEIGHT = 32;
	//Top of the board
	int m_boardTop;
	//Dimensions of board
	int m_boardWidth;
	int m_boardHeight;
	//Number of rows and columns of blocks
	int m_numberOfColumns;
	int m_numberOfRows;

	//Current score
	int m_score = 0;

	std::vector<int> m_openSlots;
	
	//Matrix of blocks
	std::vector<std::vector<std::shared_ptr<Block>>> m_blocks;
	//Stores funcitons for each blocktype
	std::map<BlockTypes::Type, MatchFunction> m_matchFunctions;

	//Upddate the board: move blocks and add new ones. Arguement is a vector that contains how many open slots there are per column
	void UpdateBoard();
	//Shifts column down starting from rowIndex.
	void ShiftColumnDown(int rowIndex,int columnIndex);
	//Calls appropriate handler function
	void PerformMove();

	//Helper function for swapping blocks
	void SwapBlocks(std::shared_ptr<Block> block1, std::shared_ptr<Block> block2)
	{
		auto temp = block1;
		block1 = block2;
		block2 = temp;
		bool b1Visiblity = block1->GetVisible();
		bool b1Broken = block1->GetBroken();
		BlockColors::ColorName b1Color = block1->GetColorName();
		BlockTypes::Type b1Type = block1->GetType();
		sf::IntRect b1TexRect = block1->GetTextureRect();

		block1->SetVisible(block2->GetVisible());
		block1->SetColorName(block2->GetColorName());
		block1->SetBroken(false);
		block1->SetType(block2->GetType());
		block1->SetTextureRect(block2->GetTextureRect());

		block2->SetVisible(b1Visiblity);
		block2->SetBroken(false);
		block2->SetColorName(b1Color);
		block2->SetType(b1Type);
		block2->SetTextureRect(b1TexRect);
	}
};

#endif

