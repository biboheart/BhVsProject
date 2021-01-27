#include "pch.h"
#include "Log.h"

CLog::CLog()
{
	const char* szFileName = "Log.log";
	_szFileName = NULL;
	_hFile = INVALID_HANDLE_VALUE;
	::InitializeCriticalSection(&_csLock);
	_fvSetFileName(szFileName);
}

CLog::CLog(const char* szFileName)
{
	_szFileName = NULL;
	_hFile = INVALID_HANDLE_VALUE;
	::InitializeCriticalSection(&_csLock);
	_fvSetFileName(szFileName);
}

CLog::~CLog(void)
{
	::DeleteCriticalSection(&_csLock);
	_fvClose();
	if (_szFileName)
	{
		delete[]_szFileName;
	}
}

const char* CLog::_fszGetFileName()
{
	return _szFileName;
}

void CLog::_fvSetFileName(const char* szName)
{
	assert(szName);
	if (_szFileName)
	{
		delete[]_szFileName;
	}
	_fvClose();
	size_t len = strlen(szName) + 1;
	_szFileName = new char[len];
	assert(_szFileName);
	strcpy_s(_szFileName, len, szName);
}

bool CLog::_fbIsOpen()
{
	return _hFile != INVALID_HANDLE_VALUE;
}

void CLog::_fvClose()
{
	if (_fbIsOpen())
	{
		CloseHandle(_hFile);
		_hFile = INVALID_HANDLE_VALUE;
	}
}

void CLog::_fvLog(LPCVOID lpBuffer, DWORD dwLength)
{
	assert(lpBuffer);
	__try
	{
		_fvLock();

		if (_fbOpenFile()) {
			_fvWriteLog(lpBuffer, dwLength);
		}
	}
	__finally
	{
		_fvUnlock();
	}
}

void CLog::_fvLog(const char* szText)
{
	_fvLog(szText, strlen(szText));
}

bool CLog::_fbOpenFile()
{
	if (_fbIsOpen())
	{
		return true;
	}
	if (!_szFileName)
	{
		return false;
	}
	size_t size = strlen(_szFileName) + 1;
	size_t converted = 0;
	wchar_t* fileName;
	fileName = (wchar_t*)malloc(size * sizeof(wchar_t));
	mbstowcs_s(&converted, fileName, size, _szFileName, _TRUNCATE);
	if (NULL == fileName) {
		return false;
	}
	_hFile = CreateFile(
		fileName,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (!_fbIsOpen() && GetLastError() == 2)//打开不成功，且因为文件不存在， 创建文件
		_hFile = CreateFile(
			fileName,
			GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	if (_fbIsOpen())
	{
		SetFilePointer(_hFile, 0, NULL, FILE_END);
	}
	return _fbIsOpen();
}

DWORD CLog::_fdwWrite(LPCVOID lpBuffer, DWORD dwLength)
{
	DWORD dwWriteLength = 0;

	if (_fbIsOpen())
		WriteFile(_hFile, lpBuffer, dwLength, &dwWriteLength, NULL);

	return dwWriteLength;
}

void CLog::_fvWriteLog(LPCVOID lpBuffer, DWORD dwLength)
{
	time_t now;
	char temp[21];
	DWORD dwWriteLength;
	struct tm newtime;

	if (_fbIsOpen())
	{
		time(&now);
		localtime_s(&newtime, &now);
		strftime(temp, 20, "%Y-%m-%d %H:%M:%S", &newtime);
		WriteFile(_hFile, "#[", 2, &dwWriteLength, NULL);
		WriteFile(_hFile, temp, 19, &dwWriteLength, NULL);
		WriteFile(_hFile, "]", 2, &dwWriteLength, NULL);
		WriteFile(_hFile, lpBuffer, dwLength, &dwWriteLength, NULL);
		WriteFile(_hFile, "\r\n", 2, &dwWriteLength, NULL);
		FlushFileBuffers(_hFile);
	}
}
