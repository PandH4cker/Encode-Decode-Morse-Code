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
#define GRAPHIC 18
#define color(param) printf("\033[1;%dm", param)
#define resetColor printf("\033[0m")
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36

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
void morseTable(Arbre tree);
void destroyTree(Arbre tree);
int mainProg(Arbre tree, int argc, char ** argv);
#endif