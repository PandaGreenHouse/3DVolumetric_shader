#pragma once

#include "MyStructure.h"
#include <windows.h>


#ifndef __WRL_READER_DLL_HEDAER__
#define __WRL_READER_DLL_HEDAER__


#ifdef WRL_EXPORTS
	#define	WRL_DLL_EX_IMPORT	_declspec(dllexport)
#else
	#define	WRL_DLL_EX_IMPORT	_declspec(dllimport)
#endif

#define		WRL_E_SUCCESS				( 0)
#define		WRL_E_INVALID_PARAMETER		(-1)
#define		WRL_E_INSUFFICIENT_MEMORY	(-2)
#define		WRL_E_FILE_NOT_FOUND		(-3)
#define		WRL_E_FORMAT_NOT_SUPPORTED	(-4)
#define		WRL_E_PARSE_FAILED			(-5)
#define		WRL_E_GETFACES_FAILED		(-6)



WRL_DLL_EX_IMPORT int  WrlOpenFileA(LPSTR	lpszFilePath, PCOM_MESH pComMesh);
WRL_DLL_EX_IMPORT int  WrlOpenFileW(LPCWSTR	lpszFilePath, PCOM_MESH pComMesh);

WRL_DLL_EX_IMPORT void WrlCloseFile(PCOM_MESH pComMesh);

WRL_DLL_EX_IMPORT int  WrlGetErrorTextA(LPSTR	lpszError, int nMaxLen);
WRL_DLL_EX_IMPORT int  WrlGetErrorTextW(LPWSTR	lpszError, int nMaxLen);


#ifdef _UNICODE
	#define	WrlOpenFile		WrlOpenFileW
	#define	WrlGetErrorText	WrlGetErrorTextW
#else
	#define	WrlOpenFile		WrlOpenFileA
	#define	WrlGetErrorText	WrlGetErrorTextA
#endif


#endif	//__WRL_READER_DLL_HEDAER__