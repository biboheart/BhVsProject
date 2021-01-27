// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都用命令行上定义的 BHLOG_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BHLOG_API 函数视为从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
//#ifdef BHLOG_EXPORTS
//#define BHLOG_API __declspec(dllexport)
//#else
//#define BHLOG_API __declspec(dllimport)
//#endif
#define BHLOG_API __declspec(dllexport)

#ifndef _BH_LOG_H
#define _BH_LOG_H

/**
 * 插入日志到文件
 * 日志插入到本模块目录的nepenthelog.log文件中
 * szText 日志内容
 */
extern "C" BHLOG_API void __stdcall insertLog(const char* szText);
/**
 * 插入日志到文件
 * 日志插入到本模块目录的指定文件名的文件中
 */
extern "C" BHLOG_API void __stdcall insertLogFile(const char* szFileName, const char* szText);
/**
 * 插入日志到文件
 * 日志插入到本模块目录的指定文件名的文件中
 */
extern "C" BHLOG_API void __stdcall insertLogPath(const char* szPath, const char* szFileName, const char* szText);

#endif //_NEPENTHE_LOG_H

