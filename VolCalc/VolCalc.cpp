// VolCalc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ModelFile.h"
#include "MeshMetric.h"
#include "MeshModel.h"
#include "math.h"
#include "gl.h"
//#include "ImageRender.h"



typedef struct tagCALC_OPTIONS
{
	LPTSTR	lpszInModelPath;
	LPTSTR	lpszOutImagePath;	//-o option : Image File Name
	VECTOR3	vRotateAngle;	//-r option : Rotate Angle
	float	fScale;			//-s option : Render Scale
	float	fAmbient;		//-a option : Ambient Value
	float	fDiffuse;		//-d option : Diffuse Value
	DWORD	dwBackColor;	//-b option : Image Background Color
	int		nImgWidth;		//Image Width  in Pixels
	int		nImgHeight;		//Image Height in Pixels
}CALC_OPTIONS, *PCALC_OPTIONS;

#define		DEF_SCALE			1.0f
#define		DEF_AMBIENT			0.2f
#define		DEF_DIFFUSE			0.5f
#define		DEF_BACK_COLOR		0x00A6CD	//0.0, 0.65, 0.8
#define		DEF_IMG_WIDTH		800
#define		DEF_IMG_HEIGHT		600
#define		MYWND_CLASS_NAME	_T("MyGLDraw")



CModelFile*		g_pClsModelFile;
CMeshMetric		g_clsVolumeCalc;
COM_MESH		g_StrMeshData;
CALC_OPTIONS	g_stuOptions;


PBYTE		g_pPixelData = NULL;
TCHAR		g_szImagePath[1024];
HDC			g_hdcWnd = NULL, g_hdcMem = NULL;
HBITMAP		g_hbmpMem = NULL, g_hbmpOld1 = NULL, g_hbmpOld2 = NULL;
HINSTANCE	g_hInstance;
CMeshModel	g_cDraw;


void print_usage()
{
	_tprintf(_T("Calculates volume and Creates an image of a 3D object model.\n"));
	_tprintf(_T("The supported formats: STL, 3DS, OBJ, WRL.\n"));
	_tprintf(_T("Usage: VolCalc [options] filename\n"));
	_tprintf(_T("   -o filename  Path to Rendering Image File.\n"));
	_tprintf(_T("          If not specified, Image is save at the same folder of 3D Model File.\n"));
	_tprintf(_T("   -b <color>  Background Color of Rendering Image. Color Format is #RRGGBB, for example, #00A6CD\n"));
	_tprintf(_T("   -r x y z     Rotation Angle of the model for rendering.\n"));
	_tprintf(_T("          x, y and z values must be between 0 and 360 in degrees.\n"));
	_tprintf(_T("   -s <value>   Scale of the Model to Save Rendering image. Default is %.2f\n"),	DEF_SCALE);
	_tprintf(_T("   -a <value>   Ambient Value of the Model for rendering. Default is %.2f\n"), DEF_AMBIENT);
	_tprintf(_T("   -d <value>   Diffuse Value of the Model for rendering. Default is %.2f\n"), DEF_DIFFUSE);
}

