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

    glColor3f(1,0,0);
    for(int i=0;i<=10;i++){
        point_2d p[4]={{i,0},{10,i},{10-i,10},{0,10-i}};
        drawPolygon(p,4);
    }
    /*
    static float a=0;
    point_2d p[360];
    color_2d col[360];
    float r=5,S;
    for(int i=0;i<360;i++){
        S=(float)i/57.3;
        if(i%20==0){
            if(r==5)r=4;
            else r=5;
        }
        p[i].x = r*cos(S+a);
        p[i].y = r*sin(S+a);
    }
    glColor3f(1,0,1);
    drawPolygon(p,360);
    a+=0.001;
    */
    /*
    //Menggambar bintang
    static float a=0;
    color_2d col[360];
    if(a==0){
        for(int i=0;i<5;i++){
            col[i].r = (float)rand()/RAND_MAX;
            col[i].b = (float)rand()/RAND_MAX;
            col[i].g = (float)rand()/RAND_MAX;
        }
    }
    point_2d p[360];
    float r=8,S;
    for(int i=0;i<10;i++){
        S=36*(float)i/57.3;
        if(r==8)r=3;
        else r=8;
        p[i].x = r*cos(S+a);
        p[i].y = r*sin(S+a);
    }
    glColor3f(1,1,1);
    FillPolygon(p,col,10);
    a+=0.001;
    */
    /*
    //menggambar pac-man
    static float a=0;
    static int b=0;
    point_2d p[360];
    float r=8,S;
    float c=30;
    if(b>100)c-30;
    else c=1;
    for(int i=0;i<360;i++){
        S=(float)i/57.3;
        if((i<c)|| (r>360-c)) r=0;
        else r=8;
        p[i].x = r*cos(S+a);
        p[i].y = r*sin(S+a);
    }
    glColor3f(1,1,1);
    drawLinePolygon(p,360);
    //a+=0.001;
    b=(b+1)%1000;
    */
    /* menggambar gelombang AM
    //menggambar grid
    glColor3f(0,0.6,0);
    //grid vertical;
    for(int i=0;i<360;i++){
        drawLine(i*20,-10,i*20,10);
    }
    //grid horizontal
    for(int i=-10;i<=10;i++){
        drawLine(0,i,360,i);
    }
    //menggambar sumbu x
    glColor3f(0,1,0);
    drawLine(0,0,360,0);

    //menggambar fungsi sinus
    static float s=0;
    point_2d p[360];
    for(int i=0;i<360;i++){
        float a=(float)i/57.3+s;
        p[i].x = (float)i;
        p[i].y = 5*sin(32*a+2*sin(8*a));
    }
    glColor3f(1,1,1);
    drawPolyLines(p,360);
    s+=0.001;
    */
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
    glutInitWindowSize(400,400);
    glutCreateWindow("Sky Night");
    glClearColor(0,0,0,0);
    gluOrtho2D(0,10,0,10);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
