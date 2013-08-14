// OpenGLTexture4.cpp
//
// Generating different textures from the same data
//
#include "stdafx.h"

#include <GL/glut.h>
#include <GL/GL.h>

#include <stdio.h>

typedef struct {
    GLfloat x, y, tx, ty;
} VertexInfo;

#define TEXTURE_WIDTH   4
#define TEXTURE_HEIGHT  4

void SetupTexture(GLenum format)
{
    static GLubyte checkerboard[TEXTURE_WIDTH * TEXTURE_HEIGHT] = {
        // The first byte is the lower-left texel
        0xff, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0xff,
        0xff, 0x00, 0xff, 0x00,
        0x00, 0xff, 0x00, 0xff,
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, format, GL_UNSIGNED_BYTE, checkerboard);
};

void SetupArrays()
{
    static VertexInfo triangle[3] = {
        //   x,      y,   tx,   ty
        { 0.0f,   0.5f, 0.5f, 1.0f}, // top
        { -0.25f, 0.0f, 0.0f, 0.0f}, // bottom-left
        { 0.25f,  0.0f, 1.0f, 0.0f}, // bottom-right
    };

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(VertexInfo), &triangle[0].tx); 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(VertexInfo), &triangle[0].x); 
}


void onDisplay(void)
{
    GLint mode;

    glClear(GL_COLOR_BUFFER_BIT);

    SetupArrays();
    glMatrixMode(GL_MODELVIEW);

    SetupTexture(GL_RED);
    glTranslatef(-.75f, 0.f, 0.f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SetupTexture(GL_GREEN);
    glTranslatef(0.5f, 0.f, 0.f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SetupTexture(GL_BLUE);
    glTranslatef(0.5f, 0.f, 0.f);
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKey);

    glEnable(GL_TEXTURE_2D);
    glutMainLoop();

    return 0;
}