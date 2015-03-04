
//
//  Deck.cpp
//  BlackJack
//
//  Created by Adrian Rangel on 3/4/15.
//  Copyright (c) 2015 ITESM. All rights reserved.
//

#include "Deck.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

Deck:: Deck() {}

int Deck::getIndex(){
    return index;
}
void Deck::resetIndex(){
    index = 0;
}
char Deck::getSuit(int k) {
    return d[k].getSuit();
}
char Deck::getValue(int k) {
    return d[k].getValue();
}
void Deck::shuffle() {
    random_shuffle(&d[0], &d[52]);
}
Card Deck::dealCard() {
    Card card = d[index];
    index++;
    return card;
};