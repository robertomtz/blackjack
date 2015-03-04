//
//  Deck.h
//  BlackJack
//
//  Created by Adrian Rangel on 3/4/15.
//  Copyright (c) 2015 ITESM. All rights reserved.
//

#ifndef BlackJack_Deck_h
#define BlackJack_Deck_h

#include <iostream>
#include <string.h>
using namespace std;
#include "Card.h"

class Deck
{
public:
    // Constructor
    Deck();

    // Otros Metodos
    char getSuit(int k);
    char getValue(int k);
    void shuffle();
    Card dealCard();
    char * str();
    //void dibuja();


private:
    // Atributos
    Card d[52]={
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A'), Card('C','A'),Card('C','A'),Card('C','A'),
        Card('C','A'), Card('C','A')
    };

};

#endif /* defined(__BlackJack__Deck__) */
