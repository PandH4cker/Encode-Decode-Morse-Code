#ifndef MORSE_H
#define MORSE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <conio.h>
#endif
#define clrscr() printf("\e[1;1H\e[2J")

#define DOT '.'
#define DASH '-'
#define SEP '_'

typedef struct Noeud 
{
	struct Noeud * dot;
	struct Noeud * dash;
	char character;
}Noeud, *Arbre;

Arbre new_node();
Arbre add_char(Arbre * tree, char * morse, char c);
Arbre initForMorse();
char seekChar(Arbre tree, char * morse);
char * morseDecypher(Arbre tree, char * morse);
char * morseCypher(Arbre tree, char * text);
bool isDot(Arbre tree);
void morseTable();
void destroyTree(Arbre tree);
#endif