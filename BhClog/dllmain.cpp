// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "Log.h"
#include "BhLog.h"

CLog* _pLogFile = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:    //DLL进程加载的时候执行事件
        if (NULL != _pLogFile) {
            delete _pLogFile;
            _pLogFile = NULL;
        }
        break;
    case DLL_THREAD_ATTACH:     //DLL进程卸载的时候执行事件
        if (NULL != _pLogFile) {
            delete _pLogFile;
            _pLogFile = NULL;
        }
        break;
    case DLL_THREAD_DETACH:     //DLL线程加载的时候执行事件
        break;
    case DLL_PROCESS_DETACH:    //DLL线程卸载的时候执行事件
        break;
    }
    return TRUE;
}

// 这是导出函数
BHLOG_API void __stdcall insertLog(const char* szText)
{
	if (_pLogFile == NULL)
	{
		_pLogFile = new CLog();
	}
	_pLogFile->_fvLog(szText);
	if (_pLogFile != NULL)
	{
		delete _pLogFile;
		_pLogFile = NULL;
	}
}

BHLOG_API void __stdcall insertLogFile(const char* szFileName, const char* szText)
{
	if (_pLogFile == NULL)
	{
		_pLogFile = new CLog(szFileName);
	}
	_pLogFile->_fvLog(szText);
	if (_pLogFile != NULL)
	{
		delete _pLogFile;
		_pLogFile = NULL;
	}
}

BHLOG_API void __stdcall insertLogPath(const char* szPath, const char* szFileName, const char* szText)
{
	if (_pLogFile == NULL)
	{
		char szFilepath[MAX_PATH * 2];
		memset(szFilepath, 0, MAX_PATH * 2);
		strcat_s(szFilepath, MAX_PATH * 2, szFileName);
		_pLogFile = new CLog(szFilepath);
	}
	_pLogFile->_fvLog(szText);
	if (_pLogFile != NULL)
	{
		delete _pLogFile;
		_pLogFile = NULL;
	}
}

