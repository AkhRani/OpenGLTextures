// OpenGLTexture1.cpp
//
// This is just about the simplest texturing example I can make.
//
#include "stdafx.h"

#include <GL/glut.h>
#include <GL/GL.h>

#include <stdio.h>

void onDisplay(void)
{
    static GLubyte checkerboard[16] = {
        // The first byte is the lower-left texel
        0xff, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0xff,
        0xff, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0xff,
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 4, 4, 0, GL_RED, GL_UNSIGNED_BYTE, checkerboard);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    // Top
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(0.0f, 1.0f);

    // bottom-right
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);

    // bottom-left
    glTexCoord2f(0.0f, 0.0f);
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
    glutInitWindowSize(480, 480);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKey);

    glEnable(GL_TEXTURE_2D);
    glutMainLoop();

    return 0;
}