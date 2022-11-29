/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	StringSensorNode.h
*
******************************************************************/

#ifndef _MYVRML_STRINGSENSORNODE_H_
#define _MYVRML_STRINGSENSORNODE_H_

#include <KeyDeviceSensorNode.h>

namespace MyVrml {

class StringSensorNode : public KeyDeviceSensorNode 
{
	SFInt32 *deletionCharacterField;
	SFString *enteredTextField;
	SFString *finalTextField;
	SFInt32 *profileField;
	SFString *terminationTextField;

public:

	StringSensorNode();
	virtual ~StringSensorNode();

	////////////////////////////////////////////////
	//	DeletionCharacter
	////////////////////////////////////////////////

	SFInt32 *getDeletionCharacterField() const;
	
	void setDeletionCharacter(int value);
	int getDeletionCharacter() const;

	////////////////////////////////////////////////
	//	Profile
	////////////////////////////////////////////////

	SFInt32 *getProfileField() const;
	
	void setProfile(int value);
	int getProfile() const;

	////////////////////////////////////////////////
	//	EnteredText
	////////////////////////////////////////////////
	
	SFString *getEnteredTextField() const;

	void setEnteredText(const char *value);
	const char *getEnteredText() const;

	////////////////////////////////////////////////
	//	FinalText
	////////////////////////////////////////////////
	
	SFString *getFinalTextField() const;

	void setFinalText(const char *value);
	const char *getFinalText() const;

	////////////////////////////////////////////////
	//	TerminationText
	////////////////////////////////////////////////
	
	SFString *getTerminationTextField() const;

	void setTerminationText(const char *value);
	const char *getTerminationText() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	StringSensorNode *next() const;
	StringSensorNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();

	////////////////////////////////////////////////
	//	Infomation
	////////////////////////////////////////////////

	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

