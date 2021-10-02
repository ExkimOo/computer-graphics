#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>

#define PI 3.14159265358979323846

class Vertex
{

private:
	GLfloat x;
	GLfloat y;

public:
	Vertex()
	{
		x = -1;
		y = -1;
	}

	Vertex(GLfloat X, GLfloat Y)
	{
		x = X;
		y = Y;
	}

	GLfloat getX()
	{
		return x;
	}

	GLfloat getY()
	{
		return y;
	}

	GLfloat setX(GLfloat X)
	{
		x = X;
	}

	GLfloat setY(GLfloat Y)
	{
		x = Y;
	}

	Vertex operator-(Vertex subtrahend)
	{
		return Vertex(this->getX() - subtrahend.getX(), this->getY() - subtrahend.getY());
	}
};

void myDisplay();
Vertex rotate(Vertex dot, Vertex dot0, float degree);
Vertex translate(Vertex dot, Vertex d);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Ferris wheel");

	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0, 1279, 0, 719);

	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}

void myDisplay()
{
	system("cls");
	std::vector<std::vector<Vertex>> vertexes;
	vertexes.resize(3);
	
	vertexes[0].push_back(Vertex(640.0f, 360.0f));
	vertexes[0].push_back(Vertex(640.0f, 180.0f));

	vertexes[1].push_back(Vertex(640.0f, 180.0f));
	vertexes[1].push_back(Vertex(690.0f, 120.0f));
	vertexes[1].push_back(Vertex(590.0f, 120.0f));

	vertexes[2].push_back(Vertex(590.0f, 120.0f));
	vertexes[2].push_back(Vertex(590.0f, 90.0f));
	vertexes[2].push_back(Vertex(690.0f, 90.0f));
	vertexes[2].push_back(Vertex(690.0f, 120.0f));	

	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINES);
		glColor3f(255.0f, 255.0f, 255.0f);

		int angle = 60;
		for (int k = 0; k < 360; k += angle)
		{
			for (int i = 0; i < vertexes.size(); ++i)
			{
				for (std::vector<Vertex>::iterator it = vertexes[i].begin(); it != vertexes[i].end() - 1; ++it)
				{
					if (i != 0)
					{
						Vertex tmp1 = translate(*it, rotate(vertexes[0][1], vertexes[0][0], k) - vertexes[0][1]);
						Vertex tmp2 = translate(*(it + 1), rotate(vertexes[0][1], vertexes[0][0], k) - vertexes[0][1]);
						glVertex2f(tmp1.getX(), tmp1.getY());
						glVertex2f(tmp2.getX(), tmp2.getY());
					}
					else
					{
						glVertex2f(it->getX(), it->getY());
						Vertex tmp = rotate(vertexes[0][1], vertexes[0][0], k);
						glVertex2f(tmp.getX(), tmp.getY());
					}
				}
				if (i != 0)
				{
					Vertex first = translate(*vertexes[i].begin(), rotate(vertexes[0][1], vertexes[0][0], k) - vertexes[0][1]);
					Vertex last = translate(*(vertexes[i].end() - 1), rotate(vertexes[0][1], vertexes[0][0], k) - vertexes[0][1]);
					glVertex2f(first.getX(), first.getY());
					glVertex2f(last.getX(), last.getY());
				}
			}
		}
		vertexes[0][0] = rotate(vertexes[0][0], Vertex(640.0f, 360.0f), 15);
		Vertex delta = vertexes[0][1];
		vertexes[0][1] = rotate(vertexes[0][1], Vertex(640.0f, 360.0f), 15);
		delta = vertexes[0][1] - delta;
		for (int i = 1; i < vertexes.size(); ++i)
		{
			for (int j = 0; j < vertexes[i].size(); ++j)
			{
				vertexes[i][j] = translate(vertexes[i][j], delta);
			}
		}
		glEnd();
		glFlush();
		Sleep(100);
	}
}
	
Vertex rotate(Vertex dot, Vertex dot0, float degree)
{
	return Vertex(dot0.getX() + (dot.getX() - dot0.getX()) * cosf(PI * degree / 180) - (dot.getY() - dot0.getY()) * sinf(PI * degree / 180),
				  dot0.getY() + (dot.getX() - dot0.getX()) * sinf(PI * degree / 180) + (dot.getY() - dot0.getY()) * cosf(PI * degree / 180));
}

Vertex translate(Vertex dot, Vertex d)
{
	return Vertex(dot.getX() + d.getX(),
				  dot.getY() + d.getY());
}