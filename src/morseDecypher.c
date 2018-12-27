#include "../headers/morse.h"

Arbre new_node()
{
	Noeud * node = malloc(sizeof(*node));
	if(!node)
	{
		fprintf(stderr, "Node creation failure\n");
		return NULL;
	}

	node->dot = NULL;
	node->dash = NULL;
	node->character = '\0';

	return node;
}

Arbre add_char(Arbre * tree, char * morse, char c)
{
	if(!morse || !tree)
	{
		fprintf(stderr, "Unable to add a character.\n");
		return NULL;
	}

	if(!*tree)
	{
		*tree = new_node(*tree);
		if(!*tree)
		{
			fprintf(stderr, "Unable to create node\n");
			return NULL;
		}
	}

	if(!*morse)
	{
		(*tree)->character = c;
		return *tree;
	}

	if(*morse == DOT)
		return add_char(&(*tree)->dot, ++morse, c);
	if(*morse == DASH)
		return add_char(&(*tree)->dash, ++morse, c);
	return NULL;
}

char seekChar(Arbre tree, char * morse)
{
	if(!tree)
		return '?';
	if(!*morse)
		return tree->character;
	if(*morse == DOT)
		return seekChar(tree->dot, ++morse);
	if(*morse == DASH)
		return seekChar(tree->dash, ++morse);
	return '?';
}

char * morseDecypher(Arbre tree, char * morse)
{
	char * current = morse;
	char * parsed = malloc(sizeof(char) * (strlen(morse)+1));

	if(!parsed)
	{
		fprintf(stderr, "Unable to alloc memory\n");
		return NULL;
	}

	char * current_parsed = parsed;
	int done = 0;
	while(!done)
	{
		while(*current && *current != SEP)
			++current;

		if(!*current)
			done = 1;

		else
			*current = '\0';
		if(strcmp(morse, " ") != 0)
			*current_parsed = seekChar(tree, morse);
		else
			*current_parsed = ' ';
		++current_parsed;
		++current;
		morse = current;
	}
	*current_parsed = '\0';
	return parsed;
}

char * morseCypher(Arbre tree, char * text)
{
	int i = 0, find = 0;
	char *parsed = malloc(sizeof(char) * 4 * (strlen(text)+1));
	if(!parsed)
	{
		fprintf(stderr, "Unable to alloc memory\n");
		return NULL;
	}
	size_t size = 54;
	char *morseCode[] = {".-\0", "-...\0", "-.-.\0", "-..\0", ".\0", "..-.\0", "--.\0",
						   "....\0", "..\0", ".---\0", "-.-\0", ".-..\0", "--\0", "-.\0",
						   "---\0", ".--.\0", "--.-\0", ".-.\0", "...\0", "-\0", "..-\0",
						   "...-\0", ".--\0", "-..-\0", "-.--\0", "--..\0", "-...-\0",
						   ".----\0", "..---\0", "...--\0", "....-\0", ".....\0", 
						   "-....\0", "--...\0", "---..\0", "----.\0", "-----\0",
						   ".-.-.-\0", "--..--\0", "..--..\0", "-..-.\0", ".----.\0",
						   "-.-.--\0", "-.-.-.\0", "---...\0", ".-.-.\0", "-....-\0",
						   "-...-\0", "-.--.\0", "-.--.-\0", "..--.-\0", "...-..-\0",
						   ".-..-.\0", ".--.-.\0", ".-...\0"};
	char * current_parsed = parsed;
	while(text[i])
	{
		char c = toupper(text[i]);
		if(c == ' ')
		{
			strcat(current_parsed, " \0");
			i++;
			continue;
		}
		for(int k = 0; k < size; k++)
		{
			if(seekChar(tree, morseCode[k]) == c)
			{
				find = 1;
				strcat(current_parsed, morseCode[k]);
				break;
			}
		}
		if(!find)
			strcat(current_parsed, "?\0");


		i++;
		if(text[i] != '\0' && text[i] != ' ')
			strcat(current_parsed, "_\0");
		find = 0;

	}
	return parsed;
}

