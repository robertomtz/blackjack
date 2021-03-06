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
int turno=1;
int turnoDealer=1;
int as=0;
int asDealer=0;
const float medida = 40;
float xRotate=1.0;

bool rotate3d=false;
bool stand=false;
bool fin=false;
bool deal=false;//checa que solo se pueda dealear una vez
bool ganoDealer=false;
bool shopas=false;
Deck deck = Deck();

void myTimer(int v)
{
    if (rotate3d) {
        xRotate=xRotate+1;
        if (xRotate >= 180) {
            xRotate = 0;
            rotate3d = false;
        }

    }
    glutPostRedisplay();
    glutTimerFunc(5, myTimer, 1);

}

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
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, c);
        glPopMatrix();
        x+=75;
    }
}

void drawHelpMessage(std::string text){
    glMatrixMode(GL_MODELVIEW);
    float x = 100;
    float y = 600;
    float size = 0.4;
    for (std::string::iterator i = text.begin(); i != text.end(); ++i) {
        glPushMatrix();
        glScaled(size, size, 0);
        glTranslatef(x, y, 0);
        char c = *i;
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, c);
        glPopMatrix();
        x+=75;
    }
}

void dibujaCarta3d(float x, float y){

    glPushMatrix();
    glTranslatef(x, y, -100);
    glRotatef(xRotate, 0, 1.0, 0);
    
    glColor3d(1, .5, .5);

    glBegin(GL_QUADS);
    //Arriba (amarillo)
    glVertex3f( -medida, medida*2.125, -medida );
    glVertex3f( -medida, medida*2.125,  medida );
    glVertex3f(  medida, medida*2.125,  medida );
    glVertex3f(  medida, medida*2.125, -medida );

    //Abajo (magenta)
    glVertex3f( -medida, -medida*2.125, -medida );
    glVertex3f(  medida, -medida*2.125, -medida );
    glVertex3f(  medida, -medida*2.125,  medida );
    glVertex3f( -medida, -medida*2.125,  medida );

    glColor3f(0, 0, 1);
    //Izquierda (azules)
    glVertex3f( -medida, -medida*2.125, -medida );
    glVertex3f( -medida, -medida*2.125,  medida );
    glVertex3f( -medida,  medida*2.125,  medida );
    glVertex3f( -medida,  medida*2.125, -medida );

    //Derecha (rojo y verde)
    glVertex3f( medida, -medida*2.125, -medida );
    glVertex3f( medida,  medida*2.125, -medida );
    glVertex3f( medida,  medida*2.125,  medida );
    glVertex3f( medida, -medida*2.125,  medida );

    
    glColor3d(1, .5, .5);
    //Frente blanco
    glVertex3f( -medida, -medida*2.125, medida );
    glVertex3f(  medida, -medida*2.125, medida );
    glVertex3f(  medida,  medida*2.125, medida );
    glVertex3f( -medida,  medida*2.125, medida );

    //Atrás blanco
    glVertex3f( -medida, -medida*2.125, -medida );
    glVertex3f( -medida,  medida*2.125, -medida );
    glVertex3f(  medida,  medida*2.125, -medida );
    glVertex3f(  medida, -medida*2.125, -medida );

    glEnd();

    glPopMatrix();
}

void dibujaMensaje3d(float g){

    glPushMatrix();
    glTranslatef(210, 250, -100);
    glRotatef(xRotate, 1.0, 0.0, 0);

    glBegin(GL_QUADS);
    glColor3f(0.4, g, 0.7);
    
    glColor3f(1, 0, 0);
    //Arriba
    glVertex3f( -medida*5.125, medida, -medida );
    glVertex3f( -medida*5.125, medida,  medida );
    glVertex3f(  medida*5.125, medida,  medida );
    glVertex3f(  medida*5.125, medida, -medida );

    //Abajo
    glVertex3f( -medida*5.125, -medida, -medida );
    glVertex3f(  medida*5.125, -medida, -medida );
    glVertex3f(  medida*5.125, -medida,  medida );
    glVertex3f( -medida*5.125, -medida,  medida );
glColor3f(0.4, g, 0.7);
    //Izquierda
    glVertex3f( -medida*5.125, -medida, -medida );
    glVertex3f( -medida*5.125, -medida,  medida );
    glVertex3f( -medida*5.125,  medida,  medida );
    glVertex3f( -medida*5.125,  medida, -medida );

    //Derecha =
    glVertex3f( medida*5.125, -medida, -medida );
    glVertex3f( medida*5.125,  medida, -medida );
    glVertex3f( medida*5.125,  medida,  medida );
    glVertex3f( medida*5.125, -medida,  medida );

    //Frente blanco
    glVertex3f( -medida*5.125, -medida, medida );
    glVertex3f(  medida*5.125, -medida, medida );
    glVertex3f(  medida*5.125,  medida, medida );
    glVertex3f( -medida*5.125,  medida, medida );

    //Atrás blanco
    glVertex3f( -medida*5.125, -medida, -medida );
    glVertex3f( -medida*5.125,  medida, -medida );
    glVertex3f(  medida*5.125,  medida, -medida );
    glVertex3f(  medida*5.125, -medida, -medida );
    glColor3f(1.0, 1.0, 1.0);
    glEnd();
    
    glPopMatrix();
}

