#ifndef MOVER_H
#define MOVER_H

#define _USE_MATH_DEFINES
#include <cmath>
#include "Cube.h"

class Mover 
{
public :
	Mover(void);
	~Mover(void);

	Cube *cubes[3][3][3];

	void rotateLocal(int type);
	void rotateLocalX(int x);
	void rotateLocalXNeg(int x);
	void rotateLocalY(int x);
	void rotateLocalYNeg(int x);
	void rotateLocalZ(int x);
	void rotateLocalZNeg(int x);
	void stepInto(int *left, int *right, int *dir, int step, int lEd, int rEd);
	void drawCube(int type, GLfloat angle);
};

#endif