int ParseParams(int argc, _TCHAR* argv[])
{
	int	nCount, k;

	if (argc < 2)
		return 0;

	//Set Default Values
	g_stuOptions.lpszInModelPath	= NULL;
	g_stuOptions.lpszOutImagePath	= NULL;
	g_stuOptions.vRotateAngle.x	= 0;
	g_stuOptions.vRotateAngle.y	= 0;
	g_stuOptions.vRotateAngle.z	= 0;
	g_stuOptions.dwBackColor= DEF_BACK_COLOR;
	g_stuOptions.fScale		= DEF_SCALE;
	g_stuOptions.fAmbient	= DEF_AMBIENT;
	g_stuOptions.fDiffuse	= DEF_DIFFUSE;
	g_stuOptions.nImgWidth	= DEF_IMG_WIDTH;
	g_stuOptions.nImgHeight	= DEF_IMG_HEIGHT;
	//Parse Command-line Arguments
	nCount = 0;
	for (k = 1; k < (argc - 1);)
	{
		if ((_tcscmp(argv[k], _T("-o")) == 0) || (_tcscmp(argv[k], _T("-O")) == 0))
		{
			g_stuOptions.lpszOutImagePath = argv[k+1];
			k += 2;
			nCount++;
		} else if ((_tcscmp(argv[k], _T("-b")) == 0) || (_tcscmp(argv[k], _T("-B")) == 0))
		{
			_stscanf(argv[k + 1], _T("#%x"), &(g_stuOptions.dwBackColor));
			k += 2;
			nCount++;
		} else if ((_tcscmp(argv[k], _T("-r")) == 0) || (_tcscmp(argv[k], _T("-R")) == 0))
		{
			_stscanf(argv[k + 1], _T("%f"), &(g_stuOptions.vRotateAngle.x));
			_stscanf(argv[k + 2], _T("%f"), &(g_stuOptions.vRotateAngle.y));
			_stscanf(argv[k + 3], _T("%f"), &(g_stuOptions.vRotateAngle.z));
			k += 4;
			nCount++;
		} else if ((_tcscmp(argv[k], _T("-s")) == 0) || (_tcscmp(argv[k], _T("-S")) == 0))
		{
			_stscanf(argv[k + 1], _T("%f"), &(g_stuOptions.fScale));
			k += 2;
			nCount++;
		} else if ((_tcscmp(argv[k], _T("-a")) == 0) || (_tcscmp(argv[k], _T("-A")) == 0))
		{
			_stscanf(argv[k + 1], _T("%f"), &(g_stuOptions.fAmbient));
			k += 2;
			nCount++;
		} else if ((_tcscmp(argv[k], _T("-d")) == 0) || (_tcscmp(argv[k], _T("-D")) == 0))
		{
			_stscanf(argv[k + 1], _T("%f"), &(g_stuOptions.fDiffuse));
			k += 2;
			nCount++;
		} else
			k++;
	}
	if (k < argc)
	{
		k = argc - 1;
		g_stuOptions.lpszInModelPath = argv[k];
		nCount++;
	}

	return nCount;
}

BOOL SaveBitmapByPixelData(TCHAR* lpszPath, PBYTE pData, int nBitCount, int nWidth, int nHeight)
{
	BYTE		pInfoHdr[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)] = {0,};
	LPBITMAPINFOHEADER	pbih = NULL;
	BITMAPFILEHEADER	bfh = {0,};
	LPRGBQUAD	pColor = NULL;
	HANDLE		hFile = INVALID_HANDLE_VALUE;
	DWORD		dwRead, dwInfoSize, dwDataSize;

	if (lpszPath == NULL || lpszPath[0] == 0 || pData == NULL)
		return FALSE;

	//Initialize BITMAPINFOHEADER
	dwDataSize = (((g_stuOptions.nImgWidth * nBitCount + 31) >> 5) << 2) * g_stuOptions.nImgHeight;	//each row has aligned by 4 bytes unit
	//---Info Header and Data Size
	pbih = (LPBITMAPINFOHEADER) pInfoHdr;
	pbih->biSize	 = sizeof(BITMAPINFOHEADER);
	pbih->biWidth	 = (LONG) nWidth;
	pbih->biHeight	 = (LONG) nHeight;
	pbih->biPlanes	 = 1;
	pbih->biBitCount = (WORD) nBitCount;
	pbih->biSizeImage= dwDataSize;
	//---Bit Count Processing
	dwInfoSize	= pbih->biSize;
	if (pbih->biBitCount < 9)
	{
		//++++++Change File Size and Offset to Data, BITMAPINFO Size
		dwRead = (DWORD) (1 << (DWORD) pbih->biBitCount) * (DWORD) sizeof(RGBQUAD);
		dwInfoSize	 += dwRead;
		//++++++Fill Palette
		pColor = (LPRGBQUAD) (pInfoHdr + sizeof(BITMAPINFOHEADER));
		switch(pbih->biBitCount)
		{
		case 1:
			pColor[0].rgbRed = pColor[0].rgbGreen = pColor[0].rgbBlue = 0;
			pColor[1].rgbRed = pColor[1].rgbGreen = pColor[1].rgbBlue = 255;
			break;

		case 8:
			for (dwRead = 0; dwRead < 256; dwRead++)
			{
				pColor[dwRead].rgbRed	= (BYTE) dwRead;
				pColor[dwRead].rgbBlue	= (BYTE) dwRead;
				pColor[dwRead].rgbGreen	= (BYTE) dwRead;
			}
			break;
		}
	}

	//Initialize BITMAPFILEHEADER
	bfh.bfType	 = 0x4D42;
	bfh.bfSize	 = dwDataSize + sizeof(BITMAPFILEHEADER) + dwInfoSize;
	bfh.bfOffBits= sizeof(BITMAPFILEHEADER) + dwInfoSize;

	//Create Image File
	hFile = CreateFile((LPCTSTR)lpszPath, GENERIC_WRITE,  FILE_SHARE_WRITE,
							NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	//Write File Header
	WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwRead, NULL);
	//Write Info Header and Color Map Table
	WriteFile(hFile, pbih, dwInfoSize, &dwRead, NULL);
	//Write Color Data
	WriteFile(hFile, pData, dwDataSize, &dwRead, NULL);

	FlushFileBuffers(hFile);

	//Close File
	CloseHandle(hFile);

	return TRUE;
}

