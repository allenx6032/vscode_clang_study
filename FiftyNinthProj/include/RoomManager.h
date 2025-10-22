#pragma once

#include <string>
#include <vector>
#include <map>

#include "NPC.h"

struct Room
{
	unsigned int selfID;
	unsigned int scriptFilePath;
};

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void Init();

	void PrintText(std::string text);
	std::string GetInput(std::string text = "");
	void ChangeRoom(const std::string& filepath);
	void SelectRandomRoomFromCategory(std::string category);
	

private:
	std::string m_roomRoot = "Rooms/";
	std::string m_luaEnvKey = "Room";
	std::vector<std::string> m_roomCategories;
	std::map<std::string, std::vector<std::string>> m_roomsByCategory;
};

