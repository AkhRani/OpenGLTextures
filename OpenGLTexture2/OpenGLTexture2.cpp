// OpenGLTexture2.cpp
//
// Simple texturing using vertex arrays (OpenGL 1.2)
//
#include "stdafx.h"

#include <GL/glut.h>
#include <GL/GL.h>

#include <stdio.h>

typedef struct {
    GLfloat x, y, tx, ty;
} VertexInfo;

void SetupTexture()
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
};

void SetupArrays()
{
    static VertexInfo triangle[3] = {
        //   x,     y,   tx,   ty
        { 0.0f,  1.0f, 0.5f, 1.0f}, // top
        { 1.0f, -1.0f, 1.0f, 0.0f}, // bottom-right
        {-1.0f, -1.0f, 0.0f, 0.0f}, // bottom-left
    };

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(VertexInfo), &triangle[0].tx); 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(VertexInfo), &triangle[0].x); 
}


void onDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    SetupTexture();
    SetupArrays();
    glDrawArrays(GL_TRIANGLES, 0, 3);

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
    glutIdleFunc(onDisplay);
    glutKeyboardFunc(onKey);

    glEnable(GL_TEXTURE_2D);
    glutMainLoop();

    return 0;
}