BOOL SaveBitmapByHandle(TCHAR* lpszPath, HBITMAP hbmp)
{
	DWORD	dwDataSize;
	BYTE	pInfoHdr[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)] = {0,}, *pData;
	HANDLE	hFile = INVALID_HANDLE_VALUE;
	BITMAP	bmInfo = {0,};
	LPBITMAPINFOHEADER	pbih = NULL;

	if (lpszPath == NULL || lpszPath[0] == 0 || hbmp == NULL)
		return FALSE;

	//Get Bitmap Info
	GetObject(hbmp, sizeof(BITMAP), &bmInfo);
	if (bmInfo.bmWidth < 1 || bmInfo.bmHeight < 1)
		return FALSE;

	//Get Pixel Data Size
	dwDataSize	= bmInfo.bmWidthBytes * bmInfo.bmHeight;

	//Allocate Memory
	pData = (BYTE*) calloc(dwDataSize, 1);
	if (pData == NULL)
		return FALSE;

	//Get Pixel Data
	//---Init Info Header
	pbih = (LPBITMAPINFOHEADER) pInfoHdr;
	pbih->biSize	 = sizeof(BITMAPINFOHEADER);
	pbih->biSizeImage= dwDataSize;
	pbih->biBitCount = bmInfo.bmBitsPixel;
	pbih->biWidth	 = (LONG) bmInfo.bmWidth;
	pbih->biHeight	 = (LONG) bmInfo.bmHeight;
	pbih->biPlanes	 = bmInfo.bmPlanes;
	GetDIBits(g_hdcMem, hbmp, 0, pbih->biHeight, pData, (LPBITMAPINFO) pbih, DIB_RGB_COLORS);

	//Create Image File
	SaveBitmapByPixelData(lpszPath, pData, (int) bmInfo.bmBitsPixel, bmInfo.bmWidth, bmInfo.bmHeight);

	//Free Memory
	free(pData);

	return TRUE;
}

void SaveGLBuffer2Image(int nWidth, int nHeight)
{
	BYTE	nTemp[4], *pCur;
	int		nCount, nPadding;

	if (g_pPixelData == NULL || nWidth < 1 || nHeight < 1)
		return;

	glReadPixels(0, 0, g_stuOptions.nImgWidth, g_stuOptions.nImgHeight,
								GL_RGB, GL_UNSIGNED_BYTE, g_pPixelData);
	nCount	= nWidth * nHeight;
	pCur	= (PBYTE) g_pPixelData;
	while (nCount)
	{
		//Swap R and B
		nTemp[0]= pCur[0];
		pCur[0]	= pCur[2];
		pCur[2]	= nTemp[0];
		pCur+= 3;
		nCount--;
	}

	SaveBitmapByPixelData(g_szImagePath, g_pPixelData, 24,
			g_stuOptions.nImgWidth, g_stuOptions.nImgHeight);
}

LRESULT MyWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		g_cDraw.DrawScene01(g_stuOptions.fScale, g_stuOptions.vRotateAngle.x,
					g_stuOptions.vRotateAngle.y, g_stuOptions.vRotateAngle.z);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

