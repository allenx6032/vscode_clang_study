#include "LevelManager.h"
#include "MatchFunctions.h"

#include <iostream>

using std::cout;
using std::endl;

LevelManager::LevelManager(int boardHeight, int boardWidth, int boardTop)
{
	m_boardTop = boardTop;

	//Seed random generator
	std::srand(std::time(0));

	//Set board dimensions
	m_boardHeight = boardHeight;
	m_boardWidth = boardWidth;

	//Calculate number of columns and rows
	m_numberOfColumns = floor(boardWidth / BLOCK_WIDTH);
	m_numberOfRows = floor(boardHeight / BLOCK_HEIGHT);

	m_blockTexture.loadFromFile("data/blockSpritesheet.png");

	auto it = BlockColors::enumToSFColor.begin();
	int typeRandom;
	BlockColors::ColorName color;
	BlockTypes::Type type;

	//Fill board
	m_blocks.resize(m_numberOfRows);
	for (int i = 0; i < m_numberOfRows; i++)
	{
		m_blocks[i].reserve(m_numberOfColumns);
		for (int j = 0; j < m_numberOfColumns; ++j)
		{

			type = BlockTypes::Type::Regular;

			//Randomize color
			it = BlockColors::enumToSFColor.begin();
			std::advance(it, rand() % (BlockColors::enumToSFColor.size()-1));
			color = it->first;

			//Randomize type
			typeRandom = rand() % 100;
			if (typeRandom > 90 && typeRandom < 95)
			{
				color = BlockColors::ColorName::White;
				type = BlockTypes::Type::Bomb;
			}
			else if (typeRandom > 95)
			{
				color = BlockColors::ColorName::White;
				type = BlockTypes::Type::Zig_Zag;
			}

			m_blocks[i].push_back(std::shared_ptr<Block>(new Block(sf::Vector2f(j*BLOCK_WIDTH, (i*BLOCK_HEIGHT)+m_boardTop), sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT), color, type, &m_blockTexture)));
		}
	}
	m_openSlots.clear();
	m_openSlots.resize(m_blocks[0].size(), 0);

	//Register match functions for each block type
	m_matchFunctions[BlockTypes::Regular] = RegularMatch;
	m_matchFunctions[BlockTypes::Bomb] = BombMatch;
	m_matchFunctions[BlockTypes::Zig_Zag] = ZigZagMatch;
}

void LevelManager::Update(float dt)
{
	//Used to make sure animations are done before updating. Not optimal.
	bool test = false;

	for (int i = 0; i < m_numberOfRows; i++)
	{
		for (int j = 0; j < m_numberOfColumns; ++j)
		{
			test |= m_blocks[i][j]->Update(dt);
		}
	}

	//Update the board
	if (!test)
		UpdateBoard();
}


void LevelManager::Draw(sf::RenderWindow& rw)
{
	for (int i = 0; i < m_numberOfRows; i++)
	{
		for (int j = 0; j < m_numberOfColumns; ++j)
		{
			m_blocks[i][j]->Draw(rw);
		}
	}
}

void LevelManager::HandleClick(sf::Vector2i mouseCoordinates)
{
	//If not ready for another click, return
	if (!m_readyForClick)
		return;

	//If mouse is outside of blocks matrix we have nothing to do, so return
	if (mouseCoordinates.y - m_boardTop > m_numberOfRows*BLOCK_HEIGHT)
		return;

	//Contains mouse coordinates in terms of block matrix
	sf::Vector2i mouseIndex;

	//Convert x,y to i,j
	mouseIndex.x = (mouseCoordinates.x) / BLOCK_WIDTH;
	mouseIndex.y = (mouseCoordinates.y - m_boardTop) / BLOCK_HEIGHT;

	//Get the blocks to be broken from function corresponding to the clicked block
	auto blocksToClear = m_matchFunctions[m_blocks[mouseIndex.y][mouseIndex.x]->GetType()](m_blocks, mouseIndex);

	//If less than 3 blocks found, return
	if (blocksToClear.size() < 3)
		return;

	//Vector for holding chained blocks
	std::vector<sf::Vector2i> chained;

	m_readyForClick = false;
	//Clears blocks
	for (int i = 0; i < blocksToClear.size(); ++i)
	{
		if (m_blocks[blocksToClear[i].y][blocksToClear[i].x]->GetType() != BlockTypes::Regular)
		{
			chained = m_matchFunctions[m_blocks[blocksToClear[i].y][blocksToClear[i].x]->GetType()](m_blocks, blocksToClear[i]);
			if (chained.size()>0)
				blocksToClear.insert(blocksToClear.end(), chained.begin(), chained.end());
		}
		m_blocks[blocksToClear[i].y][blocksToClear[i].x]->Break();
		m_openSlots[blocksToClear[i].x]++;
	}

}

int LevelManager::GetScore()
{
	return m_score;
}

void LevelManager::UpdateBoard()
{
	int i;
	int counter = 0;

	//Count number of moves
	for (int i = 0; i < m_openSlots.size(); ++i)
	{
		if (m_openSlots[i] != 0)
			counter++;
	}

	//If no moves return
	if (counter == 0)
		return;

	counter = 0;

	//Traverse the board in a bototm-up fashion. When we encounter an empty block, we shift everything above it down, and randomize the top element.
	for (int j = m_numberOfColumns - 1; j >= 0; --j)
	{
		counter = m_openSlots[j];
		for (int i = m_numberOfRows - 1; i >=0 ; --i)
		{
			while (!m_blocks[i][j]->GetVisible())
			{
				ShiftColumnDown(i, j);
				m_blocks[0][j]->Reset();
				counter--;
				m_score++;
				if (counter <= 0)
					break;
			}
			if (counter <= 0)
				break;
		}
	}

	//Resets processed flag
	for (int i = 0; i < m_numberOfRows; i++)
	{
		m_blocks[i].reserve(m_numberOfColumns);
		for (int j = 0; j < m_numberOfColumns; ++j)
		{
			m_blocks[i][j]->SetProcessed(false);
		}
	}

	m_readyForClick = true;
}

void LevelManager::ShiftColumnDown(int rowIndex, int columnIndex)
{
	for (int i = rowIndex; i > 0; --i)
	{
		SwapBlocks(m_blocks[i][columnIndex], m_blocks[i-1][columnIndex]);
	}
}