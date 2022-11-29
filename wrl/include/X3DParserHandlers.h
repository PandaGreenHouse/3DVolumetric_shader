/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	X3DParserHandlers.h
*
******************************************************************/

#include <MyVrmlConfig.h>

#ifdef MYVRML_SUPPORT_X3D

#ifndef _MYVRML_X3DPARSERHANDLERS_H_
#define _MYVRML_X3DPARSERHANDLERS_H_

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include "XMLNode.h"

namespace MyVrml {

class X3DParserHandlers : public xercesc::DefaultHandler  
{

public:

	////////////////////////////////////////////////////////////////////////////////////////////////
    //  Constructors
	////////////////////////////////////////////////////////////////////////////////////////////////

    X3DParserHandlers();

    virtual ~X3DParserHandlers();

	////////////////////////////////////////////////////////////////////////////////////////////////
    //  Implementations of the format target interface
	////////////////////////////////////////////////////////////////////////////////////////////////

    void writeChars(const XMLByte* const toWrite) const;

    void writeChars (
		const XMLByte* const toWritem,
		const unsigned int count,
		xercesc::XMLFormatter* const formatter) const;

	////////////////////////////////////////////////////////////////////////////////////////////////
    //  Implementations of the SAX DocumentHandler interface
	////////////////////////////////////////////////////////////////////////////////////////////////

    void endDocument();

    void endElement(
		const XMLCh* const uri,
		const XMLCh* const localname, 
		const XMLCh* const qname);

    void characters(
		const XMLCh* const chars,
		const unsigned int length);

    void ignorableWhitespace(
		const XMLCh* const chars,
		const unsigned int length);

    void processingInstruction(
		const XMLCh* const target,
		const XMLCh* const data);

    void startDocument();

    void startElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname,
		const xercesc::Attributes& attributes);

	void addXMLElement(
		XMLNode *xmlNode,
		const char *attrName,
		const XMLCh *attrValue);

	void addX3DElement(
		Node *x3dNode,
		const char *attrName,
		const XMLCh *attrValue);

	////////////////////////////////////////////////////////////////////////////////////////////////
    //  Implementations of the SAX ErrorHandler interface
	////////////////////////////////////////////////////////////////////////////////////////////////

	void exception(const xercesc::SAXParseException& exception);
    void warning(const xercesc::SAXParseException& exception);
    void error(const xercesc::SAXParseException& exception);
    void fatalError(const xercesc::SAXParseException& exception);

	////////////////////////////////////////////////////////////////////////////////////////////////
    //  Implementation of the SAX DTDHandler interface
	////////////////////////////////////////////////////////////////////////////////////////////////

    void notationDecl(
		const XMLCh* const name,
		const XMLCh* const publicId,
		const XMLCh* const systemId);

    void unparsedEntityDecl(
		const XMLCh* const name,
		const XMLCh* const publicId,
		const XMLCh* const systemId,
		const XMLCh* const notationName);
};

}

#endif

#endif
