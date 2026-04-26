#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

// Global tracking variable (Following faculty format)
float moveX = 0.0f;

// --- Cloud Helper Function ---
void drawPixelCloud(float x, float y) {
    float b = 15.0f; // block/step size
    glColor3f(1.0f, 1.0f, 1.0f);

    // Row 1 - bottom
    glBegin(GL_POLYGON);
        glVertex2f(x,        y);
        glVertex2f(x + 7*b,  y);
        glVertex2f(x + 7*b,  y + b);
        glVertex2f(x,        y + b);
    glEnd();
    // Row 2
    glBegin(GL_POLYGON);
        glVertex2f(x + b,    y + b);
        glVertex2f(x + 6*b,  y + b);
        glVertex2f(x + 6*b,  y + 2*b);
        glVertex2f(x + b,    y + 2*b);
    glEnd();
    // Row 3
    glBegin(GL_POLYGON);
        glVertex2f(x + 2*b,  y + 2*b);
        glVertex2f(x + 5*b,  y + 2*b);
        glVertex2f(x + 5*b,  y + 3*b);
        glVertex2f(x + 2*b,  y + 3*b);
    glEnd();
    // Row 4 - top
    glBegin(GL_POLYGON);
        glVertex2f(x + 3*b,  y + 3*b);
        glVertex2f(x + 4*b,  y + 3*b);
        glVertex2f(x + 4*b,  y + 4*b);
        glVertex2f(x + 3*b,  y + 4*b);
    glEnd();
}

