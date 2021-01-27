#pragma once

#ifndef _LOG_H
#define _LOG_H
#include <assert.h>

// 此类是从 Log.dll 导出的
class CLog
{
public:
	CLog(void);
	CLog(const char* szFileName);//设定日志文件名
	virtual ~CLog(void);
protected:
	CRITICAL_SECTION _csLock;
	char* _szFileName;
	HANDLE _hFile;
	bool _fbOpenFile();//打开文件，指针到文件尾
	DWORD _fdwWrite(LPCVOID lpBuffer, DWORD dwLength);
	virtual void _fvWriteLog(LPCVOID lpBuffer, DWORD dwLength);//写日志, 可以扩展修改
	void _fvLock() { ::EnterCriticalSection(&_csLock); }
	void _fvUnlock() { ::LeaveCriticalSection(&_csLock); }
public:
	const char* _fszGetFileName();
	void _fvSetFileName(const char* szName);//修改文件名， 同时关闭上一个日志文件
	bool _fbIsOpen();
	void _fvClose();
	void _fvLog(LPCVOID lpBuffer, DWORD dwLength);//追加日志内容
	void _fvLog(const char* szText);
private:
	CLog(const CLog&);
};
#endif
