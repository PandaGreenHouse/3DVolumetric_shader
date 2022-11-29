/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SoundSourceNode.h
*
******************************************************************/

#ifndef _MYVRML_SOUNDSOURCENODE_H_
#define _MYVRML_SOUNDSOURCENODE_H_

#include <VRML97Fields.h>
#include <Node.h>

namespace MyVrml {

const char isPlayingPrivateFieldName[] = "isPlaying";

class SoundSourceNode : public Node {

	SFString *descriptionField;
	SFFloat *pitchField;
	MFString *urlField;
	SFBool *isActiveField;
	SFTime *durationChangedField;

public:

	SoundSourceNode();
	virtual ~SoundSourceNode();

	////////////////////////////////////////////////
	//	Description
	////////////////////////////////////////////////

	SFString *getDescriptionField() const;

	void setDescription(const char * value);
	const char *getDescription() const;

	////////////////////////////////////////////////
	//	Pitch
	////////////////////////////////////////////////

	SFFloat *getPitchField() const;
	
	void setPitch(float value);
	float getPitch() const;

	////////////////////////////////////////////////
	//	isActive
	////////////////////////////////////////////////
	
	SFBool *getIsActiveField() const;

	void setIsActive(bool  value);
	bool  getIsActive() const;
	bool  isActive() const;

	////////////////////////////////////////////////
	//	duration_changed
	////////////////////////////////////////////////

	SFTime *getDurationChangedField() const;
	
	void setDurationChanged(double value);
	double getDurationChanged() const;

	////////////////////////////////////////////////
	// Url
	////////////////////////////////////////////////

	MFString *getUrlField() const;

	void addUrl(const char * value);
	int getNUrls() const;
	const char *getUrl(int index) const;
	void setUrl(int index, const char *urlString);
};

}

#endif
