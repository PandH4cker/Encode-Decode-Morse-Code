/*************************************************************************/
/*** Authors : Raphael Dray, Alexandre de Sevin ***/
/*** Encode&Decode Morse Code ***/
/*** GitHub Link: https://github.com/MrrRaph/Encode-Decode-Morse-Code ***/
/***********************************************************************/

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
#define clrscr() printf("\e[1;1H\e[2J") //Définition en préprocesseur de la fonction d'effacement d'affichage

#define DOT '.'
#define DASH '-'
#define SEP '_'
#define GRAPHIC 18 //Valeur arbitraire
#define color(param) printf("\033[1;%dm", param) //Définition en préprocesseur de la fonction de changement de couleur du terminal
#define resetColor printf("\033[0m") //Définition en préprocesseur de la fonction de réinitialisation de la couleur du terminal
/** Définition des couleurs **/
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36

/* Structure de l'Arbre */
typedef struct Noeud 
{
	struct Noeud * dot;
	struct Noeud * dash;
	char character;
}Noeud, *Arbre;

Arbre new_node(); // Création d'un noeud
Arbre add_char(Arbre * tree, char * morse, char c); //Ajout d'un caractère dans l'arbre
Arbre initForMorse(); //Construction de l'arbre
char seekChar(Arbre tree, char * morse); //Recherche d'un caractère dans l'arbre
char * morseDecypher(Arbre tree, char * morse); //Décodage du corde morse
char * morseCypher(Arbre tree, char * text); //Encodage du code morse
char ** str_split(char * s, const char * ct); //Split une chaîne de caractère par un délimiteur (const char * ct) et renvoie sous forme de tableau
void morseTable(Arbre tree); //Affichage de la table morse
void destroyTree(Arbre tree); //Destruction de l'arbre
int mainProg(Arbre tree, int argc, char ** argv); //Fonction principale du programme
#endif