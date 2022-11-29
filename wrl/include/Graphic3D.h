/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File: Graphic3D.h
*
******************************************************************/

#ifndef _MYVRML_GRAPHIC3D_H_
#define _MYVRML_GRAPHIC3D_H_

#include <MyVrmlConfig.h>

#ifdef MYVRML_SUPPORT_OPENGL

#ifdef WIN32
#include <windows.h>
#endif // WIN32

#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif // MACOSX

#ifdef WIN32
typedef GLvoid (CALLBACK*GLUtessCallBackFunc)(void);
#else
typedef GLvoid (*GLUtessCallBackFunc)(void);
#endif // WIN32

#endif // MYVRML_SUPPORT_OPENGL

#endif
