#pragma once

#ifndef _LOG_H
#define _LOG_H
#include <assert.h>

// �����Ǵ� Log.dll ������
class CLog
{
public:
	CLog(void);
	CLog(const char* szFileName);//�趨��־�ļ���
	virtual ~CLog(void);
protected:
	CRITICAL_SECTION _csLock;
	char* _szFileName;
	HANDLE _hFile;
	bool _fbOpenFile();//���ļ���ָ�뵽�ļ�β
	DWORD _fdwWrite(LPCVOID lpBuffer, DWORD dwLength);
	virtual void _fvWriteLog(LPCVOID lpBuffer, DWORD dwLength);//д��־, ������չ�޸�
	void _fvLock() { ::EnterCriticalSection(&_csLock); }
	void _fvUnlock() { ::LeaveCriticalSection(&_csLock); }
public:
	const char* _fszGetFileName();
	void _fvSetFileName(const char* szName);//�޸��ļ����� ͬʱ�ر���һ����־�ļ�
	bool _fbIsOpen();
	void _fvClose();
	void _fvLog(LPCVOID lpBuffer, DWORD dwLength);//׷����־����
	void _fvLog(const char* szText);
private:
	CLog(const CLog&);
};
#endif
