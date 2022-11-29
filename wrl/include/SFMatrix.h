/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	SFMatrix.h
*
******************************************************************/

#ifndef _MYVRML_SFMATRIX_H_
#define _MYVRML_SFMATRIX_H_

#include <math.h>
#include <Field.h>
#include <SFVec3f.h>
#include <SFRotation.h>

namespace MyVrml {

class SFRotation;

class SFMatrix : public Field {

	float mValue[4][4]; 

public:

	SFMatrix();
	SFMatrix(float value[4][4]);
	SFMatrix(SFMatrix *value);
	SFMatrix(SFRotation *rot);
	SFMatrix(float x, float y, float z, float angle);
	SFMatrix(float x, float y, float z);

	////////////////////////////////////////////////
	//	set value 
	////////////////////////////////////////////////

	void setValue(float value[4][4]);
	void setValue(SFMatrix *matrix);

	int getValueCount() const 
	{
		return 16;
	}

	////////////////////////////////////////////////
	//	set as scaling value 
	////////////////////////////////////////////////

	void setScaling(SFVec3f *vector);
	void setScaling(float value[]);
	void setScaling(float x, float y, float z);

	////////////////////////////////////////////////
	//	set as translation value 
	////////////////////////////////////////////////

	void setTranslation(SFVec3f *vector);
	void setTranslation(float value[]);
	void setTranslation(float x, float y, float z);

	////////////////////////////////////////////////
	//	set as direction value 
	////////////////////////////////////////////////

	void setDirection(SFVec3f *vector);
	void setDirection(float value[]);
	void setDirection(float x, float y, float z);

	////////////////////////////////////////////////
	//	set as rotation value 
	////////////////////////////////////////////////

	void setRotation(SFRotation *rotation);
	void setRotation(float value[]);
	void setRotation(float x, float y, float z, float rot);
	
	////////////////////////////////////////////////
	//	get value
	////////////////////////////////////////////////

	void getValue(float value[4][4]) const;

	////////////////////////////////////////////////
	//	get value only translation
	////////////////////////////////////////////////

	void getTranslation(float value[]) const;

	////////////////////////////////////////////////
	//	add 
	////////////////////////////////////////////////

	void add(SFMatrix *matrix);

	////////////////////////////////////////////////
	//	multi 
	////////////////////////////////////////////////

	void multi(float vector[]);
	void multi(float *x, float *y, float *z);
	void multi(SFVec3f *vector);

	////////////////////////////////////////////////
	//	convert
	////////////////////////////////////////////////

	void getSFRotation(SFRotation *rotation) const;

	////////////////////////////////////////////////
	//	toString
	////////////////////////////////////////////////

	void setValue(const char *value);
	const char *getValue(char *buffer, int bufferLen) const;

	////////////////////////////////////////////////
	//	other
	////////////////////////////////////////////////
	
	void invert();
	float determinant() const;
	void init();

	////////////////////////////////////////////////
	//	Java
	////////////////////////////////////////////////

#if defined(MYVRML_SUPPORT_JSAI)

	jobject toJavaObject(int bConstField = 0);
	void setValue(jobject field, int bConstField = 0);
	void getValue(jobject field, int bConstField = 0);

#endif
};

}

#endif
