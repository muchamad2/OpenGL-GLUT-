// Include standard headers
#include <GL\glut.h>
#include <iostream>
#include <Math.h>
#define PHI  3.14159265f;
using namespace std;

typedef struct {
	float x, y;
}lokasi;

typedef struct {
	float r, g, b;
}the_color;

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 255.0); // set bg to black
}

void drawPoly(lokasi xy[], the_color tcolor[], int max, bool isSingle) {
	glBegin(GL_POLYGON);
	if (isSingle) {
		for (int i = 0; i < max; i++)
		{
			glColor3f(tcolor[0].r, tcolor[0].g, tcolor[0].b);
			glVertex2f(xy[i].x, xy[i].y);
		}
	}
	else {
		for (int i = 0; i < max; i++)
		{
			glColor3f(tcolor[i].r, tcolor[i].g, tcolor[i].b);
			glVertex2f(xy[i].x, xy[i].y);
		}
	}
	glEnd();
}

void Kanvas() {
	
	//flame
	static int count2=0;
	static bool boost=false, almost_die = false;
	if (count2 >= 300) {
		count2 = 0;
		if (almost_die)almost_die = false;
		else almost_die = true;
	}
	else count2++;

	lokasi flame[60];
	the_color flame_aura[1] = { 0.9,0.6,0.3 };
	int jari = 30, boost_long = 60;
	float x;

	for (int i = 0; i<60; i++) {
		x = (float)i * 6 / 180;
		x = x * PHI;
		flame[i].x = 250 + jari * cos(x);
		
		if (almost_die) {
			if(count2%3==0){
				if (boost)boost = false;
				else boost = true;
			}
		}
		else {
			boost_long = 60;
			boost = false;
		}

		if (boost)boost_long = 70;
		else boost_long = 30;

		if (i > 30) {
			flame[i].y = (jari + (float)rand() * boost_long / RAND_MAX) * sin(x);
			flame[i].y = flame[i].y + 200;
		}
		else flame[i].y = 200 + jari * sin(x);
	}
	drawPoly(flame, flame_aura, 60, true);

	//badan pesawat
	lokasi bp[4] = { {250,400},{ 400,100 },{ 250,200 },{ 100,100 } };
	the_color bp_color[1] = { {1,1,1} };
	drawPoly(bp, bp_color, 4, true);

	//pilot pesawat
	lokasi koor_kaca[60];
	the_color warna_kaca[1] = { 0,0,0 };
	for (int i = 0; i < 60; i++)
	{
		x = (float)i * 6 / 180;
		x = x * PHI;
		koor_kaca[i].x = 250 + (jari/2) * cos(x);
		koor_kaca[i].y = 320 + jari * sin(x);
	}
	drawPoly(koor_kaca, warna_kaca, 60, true);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	Kanvas();
	glutSwapBuffers();
}

int lebarLayar = 500, tinggiLayar = 500, WXpost = 50, WYpost = 50;

void startGLUT() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // enable double buffered mode
	glutInitWindowSize(lebarLayar, tinggiLayar);
	glutInitWindowPosition(WXpost, WYpost); //Initial window top-left corner
	glutCreateWindow("Primitive Graph");
	gluOrtho2D(0, 500, 0, 500);
	glutDisplayFunc(display); //register window callback handler for window repaint
	glutIdleFunc(display);
	initGL();
	glutMainLoop();
}
int main(int argc, char**argv) {
	int a;
	glutInit(&argc, argv);
	startGLUT();
}