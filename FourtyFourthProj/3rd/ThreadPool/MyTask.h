/** 
* @file MyTask.h
* @brief 任务实例
*/

#pragma once
#include "task.h"
#include "SimpleSocket.h"

/**
* @class CMyTask 
* @brief 项目ThreadPool的任务实例
*/
class CMyTask : public CTask
{
protected:
	static SOCKET m_Socket; // find a socket
	static char m_strIp[64];// find a ip

public:
	char m_curIp[64];		// IP

	int m_nPort;			// Port

	CSimpleSocket *m_pClient;// Socket

	CMyTask(const char *ip, int port, CSimpleSocket *pClient, int id);

	static SOCKET GetSocket() { return m_Socket; }

	static const char* GetIp() { return m_strIp; }

	static void SetSocket(SOCKET s) { m_Socket = s; }

	static bool isFind() { return INVALID_SOCKET != m_Socket; }

	static void Reset() { m_Socket = INVALID_SOCKET; }

protected:
	~CMyTask(void);
public:
	_inline virtual void Destroy();
	virtual void taskProc();
};


// 版本信息
// #define KEEPER_VERSION "KeepApplication-Ver1.0"

// 日期时间
// #define KEEPER_DATETIME 201804

// 获取注册信令包
// void GetRegisterPkg(char *reg, const char *from, const char *to);
