#include <iostream> // Opsional
#include <math.h>
#include <GL/freeglut.h>


class myCanvas {
public: 
	float orthoMin = -50;
	float orthoMax = 50;
	float marginHorizontal = 20;
	float marginVertical = 20;
	float parentSize = 8;
	float childSize = 3;
	float parentPosition = -50;
	float childPosition = -45;
	float deltaPosition = abs(abs(parentPosition) - abs(childPosition));
};

class batikPattern {
public :
	void pattern(int size, int startPointX, int startPointY) {
		glLineWidth(10);
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < size; i++) {
				glVertex2f(startPointX + i, (startPointY + i) - 1);
				glVertex2f(startPointX + i, (startPointY + i));
			}

			for (int i = 0; i < size; i++) {
				glVertex2f(startPointX + i + size, (startPointY + (size - i)) - 1);
				glVertex2f(startPointX + i + size, (startPointY + (size - i)) - 2);
			}
			for (int i = 0; i < size - 1; i++) {
				glVertex2f(startPointX * 2 + (size * 2 - (startPointX + i + 2)), (startPointY - i) - 1);
				glVertex2f(startPointX * 2 + (size * 2 - (startPointX + i + 2)), (startPointY - i) - 2);
			}
			for (int i = 0; i < size; i++) {
				glVertex2f(startPointX * 2 + (size - (startPointX + i + 1)), (startPointY - size + i));
				glVertex2f(startPointX * 2 + (size - (startPointX + i + 1)), (startPointY - size + i) + 1);
			}
		}
		glEnd();

	}

	void pattern(int size, int startPointX, int startPointY, bool subPattern) {
		if (subPattern) {
			glLineWidth(10);
			glColor3f(1, 1, 1);
			glBegin(GL_LINE_STRIP);
			{
				for (int i = 0; i < size; i++) {
					glVertex2f(startPointX + i, (startPointY + i) - 1);
					glVertex2f(startPointX + i, (startPointY + i));
				}

				for (int i = 0; i < size; i++) {
					glVertex2f(startPointX + i + size, (startPointY + (size - i)) - 1);
					glVertex2f(startPointX + i + size, (startPointY + (size - i)) - 2);
				}
				for (int i = 0; i < size - 1; i++) {
					glVertex2f(startPointX * 2 + (size * 2 - (startPointX + i + 2)), (startPointY - i) - 1);
					glVertex2f(startPointX * 2 + (size * 2 - (startPointX + i + 2)), (startPointY - i) - 2);
				}
				for (int i = 0; i < size; i++) {
					glVertex2f(startPointX * 2 + (size - (startPointX + i + 1)), (startPointY - size + i));
					glVertex2f(startPointX * 2 + (size - (startPointX + i + 1)), (startPointY - size + i) + 1);
				}
			}
			glEnd();
		}
	}

	void backgroundTexture() {
		myCanvas canvas;

		glPointSize(3);

		glBegin(GL_POINTS);
		glColor3ub(82, 82, 82);
		for (int i = canvas.orthoMin; i < canvas.orthoMax; i++) {
			for (int j = canvas.orthoMin; j < canvas.orthoMax; j++) {
				if (i % 3 == 0) {
					if (j % 2 == 0) {
						glVertex2f(i, j);
					}
				}
			}
		}
		glEnd();
	}
};



void renderObject() {
	glClear(GL_COLOR_BUFFER_BIT);

	batikPattern batikObject;
	myCanvas canvas;

	float posX = 0;
	float posY = 0;

	batikObject.backgroundTexture();

	for (int i = 0; i < 15; i++) {
		posX = 0;
		for (int j = 0; j < 15; j++) {
			if (i % 2 == 0) {
				batikObject.pattern(canvas.parentSize, canvas.parentPosition + posX, canvas.orthoMin + posY);
				batikObject.pattern(canvas.childSize, canvas.childPosition + posX, canvas.orthoMin + posY, true);
			}
			else {
				batikObject.pattern(canvas.parentSize, canvas.parentPosition - canvas.deltaPosition + posX, canvas.orthoMin + posY);
				batikObject.pattern(canvas.childSize, canvas.parentPosition - canvas.deltaPosition + posX, canvas.orthoMin + posY, true);
			}

			posX += canvas.marginHorizontal;
		}

		posY += canvas.marginHorizontal;
	}

	glFlush();
}


int main(int argc, char** argv) {
	myCanvas canvas;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("TTS ~ Kelvin Kurniawan");

	glutDisplayFunc(renderObject);
	gluOrtho2D(canvas.orthoMin, canvas.orthoMax, canvas.orthoMin, canvas.orthoMax);

	glutMainLoop();

	return 0;
}