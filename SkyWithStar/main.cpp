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
void drawPolygon(point_2d p[],int n){
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x,p[i].y);
    }
    glEnd();
}
void drawPolygon(point_2d p[],color_2d c,int n){
    glColor3f(c.r,c.g,c.b);
    glBegin(GL_POLYGON);
    for(int i=0;i<n;i++){
        glVertex2f(p[i].x,p[i].y);
    }
    glEnd();
}
void drawPolygon(point_2d p[],color_2d c[],int n){
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
    point_2d p[]={{0,0},{300,0},{300,200},{0,200}};
    color_2d c[] = {{0,0,1},{0,0,1},{0,0,0},{0,0,0}};
    drawPolygon(p,c,4);

    static point_2d bintang[200];
    static int d_size[200];
    static bool sw = true;
    if(sw){
        for(int i=0;i<200;i++){
            bintang[i].x = 300*(float)rand()/RAND_MAX;
            bintang[i].y = 200*(float)rand()/RAND_MAX;
            d_size[i] = 1+rand()%3;
        }
    }
    sw = false;
    for(int i=0;i<200;i++){
        glPointSize(d_size[i]);
        float r = (float)rand()/RAND_MAX;
        if(r<0.05)
            glColor3f(0,0,0);
        else
            glColor3f(1,1,1);
        drawDot(bintang[i].x,bintang[i].y);
    }

    point_2d bulan[60];
    float sdt;
    color_2d bulan_c = {1,1,1};
    for(int i=0;i<60;i++){
        sdt=(float)i*57.3;
        bulan[i].x = 260+12*cos(sdt);
        bulan[i].y = 180+12*sin(sdt);
    }
    static point_2d mt;
    static bool st = false;
    if(st == false){
        int r = rand()%1000;
        if(r<10){
            st = true;
            mt.x = 300*(float)rand()/RAND_MAX;
            mt.y = 200;
        }
    }
    else{
        glPointSize(4);
        drawDot(mt.x,mt.y);
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex2f(mt.x,mt.y);
        glVertex2f(mt.x+10,mt.y+10);
        glEnd();
        mt.x -= 0.3;
        mt.y -= 0.3;
        if(mt.y < 60)
            st = false;
    }
    drawPolygon(bulan,bulan_c,60);

    point_2d laut[]={{0,0},{300,0},{300,60},{0,60}};
    color_2d laut_c[] = {{0,0,0},{0,0,0},{0,0,1},{0,0,1}};
    drawPolygon(laut,laut_c,4);

        for(int i=0;i<10;i++){
        float r = (float)rand()/RAND_MAX;
        if(r<0.1){
            glBegin(GL_LINES);
            glColor3f(0,0,0.65);
            glVertex2f(0,60-i);
            glVertex2f(300,60-i);
            glEnd();
        }

    }


    for(int i=0;i<60;i++){
        sdt=(float)i*57.3;
        bulan[i].x = 260+(8+8*(float)rand()/RAND_MAX)*cos(sdt);
        bulan[i].y = 40+9*sin(sdt);
    }
    drawPolygon(bulan,bulan_c,60);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    userDraw();
    glutSwapBuffers();
}
int main(int argc,char*argv[]){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("Sky Night");
    glClearColor(0,0,0,0);
    gluOrtho2D(0,300,0,200);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