HWND CreateDrawWnd()
{
	WNDCLASS	wc = {0,};
	DWORD	dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	RECT	rcWnd;
	

	//Get Instance Handle
	g_hInstance = GetModuleHandle(NULL);

	//Register Class
	wc.style		= CS_HREDRAW | CS_OWNDC;
	wc.hInstance	= g_hInstance;
	wc.lpfnWndProc	= (WNDPROC) MyWndProc;
	wc.lpszClassName= MYWND_CLASS_NAME;
	wc.hbrBackground= (HBRUSH) GetStockObject(WHITE_BRUSH);
	RegisterClass(&wc);

	//Get Window Size
	rcWnd.left	= rcWnd.top = 0;
	rcWnd.right	= g_stuOptions.nImgWidth;
	rcWnd.bottom= g_stuOptions.nImgHeight;
	AdjustWindowRect(&rcWnd, dwStyle, FALSE);
	rcWnd.right	-= rcWnd.left;
	rcWnd.bottom-= rcWnd.top;
	rcWnd.left	 = rcWnd.top = 0;
	//Create Draw Window
	return	CreateWindow(MYWND_CLASS_NAME, _T("Test"), dwStyle, rcWnd.left, rcWnd.top,
							rcWnd.right, rcWnd.bottom, NULL, NULL, g_hInstance, NULL);
}

void DestroyDrawWnd(HWND hWnd)
{
	if (hWnd)
		DestroyWindow(hWnd);
	UnregisterClass(MYWND_CLASS_NAME, g_hInstance);
}

BOOL CreateMemDC(HWND hWnd)
{
	BOOL bSuccess = FALSE;

	//Create Compatible DC
	g_hdcWnd = GetDC(hWnd);
	if (g_hdcWnd)
	{
		g_hdcMem	= CreateCompatibleDC(g_hdcWnd);
		g_hbmpMem	= CreateCompatibleBitmap(g_hdcWnd, g_stuOptions.nImgWidth, g_stuOptions.nImgHeight);
		g_hbmpOld1	= (HBITMAP) SelectObject(g_hdcMem, g_hbmpMem);
		g_hbmpOld2	= (HBITMAP) SelectObject(g_hdcWnd, g_hbmpMem);
		bSuccess	= (g_hdcMem && g_hbmpMem);
	}

	return bSuccess;
}

void ReleaseMemDC()
{
	if (g_hbmpMem)
	{
		if (g_hdcMem)
		{
			//SelectObject(g_hdcMem, g_hbmpOld1);
			DeleteDC(g_hdcMem);
		}
		if (g_hdcWnd)
		{
			SelectObject(g_hdcWnd, g_hbmpOld2);
		}
		DeleteObject(g_hbmpMem);
	}
}
//Add Suffix to a Path String
//lpszPath	: pointer to the Path String to Add Suffix
//lpszSuffix: pointer to the Suffix String
//lpszCheck	: pointer to the String to check after Dot(.) found.
void Path_AddSuffix(LPTSTR lpszPath, LPTSTR lpszSuffix, LPTSTR lpszCheck)
{
	TCHAR	*pszSlash, *pszDot;

	if (lpszPath == NULL || lpszSuffix == NULL || lpszSuffix[0] == 0)
		return;

	//---Find Slash(\)
	pszSlash = _tcsrchr(lpszPath, '\\');
	if (pszSlash == NULL)
		pszSlash = _tcsrchr(lpszPath, '/');
	//---Find Dot(.) from Path
	pszDot	 = _tcsrchr(lpszPath, '.');
	//---Add suffix after model file name
	if ((pszDot != NULL) && (pszSlash != NULL) && (pszDot >= pszSlash))
		*pszDot = 0;
	else
	{ //if dot is before slash, dot is not for file extension, so set pszDot to the end of path string
		pszDot = g_szImagePath;
		while(*pszDot)
			pszDot++;
	}

	if (lpszCheck)
	{
		if (_tcscmp(pszDot, lpszCheck))
			_tcscpy(pszDot, lpszSuffix);
	} else
		_tcscpy(pszDot, lpszSuffix);
}

