/******************************************************************
*
*	MyVrml for C++
*
*	
*
*	File:	BoundingBox.h
*
******************************************************************/

#ifndef _MYVRML_BOUNDINGBOX_H_
#define _MYVRML_BOUNDINGBOX_H_

namespace MyVrml {

class SFMatrix;

class BoundingBox {

	float	mMaxPosition[3];
	float	mMinPosition[3];
	int		mNPoints;

public:

	BoundingBox();
	BoundingBox(BoundingBox *bbox);
	BoundingBox(float center[3], float size[3]);

	virtual ~BoundingBox();

	void	initialize();

	void	addPoint(float point[3]);
	void	addPoint(float x, float y, float z);
	void	addBoundingBox(SFMatrix *mx, float center[3], float size[3]);
	void	addBoundingBox(SFMatrix *mx, BoundingBox *bbox);

	void	setNPoints(int npoints);
	int		getNPoints() const;

	void	setMinPosition(float pos[3]);
	void	setMaxPosition(float pos[3]);

	void	setMinPosition(float x, float y, float z);
	void	setMaxPosition(float x, float y, float z);

	void	getMinPosition(float pos[3]) const;
	void	getMaxPosition(float pos[3]) const;

	void	set(float center[3], float size[3]);
	void	set(BoundingBox *bbox);

	void	getCenter(float center[3]) const;
	void	getSize(float size[3]) const;

};

}

#endif
