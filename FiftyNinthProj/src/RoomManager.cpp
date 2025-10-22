#include "RoomManager.h"
#include "LuaWrapper/LuaWrapper.h"

#include <iostream>

RoomManager::RoomManager()
{

}


RoomManager::~RoomManager()
{
}

void RoomManager::Init()
{
	LuaWrapper::GetInstance().LoadScript(m_luaEnvKey, m_roomRoot + "RoomDirectory.lua");

	std::string entrance = LuaWrapper::GetInstance().GetGlobalValue<std::string>(m_luaEnvKey, "Entrance");

	m_roomCategories = LuaWrapper::GetInstance().TableToVector<std::string>(m_luaEnvKey, "Categories");

	for (int i = 0; i < m_roomCategories.size(); ++i)
		m_roomsByCategory[m_roomCategories[i]] = LuaWrapper::GetInstance().TableToVector<std::string>(m_luaEnvKey, m_roomCategories[i]);

	ChangeRoom(m_roomRoot + entrance);
}

void RoomManager::PrintText(std::string text) 
{
	std::cout << text;
}

std::string RoomManager::GetInput(std::string text) 
{
	std::string result;

	std::cout << text;
	std::getline(std::cin, result);

	return result;
}

void RoomManager::SelectRandomRoomFromCategory(std::string category)
{
	std::string result;

	auto it = m_roomsByCategory.find(category);
	if (it == m_roomsByCategory.end())
		PrintText("CATEGORY NOT FOUND");
	else
	{
		int index = std::rand() % it->second.size();
		result = it->second[index];
	}	
	ChangeRoom(m_roomRoot + result);
}

void RoomManager::ChangeRoom(const std::string& filepath)
{
	LuaWrapper::GetInstance().LoadScript(m_luaEnvKey, filepath);
	LuaWrapper::GetInstance().RegisterMemberFunction<RoomManager, void>(m_luaEnvKey, this, "Room", "room", &RoomManager::PrintText, "PrintText");
	LuaWrapper::GetInstance().RegisterMemberFunction(m_luaEnvKey, this, "Room", "room", &RoomManager::GetInput, "GetInput");
	LuaWrapper::GetInstance().RegisterMemberFunction<RoomManager, void>(m_luaEnvKey, this, "Room", "room", &RoomManager::SelectRandomRoomFromCategory, "ChangeRoom");
	LuaWrapper::GetInstance().RunFunction<void>(m_luaEnvKey, FuncNameInfo("main", "room"));

}