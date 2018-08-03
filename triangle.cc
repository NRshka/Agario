#include "GL/freeglut.h"
#include "GL/gl.h"
#include "stdint.h"

// инициализация переменных цвета в 1.0
// треугольник - белый
float red=1.0f, blue=1.0f, green=1.0f;

typedef struct{
    float x;
    float y;
} VECTOR;

VECTOR speed{
    .x = 0,
    .y = 0
};
VECTOR acceleration{
    .x = 0,
    .y = 0
};

float friction = 0.0005f;
// угол поворота
float angle = 0.0f;
 
void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}

int sign(float n){
    return (n >= 0)?1:-1;
}

void renderScene(void) {
    speed.x += acceleration.x;
    speed.y += acceleration.y;
    if(acceleration.x != 0)
        acceleration.x -= sign(acceleration.x) * friction;
    if(acceleration.y != 0)
        acceleration.y -= sign(acceleration.y) * friction;

	// очистить буфер цвета и глубины.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнулить трансформацию
	glLoadIdentity();
	// установить камеру
	gluLookAt( 0.0f, 0.0f, 10.0f,
		   0.0f, 0.0f,  0.0f,
		   0.0f, 1.0f,  0.0f);
	//поворот на заданную величину
	//glRotatef(angle, 0.0f, 1.0f, 0.0f);
	// установить цвет модели
	glColor3f(red,green,blue);
	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0f + speed.x, -1.0f + speed.y, 0.0f);
		glVertex3f( 0.0f + speed.x,  1.0f + speed.y, 0.0f);
		glVertex3f( 1.0f + speed.x, -1.0f + speed.y, 0.0f);
	glEnd();
 
	glutSwapBuffers();
}
 
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}
 
void processSpecialKeys(int key, int x, int y) {
 
	switch(key) {
		case GLUT_KEY_F1 :
				red = 1.0;
				green = 0.0;
				blue = 0.0; 
                break;
		case GLUT_KEY_F2 :
				red = 0.0;
				green = 1.0;
				blue = 0.0; break;
		case GLUT_KEY_F3 :
				red = 0.0;
				green = 0.0;
				blue = 1.0; break;
        case GLUT_KEY_UP:
                acceleration.y += 0.01f;
                break;
        case GLUT_KEY_DOWN:
                acceleration.y -= 0.01f;
                break;
        case GLUT_KEY_RIGHT:
                acceleration.x += 0.01f;
                break;
        case GLUT_KEY_LEFT:
                acceleration.x -= 0.01f;
                break;
	}
}
 
int main(int argc, char **argv) {
 
	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Урок 4");
 
	// регистрация
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
 
	// обработка клавиш
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
 
	// основной цикл
	glutMainLoop();
 
	return 1;
}