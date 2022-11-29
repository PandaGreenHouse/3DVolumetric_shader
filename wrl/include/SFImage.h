/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SFImage.h
*
******************************************************************/

#ifndef _MYVRML_SFIMAGE_H_
#define _MYVRML_SFIMAGE_H_

#include <MField.h>
#include <SFInt32.h>

namespace MyVrml {

class SFImage : public MField {

	static	int	mInit;

public:

	SFImage();

	void InitializeJavaIDs();

	void addValue(int value);
	void addValue(SFInt32 *sfvalue);
	void addValue(const char *value);

	void insertValue(int index, int value);
	int get1Value(int index) const;

	void set1Value(int index, int value);
	void setValue(MField *mfield);

	int getValueCount() const 
	{
		return 1;
	}

	////////////////////////////////////////////////
	//	Output
	////////////////////////////////////////////////

	void outputContext(std::ostream& printStream, const char *indentString) const;

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

	void setValue(const char *value);
	const char *getValue(char *buffer, int bufferLen) const;

	////////////////////////////////////////////////
	//	Java
	////////////////////////////////////////////////

#if defined(MYVRML_SUPPORT_JSAI)

private:

	static jclass		mFieldClassID;
	static jclass		mConstFieldClassID;

	static jmethodID	mInitMethodID;
	static jmethodID	mSetValueMethodID;
	static jmethodID	mGetValueMethodID;
	static jmethodID	mSetNameMethodID;

	static jmethodID	mConstInitMethodID;
	static jmethodID	mConstSetValueMethodID;
	static jmethodID	mConstGetValueMethodID;
	static jmethodID	mConstSetNameMethodID;

public:

	void		setJavaIDs();

	jclass		getFieldID()			{return mFieldClassID;}
	jclass		getConstFieldID()		{return mConstFieldClassID;}

	jmethodID	getInitMethodID()		{return mInitMethodID;}
	jmethodID	getSetValueMethodID()		{return mSetValueMethodID;}
	jmethodID	getGetValueMethodID()		{return mGetValueMethodID;}
	jmethodID	getSetNameMethodID()		{return mSetNameMethodID;}

	jmethodID	getConstInitMethodID()		{return mConstInitMethodID;}
	jmethodID	getConstSetValueMethodID()	{return mConstSetValueMethodID;}
	jmethodID	getConstGetValueMethodID()	{return mConstGetValueMethodID;}
	jmethodID	getConstSetNameMethodID()	{return mConstSetNameMethodID;}

	jobject toJavaObject(int bConstField = 0);
	void setValue(jobject field, int bConstField = 0);
	void getValue(jobject field, int bConstField = 0);

#endif
};

}

#endif
