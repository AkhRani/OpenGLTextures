// OpenGLTexture3.cpp
//
// Manually specifying mipmaps.
//
#include "stdafx.h"

#include <GL/glut.h>
#include <GL/GL.h>

#include <stdio.h>

typedef struct {
    GLfloat x, y, tx, ty;
} VertexInfo;

#define TEXTURE_REPEAT  70
#define TEXTURE_WIDTH   7
#define TEXTURE_HEIGHT  7

void SetupTexture()
{
     // Notice extra byte added for alignment.
    static GLubyte crossLevel0[8 * TEXTURE_HEIGHT] = {
        // The first byte is the lower-left texel
        0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0,
        0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0,
        0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0,
        0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0,
        0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0,
        0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0,
        0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0,
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RED, GL_UNSIGNED_BYTE, crossLevel0);

    static GLubyte crossLevel1[4 * TEXTURE_HEIGHT/2] = {
        0xff, 0x00, 0xff, 0, 
        0x00, 0xff, 0x00, 0, 
        0xff, 0x00, 0xff, 0, 
    };
    // Try changing GL_RED to GL_GREEN or GL_BLUE in the following line,
    // and see what effect it has as you increase TEXTURE_REPEAT.
    glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA8, TEXTURE_WIDTH/2, TEXTURE_HEIGHT/2, 0, GL_RED, GL_UNSIGNED_BYTE, crossLevel1);

    static GLubyte crossLevel2[4 * TEXTURE_HEIGHT/4] = {
        0x80, 0, 0, 0,
    };
    glTexImage2D(GL_TEXTURE_2D, 2, GL_RGBA8, TEXTURE_WIDTH/4, TEXTURE_HEIGHT/4, 0, GL_RED, GL_UNSIGNED_BYTE, crossLevel2);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
};

void SetupArrays()
{
    static VertexInfo triangle[3] = {
        //   x,     y,   tx,   ty
        { 0.0f,  1.0f, TEXTURE_REPEAT / 2.0f, TEXTURE_REPEAT * 1.0f}, // top
        { 1.0f, -1.0f, TEXTURE_REPEAT * 1.0f, 0.0f},                // bottom-right
        {-1.0f, -1.0f, 0.0f, 0.0f},                                 // bottom-left
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
