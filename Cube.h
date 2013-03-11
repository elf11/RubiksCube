#ifndef CUBE_H
#define CUBE_H

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "dependente\freeglut.h"

#define CUBE_SIZE 2

class Cube 
{
public :
	Cube(void);
	~Cube(void);
	GLuint loadTextureRaw(char *filename, int wrap);
	void freeTexture(GLuint texture);
	void drawFace(GLfloat x, GLfloat y, GLfloat z);
	void rotateX(void);
	void rotateXNeg(void);
	void rotateY(void);
	void rotateYNeg(void);
	void rotateZ(void);
	void rotateZNeg(void);

	int direction[6];
	GLuint textureMap[6];
	GLuint white;
	GLuint red;
	GLuint blue;
	GLuint green;
	GLuint yellow;
	GLuint pink;

	void rotate_X(int dir);
	void rotate_Y(int dir);
	void rotate_Z(int dir);
};

#endif