int   RenderImage()
{
	//RENDER_OPTIONS	sRenderOptions;
	TCHAR	szSuffix[80];
	HWND	hWnd;

	//Get Image Path
	if (g_stuOptions.lpszOutImagePath)
	{
		//---Get Image File Path
		_tcscpy_s(g_szImagePath, 1024, g_stuOptions.lpszOutImagePath);
		_stprintf(szSuffix, _T(".bmp"));
		Path_AddSuffix(g_szImagePath, szSuffix, szSuffix);
	} else
	{
		//---Get Model File Path
		_tcscpy_s(g_szImagePath, 1024, g_stuOptions.lpszInModelPath);
		_stprintf(szSuffix, _T("_out_%dx%d.bmp"), g_stuOptions.nImgWidth, g_stuOptions.nImgHeight);
		Path_AddSuffix(g_szImagePath, szSuffix, NULL);
	}

	/* Create Window, Render Scene, and Read from Pixel Buffer*/
	g_pPixelData	= (PBYTE) calloc(g_stuOptions.nImgWidth * g_stuOptions.nImgHeight + 4 , 4);
	if (g_pPixelData == NULL)
		return ERROR_NOT_ENOUGH_MEMORY;
	//Create Window, Draw and Save Bitmap, Destroy Window
	hWnd = CreateDrawWnd();
	if (hWnd)
	{
		if (CreateMemDC(hWnd))
		{ //Draw to Bitmap
			g_cDraw.InitOpenGL(g_hdcMem, FALSE);
			g_cDraw.SetLightVals(g_stuOptions.fAmbient, g_stuOptions.fDiffuse);
			g_cDraw.SetBackColor(g_stuOptions.dwBackColor);
			g_cDraw.InitializeMeshObject(&g_StrMeshData);

			//---Draw Meshes
			g_cDraw.DrawScene01(g_stuOptions.fScale, g_stuOptions.vRotateAngle.x,
						g_stuOptions.vRotateAngle.y, g_stuOptions.vRotateAngle.z);
			//---Save by Memory Bitmap
			SaveBitmapByHandle(g_szImagePath, g_hbmpMem);
			//---Close Open GL Drawing
			g_cDraw.CloseOpenGL();
			//---Release Memory DC
			ReleaseMemDC();
		} else /**/ 
		{ //Draw to Window
			g_hdcWnd = GetDC(hWnd);
			g_cDraw.InitOpenGL(g_hdcWnd, TRUE);
			g_cDraw.SetLightVals(g_stuOptions.fAmbient, g_stuOptions.fDiffuse);
			g_cDraw.SetBackColor(g_stuOptions.dwBackColor);
			g_cDraw.InitializeMeshObject(&g_StrMeshData);

			//---Draw Meshes
			g_cDraw.DrawScene01(g_stuOptions.fScale, g_stuOptions.vRotateAngle.x,
							g_stuOptions.vRotateAngle.y, g_stuOptions.vRotateAngle.z);
			//---Read GL Pixel Buffer and Save Image
			SaveGLBuffer2Image(g_stuOptions.nImgWidth, g_stuOptions.nImgHeight);
			//---Close Open GL Drawing
			g_cDraw.CloseOpenGL();
			//---Release Window DC
			ReleaseDC(hWnd, g_hdcWnd);
		}

		//---Destroy Window
		DestroyDrawWnd(hWnd);
	} else
		return ERROR_BAD_ENVIRONMENT;

	//Free Pixel Data Memory
	if (g_pPixelData)
	{
		free(g_pPixelData);
		g_pPixelData = NULL;
	} /**/

	return ERROR_SUCCESS;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nExitCode;

	if (ParseParams(argc, argv) < 1 || g_stuOptions.lpszInModelPath == NULL)
	{
		print_usage();
		return -1;
	}
	
	//Create 3D Object Model File Object
	g_pClsModelFile = CreateModelFile(g_stuOptions.lpszInModelPath);
	if (g_pClsModelFile == NULL)
	{
		_tprintf(_T("File not found! or not supported format.\n"));
		return -1;
	}

	//Open Model File
	if (!g_pClsModelFile->Open(g_stuOptions.lpszInModelPath, &g_StrMeshData))
	{
		_tprintf(_T("File open failed.\n"));
		return -2;
	}

	//Calculate Volume
	g_clsVolumeCalc.CalculateVolume(&g_StrMeshData);

	_tprintf(_T("Face   Count: %d\n"),	g_StrMeshData.intFaceCount);
	_tprintf(_T("Vertex Count: %d\n"),	g_StrMeshData.intVertexCount);
	_tprintf(_T("DX: %.2lf\n"), g_StrMeshData.Dx);
	_tprintf(_T("DY: %.2lf\n"), g_StrMeshData.Dy);
	_tprintf(_T("DZ: %.2lf\n"), g_StrMeshData.Dz);
	_tprintf(_T("Volume: %.2lf\n"), g_StrMeshData.fVolume);

	//Rendering Image
	nExitCode = RenderImage();

	//Print Output Image Path
	_tprintf(_T("Image File %s created.\n\n"), g_szImagePath);

	//Close Model File
	ReleaseModelFile(&g_pClsModelFile);

	return nExitCode;
}