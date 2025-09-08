#include "MyTask.h"
#include <assert.h>
#include <time.h>

#ifdef _DEBUG
#define OUTPUT TRACE
#else
#define OUTPUT
#endif

SOCKET CMyTask::m_Socket = INVALID_SOCKET;

char CMyTask::m_strIp[] = { 0 };

/**
* @brief 构造一个任务
* @param[in] id 任务编号
*/
CMyTask::CMyTask(const char *ip, int port, CSimpleSocket *pClient, int id):CTask(id)
{
	strcpy_s(m_curIp, ip);
	m_nPort = port;
	m_pClient = pClient;
}

/// 默认析构函数
CMyTask::~CMyTask(void)
{
}

/// delete this
void CMyTask::Destroy()
{
	delete this;
}

/// 获取本机IP
const char* getLocalHost()
{
	static char localhost[64] = { "127.0.0.1" };
	char hostname[128] = { 0 };
	if (0 == gethostname(hostname, 128))
	{
		hostent *host = gethostbyname(hostname);
		// 将ip转换为字符串
		char *hostip = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
		memcpy(localhost, hostip, strlen(hostip));
	}
	return localhost;
}

/// CMyTask重载的任务执行函数
void CMyTask::taskProc()
{
	if (INVALID_SOCKET == CMyTask::GetSocket())
	{
		clock_t t = clock();
		if (0 == m_pClient->connectServer(m_curIp, m_nPort))
		{
			char buffer[512] = { 0 };
			static const char *localhost = getLocalHost();
			// GetRegisterPkg(buffer, localhost, m_curIp);
			m_pClient->sendData(buffer, strlen(buffer));
			memset(buffer, 0, 64);
			if (m_pClient->recvData(buffer, 63) >= 0 && 0 == strcmp("register:success", buffer))
			{
				strcpy_s(CMyTask::m_strIp, m_curIp);
				CMyTask::SetSocket(m_pClient->getSocket());
			}
		}
		SOCKET s = m_pClient->GetSocket();
		m_pClient->Close();
		OUTPUT("======> Socket [%d] Connect %s:%d use time = %d\n", s, m_curIp, m_nPort, clock() - t);
	}
}


// extern CKeeperDlg *g_KeeperDlg;

/**
Keeper向管理终端进行注册
<?xml version="1.0" encoding="GB2312" standalone="yes"?>
<request command="register">
  <parameters>
    <szAppName>%s</szAppName>
    <szAppId>%s</szAppId>
    <szPassword>%s</szPassword>
  </parameters>
</request>
*/
// void GetRegisterPkg(char *reg, const char *from, const char *to)
// {
// 	char xml[512];
// 	sprintf_s(xml, 
// 		"<?xml version=\"1.0\" encoding=\"GB2312\" standalone=\"yes\"?>\r\n"
// 		"<request command=\"%s\">\r\n"
// 		"  <parameters>\r\n"
// 		"    <szAppName>%s</szAppName>\r\n"
// 		"    <szAppId>%s</szAppId>\r\n"
// 		"    <szPassword>%s</szPassword>\r\n"
// 		"  </parameters>\r\n"
// 		"</request>\r\n\r\n", REGISTER, g_KeeperDlg ? g_KeeperDlg->GetAppName() : "APP", 
// 		g_KeeperDlg ? g_KeeperDlg->GetAppId() : "admin", 
// 		g_KeeperDlg ? g_KeeperDlg->GetAppPwd() : "admin");
// 	sprintf(reg, SIP_RequestHeader_i(from, to, KEEPER_VERSION, KEEPER_DATETIME, (int)strlen(xml)));
// 	strcat(reg, xml);
// }
