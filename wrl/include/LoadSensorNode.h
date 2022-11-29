/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	LoadSensorNode.h
*
******************************************************************/

#ifndef _MYVRML_LOADSENSORNODE_H_
#define _MYVRML_LOADSENSORNODE_H_

#include <X3DFields.h>
#include <NetworkSensorNode.h>

namespace MyVrml {

class LoadSensorNode : public NetworkSensorNode {

	MFNode* watchListField;
	SFBool *enabledField;
	SFTime *timeoutField;
	SFBool *isActiveField;
	SFBool *isLoadedField;
	SFTime *loadTimeField;
	SFFloat *progressField;

public:

	LoadSensorNode();
	virtual ~LoadSensorNode();

	////////////////////////////////////////////////
	//	watchList
	////////////////////////////////////////////////

	MFNode* getWatchListField() const;

	////////////////////////////////////////////////
	//	Enabled
	////////////////////////////////////////////////
	
	SFBool *getEnabledField() const;

	void setEnabled(bool value);
	bool getEnabled() const;
	bool isEnabled() const;

	////////////////////////////////////////////////
	//	timeout
	////////////////////////////////////////////////
	
	SFTime *getTimeoutField() const;

	void setTimeout(double value);
	double getTimeout() const;

	////////////////////////////////////////////////
	//	isActive
	////////////////////////////////////////////////
	
	SFBool *getIsActiveField() const;

	void setIsActive(bool value);
	bool getIsActive() const;
	bool isActive() const;

	////////////////////////////////////////////////
	//	isLoaded
	////////////////////////////////////////////////
	
	SFBool *getIsLoadedField() const;

	void setIsLoaded(bool value);
	bool getIsLoaded() const;
	bool isLoaded() const;

	////////////////////////////////////////////////
	//	loadTime
	////////////////////////////////////////////////
	
	SFTime *getLoadTimeField() const;

	void setLoadTime(double value);
	double getLoadTime() const;

	////////////////////////////////////////////////
	//	progress
	////////////////////////////////////////////////

	SFFloat *getProgressField() const;

	void setProgress(float value);
	float getProgress() const;

	////////////////////////////////////////////////
	//	List
	////////////////////////////////////////////////

	LoadSensorNode *next() const;
	LoadSensorNode *nextTraversal() const;

	////////////////////////////////////////////////
	//	Virtual functions
	////////////////////////////////////////////////
	
	bool isChildNodeType(Node *node) const;
	void initialize();
	void uninitialize();
	void update();
	void outputContext(std::ostream &printStream, const char *indentString) const;
};

}

#endif