void dibuja()
{
    //puntos actuales jugador y dealer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    char value;
    int vala = 0;
    as=0;
    for (int i = 0; i<=turno; i++) {
        value = deck.getValue(i);
        if ( value == 'A') {
            vala = 11;
            as++;
        }else if (value == 'K' || value == 'Q' || value == 'T' || value == 'J'){
            vala = 10;
        }else{
            vala = value - '0';
        }
        points += vala;
    }
    
    if (points>21) {
        while (as!=0 && points>21){
            points-=10;
            as--;
        }
        if (points>21){
            stand=true;
        }
    }
    
    if (points==21) {
        stand=true;
    }



    asDealer=0;
    if (stand) {
        while (!fin) {
            if (points>21) {
                scoreDealer++;
                ganoDealer = true;
                fin=true;
                deal=false;
            } else if (pointsDealer<17) {
                turnoDealer++;
                vala = 0;
                pointsDealer=0;
                for (int i = 5; i<=5+turnoDealer; i++) {
                    value = deck.getValue(i);
                    if ( value == 'A') {
                        vala = 11;
                        asDealer++;
                    }else if (value == 'K' || value == 'Q' || value == 'T' || value == 'J'){
                        vala = 10;
                    }else{
                        vala = value - '0';
                    }
                    pointsDealer += vala;
                    cout<<"turno dealer: "<<turnoDealer<<endl;
                    cout<<"carta: "<<value<<endl;
                    cout<<pointsDealer<<endl;
                }
            } else if (pointsDealer>21){
                while (asDealer>0 && pointsDealer>21){
                    pointsDealer-=10;
                    asDealer--;
                }
                cout<<"correccion As: "<<pointsDealer<<endl;
                if (pointsDealer>21) {
                    fin=true;
                    deal=false;
                    score++;
                }
            } else{
                fin=true;
                deal=false;
                if (points>pointsDealer) {
                    score++;
                }else{
                    scoreDealer++;
                    ganoDealer = true;
                }
            }
        }
    }

    glColor3d(1,1,1);
    if (fin && ganoDealer) {
        dibujaMensaje3d(1);
        if (shopas) {
            drawHelpMessage("New Deal?");
        }else{
            drawHelpMessage("You Lose");
        }
    }else if (fin && !ganoDealer){
        dibujaMensaje3d(0.7);
        if (shopas) {
            drawHelpMessage("New Deal?");
        }else{
            drawHelpMessage("You Win!!");
        }
    }else if(!fin && deal){
        dibujaMensaje3d(0.3);
        drawHelpMessage("Hit or stand");
    }else {
        dibujaMensaje3d(0);
        drawHelpMessage("New Deal?");
    }
    drawText(-400, 850, 0.5, "BLACKJACK", GLUT_BITMAP_9_BY_15);

    drawText(-1000, 850, 0.4, "SCORE " +toString(score), GLUT_BITMAP_9_BY_15);
    drawText(-100, 850, 0.4, "SCORE DEALER " +toString(scoreDealer), GLUT_BITMAP_9_BY_15);
    
    drawText(-1200, 400, 0.4, "DEALER ", GLUT_BITMAP_9_BY_15);
    drawText(-1200, -300, 0.4, "PLAYER", GLUT_BITMAP_9_BY_15);
    
    drawText(800, 400, 0.3, "DEALER " +toString(pointsDealer), GLUT_BITMAP_9_BY_15);
    drawText(800, -300, 0.3, "PLAYER " +toString(points), GLUT_BITMAP_9_BY_15);
    
    drawText(-1200, -900, 0.4, "D-DEAL H-HIT S-STAND ESC-SALIR", GLUT_BITMAP_9_BY_15);
    drawText(-1200, -1100, 0.4, "AUTOR: ROBERTO MTZ A01190757 ", GLUT_BITMAP_9_BY_15);
    drawText(-1200, -1230, 0.4, "AUTOR: ADRIAN RANGEL A01190871 ", GLUT_BITMAP_9_BY_15);
    
    points = 0;
    pointsDealer = 0;
    
    //PLAYER INFO
    glColor3d(1,1,1);
    drawText(-660, -300, 0.4,cToString(deck.getSuit(0)) +cToString(deck.getValue(0)), GLUT_BITMAP_9_BY_15);
    drawText(-410, -300, 0.4,cToString(deck.getSuit(1)) +cToString(deck.getValue(1)), GLUT_BITMAP_9_BY_15);
    if(turno>1){
        drawText(-160, -300, 0.4,cToString(deck.getSuit(2)) +cToString(deck.getValue(2)), GLUT_BITMAP_9_BY_15);
    }
    if(turno>2){
        drawText(90, -300, 0.4,cToString(deck.getSuit(3)) +cToString(deck.getValue(3)), GLUT_BITMAP_9_BY_15);
    }if (turno>3) {
        drawText(340, -300, 0.4,cToString(deck.getSuit(4)) +cToString(deck.getValue(4)), GLUT_BITMAP_9_BY_15);
    }
    
    
    glColor3d(0, .5, .5);
    dibujaCarta3d(-240,-85);
    dibujaCarta3d(-140,-85);
    if(turno>1){
        dibujaCarta3d(-40,-85);}
    if(turno>2){
        dibujaCarta3d(60,-85);}
    if(turno>3){
        dibujaCarta3d(160,-85);}
    
    
    
    //DEALER INFO
        glColor3d(1,1,1);
        drawText(-660, 400, 0.4,cToString(deck.getSuit(5)) +cToString(deck.getValue(5)), GLUT_BITMAP_9_BY_15);
    if(turnoDealer>1){
        drawText(-410, 400, 0.4,cToString(deck.getSuit(6)) +cToString(deck.getValue(6)), GLUT_BITMAP_9_BY_15);}
        if (turnoDealer>1) {
            drawText(-160, 400, 0.4,cToString(deck.getSuit(7)) +cToString(deck.getValue(7)), GLUT_BITMAP_9_BY_15);}
        if (turnoDealer>2) {
            drawText(90, 400, 0.4,cToString(deck.getSuit(8)) +cToString(deck.getValue(8)), GLUT_BITMAP_9_BY_15);}
        if (turnoDealer>3) {
            drawText(340, 400, 0.4,cToString(deck.getSuit(9)) +cToString(deck.getValue(9)), GLUT_BITMAP_9_BY_15);}
    
    
    glColor3d(1, .5, .5);
    dibujaCarta3d(-240,215);
    dibujaCarta3d(-140,215);
    if(turnoDealer>1){
        dibujaCarta3d(-40,215);}
    if(turnoDealer>2){
        dibujaCarta3d(60,215);}
    if(turnoDealer>3){
        dibujaCarta3d(160,215);}
    glColor3f(1.0, 1.0, 1.0);
    glutSwapBuffers();
}


void myKey(unsigned char theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
        case 'h':
        case 'H':
            rotate3d=true;
            if(turno<4 && !stand){
                turno++;
            } else{
                shopas=true;
            }
            break;
            
        case 's':
        case 'S':
            rotate3d=true;
            stand=true;
            break;
            
        case 'd':
        case 'D':
            rotate3d=true;
            if(!deal){
                deal=true;
                deck.shuffle();
                points=0;
                pointsDealer=0;
                turno=1;
                turnoDealer=1;
                stand=false;
                fin=false;
                ganoDealer=false;
                shopas=false;
            }
            break;
            
        case 27:
            exit(-1);
            //terminate the program
            break;
            
        default:
            break;		      // do nothing
    }
    glutPostRedisplay();
}


void reshape(int ancho, int alto)
{
    // Ventana
    glViewport(0, 0, ancho, alto);
    // Sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500, 500, -500, 500,100, 300.0 ); //izq, der, abajo, arriba, cerca, lejos
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);

}

int main(int argc, char *argv[])
{
    srand ( time(NULL) );
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE );
    glutCreateWindow("Blackjack A01190757 - A01190871");
    init();
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(myKey);
    glutDisplayFunc(dibuja);
    glutTimerFunc(5, myTimer, 1);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