void drawScene() {
    glClearColor(0.05f, 0.91f, 0.892f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup Perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 800);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // --- GROUND ---
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.75f, 0.1f);
    glVertex2f(0.0f, 515.0f);
    glVertex2f(0.0f, 100.0f);
    glVertex2f(600.0f, 100.0f);
    glVertex2f(600.0f, 515.0f);
    glEnd();

    // --- WALLS ---
    float thickness = 10.0f;
    // Bottom Wall
    glBegin(GL_QUADS); glColor3f(0.1f, 0.4f, 0.1f);
    glVertex2f(0.0f, 100.0f); glVertex2f(600.0f, 100.0f);
    glVertex2f(600.0f, 100.0f + thickness); glVertex2f(0.0f, 100.0f + thickness); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 100.0f); glVertex2f(600.0f, 100.0f);
    glVertex2f(600.0f, 100.0f + thickness); glVertex2f(0.0f, 100.0f + thickness); glEnd();

    // Top Wall
    glBegin(GL_QUADS); glColor3f(0.1f, 0.4f, 0.1f);
    glVertex2f(0.0f, 515.0f - thickness); glVertex2f(600.0f, 515.0f - thickness);
    glVertex2f(600.0f, 515.0f); glVertex2f(0.0f, 515.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 515.0f - thickness); glVertex2f(600.0f, 515.0f - thickness);
    glVertex2f(600.0f, 515.0f); glVertex2f(0.0f, 515.0f); glEnd();

    // Left Wall
    glBegin(GL_QUADS); glColor3f(0.1f, 0.4f, 0.1f);
    glVertex2f(0.0f, 100.0f); glVertex2f(thickness, 100.0f);
    glVertex2f(thickness, 515.0f); glVertex2f(0.0f, 515.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 100.0f); glVertex2f(thickness, 100.0f);
    glVertex2f(thickness, 515.0f); glVertex2f(0.0f, 515.0f); glEnd();

    // Right Wall
    glBegin(GL_QUADS); glColor3f(0.1f, 0.4f, 0.1f);
    glVertex2f(600.0f - thickness, 100.0f); glVertex2f(600.0f, 100.0f);
    glVertex2f(600.0f, 515.0f); glVertex2f(600.0f - thickness, 515.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(600.0f - thickness, 100.0f); glVertex2f(600.0f, 100.0f);
    glVertex2f(600.0f, 515.0f); glVertex2f(600.0f - thickness, 515.0f); glEnd();

    glLineWidth(1.5f);

    // --- MANSION ---
    // Left Quad
    glBegin(GL_QUADS); glColor3f(0.9f, 0.8f, 0.6f);
    glVertex2f(197.5f, 400.0f); glVertex2f(242.5f, 400.0f); glVertex2f(242.5f, 470.0f); glVertex2f(197.5f, 470.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(197.5f, 400.0f); glVertex2f(242.5f, 400.0f); glVertex2f(242.5f, 470.0f); glVertex2f(197.5f, 470.0f); glEnd();
    // Middle Quad
    glBegin(GL_QUADS); glColor3f(0.9f, 0.8f, 0.6f);
    glVertex2f(242.5f, 400.0f); glVertex2f(357.5f, 400.0f); glVertex2f(357.5f, 560.0f); glVertex2f(242.5f, 560.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(242.5f, 400.0f); glVertex2f(357.5f, 400.0f); glVertex2f(357.5f, 560.0f); glVertex2f(242.5f, 560.0f); glEnd();
    // Right Quad
    glBegin(GL_QUADS); glColor3f(0.9f, 0.8f, 0.6f);
    glVertex2f(357.5f, 400.0f); glVertex2f(402.5f, 400.0f); glVertex2f(402.5f, 470.0f); glVertex2f(357.5f, 470.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(357.5f, 400.0f); glVertex2f(402.5f, 400.0f); glVertex2f(402.5f, 470.0f); glVertex2f(357.5f, 470.0f); glEnd();

    // Left Roof
    glBegin(GL_QUADS); glColor3f(0.5f, 0.07f, 0.08f);
    glVertex2f(190.0f, 470.0f); glVertex2f(242.5f, 470.0f); glVertex2f(242.5f, 500.0f); glVertex2f(197.5f, 500.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(190.0f, 470.0f); glVertex2f(242.5f, 470.0f); glVertex2f(242.5f, 500.0f); glVertex2f(197.5f, 500.0f); glEnd();
    // Middle Roof
    glBegin(GL_QUADS); glColor3f(0.5f, 0.07f, 0.08f);
    glVertex2f(235.0f, 560.0f); glVertex2f(365.5f, 560.0f); glVertex2f(357.5f, 600.0f); glVertex2f(242.5f, 600.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(235.0f, 560.0f); glVertex2f(365.5f, 560.0f); glVertex2f(357.5f, 600.0f); glVertex2f(242.5f, 600.0f); glEnd();
    // Right Roof
    glBegin(GL_QUADS); glColor3f(0.5f, 0.07f, 0.08f);
    glVertex2f(357.5f, 470.0f); glVertex2f(410.0f, 470.0f); glVertex2f(402.5f, 500.0f); glVertex2f(357.5f, 500.0f); glEnd();
    glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(357.5f, 470.0f); glVertex2f(410.0f, 470.0f); glVertex2f(402.5f, 500.0f); glVertex2f(357.5f, 500.0f); glEnd();

    // --- HARD CODED WINDOWS ---
    // (Collapsed onto single lines to save space)
    glBegin(GL_QUADS); glColor3f(0.0f, 0.5f, 1.0f); glVertex2f(207.5f, 422.5f); glVertex2f(232.5f, 422.5f); glVertex2f(232.5f, 447.5f); glVertex2f(207.5f, 447.5f); glEnd();
    glLineWidth(3.0f); glBegin(GL_LINE_LOOP); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(207.5f, 422.5f); glVertex2f(232.5f, 422.5f); glVertex2f(232.5f, 447.5f); glVertex2f(207.5f, 447.5f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINES); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(220.0f, 422.5f); glVertex2f(220.0f, 447.5f); glVertex2f(207.5f, 435.0f); glVertex2f(232.5f, 435.0f); glEnd();

    glBegin(GL_QUADS); glColor3f(0.0f, 0.5f, 1.0f); glVertex2f(367.5f, 422.5f); glVertex2f(392.5f, 422.5f); glVertex2f(392.5f, 447.5f); glVertex2f(367.5f, 447.5f); glEnd();
    glLineWidth(3.0f); glBegin(GL_LINE_LOOP); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(367.5f, 422.5f); glVertex2f(392.5f, 422.5f); glVertex2f(392.5f, 447.5f); glVertex2f(367.5f, 447.5f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINES); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(380.0f, 422.5f); glVertex2f(380.0f, 447.5f); glVertex2f(367.5f, 435.0f); glVertex2f(392.5f, 435.0f); glEnd();

    glBegin(GL_QUADS); glColor3f(0.0f, 0.5f, 1.0f); glVertex2f(252.5f, 497.5f); glVertex2f(277.5f, 497.5f); glVertex2f(277.5f, 522.5f); glVertex2f(252.5f, 522.5f); glEnd();
    glLineWidth(3.0f); glBegin(GL_LINE_LOOP); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(252.5f, 497.5f); glVertex2f(277.5f, 497.5f); glVertex2f(277.5f, 522.5f); glVertex2f(252.5f, 522.5f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINES); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(265.0f, 497.5f); glVertex2f(265.0f, 522.5f); glVertex2f(252.5f, 510.0f); glVertex2f(277.5f, 510.0f); glEnd();

    glBegin(GL_QUADS); glColor3f(0.0f, 0.5f, 1.0f); glVertex2f(287.5f, 497.5f); glVertex2f(312.5f, 497.5f); glVertex2f(312.5f, 522.5f); glVertex2f(287.5f, 522.5f); glEnd();
    glLineWidth(3.0f); glBegin(GL_LINE_LOOP); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(287.5f, 497.5f); glVertex2f(312.5f, 497.5f); glVertex2f(312.5f, 522.5f); glVertex2f(287.5f, 522.5f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINES); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(300.0f, 497.5f); glVertex2f(300.0f, 522.5f); glVertex2f(287.5f, 510.0f); glVertex2f(312.5f, 510.0f); glEnd();

    glBegin(GL_QUADS); glColor3f(0.0f, 0.5f, 1.0f); glVertex2f(322.5f, 497.5f); glVertex2f(347.5f, 497.5f); glVertex2f(347.5f, 522.5f); glVertex2f(322.5f, 522.5f); glEnd();
    glLineWidth(3.0f); glBegin(GL_LINE_LOOP); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(322.5f, 497.5f); glVertex2f(347.5f, 497.5f); glVertex2f(347.5f, 522.5f); glVertex2f(322.5f, 522.5f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINES); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(335.0f, 497.5f); glVertex2f(335.0f, 522.5f); glVertex2f(322.5f, 510.0f); glVertex2f(347.5f, 510.0f); glEnd();

    glBegin(GL_QUADS); glColor3f(0.0f, 0.5f, 1.0f); glVertex2f(252.5f, 422.5f); glVertex2f(277.5f, 422.5f); glVertex2f(277.5f, 447.5f); glVertex2f(252.5f, 447.5f); glEnd();
    glLineWidth(3.0f); glBegin(GL_LINE_LOOP); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(252.5f, 422.5f); glVertex2f(277.5f, 422.5f); glVertex2f(277.5f, 447.5f); glVertex2f(252.5f, 447.5f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINES); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(265.0f, 422.5f); glVertex2f(265.0f, 447.5f); glVertex2f(252.5f, 435.0f); glVertex2f(277.5f, 435.0f); glEnd();

    glBegin(GL_QUADS); glColor3f(0.0f, 0.5f, 1.0f); glVertex2f(322.5f, 422.5f); glVertex2f(347.5f, 422.5f); glVertex2f(347.5f, 447.5f); glVertex2f(322.5f, 447.5f); glEnd();
    glLineWidth(3.0f); glBegin(GL_LINE_LOOP); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(322.5f, 422.5f); glVertex2f(347.5f, 422.5f); glVertex2f(347.5f, 447.5f); glVertex2f(322.5f, 447.5f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINES); glColor3f(0.2f, 0.1f, 0.05f); glVertex2f(335.0f, 422.5f); glVertex2f(335.0f, 447.5f); glVertex2f(322.5f, 435.0f); glVertex2f(347.5f, 435.0f); glEnd();

    // DOOR
    glBegin(GL_QUADS); glColor3f(0.2f, 0.1f, 0.0f); glVertex2f(285.0f, 400.0f); glVertex2f(315.0f, 400.0f); glVertex2f(315.0f, 450.0f); glVertex2f(285.0f, 450.0f); glEnd();
    glLineWidth(2.0f); glBegin(GL_LINE_LOOP); glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(285.0f, 400.0f); glVertex2f(315.0f, 400.0f); glVertex2f(315.0f, 450.0f); glVertex2f(285.0f, 450.0f); glEnd();
    glBegin(GL_QUADS); glColor3f(0.9f, 0.7f, 0.0f); glVertex2f(308.0f, 420.0f); glVertex2f(312.0f, 420.0f); glVertex2f(312.0f, 425.0f); glVertex2f(308.0f, 425.0f); glEnd();

    glPushMatrix();

        glTranslatef(moveX, 0.0f, 0.0f); // moving along x-axis

        drawPixelCloud(50.0f, 600.0f);
        drawPixelCloud(300.0f, 620.0f);
        drawPixelCloud(150.0f, 700.0f);

    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    moveX += 1.0f;
    if( moveX > 600.0f ){
        moveX = -450.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(15, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mansion Scenario");

    glutDisplayFunc(drawScene);
    glutTimerFunc(20, update, 0);

    glutMainLoop();
    return 0;
}
