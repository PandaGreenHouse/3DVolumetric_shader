/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	VRML97Parser.cpp
*
*      03/12/04
*              - Added the following functions to parse more minimum memory.
*                VRML97ParserSetBufSize(), VRML97ParserGetBufSize().
*
******************************************************************/

#include <stdio.h>
#include <VRML97Parser.h>
#include <VRML97ParserFunc.h>
#if defined(MYVRML_SUPPORT_GZIP)
#include <zlib.h>
#endif

using namespace MyVrml;

////////////////////////////////////////////////
//	VRML97Parser::load
////////////////////////////////////////////////

VRML97Parser::VRML97Parser() 
{
	setParserResult(false);
	setParseringState(false);
}

VRML97Parser::~VRML97Parser() 
{
}

////////////////////////////////////////////////
//	VRML97Parser::load
////////////////////////////////////////////////

bool VRML97Parser::loadA(const char *fileName, void (*callbackFn)(int nLine, void *info), void *callbackFnInfo) 
{
	FILE *fp = NULL;
	fopen_s(&fp, fileName, "rb");

#if defined(MYVRML_SUPPORT_URL)
	SceneGraph *sg = (SceneGraph *)this;
#endif

#if defined(MYVRML_SUPPORT_URL)
	if (fp == NULL){
		if (sg->getUrlStream(fileName)) {
			char *outputFilename = sg->getUrlOutputFilename();
			fopen_s(&fp, outputFilename, "rb");
			sg->setUrl(fileName);
		}
	}
#endif

	if (fp == NULL) {
		fprintf(stderr, "Cannot open data file %s\n", fileName);
		setParserResult(false);
		setParseringState(false);
		return false;
	}

#if defined(MYVRML_SUPPORT_GZIP)
	gzFile gfd = gzdopen(fileno(fp), "rb");

	if (gfd == 0){
		return false;
	}
	std::string buffer = "";
    char buf[64];
	while (!gzeof(gfd)) {
          memset(buf, '\0', 64);
	  int size = gzread(gfd, &buf[0], 63);
	  buffer += buf;
	}
    int lexBufferSize = buffer.size();	
    SetInputBuffer(buffer.c_str(), buffer.size());
#else
	#ifdef USE_MAX_LEX_BUFFER
	fseek(fp, 0, SEEK_END);
	int lexBufferSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	#else
	int lexBufferSize = VRML97ParserGetBufSize();
	#endif
#endif

	if (GetParserObject() == NULL) {
#if defined(MYVRML_SUPPORT_GZIP)
		MakeLexerStringBuffers(lexBufferSize, DEFAULT_LEX_LINE_BUFFER_SIZE);
#else
		MakeLexerBuffers(lexBufferSize, DEFAULT_LEX_LINE_BUFFER_SIZE);
#endif
	}

	clearNodeList();
	clearRouteList();
	deleteDEFs();
	deletePROTOs();

	beginParse();

	SetLexCallbackFn(callbackFn, callbackFnInfo);
#if !defined(MYVRML_SUPPORT_GZIP)
	SetInputFile(fp);
#endif
    setParserResult(!yyparse() ? true : false);

	endParse();

	if (GetParserObject() == NULL) {
#if defined(MYVRML_SUPPORT_GZIP)
		DeleteLexerStringBuffers();
#else
		DeleteLexerBuffers();
#endif
	}

#if defined(MYVRML_SUPPORT_GZIP)
   gzclose(gfd);
#endif
	fclose(fp);

#if defined(MYVRML_SUPPORT_URL)
	sg->deleteUrlOutputFilename();
#endif

	return getParserResult();
}

bool VRML97Parser::loadW(const wchar_t *fileName, void (*callbackFn)(int nLine, void *info), void *callbackFnInfo) 
{
	FILE *fp = NULL;
	_wfopen_s(&fp, fileName, L"rb");

#if defined(MYVRML_SUPPORT_URL)
	SceneGraph *sg = (SceneGraph *)this;
#endif

#if defined(MYVRML_SUPPORT_URL)
	if (fp == NULL){
		if (sg->getUrlStream(fileName)) {
			char *outputFilename = sg->getUrlOutputFilename();
			fopen_s(&fp, outputFilename, "rb");
			sg->setUrl(fileName);
		}
	}
#endif

	if (fp == NULL) {
		fprintf(stderr, "Cannot open data file %s\n", fileName);
		setParserResult(false);
		setParseringState(false);
		return false;
	}

#if defined(MYVRML_SUPPORT_GZIP)
	gzFile gfd = gzdopen(fileno(fp), "rb");

	if (gfd == 0){
		return false;
	}
	std::string buffer = "";
	char buf[64];
	while (!gzeof(gfd)) {
		memset(buf, '\0', 64);
		int size = gzread(gfd, &buf[0], 63);
		buffer += buf;
	}
	int lexBufferSize = buffer.size();	
	SetInputBuffer(buffer.c_str(), buffer.size());
#else
#ifdef USE_MAX_LEX_BUFFER
	fseek(fp, 0, SEEK_END);
	int lexBufferSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
#else
	int lexBufferSize = VRML97ParserGetBufSize();
#endif
#endif

	if (GetParserObject() == NULL) {
#if defined(MYVRML_SUPPORT_GZIP)
		MakeLexerStringBuffers(lexBufferSize, DEFAULT_LEX_LINE_BUFFER_SIZE);
#else
		MakeLexerBuffers(lexBufferSize, DEFAULT_LEX_LINE_BUFFER_SIZE);
#endif
	}

	clearNodeList();
	clearRouteList();
	deleteDEFs();
	deletePROTOs();

	beginParse();

	SetLexCallbackFn(callbackFn, callbackFnInfo);
#if !defined(MYVRML_SUPPORT_GZIP)
	SetInputFile(fp);
#endif
	setParserResult(!yyparse() ? true : false);

	endParse();

	if (GetParserObject() == NULL) {
#if defined(MYVRML_SUPPORT_GZIP)
		DeleteLexerStringBuffers();
#else
		DeleteLexerBuffers();
#endif
	}

#if defined(MYVRML_SUPPORT_GZIP)
	gzclose(gfd);
#endif
	fclose(fp);

#if defined(MYVRML_SUPPORT_URL)
	sg->deleteUrlOutputFilename();
#endif

	return getParserResult();
}

////////////////////////////////////////////////
//     VRML97Parser::load
////////////////////////////////////////////////

static int vrml97parserBufSize = VRML97_PARSER_DEFAULT_BUF_SIZE;

void  MyVrml::VRML97ParserSetBufSize(int bufSize)
{
       vrml97parserBufSize = bufSize;
}

int MyVrml::VRML97ParserGetBufSize()
{
       return vrml97parserBufSize;
}

