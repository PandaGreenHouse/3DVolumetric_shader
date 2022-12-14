/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	Event.h
*
******************************************************************/

#ifndef _MYVRML_EVENT_H_
#define _MYVRML_EVENT_H_

#include <time.h>
#include <StringUtil.h>
#include <Field.h>
#include <SFTime.h>
#include <JavaVM.h>

namespace MyVrml {

#if defined(MYVRML_SUPPORT_JSAI)
class Event : public JavaVM {
#else
class Event {
#endif

#if defined(MYVRML_SUPPORT_JSAI)
	jclass		mEventClass;
#endif

	String		mName;
	double		mTime;
	Field		*mField;

public:

	Event(Field *field);
	Event(const char *name, double time, Field *field);

	void InitializeJavaIDs();

	////////////////////////////////////////////////
	//	Name
	////////////////////////////////////////////////

	void setName(const char *name);
	const char *getName() const;

	////////////////////////////////////////////////
	//	Time
	////////////////////////////////////////////////
	
	void setTimeStamp(double time);
	double getTimeStamp() const;

	////////////////////////////////////////////////
	//	ConstField
	////////////////////////////////////////////////

	void setField(Field *field);
	Field *getField() const;

	////////////////////////////////////////////////
	//	for Java
	////////////////////////////////////////////////

#if defined(MYVRML_SUPPORT_JSAI)

	void setEventClass(jclass eventClass);
	jclass getEventClass();
	jobject toJavaObject();

#endif

};

}

#endif
