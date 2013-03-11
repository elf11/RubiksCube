#include "Cube.h"

/*
 * Setam directia fetelor cubului, 1,2,3 = X, Y, Z precum si sensul pozitiv sau negativ al acestora.
 */
Cube::Cube() 
{
	direction[0] = 3;
	direction[1] = 1;
	direction[2] = -3;
	direction[3] = -1;
	direction[4] = 2;
	direction[5] = -2;
}

Cube::~Cube()
{
}
/*
 * Functie de incarcare a texturilor, texturile sunt incarcate din fisiere de tip *.RAW, valorile sunt dispuse in acest tip de fisiere sub forma (r,g,b) si pot fi citite direct, nu necesita tratarea headerelor pentru compresie, acesta fiind si motivul pentru care am ales sa incarc texturi de acest tip.
 */
GLuint Cube::loadTextureRaw(char *filename, int wrap)
{
	GLuint texture;
	int width, height;
	long lSize;
	BYTE *data;
	FILE *file;

	file = fopen(filename, "rb");
	if (file == NULL)
	{
		fputs("File error", stderr);
		return 0;
	}
	width = 256;
	height = 256;
	fseek(file, 0, SEEK_END);
	lSize = ftell(file);
	rewind(file);
	data = (BYTE *)malloc(width * height * 3);

	fread(data, width * height * 3, 1, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	free(data);

	return texture;
}

void Cube::freeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}
/*
 * Am incarcat texturile care mai apoi au primit fiecare cate o fata, unei fete ii este asignata o culoare prin intermediul vectorului de texturi, in sensul celor 3 axe, X, Y, Z pozitiv si negativ, atunci cand se redeseneaza o fata in urma unei mutari acea fata se redeseneaza avand atasata textura specifica directiei si sensului inspre care fata este orientata.
 */

void Cube::drawFace(GLfloat x, GLfloat y, GLfloat z)
{
	white = loadTextureRaw("white.raw", TRUE);
	red = loadTextureRaw("red.raw", TRUE);
	blue = loadTextureRaw("blue.raw", TRUE);
	green = loadTextureRaw("green.raw", TRUE);
	yellow = loadTextureRaw("yellow.raw", TRUE);
	pink = loadTextureRaw("pink.raw", TRUE);

	textureMap[0] = white;
	textureMap[1] = red;
	textureMap[2] = blue;
	textureMap[3] = green;
	textureMap[4] = yellow;
	textureMap[5] = pink;
	
	for (int i = 0; i < 6; i += 1)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureMap[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//draw front face
		if (direction[i] == 3)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y+CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y-CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y-CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y+CUBE_SIZE,z+CUBE_SIZE);
			glEnd();
		}

		if (direction[i] == -3)
		{
			//draw back face
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y+CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y-CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y-CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y+CUBE_SIZE,z-CUBE_SIZE);
			glEnd();
		}

		if (direction[i] == 2)
		{
			//draw top face
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y+CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y+CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y+CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y+CUBE_SIZE,z-CUBE_SIZE);
			glEnd();
		}

		if (direction[i] == -2)
		{
			//draw bottom face
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y-CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y-CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y-CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y-CUBE_SIZE,z-CUBE_SIZE);
			glEnd();
		}

		if (direction[i] == 1)
		{
			//draw left face
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y+CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(x+CUBE_SIZE,y+CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(x+CUBE_SIZE,y-CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(x+CUBE_SIZE,y-CUBE_SIZE,z+CUBE_SIZE);
			glEnd();
		}

		if (direction[i] == -1)
		{
			//draw right face
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x-CUBE_SIZE,y+CUBE_SIZE,z+CUBE_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(x-CUBE_SIZE,y+CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y-CUBE_SIZE,z-CUBE_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(x-CUBE_SIZE,y-CUBE_SIZE,z+CUBE_SIZE);
			glEnd();
		}
	}

	freeTexture(white);
	freeTexture(red);
	freeTexture(blue);
	freeTexture(green);
	freeTexture(yellow);
	freeTexture(pink);
	
}

void Cube::rotateX(void) 
{
	rotate_X(-1);
}

void Cube::rotateXNeg(void)
{
	rotate_X(1);
}

/*
 * Stabilim noua directie inspre care fata trebuie sa se afle in
 * urma rotirii pe axa X pozitiva sau negativa
 */

void Cube::rotate_X(int dir)
{
	for (int i = 0; i < 6; i += 1)
	{
		switch(direction[i])
		{
			case 2 :
				direction[i] = dir * 3;
				break;
			case -2 :
				direction[i] = (-1)*dir*3;
				break;
			case 3 :
				direction[i] = (-1)*dir*2;
				break;
			case -3 :
				direction[i] = dir * 2;
				break;
			default :
				break;
		}
	}
}

void Cube::rotateY(void) 
{
	rotate_Y(-1);
}

void Cube::rotateYNeg(void)
{
	rotate_Y(1);
}

/*
 * Stabilim noua directie inspre care fata trebuie sa se afle in
 * urma rotirii pe axa Y pozitiva sau negativa
 */

void Cube::rotate_Y(int dir)
{
	for (int i = 0; i < 6; i += 1)
	{
		switch(direction[i])
		{
			case 1 :
				direction[i] = (-1) * dir * 3;
				break;
			case -1 :
				direction[i] = dir*3;
				break;
			case 3 :
				direction[i] = dir*1;
				break;
			case -3 :
				direction[i] = (-1) * dir * 1;
				break;
			default :
				break;
		}
	}
}

void Cube::rotateZ(void) 
{
	rotate_Z(-1);
}

void Cube::rotateZNeg(void)
{
	rotate_Z(1);
}

/*
 * Stabilim noua directie inspre care fata trebuie sa se afle in
 * urma rotirii pe axa Z pozitiva sau negativa
 */

void Cube::rotate_Z(int dir)
{
	for (int i = 0; i < 6; i += 1)
	{
		switch(direction[i])
		{
			case 1 :
				direction[i] = dir * 2;
				break;
			case -1 :
				direction[i] = (-1) * dir * 2;
				break;
			case 2 :
				direction[i] = (-1) * dir * 1;
				break;
			case -2 :
				direction[i] = dir * 1;
				break;
			default :
				break;
		}
	}
}