Arbre initForMorse()
{
	Arbre tree = NULL;
	add_char(&tree, ".-\0", 'A');
	add_char(&tree, "-...\0", 'B');
	add_char(&tree, "-.-.\0", 'C');
	add_char(&tree, "-..\0", 'D');
	add_char(&tree, ".\0", 'E');
	add_char(&tree, "..-.\0", 'F');
	add_char(&tree, "--.\0", 'G');
	add_char(&tree, "....\0", 'H');
	add_char(&tree, "..\0", 'I');
	add_char(&tree, ".---\0", 'J');
	add_char(&tree, "-.-\0", 'K');
	add_char(&tree, ".-..\0", 'L');
	add_char(&tree, "--\0", 'M');
	add_char(&tree, "-.\0", 'N');
	add_char(&tree, "---\0", 'O');
	add_char(&tree, ".--.\0", 'P');
	add_char(&tree, "--.-\0", 'Q');
	add_char(&tree, ".-.\0", 'R');
	add_char(&tree, "...\0", 'S');
	add_char(&tree, "-\0", 'T');
	add_char(&tree, "..-\0", 'U');
	add_char(&tree, "...-\0", 'V');
	add_char(&tree, ".--\0", 'W');
	add_char(&tree, "-..-\0", 'X');
	add_char(&tree, "-.--\0", 'Y');
	add_char(&tree, "--..\0", 'Z');
	add_char(&tree, ".----\0", '1');
	add_char(&tree, "..---\0", '2');
	add_char(&tree, "...--\0", '3');
	add_char(&tree, "....-\0", '4');
	add_char(&tree, ".....\0", '5');
	add_char(&tree, "-....\0", '6');
	add_char(&tree, "--...\0", '7');
	add_char(&tree, "---..\0", '8');
	add_char(&tree, "----.\0", '9');
	add_char(&tree, "-----\0", '0');
	add_char(&tree, ".-.-.-\0", '.');
	add_char(&tree, "--..--\0", ',');
	add_char(&tree, "..--..\0", '?');
	add_char(&tree, "-..-.\0", '/');
	add_char(&tree, ".----.\0", '\'');
	add_char(&tree, "-.-.--\0", '!');
	add_char(&tree, "-.-.-.\0", ';');
	add_char(&tree, "---...\0", ':');
	add_char(&tree, ".-.-.\0", '+');
	add_char(&tree, "-....-\0", '-');
	add_char(&tree, "-...-\0", '=');
	add_char(&tree, "-.--.\0", '(');
	add_char(&tree, "-.--.-\0", ')');
	add_char(&tree, "..--.-\0", '_');
	add_char(&tree, "...-..-\0", '$');
	add_char(&tree, ".-..-.\0", '"');
	add_char(&tree, ".--.-.\0", '@');
	return tree;	
}

void morseTable(Arbre tree)
{
	clrscr();
	color(BLUE);
	puts("\t-----------------");
	puts("\t|  MORSE TABLE  |");
	printf("\t-----------------\n\n");
	resetColor;
	int j;
	char c;
	color(MAGENTA);
	for(int i = 0; i < 26; i++)
	{
		char str1[2], str2[2];
		sprintf(str1, "%c", (char)(65+i));
		if(i < 10)
		{
			j = i;
			c = (char)(48 + j);
		}
		else if(i < 12 && i > 9)
		{
			j = i % 10;
			c = (char)(33 + j);
		}
		else if(i < 15 && i > 11)
		{
			j = i - 12;
			c = (char)(39 + j);
		}
		else if(i < 19 && i > 14)
		{
			j = i - 15;
			c = (char)(43 + j);
		}
		else if(i < 21 && i > 18)
		{
			j = i - 19;
			c = (char)(58 + j);
		}
		else if(i < 23 && i > 20)
		{
			j = i - 21;
			c = (char)(63 + j);
		}
		if(i >= 23)
		{
			switch(i)
			{
				case 23:
					c = '=';
				break;
				case 24:
					c = '$';
				break;
				case 25:
					c = '_';
				break;
			}
		}
		sprintf(str2, "%c", c);		
		printf("%s\t%c\t\t%s\t%c\n", morseCypher(tree, str1) , (char)(65+i), 
									 morseCypher(tree, str2), c);
	}
	resetColor;
}

void destroyTree(Arbre tree)
{
	if(tree)
	{
		destroyTree(tree->dot);
		destroyTree(tree->dash);
		free(tree);
	}
}

int mainProg(Arbre tree, int argc, char ** argv)
{
	if(argc <= 1)
	{
		color(RED);
		printf("Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		resetColor;
		return EXIT_FAILURE;
	}
	if(strcmp(argv[1], "--help") == 0)
	{
		color(YELLOW);
		puts("Bienvenu dans l'aide de Code&EncodeMorse, voici les options utilisables:");
		printf("Utilisation: %s [Options]\n", argv[0]);
		printf("Vous pouvez utiliser les espaces afin de séparer les mots et utiliser '_' pour coller les lettres en morse\n");
		printf("Exemple: %s -d ._. ..\n", argv[0]);
		color(CYAN);
		puts("-d [morse]\t\tDécode le morse passé en paramètre");
		puts("-e [texte]\t\tEncode le texte en morse");
		puts("-g\t\t\tPassage en affichage graphique");
		puts("-a\t\t\tAffichage de la table de morse");
		puts("--help\t\t\tAffiche cette aide");
		resetColor;
	}
	else if(strcmp(argv[1], "-a") == 0)
		morseTable(tree);
	else if(strcmp(argv[1], "-g") == 0)
		return GRAPHIC;
	else if(argc <= 2 || (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-e") != 0))
	{
		color(RED);
		printf("Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		resetColor;
		return EXIT_FAILURE;
	}
	else if(strcmp(argv[1], "-d") == 0)
	{
		printf("%s",morseDecypher(tree, argv[2]));
		if(argc > 2)
			for(int i = 3; i < argc; i++)
			{
				printf("%s",morseDecypher(tree, " \0"));
				printf("%s",morseDecypher(tree, argv[i]));
			}
		printf("\n");
	}
	else if(strcmp(argv[1], "-e") == 0)
	{
		printf("%s", (morseCypher(tree, argv[2])));
		if(argc > 2)
			for(int i = 3; i < argc; i++)
			{
				printf("%s",morseCypher(tree, " \0"));
				printf("%s", morseCypher(tree, argv[i]));
			}
		printf("\n");
	}
	return EXIT_SUCCESS;
}
