#include "Mover.h"

Mover::Mover()
{
	for (int i = 0; i < 3; i += 1)
		for (int j = 0; j < 3; j += 1)
			for (int k = 0; k < 3; k += 1)
				cubes[i][j][k] = new Cube();
}

Mover::~Mover()
{
}

void Mover::rotateLocal(int type)
{
	switch(type)
	{
	case 1:
		rotateLocalZ(2);
		break;
	case 2:
		rotateLocalX(2);
		break;
	case 3:
		rotateLocalZNeg(0);
		break;
	case 4:
		rotateLocalXNeg(0);
		break;
	case 5:
		rotateLocalY(2);
		break;
	case 6:
		rotateLocalYNeg(0);
		break;
	case 7:
		rotateLocalZNeg(2);
		break;
	case 8:
		rotateLocalXNeg(2);
		break;
	case 9:
		rotateLocalZ(0);
		break;
	case 10:
		rotateLocalX(0);
		break;
	case 11:
		rotateLocalYNeg(2);
		break;
	case 12:
		rotateLocalY(0);
		break;
	default :
		break;
	}
}

void Mover::stepInto(int *left, int *right, int *dir, int step, int lEd, int rEd)
{
	for (int i = 0; i < step; i += 1)
	{
		switch(*dir)
		{
		case 0:
			*left -= 1;
			if (*left < lEd)
			{
				*left += 1;
				*dir = 3;
				*right += 1;
			}
			break;
		case 1:
			*right -= 1;
			if (*right < lEd)
			{
				*right += 1;
				*dir = 0;
				*left -= 1;
			}
			break;
		case 2:
			*left += 1;
			if (*left >= rEd)
			{
				*left -= 1;
				*dir = 1;
				*right -= 1;
			}
			break;
		case 3:
			*right += 1;
			if (*right >= rEd)
			{
				*right -= 1;
				*dir = 2;
				*left += 1;
			}
			break;
		default:
			break;
		}
	}
}

/*
 *
 * Mutam straturi de cuburi de pe latura X pozitiva.
 *
 */

void Mover::rotateLocalX(int x)
{
	int step, lEd = 0, rEd = 3, dir0 = 3, dir1 = 3, y0 = 0, y1 = 0, z0 = 0, z1 = 0;
	Cube *temp[3][3];

	temp[1][1] = cubes[x][1][1];
	cubes[x][1][1]->rotateX();
	for (int i = 0; i < 2; i += 1)
	{
		step = 2 - i * 2;
		dir0 = 3;
		dir1 = 3;
		lEd = i;
		rEd = 3 - i;
		y0 = lEd;
		y1 = lEd;
		z0 = lEd;
		z1 = lEd;
		stepInto(&y1, &z1, &dir1, step, lEd, rEd);
		for (int j = 0; j < step * 4; j += 1)
		{
			temp[y1][z1] = cubes[x][y0][z0];
			cubes[x][y0][z0]->rotateX();
			stepInto(&y0, &z0, &dir0, 1, lEd, rEd);
			stepInto(&y1, &z1, &dir1, 1, lEd, rEd);
		}
		for (int k = 0; k < 3; k += 1)
			for (int l = 0; l < 3; l += 1)
				cubes[x][k][l] = temp[k][l];
	}
}

/*
 *
 * Mutam straturi de cuburi de pa latura X negativa prin 3 succesiuni de mutari pe latura X pozitiva. - 3 mutari in  sens pozitiv ne aduc in aceeasi pozitie ca si cum ne-am muta o singura data in sens negativ
 *
 */

void Mover::rotateLocalXNeg(int x)
{
	rotateLocalX(x);
	rotateLocalX(x);
	rotateLocalX(x);
}

/*
 *
 * Mutam straturi de cuburi de pe latura Y pozitiva.
 *
 */

