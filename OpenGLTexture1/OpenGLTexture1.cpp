// OpenGLTexture1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <GL/glut.h>
#include <GL/GL.h>

#include <stdio.h>

void onDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    glutSwapBuffers();
}

void onKey(unsigned char key, int x, int y)
{
    exit(0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKey);

    glutMainLoop();

    return 0;
}