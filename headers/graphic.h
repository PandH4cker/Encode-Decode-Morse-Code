#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
#include "morse.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS 25
#define DELAY_TIME 1000.0f/FPS

int graphicInterface(Arbre tree); //Interface graphique du programme
int SDLnIMGnTTF_Initialize(); //Initialisation de la SDL2, IMG et TTF
bool isInRegion(int x, int y, int xInf, int xSup, int yInf, int ySup);
char ** str_split(char * s, const char * ct);
SDL_Texture * loadTexture(const char * file, SDL_Renderer * renderer); //Chargement de texture
SDL_Texture * renderText(const char * text, const char * fontName, SDL_Color color, int fontSize, SDL_Renderer * renderer); //Copie du texte sur le rendu
void renderTextureClip(SDL_Texture * texture, SDL_Renderer * renderer, SDL_Rect dest, SDL_Rect * clip); //Copie de la texture clipée sur le rendu
void renderTexture(SDL_Texture * texture, SDL_Renderer * renderer, int x, int y, SDL_Rect * clip); //Copie de la texture sur le rendu
void cleanUp(SDL_Window * window, SDL_Renderer * renderer);
#endif