// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ������������϶���� BHLOG_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// BHLOG_API ������Ϊ�� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
//#ifdef BHLOG_EXPORTS
//#define BHLOG_API __declspec(dllexport)
//#else
//#define BHLOG_API __declspec(dllimport)
//#endif
#define BHLOG_API __declspec(dllexport)

#ifndef _BH_LOG_H
#define _BH_LOG_H

/**
 * ������־���ļ�
 * ��־���뵽��ģ��Ŀ¼��nepenthelog.log�ļ���
 * szText ��־����
 */
extern "C" BHLOG_API void __stdcall insertLog(const char* szText);
/**
 * ������־���ļ�
 * ��־���뵽��ģ��Ŀ¼��ָ���ļ������ļ���
 */
extern "C" BHLOG_API void __stdcall insertLogFile(const char* szFileName, const char* szText);
/**
 * ������־���ļ�
 * ��־���뵽��ģ��Ŀ¼��ָ���ļ������ļ���
 */
extern "C" BHLOG_API void __stdcall insertLogPath(const char* szPath, const char* szFileName, const char* szText);

#endif //_NEPENTHE_LOG_H