void Mover::rotateLocalY(int y)
{
	int step, lEd = 0, rEd = 3, dir0 = 3, dir1 = 3, x0 = 0, x1 = 0, z0 = 0, z1 = 0;
	Cube *temp[3][3];

	temp[1][1] = cubes[1][y][1];
	cubes[1][y][1]->rotateY();
	for (int i = 0; i < 2; i += 1)
	{
		step = 2 - i * 2;
		dir0 = 3;
		dir1 = 3;
		lEd = i;
		rEd = 3 - i;
		x0 = lEd;
		x1 = lEd;
		z0 = lEd;
		z1 = lEd;
		stepInto(&z1, &x1, &dir1, step, lEd, rEd);
		for (int j = 0; j < step * 4; j += 1)
		{
			temp[x1][z1] = cubes[x0][y][z0];
			cubes[x0][y][z0]->rotateY();
			stepInto(&z0, &x0, &dir0, 1, lEd, rEd);
			stepInto(&z1, &x1, &dir1, 1, lEd, rEd);
		}
		for (int k = 0; k < 3; k += 1)
			for (int l = 0; l < 3; l += 1)
				cubes[k][y][l] = temp[k][l];
	}
}

/*
 *
 * Mutam straturi de cuburi de pa latura Y negativa prin 3 succesiuni de mutari pe latura Y pozitiva. - 3 mutari in  sens pozitiv ne aduc in aceeasi pozitie ca si cum ne-am muta o singura data in sens negativ
 *
 */

void Mover::rotateLocalYNeg(int y)
{
	rotateLocalY(y);
	rotateLocalY(y);
	rotateLocalY(y);
}

/*
 *
 * Mutam straturi de cuburi de pe latura Z pozitiva.
 *
 */

void Mover::rotateLocalZ(int z)
{
	int step, lEd = 0, rEd = 3, dir0 = 3, dir1 = 3, y0 = 0, y1 = 0, x0 = 0, x1 = 0;
	Cube *temp[3][3];

	temp[1][1] = cubes[1][1][z];
	cubes[1][1][z]->rotateZ();
	for (int i = 0; i < 2; i += 1)
	{
		step = 2 - i * 2;
		dir0 = 3;
		dir1 = 3;
		lEd = i;
		rEd = 3 - i;
		y0 = lEd;
		y1 = lEd;
		x0 = lEd;
		x1 = lEd;
		stepInto(&x1, &y1, &dir1, step, lEd, rEd);
		for (int j = 0; j < step * 4; j += 1)
		{
			temp[x1][y1] = cubes[x0][y0][z];
			cubes[x0][y0][z]->rotateZ();
			stepInto(&x0, &y0, &dir0, 1, lEd, rEd);
			stepInto(&x1, &y1, &dir1, 1, lEd, rEd);
		}
		for (int k = 0; k < 3; k += 1)
			for (int l = 0; l < 3; l += 1)
				cubes[k][l][z] = temp[k][l];
	}
}

/*
 *
 * Mutam straturi de cuburi de pa latura Z negativa prin 3 succesiuni de mutari pe latura Z pozitiva. - 3 mutari in  sens pozitiv ne aduc in aceeasi pozitie ca si cum ne-am muta o singura data in sens negativ
 *
 */

void Mover::rotateLocalZNeg(int z)
{
	rotateLocalZ(z);
	rotateLocalZ(z);
	rotateLocalZ(z);
}

/*
 * functia redeseneaza fetele cubului o data ce am efectuat o mutare, fetele sunt redesenate pe rand utilizand functia drawFace din clasa Cube, fiecare fata se muta pe una dintre directiile X, y, Z in functie de tipul rotatie, iar unghiul de rotatie depinde de faptul daca rotatia se realizeaza in sensul pozitiv sau negativ al axei
 */
