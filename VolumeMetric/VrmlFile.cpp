#include "StdAfx.h"
#include "VrmlFile.h"
#include "wrl.h"



BOOL CVrmlFile::IsModelFile(LPCTSTR lpszFilePath)
{
	char	szText[20];
	BOOL	bIsType = FALSE;
	DWORD	dwRead = 0;
	HANDLE	hFile;

	if (lpszFilePath == NULL || lpszFilePath[0] == 0)
		return FALSE;

	hFile = ::CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
								OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	//Read File and Header Check
	dwRead = 0;
	if (ReadFile(hFile, szText, 20, &dwRead, NULL) && (dwRead > 5))
	{
		if (strncmp(szText, "#VRML", 5) == 0 || wcsncmp((wchar_t*) szText, L"#VRML", 5) == 0)
			bIsType = TRUE;
	}

	//Close File
	::CloseHandle(hFile);
	return bIsType;
}

CVrmlFile::CVrmlFile(void)
{
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}


CVrmlFile::~CVrmlFile(void)
{
	Close();
}

BOOL CVrmlFile::Open(LPCTSTR lpszFilePath, COM_MESH* pComMesh)
{
	if (lpszFilePath == NULL || lpszFilePath[0] == 0 || pComMesh == NULL)
		return FALSE;

	int		nCode = 0;
	TCHAR	szError[1024] = _T("");

	nCode = WrlOpenFile(lpszFilePath, &m_StrComMesh);
	if (nCode == WRL_E_SUCCESS)
	{
		InitMesh(&m_StrComMesh);
		memcpy(pComMesh, &m_StrComMesh, sizeof(COM_MESH));
	}

	return (nCode == WRL_E_SUCCESS);
}

void CVrmlFile::Close()
{
	WrlCloseFile(&m_StrComMesh);
	memset(&m_StrComMesh, 0, sizeof(COM_MESH));
}

PCOM_MESH CVrmlFile::GetMesh()
{
	return (&m_StrComMesh);
}

BOOL CVrmlFile::ConstructingComMesh()
{
	return TRUE;
}