#pragma once

#ifndef __IMAGE_RENDER_HEADER__
#define __IMAGE_RENDER_HEADER__

#include "MyStructure.h"

typedef struct tagRENDER_OPTIONS
{
	PCOM_MESH	pModelMesh;			//Model Mesh Info
	LPTSTR		lpszOutImagePath;	//-o option : Image File Name
	VECTOR3		vRotateAngle;		//-r option : Rotate Angle
	float		fScale;				//-s option : Render Scale
	float		fAmbient;			//-a option : Ambient Value
	float		fDiffuse;			//-d option : Diffuse Value
	DWORD		dwBackColor;		//-b option : Image Background Color
	int			nImgWidth;			//Image Width  in Pixels
	int			nImgHeight;			//Image Height in Pixels
}RENDER_OPTIONS, *PRENDER_OPTIONS;

BOOL IR_Initialize(BOOL bOffScreen, PRENDER_OPTIONS pOptions);



#endif	//__IMAGE_RENDER_HEADER__