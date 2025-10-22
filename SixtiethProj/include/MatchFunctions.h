#ifndef MATCH_FUNCITONS_H
#define MATCH_FUNCTIONS_H
#define _USE_MATH_DEFINES
#include "Block.h"

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <cmath>
// #include <algorithm>
#ifndef M_PI
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401
#endif

//Uses flood fill to find all blocks to clear. Takes current index, color to look for and vector to store the indicies of bloacks that match the color
void FloodBlocks(sf::Vector2i nodeIndex, BlockColors::ColorName targetColor, std::vector<sf::Vector2i>& blocksToClear, std::vector<std::vector<std::shared_ptr<Block>>>& blocks)
{
	//Make sure indicies are not out of bounds
	if (nodeIndex.x < 0 || nodeIndex.x >= blocks[0].size() || nodeIndex.y < 0 || nodeIndex.y >= blocks.size())
		return;

	//Make sure block has not been processed
	if (blocks[nodeIndex.y][nodeIndex.x]->GetProcessed())
		return;

	blocks[nodeIndex.y][nodeIndex.x]->SetProcessed(true);

	//If block is different color, return
	if (blocks[nodeIndex.y][nodeIndex.x]->GetColorName() != targetColor)
		return;

	//Otherwise add to list
	blocksToClear.push_back(nodeIndex);

	//Recursively run in other directions
	FloodBlocks(sf::Vector2i(nodeIndex.x, nodeIndex.y + 1), targetColor, blocksToClear, blocks);
	FloodBlocks(sf::Vector2i(nodeIndex.x, nodeIndex.y - 1), targetColor, blocksToClear, blocks);
	FloodBlocks(sf::Vector2i(nodeIndex.x + 1, nodeIndex.y), targetColor, blocksToClear, blocks);
	FloodBlocks(sf::Vector2i(nodeIndex.x - 1, nodeIndex.y), targetColor, blocksToClear, blocks);
}

//Function for caluclating a regular match (color click)
std::vector<sf::Vector2i> RegularMatch(std::vector<std::vector<std::shared_ptr<Block>>>& blocks, sf::Vector2i mouseIndex)
{
	//Contains indicies of blocks that need to be cleared
	std::vector<sf::Vector2i> blocksToClear;

	//Finds all the blocks that need to be cleared
	FloodBlocks(mouseIndex, blocks[mouseIndex.y][mouseIndex.x]->GetColorName(), blocksToClear, blocks);


	return blocksToClear;
}

//Function for calculating a bomb match (bomb click)
std::vector<sf::Vector2i> BombMatch(std::vector<std::vector<std::shared_ptr<Block>>>& blocks, sf::Vector2i mouseIndex)
{
	//Range of bomb
	int range = 1;

	//Terimnator for loop
	int size = 2 * range + 1;

	//Contains indicies of blocks that need to be cleared
	std::vector<sf::Vector2i> blocksToClear;

	sf::Vector2i nodeIndex;

	//Add everything in range
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			nodeIndex.x = mouseIndex.x + (i - 1);
			nodeIndex.y = mouseIndex.y + (j - 1);

			//Make sure node isn't out of bounds or already processed
			if (nodeIndex.x >= 0 && nodeIndex.x < blocks[0].size() && nodeIndex.y >= 0 && nodeIndex.y < blocks.size() && !blocks[nodeIndex.y][nodeIndex.x]->GetProcessed())
			{
				blocks[nodeIndex.y][nodeIndex.x]->SetProcessed(true);
				blocksToClear.push_back(nodeIndex);
			}
				
		}
	}

	return blocksToClear;
}

//Function for calulating zig-zag match
std::vector<sf::Vector2i> ZigZagMatch(std::vector<std::vector<std::shared_ptr<Block>>>& blocks, sf::Vector2i mouseIndex)
{
	int temp;
	//Number of blocks to encounter before stoping
	int numberOfBlocks = 10;
	//Contains indicies of blocks that need to be cleared
	std::vector<sf::Vector2i> blocksToClear;

	//Direction "line" is traveling in
	int direction;
	direction = (std::rand() % 8) * 45;

	//Push zig-zag block into array if it hasnt been processed
	if (!blocks[mouseIndex.y][mouseIndex.x]->GetProcessed())
	{
		blocksToClear.push_back(mouseIndex);
		blocks[mouseIndex.y][mouseIndex.x]->SetProcessed(true);
	}
	
	sf::Vector2i nodeIndex;

	//Set starting point to zig-zag block
	nodeIndex = mouseIndex;
	
	//As long as there are blocks left, keep adding more
	while (numberOfBlocks != 0)
	{
		nodeIndex.x = nodeIndex.x + std::ceil(cos(direction* M_PI / 180)) * -1;
		nodeIndex.y = nodeIndex.y + std::ceil(sin(direction* M_PI / 180)) * 1;
		if (nodeIndex.x >= 0 && nodeIndex.x < blocks[0].size() && nodeIndex.y >= 0 && nodeIndex.y < blocks.size())
		{
			if (!blocks[nodeIndex.y][nodeIndex.x]->GetProcessed())
			{
				blocks[nodeIndex.y][nodeIndex.x]->SetProcessed(true);
				blocksToClear.push_back(nodeIndex);
			}
			numberOfBlocks--;

			//Randomly change direction
			if (std::rand() % 10 > 5)
			{
				temp = direction;
				while (temp == direction)
					direction = (std::rand() % 8) * 45;
			}

		}
		else
		{

			//If weve hit a boundry, backtrack and reverse direction
			nodeIndex.x = nodeIndex.x - (std::ceil(cos(direction* M_PI / 180)) * -1);
			nodeIndex.y = nodeIndex.y - (std::ceil(sin(direction* M_PI / 180)) * 1);
			direction = (direction + 135) % 360;
		}

	}

	return blocksToClear;
}

#endif