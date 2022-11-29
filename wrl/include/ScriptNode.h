/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	ScriptNode.h
*
******************************************************************/

#ifndef _MYVRML_SCRIPT_H_
#define _MYVRML_SCRIPT_H_

#include <VRML97Fields.h>
#include <Node.h>
#include <JavaVM.h>
#include <JScript.h>

namespace MyVrml {

#if defined(MYVRML_SUPPORT_JSAI)
class ScriptNode : public Node, public CJavaVM { 
#else
class ScriptNode : public Node { 
#endif

	SFBool *directOutputField;
	SFBool *mustEvaluateField;
	MFString *urlField;

#if defined(MYVRML_SUPPORT_JSAI)
	JScript			*mpJScriptNode;
#endif

public:

	ScriptNode();
	virtual ~ScriptNode();

	////////////////////////////////////////////////
	// Initialization
	////////////////////////////////////////////////

	void initialize();
	void uninitialize();

	////////////////////////////////////////////////
	// DirectOutput
	////////////////////////////////////////////////

	SFBool *getDirectOutputField() const;

	void setDirectOutput(bool  value);
	void setDirectOutput(int value);
	bool  getDirectOutput() const;

	////////////////////////////////////////////////
	// MustEvaluate
	////////////////////////////////////////////////

	SFBool *getMustEvaluateField() const;

	void setMustEvaluate(bool  value);
	void setMustEvaluate(int value);
	bool  getMustEvaluate() const;

	////////////////////////////////////////////////
	// Url
	////////////////////////////////////////////////

	MFString *getUrlField() const;

	void addUrl(const char * value);
	int getNUrls() const;
	const char *getUrl(int index) const;
	void setUrl(int index, const char *urlString);

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	ScriptNode *next() const;
	ScriptNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	virtual function
	////////////////////////////////////////////////

	bool isChildNodeType(Node *node) const;

	////////////////////////////////////////////////
	//	update
	////////////////////////////////////////////////

	void update();

	////////////////////////////////////////////////
	//	output
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;

	////////////////////////////////////////////////
	// JSAI
	////////////////////////////////////////////////

#if defined(MYVRML_SUPPORT_JSAI)

	int hasScript() {
		return getJavaNode() ? 1 : 0;
	}

	JScript	*getJavaNode()	{return mpJScriptNode;}

#endif

	////////////////////////////////////////////////
	// Update Java Fields
	////////////////////////////////////////////////

	void	update(Field *eventInField);
	void	updateFields();
};

}

#endif

