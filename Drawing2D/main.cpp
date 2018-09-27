#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
typedef struct{
    float x,y;
}point_2d;
typedef struct{
    float r,g,b;
}color_2d;
typedef struct{
    float v[3];
}vector_2d;
void drawLine(float x1,float y1,float x2, float y2){
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}
void drawPolyLines(point_2d p[],int n){
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x,p[i].y);
    }
    glEnd();
}
void drawPolygon(point_2d p[],int n){
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x,p[i].y);
    }
    glEnd();
}

void FillPolygon(point_2d p[],int n){
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x,p[i].y);
    }
    glEnd();
}
void FillPolygon(point_2d p[],color_2d c,int n){
    glColor3f(c.r,c.g,c.b);
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x,p[i].y);
    }
    glEnd();
}
void FillPolygon(point_2d p[],color_2d c[],int n){
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++){
        glColor3f(c[i].r,c[i].g,c[i].b);
        glVertex2f(p[i].x,p[i].y);
    }
    glEnd();
}
void drawDot(float x,float y){
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}

void userDraw(){
    float speed = 0.01;

    point_2d lingkaran[360];
    float r1 = 10;
    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(3**t+85);
        lingkaran[i].x = r1*sin(t+speed);
        lingkaran[i].y = r1*cos(t+speed);
    }
    glColor3f(0,0,0);
    FillPolygon(lingkaran,360);

    point_2d circle[360];
    float r = 10;
    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(3**t+85);
        circle[i].x = (r-8)*sin(t+speed);
        circle[i].y = r*cos(t+speed);
    }
    glColor3f(0.7,0,0);
    FillPolygon(circle,360);

    point_2d circle2[360];
    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(t+85);
        circle2[i].x = 11*cos(r)*sin(t+65+speed);
        circle2[i].y = 8*sin(r)*cos(t+speed);
    }
    glColor3f(0.7,0,0);
    FillPolygon(circle2,360);

    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(t+85);
        circle2[i].x = 11*cos(r)*sin(t-65+speed);
        circle2[i].y = 8*sin(r)*cos(t+speed);
    }
    glColor3f(0.7,0,0);
    FillPolygon(circle2,360);

    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(t+85);
        circle2[i].x = 11*cos(r)*sin(t+65+speed);
        circle2[i].y = 8*sin(r)*cos(t+speed);
    }
    glColor3f(0,0,0);
    drawPolygon(circle2,360);

    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(t+85);
        circle2[i].x = 11*cos(r)*sin(t-65+speed);
        circle2[i].y = 8*sin(r)*cos(t+speed);
    }
    glColor3f(0,0,0);
    drawPolygon(circle2,360);
    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(3**t+85);
        circle[i].x = (r-8)*sin(t+speed);
        circle[i].y = r*cos(t+speed);
    }
    glColor3f(0,0,0);
    drawPolygon(circle,360);

    for(int i=0;i<360;i++){
        float t=(float)i/57.3;
        //r = 10*cos(3**t+85);
        lingkaran[i].x = (r1-9)*sin(t+speed);
        lingkaran[i].y = (r1-9)*cos(t+speed);
    }
    glColor3f(0,0,0);
    FillPolygon(lingkaran,360);


}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    userDraw();
    glutSwapBuffers();
}
int main(int argc,char*argv[]){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("Sky Night");
    glClearColor(1,1,1,1);
    gluOrtho2D(-10,10,-10,10);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
