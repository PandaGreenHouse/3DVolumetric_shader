#include "stdafx.h"
#include "ImageRender.h"
#include "GL.H"
#include "glut.h"

PRENDER_OPTIONS	g_pOptions = NULL;

BOOL IR_Initialize(BOOL bOffScreen, PRENDER_OPTIONS pOptions)
{
	int	doubleBuffer;

	if (pOptions == NULL || pOptions->pModelMesh == NULL ||
		pOptions->lpszOutImagePath == NULL || pOptions->lpszOutImagePath[0] == 0)
		return FALSE;

	g_pOptions = pOptions;
	glutInit(0, NULL);
	if (bOffScreen) {
		glutInitWindowSize(1, 1);
		doubleBuffer = GLUT_SINGLE;
	} else {
		glutInitWindowSize(g_pOptions->nImgWidth , g_pOptions->nImgWidth);
		glutInitWindowPosition(0, 0);
		doubleBuffer = GLUT_DOUBLE;
	}
	glutInitDisplayMode( doubleBuffer | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(g_pOptions->nImgWidth , g_pOptions->nImgWidth);
	glutCreateWindow("Test");
	if (bOffScreen)
	{
		//glGenRenderbuffers(1, &rboColor);
		glutHideWindow();
	}

	return FALSE;
}