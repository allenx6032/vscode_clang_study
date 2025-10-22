#ifndef NPC_H
#define NPC_H

#include <string>



class NPC
{
public:
	NPC(int hp, std::string name, std::string luaEnvKey) : m_hp(hp), m_name(name), m_luaEnvKey(luaEnvKey) {};

	void SetHP(int newHP)
	{
		m_hp = newHP;
	}
	int GetHP() const
	{
		return m_hp;
	}

	void SetName(std::string name)
	{
		m_name = name;
	}
	std::string GetName() const
	{
		return m_name;
	}

	void SetLUAEnvKey(std::string key)
	{
		m_luaEnvKey = key;
	}
	std::string GetLUAEnvKey() const
	{
		return m_luaEnvKey;
	}

private:
	int m_hp;
	std::string m_name;
	std::string m_luaEnvKey;
};

#endif