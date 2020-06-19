#include <iostream>
#include <math.h>
#include <GL/freeglut.h>


class myCanvas {
public: 
	float orthoMin = -50;
	float orthoMax = 50;
	float parentSize = 8;
	float childSize = 3;
	float parentPosition = -50;
	float childPosition = -45;
	float deltaPosition = abs(abs(parentPosition) - abs(childPosition));

	int marginHorizontal = 20;
	int marginVertical = 15;

	void applyCanvas() {
		glBegin(GL_QUADS); 
		{
			glColor3ub(0, 0, 0);
			glVertex2f(orthoMin, orthoMin);
			glColor3ub(0, 0, 0);
			glVertex2f(orthoMin, orthoMax);
			glColor3ub(43, 43, 43);
			glVertex2f(orthoMax, orthoMax);
			glColor3ub(0, 0, 0);
			glVertex2f(orthoMax, orthoMin);
		}
		glEnd();
	}
};

class batikPattern {
public :
	float rectTextureSize = 0.5;

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

	void rectTexture(float x, float y) {
		glBegin(GL_POLYGON);
		{
			glVertex2f(x, y);
			glVertex2f(x, y + rectTextureSize);
			glVertex2f(x + rectTextureSize, y + rectTextureSize);
			glVertex2f(x + rectTextureSize, y);
		}
		glEnd();
	}

	void circTexture(float x, float y) {
		glBegin(GL_POINTS);
		{
			glVertex2f(x, y);
		}
		glEnd();
	}

	void backgroundTexture() {
		myCanvas canvas;

		glPointSize(3);

		canvas.applyCanvas();

		glColor3ub(51, 51, 51);

		for (int i = canvas.orthoMin; i < canvas.orthoMax; i++) {
			for (int j = canvas.orthoMin; j < canvas.orthoMax; j++) {
				if (i % 3 == 0) {

					if (j % 2 == 0) {
						circTexture(i, j);
					}

					if (j % 3 == 0) {
						rectTexture(i,j);
					}
				}
			}
		}
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
				batikObject.pattern(canvas.childSize, canvas.childPosition + posX, canvas.orthoMin + posY);
			}
			else {
				batikObject.pattern(canvas.parentSize, canvas.parentPosition - (canvas.deltaPosition * 2) + posX, canvas.orthoMin + posY);
				batikObject.pattern(canvas.childSize, canvas.parentPosition - canvas.deltaPosition + posX, canvas.orthoMin + posY);
			}

			posX += canvas.marginHorizontal;
		}

		posY += canvas.marginVertical;
	}

	glFlush();
}

int main(int argc, char** argv) {
	myCanvas canvas;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("TTS ~ Kelvin Kurniawan Oktavianto");

	glutDisplayFunc(renderObject);
	gluOrtho2D(canvas.orthoMin, canvas.orthoMax, canvas.orthoMin, canvas.orthoMax);

	glutMainLoop();

	return 0;
}