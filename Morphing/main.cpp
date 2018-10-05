#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
typedef struct{
    float x,y;
}point_2d;
typedef struct{
    float r,g,b;
}color_2d;

typedef struct{
    float v[3];
}vector2d;
typedef struct{
    float m[3][3];
}matrix2d;
typedef struct{
    color_2d red = {1,0,0};
    color_2d green = {0,1,0};
    color_2d blue = {0,0,1};
}Color2d;

vector2d point2vector(point_2d p){
    vector2d vec;
    vec.v[0]=p.x;
    vec.v[1]=p.y;
    vec.v[2]=1;
    return vec;
}
  point_2d vector2point(vector2d vec){
    point_2d p;
    p.x=vec.v[0];
    p.y=vec.v[1];
    return p;
}
matrix2d createIdentity(){
    matrix2d mat;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            mat.m[i][j]=0;
        mat.m[i][i]=1;
    }
    return mat;
}
  matrix2d translationMt(float dx,float dy){
    matrix2d mat=createIdentity();
    mat.m[0][2]=dx;
    mat.m[1][2]=dy;
    return mat;
}
  matrix2d scalingMt(float sx,float sy){
    matrix2d mat=createIdentity();
    mat.m[0][0]=sx;
    mat.m[1][1]=sy;
    return mat;
}
  matrix2d rotationMt(float a){
    matrix2d mat=createIdentity();
    mat.m[0][0]=cos(a);
    mat.m[0][1]=-sin(a);
    mat.m[1][0]=sin(a);
    mat.m[1][1]=cos(a);
    return mat;
}
  vector2d operator*(matrix2d mt,vector2d vec){
    vector2d vec1;
    for(int i=0;i<3;i++){
        vec1.v[i] = 0;
        for(int j=0;j<3;j++){
            vec1.v[i] += mt.m[i][j]*vec.v[j];
        }
    }
    return vec1;
}
matrix2d operator*(matrix2d A,matrix2d B){
    matrix2d C;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            C.m[i][j]=0;
            for(int k=0;k<3;k++){
                C.m[i][j]+=A.m[i][k]*B.m[k][j];
            }
        }
    }
    return C;
}
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
void drawObject(point_2d p[], matrix2d mat,color_2d col, int n){
    point_2d p1[360];
    vector2d vec;
    for(int i=0;i<n;i++){
        vec=point2vector(p[i]);
        vec=mat*vec;
        p1[i]=vector2point(vec);
    }
    FillPolygon(p1,col,n);
}
void drawEarthEvo(){
    point_2d p[30];
    float r;
    for(int i=0;i<30;i++){
        r=(float)i*12/57.3;
        p[i].x = 10*cos(r);
        p[i].y = 10*sin(r);
    }
    matrix2d mt = scalingMt(8,8);
    color_2d w1 = {1,1,0};
    drawObject(p,mt,w1,30);

    static float a=0;
    vector2d vec;
    matrix2d mat2=rotationMt(a)*translationMt(180,0)*scalingMt(3, 3);
    color_2d w2={0,1,0};
    drawObject(p,mat2,w2,30);

    point_2d orbitbumi[30];
    matrix2d mat2a=scalingMt(18, 18);
    for(int i=0;i<30;i++){
        vec=point2vector(p[i]);
        vec=mat2a*vec;
        orbitbumi[i]=vector2point(vec);
    }
    drawPolygon(orbitbumi,30);

    matrix2d mat3=rotationMt(a)*translationMt(180,0)*rotationMt(3*a)*translationMt(70,0)*scalingMt(1.5, 1.5);
    color_2d w3={1,0.5,0};
    drawObject(p, mat3, w3, 30);

    point_2d orbitbulan[30];
    matrix2d mat3a=rotationMt(a)*translationMt(180,0)*scalingMt(7, 7);
    for(int i=0;i<30;i++){
        vec=point2vector(p[i]);
        vec=mat3a*vec;
        orbitbulan[i]=vector2point(vec);
    }
    drawPolygon(orbitbulan,30);

    a+=0.001;
}
point_2d interpolate2D(point_2d p1,point_2d p2,float a){
    point_2d p3;
    p3.x = (1-a)*p1.x+a*p2.x;
    p3.y = (1-a)*p1.y+a*p2.y;
    return p3;
}
void userDraw(){
    static float a=0,n=0.001;
    glColor3f(0,1,0);
    point_2d praSpear[] = {{30,5},{40,10},{33,15},{33,50},{35,100},
    {40,90},{38,120},{35,110},{30,130},{25,110},{23,120},{20,90},{25,100},{27,50},
    {27,15},{20,10}};
    //drawPolygon(praSpear,16);

    point_2d Abstract[] = {{30,5},{40,25},{40,30},{34,35},{34,100},{39,105},{39,110},{34,115},{30,118},
                            {26,115},{21,110},{21,105},{26,100},{26,35},{20,30},{20,25}};
    //drawPolygon(Abstract,16);
    point_2d obj3[16];
    for(int i=0;i<16;i++){
        obj3[i] = interpolate2D(Abstract[i],praSpear[i],a);
    }
    drawPolygon(obj3,16);
    a+=n;
    if(a<0||a>1)
        n *= -1;

}
void display(){
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    userDraw();
    glutSwapBuffers();
    //glFlush();
}
int main(int argc,char*argv[]){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Sky Night");
    gluOrtho2D(0,200,0,200);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
