#include <iostream> // Opsional
#include <math.h>
#include <GL/freeglut.h>

float orthoMin = -50;
float orthoMax = 50;

float orthoSize = abs(orthoMin) + abs(orthoMax);

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

void subPattern(int size, int startPointX, int startPointY) {
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

void backgroundTexture() {
	glPointSize(3);

	glBegin(GL_POINTS);
	glColor3ub(82, 82, 82);
	for (int i = orthoMin; i < orthoMax; i++) {
		for (int j = orthoMin; j < orthoMax; j++) {
			if (i % 3 == 0) {
				if (j % 2 == 0) {
					glVertex2f(i, j);
				}
			}
		}
	}
	glEnd();
}

void renderObject() {
	float posX = 0;
	float posY = 0;

	backgroundTexture();

	for (int i = 0; i < 15; i++) {
		posX = 0;
		for (int j = 0; j < 15; j++) {
			if (i % 2 == 0) {
				pattern(8, -50 + posX, orthoMin + posY);
				subPattern(4, -46 + posX, orthoMin + posY);
			}
			else {
				pattern(8, -60 + posX, orthoMin + posY);
				subPattern(4, -56 + posX, orthoMin + posY);
			}

			posX += 20;
		}

		posY += 12;
	}

	glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("TTS ~ Kelvin Kurniawan");

	glutDisplayFunc(renderObject);
	gluOrtho2D(orthoMin, orthoMax, orthoMin, orthoMax);

	glutMainLoop();

	return 0;
}