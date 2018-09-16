#include <windows.h>
#include <Gl/glut.h>
float vx = 0;
float vy = 0;
float sx = 0;
float sy = 0.1;
float a = 0.0001;
void userdraw(){
    glBegin(GL_TRIANGLES);
    glVertex2f(10+vx,10+vy);
    glVertex2f(10+vx,30+vy);
    glVertex2f(30+vx,10+vy);
    glColor3f(1.0,1.0,1.0);
    glEnd();
    //sx = sx + a;
    sy = sy + a;
   // vx = vx+sx;
    vy = vy+sy;
    //sy = sy + a;
    if(vx >= 170 || vx <= -10){
        sx = -sx;
    }
    if(vy >= 170 || vy <= -15){
        sy = -sy;
    }

}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    userdraw();
    glutSwapBuffers();
}
int main(int argc,char* argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Praktikum 1");
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    gluOrtho2D(0,200,0,200);

    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