void Mover::drawCube(int type,GLfloat angle) {
	GLfloat x,y,z;
	int i,j,k;

	x=0-(CUBE_SIZE/2)*5;
	y=0-(CUBE_SIZE/2)*5;
	z=0-(CUBE_SIZE/2)*5;

	switch(type)
	{
	case 0:
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				for (k=0;k<3;k++)
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 1: 
  		glPushMatrix();
  		glRotatef(360-180*angle/M_PI,0.0f,0.0f,1.0f);
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				cubes[i][j][2]->drawFace(x+5*i,y+5*j,z+5*2);
  		glPopMatrix();
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				for (k=0;k<2;k++)
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 2: 
  		glPushMatrix();
  		glRotatef(360-180*angle/M_PI,1.0f,0.0f,0.0f);
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				cubes[2][i][j]->drawFace(x+5*2,y+5*i,z+5*j);
  		glPopMatrix();
		for (i=0;i<2;i++)
			for (j=0;j<3;j++)
				for (k=0;k<3;k++)
						cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 3: 
  		glPushMatrix();
  		glRotatef(360-180*angle/M_PI,0.0f,0.0f,-1.0f);
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				cubes[i][j][0]->drawFace(x+5*i,y+5*j,z);
  		glPopMatrix();
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				for (k=1;k<3;k++)
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 4: 
  		glPushMatrix();
  		glRotatef(360-180*angle/M_PI,-1.0f,0.0f,0.0f);
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				cubes[0][i][j]->drawFace(x,y+5*i,z+5*j);
  		glPopMatrix();
		for (i=1;i<3;i++)
			for (j=0;j<3;j++)
				for (k=0;k<3;k++)
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 5:
  		glPushMatrix();
  		glRotatef(360-180*angle/M_PI,0.0f,1.0f,0.0f);
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				cubes[i][2][j]->drawFace(x+5*i,y+5*2,z+5*j);
  		glPopMatrix();
		for (i=0;i<3;i++) 
			for (j=0;j<2;j++) 
				for (k=0;k<3;k++) 
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 6: 
  		glPushMatrix();
  		glRotatef(360-180*angle/M_PI,0.0f,-1.0f,0.0f);
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				cubes[i][0][j]->drawFace(x+5*i,y,z+5*j);
  		glPopMatrix();
		for (i=0;i<3;i++) 
			for (j=1;j<3;j++) 
				for (k=0;k<3;k++) 
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 7: 
  		glPushMatrix();
  		glRotatef(180*angle/M_PI,0.0f,0.0f,1.0f);
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				cubes[i][j][2]->drawFace(x+5*i,y+5*j,z+5*2);
  		glPopMatrix();
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				for (k=0;k<2;k++) 
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 8: 
  		glPushMatrix();
  		glRotatef(180*angle/M_PI,1.0f,0.0f,0.0f);
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				cubes[2][i][j]->drawFace(x+5*(2),y+5*i,z+5*j);
  		glPopMatrix();
		for (i=0;i<2;i++) 
			for (j=0;j<3;j++) 
				for (k=0;k<3;k++) 
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 9: 
  		glPushMatrix();
  		glRotatef(180*angle/M_PI,0.0f,0.0f,-1.0f);
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				cubes[i][j][0]->drawFace(x+5*i,y+5*j,z);
  		glPopMatrix();
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				for (k=1;k<3;k++) 
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 10: 
  		glPushMatrix();
  		glRotatef(180*angle/M_PI,-1.0f,0.0f,0.0f);
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				cubes[0][i][j]->drawFace(x,y+5*i,z+5*j);
  		glPopMatrix();
		for (i=1;i<3;i++) 
			for (j=0;j<3;j++) 
				for (k=0;k<3;k++) 
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 11: 
  		glPushMatrix();
  		glRotatef(180*angle/M_PI,0.0f,1.0f,0.0f);
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				cubes[i][2][j]->drawFace(x+5*i,y+5*2,z+5*j);
  		glPopMatrix();
		for (i=0;i<3;i++) 
			for (j=0;j<2;j++) 
				for (k=0;k<3;k++) 
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	case 12: 
  		glPushMatrix();
  		glRotatef(180*angle/M_PI,0.0f,-1.0f,0.0f);
		for (i=0;i<3;i++) 
			for (j=0;j<3;j++) 
				cubes[i][0][j]->drawFace(x+5*i,y,z+5*j);
  		glPopMatrix();
		for (i=0;i<3;i++)
			for (j=1;j<3;j++)
				for (k=0;k<3;k++)
					cubes[i][j][k]->drawFace(x+5*i,y+5*j,z+5*k);
	break;
	default:
		break;

	}
}
