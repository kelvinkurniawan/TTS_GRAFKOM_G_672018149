#include <iostream>
#include <math.h>
#include <GL/freeglut.h>

class myColor {
public:
	/* Set color variable */
	GLfloat PrimaryColor[3] = { 1, 1, 1 };
	GLubyte SecondaryColor[3] = { 51, 51, 51 };
	GLfloat Black[3] = { 0, 0, 0 };
	GLubyte _options_canvasGrad[3] = { 55, 55, 55 }; // Gradient color for canvas
};

class myCanvas {
public: 
	/* Windows size */
	float windowHeight = 600;
	float windowWidth = 600;

	/* Window position*/
	float windowPositionX = 360;
	float windowPositionY = 0;

	float orthoMin = -50; // Ortho size - min
	float orthoMax = 50;  // Ortho size - max
	float parentSize = 8; // Size for parent pattern
	float childSize = 3; // Size for child pattern
	float parentPosition = -50; // Starting position of parent pattern
	float childPosition = -45; // Starting position of child pattern
	float deltaPosition = abs(abs(parentPosition) - abs(childPosition)); // absolute value of the parent and child distance

	// Margin of every pattern
	int marginHorizontal = 20;
	int marginVertical = 15;

	/* Create Canvas */
	void applyCanvas() {

		myColor color;

		glBegin(GL_QUADS); // Using quads to create canvas
		{
			glColor3fv(color.Black);
			glVertex2f(orthoMin, orthoMin);
			glColor3fv(color.Black);
			glVertex2f(orthoMin, orthoMax);
			glColor3ubv(color._options_canvasGrad); // Applying gradient
			glVertex2f(orthoMax, orthoMax);
			glColor3fv(color.Black);
			glVertex2f(orthoMax, orthoMin);
		}
		glEnd();
	}
};

class batikPattern {
public :
	float rectTextureSize = 0.5; // Set rectangle size for background texture

	void pattern(int size, int startPointX, int startPointY) {

		myColor color;

		glLineWidth(10); // Set line width
		glColor3fv(color.PrimaryColor);

		// Create pattern using line loop
		glBegin(GL_LINE_LOOP);
		{
			// x+ y+ pattern
			for (int i = 0; i < size; i++) {
				glVertex2f(startPointX + i, (startPointY + i) - 1);
				glVertex2f(startPointX + i, (startPointY + i));
			}

			// x+ y- pattern
			for (int i = 0; i < size; i++) {
				glVertex2f(startPointX + i + size, (startPointY + (size - i)) - 1);
				glVertex2f(startPointX + i + size, (startPointY + (size - i)) - 2);
			}

			// x- y- pattern
			for (int i = 0; i < size - 1; i++) {
				glVertex2f(startPointX * 2 + (size * 2 - (startPointX + i + 2)), (startPointY - i) - 1);
				glVertex2f(startPointX * 2 + (size * 2 - (startPointX + i + 2)), (startPointY - i) - 2);
			}

			// x- y+ pattern
			for (int i = 0; i < size; i++) {
				glVertex2f(startPointX * 2 + (size - (startPointX + i + 1)), (startPointY - size + i));
				glVertex2f(startPointX * 2 + (size - (startPointX + i + 1)), (startPointY - size + i) + 1);
			}
		}
		glEnd();

	}

	// Component for texture
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

	void applyBackgroundTexture() {
		myCanvas canvas;
		myColor color;

		glPointSize(3);

		canvas.applyCanvas(); // Applying the canvas

		glColor3ubv(color.SecondaryColor); // Applying secondary color

		for (int i = canvas.orthoMin; i < canvas.orthoMax; i++) {
			for (int j = canvas.orthoMin; j < canvas.orthoMax; j++) {
				if (i % 3 == 0) {

					if (j % 2 == 0) { 
						circTexture(i, j); // Applying circle texture
					}

					if (j % 3 == 0) {
						rectTexture(i, j); // Applying circle rectangle
					}

				}
			}
		}
	}
};

void renderObject() {

	batikPattern batikObject; // Create batikObject from batikPattern
	myCanvas canvas;

	glClear(GL_COLOR_BUFFER_BIT);
	
	int numbersOfPattern = 15;
	float posX = 0; // Declare increment variable - horizontal
	float posY = 0; // Declare increment variable - vertical

	batikObject.applyBackgroundTexture(); // Applying all off background texture

	/* Applying the pattern */

	for (int i = 0; i < numbersOfPattern; i++) {

		posX = 0; // Reset variable value

		for (int j = 0; j < numbersOfPattern; j++) {
			if (i % 2 == 0) {
				batikObject.pattern(canvas.parentSize, canvas.parentPosition + posX, canvas.orthoMin + posY);
				batikObject.pattern(canvas.childSize, canvas.childPosition + posX, canvas.orthoMin + posY);
			}
			else {
				batikObject.pattern(canvas.parentSize, canvas.parentPosition - (canvas.deltaPosition * 2) + posX, canvas.orthoMin + posY);
				batikObject.pattern(canvas.childSize, canvas.parentPosition - canvas.deltaPosition + posX, canvas.orthoMin + posY);
			}

			posX += canvas.marginHorizontal; // Increment
		}

		posY += canvas.marginVertical; // Increment
	}

	glFlush();
}

int main(int argc, char** argv) {
	myCanvas canvas;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(canvas.windowWidth, canvas.windowWidth);
	glutInitWindowPosition(canvas.windowPositionX, canvas.windowPositionY);
	glutCreateWindow("TTS ~ Kelvin Kurniawan Oktavianto");

	glutDisplayFunc(renderObject);
	gluOrtho2D(canvas.orthoMin, canvas.orthoMax, canvas.orthoMin, canvas.orthoMax);

	glutMainLoop();

	return 0;
}