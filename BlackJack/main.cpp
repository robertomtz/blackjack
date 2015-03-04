#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <ctime>
#include "Card.h"
#include "Deck.h"

int score=0;
int scoreDealer=0;
int points=0;
int pointsDealer=0;
Deck deck = Deck();

void init()
{
    // Para que las paredes se vean sólidas (no transparentes)
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    
    
}


std::string cToString(char a){
    std::stringstream ss;
    ss << a;
    return ss.str();
}

std::string toString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

void drawText(float x, float y, float size, std::string text, void* font) {
    glMatrixMode(GL_MODELVIEW);
    for (std::string::iterator i = text.begin(); i != text.end(); ++i)
    {
        glPushMatrix();
        glScaled(size, size, 0);
        glTranslatef(x, y, 0);
        char c = *i;
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
        glPopMatrix();
        x+=75;
    }
}

void dibuja()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    drawText(-400, 850, 0.5, "BLACKJACK", GLUT_BITMAP_9_BY_15);
    
    drawText(-1000, 850, 0.4, "SCORE " +toString(score), GLUT_BITMAP_9_BY_15);
    drawText(-100, 850, 0.4, "SCORE DEALER " +toString(scoreDealer), GLUT_BITMAP_9_BY_15);
    
    drawText(-1200, 400, 0.4, "DEALER ", GLUT_BITMAP_9_BY_15);
    drawText(-1200, -300, 0.4, "PLAYER", GLUT_BITMAP_9_BY_15);
    
    drawText(800, 400, 0.3, "DEALER " +toString(points), GLUT_BITMAP_9_BY_15);
    drawText(800, -300, 0.3, "PLAYER " +toString(pointsDealer), GLUT_BITMAP_9_BY_15);
    
    drawText(-1200, -900, 0.4, "D-DEAL H-HIT S-STAND ESC-SALIR", GLUT_BITMAP_9_BY_15);
    drawText(-1200, -1200, 0.4, "AUTOR: ROBERTO MTZ A01190757 ", GLUT_BITMAP_9_BY_15);
    
    
    glColor3d(1,1,1);
    points = 0;
    pointsDealer = 0;

    drawText(-660, 400, 0.4,cToString(deck.getSuit(0)) +cToString(deck.getValue(0)), GLUT_BITMAP_9_BY_15);
    drawText(-410, 400, 0.4,cToString(deck.getSuit(1)) +cToString(deck.getValue(1)), GLUT_BITMAP_9_BY_15);
    drawText(-160, 400, 0.4,cToString(deck.getSuit(2)) +cToString(deck.getValue(2)), GLUT_BITMAP_9_BY_15);
    drawText(90, 400, 0.4,cToString(deck.getSuit(3)) +cToString(deck.getValue(3)), GLUT_BITMAP_9_BY_15);
    drawText(340, 400, 0.4,cToString(deck.getSuit(4)) +cToString(deck.getValue(4)), GLUT_BITMAP_9_BY_15);

    char value;
    int vala = 0;
    for (int i = 0; i<=4; i++) {
        value = deck.getValue(i);
        if ( value == 'A') {
            vala = 11;
        }else if (value == 'K' || value == 'Q' || value == 'T' || value == 'J'){
            vala = 10;
        }else{
            vala = value - '0';
        }
        points += vala;
    }

    drawText(-660, -300, 0.4,cToString(deck.getSuit(5)) +cToString(deck.getValue(5)), GLUT_BITMAP_9_BY_15);
    drawText(-410, -300, 0.4,cToString(deck.getSuit(6)) +cToString(deck.getValue(6)), GLUT_BITMAP_9_BY_15);
    drawText(-160, -300, 0.4,cToString(deck.getSuit(7)) +cToString(deck.getValue(7)), GLUT_BITMAP_9_BY_15);
    drawText(90, -300, 0.4,cToString(deck.getSuit(8)) +cToString(deck.getValue(8)), GLUT_BITMAP_9_BY_15);
    drawText(340, -300, 0.4,cToString(deck.getSuit(9)) +cToString(deck.getValue(9)), GLUT_BITMAP_9_BY_15);

    vala = 0;
    for (int i = 5; i<=9; i++) {
        value = deck.getValue(i);
        if ( value == 'A') {
            vala = 11;
        }else if (value == 'K' || value == 'Q' || value == 'T' || value == 'J'){
            vala = 10;
        }else{
            vala = value - '0';
        }
        pointsDealer += vala;
    }


    
    
    glColor3d(1, .5, .5);
    glRectd(-200, 300, -280, 130);
    glRectd(-100, 300, -180, 130);
    glRectd(   0, 300,  -80, 130);
    glRectd( 100, 300,   20, 130);
    glRectd( 200, 300,  120, 130);
    
    
    glColor3d(0, .5, .5);
    glRectd(-200, 20, -280, -150);
    glRectd(-100, 20, -180, -150);
    glRectd(   0, 20,  -80, -150);
    glRectd( 100, 20,   20, -150);
    glRectd( 200, 20,  120, -150);
    
    glPushMatrix() ;
    glTranslated(0, 0, 0);
   
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int ancho, int alto)
{
    // Ventana
    glViewport(0, 0, ancho, alto);
    // Sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500, 500, -500, 500,1,12 ); //izq, der, abajo, arriba, cerca, lejos
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char *argv[])
{
    srand ( time(NULL) );
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE );
    glutCreateWindow("Blackjack A01190757");
    init();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

