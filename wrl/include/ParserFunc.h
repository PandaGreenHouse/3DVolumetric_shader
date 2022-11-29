/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ParserFunc.h
*
******************************************************************/

#ifndef _MYVRML_PARSERFUNC_H_
#define _MYVRML_PARSERFUNC_H_

#include <Parser.h>
#include <ParserResult.h>

namespace MyVrml {

void PushParserObject(Parser *parser);
void PopParserObject();
Parser *GetParserObject();

void SetParserResultObject(ParserResult *parserResult);
ParserResult *GetParserResultObject();

int ParserGetCurrentNodeType(void);
int ParserGetParentNodeType(void);
Node *ParserGetCurrentNode(void);

void ParserPushNode(int parserType, Node *node);
void ParserPushNode(Node *node);
void ParserPopNode(void);

void ParserAddNode(Node *node);
void ParserAddRouteInfo(const char *string);

Node *CreateNode(int nodeType);
Node *CreateX3DNode(int nodeType);

}

#endif
