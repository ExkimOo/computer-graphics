#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

void myDisplay();
void drawCDALine(int x1, int y1, int x2, int y2, int size);
void drawBresenhamLine(int x1, int y1, int x2, int y2, int size);
void drawPseudoPixel(int x, int y, int size);
void reshape(int w, int h);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Jewish Star");

	gluOrtho2D(0, 1279, 0, 719);

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void myDisplay()
{
	glBegin(GL_POINTS);

	glColor3f(0.0f, 255.0f, 0.0f);
	drawCDALine(0, 179, 639, 179, 10);
	drawCDALine(0, 179, 639, 708, 10);
	drawCDALine(639, 708, 1279, 179, 10);
	
	glColor3f(255.0, 0.0f, 0.0f);
	drawBresenhamLine(0, 539, 1279, 539, 20);
	drawBresenhamLine(0, 539, 639, 0, 20);
	drawBresenhamLine(639, 0, 1279, 539, 20);

	glEnd();
	glFlush();
}

void drawCDALine(int x1, int y1, int x2, int y2, int size)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	float x = (float)x1;
	float y = (float)y1;

	drawPseudoPixel(x1, y1, size);
	drawPseudoPixel(x2, y2, size);

	if (dx == 0)
	{
		for (int i = 0; i < dy - size; i += size)
		{
			y += size;

			drawPseudoPixel(round(x), round(y), size);
		}
	}

	if (dy == 0)
	{
		for (int i = 0; i < dx - size; i += size)
		{
			x += size;

			drawPseudoPixel(round(x), round(y), size);
		}
	}

	if (dx >= dy)
	{
		float d = (float)dy / dx * size;
		for (int i = 0; i < dx - size; i += size)
		{
			x += size;
			y += d;

			drawPseudoPixel(round(float(x) / size) * size, round(float(y) / size) * size, size);
		}
	}
	else
	{
		float d = (float)dx / dy * size;
		for (int i = 0; i < dy - size; i += size)
		{
			x += size;
			x += d;

			drawPseudoPixel(round(float(x) / size) * size, round(float(y) / size) * size, size);
		}
	}
}

void drawBresenhamLine(int x1, int y1, int x2, int y2, int size)
{
	int deltaX = (x2 - x1);
	int deltaY = (y2 - y1);
	int delta, 
		dx, 
		dy, 
		t;

	if (deltaX >= 0)
	{
		dx = size;
	}
	else
	{
		dx = -size;
		deltaX = -deltaX;
	}

	if (deltaY >= 0)
	{
		dy = size;
	}
	else
	{
		dy = -size;
		deltaY = -deltaY;
	}
		
	int d = 0;
	if (deltaY >= deltaX)
	{
		t = deltaX << 1;
		delta = deltaY << 1;
	}
	else
	{
		t = deltaY << 1;
		delta = deltaX << 1;
	}

	int x = x1;	
	int y = y1;
	
	drawPseudoPixel(x, y, size);
	for (int i = 0; i < deltaX - size; i += size)
	{
		x += size;
		d += t;

		if (d > deltaX)
		{
			y += dy;
			d -= delta;
		}

		drawPseudoPixel(x, y, size);
	}
	
}

void drawPseudoPixel(int x, int y, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			glVertex2i(x + i, y + j);
		}
	}
}

void reshape(int w, int h)
{
	system("cls");
	std::cout << (GLfloat)w << " " << (GLfloat)h << std::endl;

	if (h == 0)
	{
		h = 1;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w > h)
	{
		float ratio = (float)w / h;
		gluOrtho2D(-ratio, ratio, -1, 1);
	}
	else
	{
		float ratio = (float)h / w;
		gluOrtho2D(-1, 1, -ratio, ratio);
	}

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}