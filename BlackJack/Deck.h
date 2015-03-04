//
//  Deck.h
//  BlackJack
//
//  Created by Adrian Rangel on 3/4/15.
//  Copyright (c) 2015 ITESM. All rights reserved.
//

#ifndef BlackJack_Deck_h
#define BlackJack_Deck_h

using namespace std;

class Deck {
public:
    // Constructor
    Deck(char ss, char vv);
    // metodos modificadores
    void setSuit(char ss); void setValue(char vv);
    // metodos de acceso
    char getSuit(); char getValue();
    // otros métodos
    void muestra();
    static void dibujaPoligono(int xMin, int xMax, int yMin, int yMax); void draw(int x, int y);
private:
    // Atributos
    char s, v;
};

#endif
