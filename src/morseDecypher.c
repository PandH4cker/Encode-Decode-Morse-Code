#include "../headers/morse.h"

/** Création d'un noeud **/
Arbre new_node()
{
	Noeud * node = malloc(sizeof(*node));
	if(!node) //Si l'allocation ne s'est pas faite
	{
		fprintf(stderr, "Node creation failure\n");
		return NULL;
	}

	//Initialisation de la structure du noeud
	node->dot = NULL;
	node->dash = NULL;
	node->character = '\0';

	return node;
}
/***********************************************************************/
/** Ajout d'un caractère dans l'arbre **/
Arbre add_char(Arbre * tree, char * morse, char c)
{
	if(!morse || !tree) //Si l'arbre est vide ou que la chaîne est vide
	{
		fprintf(stderr, "Unable to add a character.\n");
		return NULL;
	}

	if(!*tree) //Si le noeud n'existe pas
	{
		*tree = new_node(*tree); //On le crée
		if(!*tree) //Si le noeud ne s'est pas créé
		{
			fprintf(stderr, "Unable to create node\n");
			return NULL;
		}
	}

	if(!*morse) //Si on arrive à la fin de la chaîne (\0)
	{
		(*tree)->character = c; //On ajoute le caractère au noeud de l'arbre où on se trouve
		return *tree;
	}

	if(*morse == DOT) //Si le caractère est un point
		return add_char(&(*tree)->dot, ++morse, c);
	if(*morse == DASH) //Si le caractère est un tiret
		return add_char(&(*tree)->dash, ++morse, c);
	return NULL;
}
/***********************************************************************/
/** Recherche du caractère dans l'arbre **/
char seekChar(Arbre tree, char * morse)
{
	if(!tree) //Si l'arbre est vide
		return '?';
	if(!*morse) //Si on arrive à la fin de la chaîne de caractère
		return tree->character;
	if(*morse == DOT) //Si le caractère est un point
		return seekChar(tree->dot, ++morse);
	if(*morse == DASH) //Si le caractère est un tiret
		return seekChar(tree->dash, ++morse);
	return '?';
}
/***********************************************************************/
/** Décodage du code morse **/
char * morseDecypher(Arbre tree, char * morse)
{
	char * current = morse; //Pointeur sur le morse
	char * parsed = malloc(sizeof(char) * (strlen(morse)+1)); //Allocation de mémoire pour le résultat

	if(!parsed) //Si l'allocation ne s'est pas faite
	{
		fprintf(stderr, "Unable to alloc memory\n");
		return NULL;
	}

	char * current_parsed = parsed; //Pointeur sur le résultat
	int done = 0;
	while(!done) //Tant que ce n'est pas fini
	{
		while(*current && *current != SEP) //On parcours le morse jusqu'au séparateur
			++current;

		if(!*current) //Si on arrive à la fin du morse on a fini
			done = 1;

		else //Sinon on réduit la chaine jusqu'où on est arrivé
			*current = '\0';
		if(strcmp(morse, " ") != 0) //Si ce n'est pas un espace
			*current_parsed = seekChar(tree, morse);
		else //Sinon
			*current_parsed = ' ';
		++current_parsed;
		++current;
		morse = current; //On fait avancer notre chaine jusqu'où le pointeur est
	}
	*current_parsed = '\0'; //On s'assure de fermer la chaine avant de retourner le résultat
	return parsed;
}
/***********************************************************************/
/** Encodage du code morse **/
char * morseCypher(Arbre tree, char * text)
{
	int i = 0, find = 0;
	char *parsed = malloc(sizeof(char) * 4 * (strlen(text)+1)); //Allocation de mémoire pour le résultat
	if(!parsed) //Si l'allocation ne s'est pas faite
	{
		fprintf(stderr, "Unable to alloc memory\n");
		return NULL;
	}
	size_t size = 54; //Définition du nombre de code morse dans le tableau
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
	char * current_parsed = parsed; //Pointeur sur le résultat
	while(text[i]) //Tant qu'on n'est pas arrivé à la fin de la chaîne
	{
		char c = toupper(text[i]); //On assigne la lettre en majuscule au caractère
		if(c == ' ') //Si c'est un espace
		{
			strcat(current_parsed, " \0"); //On concatène l'espace avec la chaîne actuel
			i++;
			continue; //On passe tout le code qui suit
		}
		for(int k = 0; k < size; k++) //On parcours tout le tableau de morse
		{
			if(seekChar(tree, morseCode[k]) == c) //On vérifie si on trouve le caractère correspondant au code morse
			{
				find = 1;
				strcat(current_parsed, morseCode[k]); //On concatène avec la chaîne existante le code morse trouvé
				break; //On sort de la boucle
			}
		}
		if(!find) //Si on n'a pas trouvé d'equivalent
			strcat(current_parsed, "?\0"); //On concatène avec un point d'intérrogation


		i++;
		if(text[i] != '\0' && text[i] != ' ') //Si on n'est pas arrivé à la fin de la chaîne et que ce n'est pas un espace
			strcat(current_parsed, "_\0"); //On ajoute le séparateur
		find = 0;
		if(text[i+1] == '\0')
			strcat(current_parsed, "\0");
	}
	return parsed;
}
/***********************************************************************/
/** Construction de l'arbre **/
Arbre initForMorse()
{
	Arbre tree = NULL;
	/* On ajoute tout les caractère de la table de morse */
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
/***********************************************************************/
/** Affichage de la table morse **/
void morseTable(Arbre tree)
{
	clrscr(); //On efface l'affichage précédent
	color(BLUE); //On passe l'affichage en bleu
	puts("\t-----------------");
	puts("\t|  MORSE TABLE  |");
	printf("\t-----------------\n\n");
	resetColor; //On réinitialise la couleur du terminal
	int j;
	char c;
	color(MAGENTA); //On passe l'affichage en magenta
	for(int i = 0; i < 26; i++) //On parcours la moitié des caractères de l'arbre en 2 fois (2x26 caractères)
	{
		char str1[2], str2[2];
		sprintf(str1, "%c", (char)(65+i)); //On stocke dans une chaine le résultat (A-Z)
		/* Petit calcul amusant pour afficher les caractère :) */
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
		sprintf(str2, "%c", c);	//On stocke dans une chaîne le caractère	
		printf("%s\t%c\t\t%s\t%c\n", morseCypher(tree, str1) , (char)(65+i), 
									 morseCypher(tree, str2), c); //On affiche une table de deux colonnes
	}
	resetColor; //On réinitialise la couleur du terminal
}
/***********************************************************************/
/** Destruction de l'arbre **/
void destroyTree(Arbre tree)
{
	if(tree) //Si l'arbre n'est pas vide
	{
		destroyTree(tree->dot);
		destroyTree(tree->dash);
		free(tree);
	}
}
/***********************************************************************/
/** Fonction principale du programme **/
int mainProg(Arbre tree, int argc, char ** argv)
{
	if(argc <= 1) //Si il n'y a pas d'arguments
	{
		color(RED); //On passe la couleur du terminal en rouge
		printf("Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		resetColor; //On réinitialise la couleur du terminal
		return EXIT_FAILURE;
	}
	if(strcmp(argv[1], "--help") == 0) //Si on veut afficher l'aide
	{
		color(YELLOW); //On passe la couleur du terminal en jaune
		puts("Bienvenu dans l'aide de Code&EncodeMorse, voici les options utilisables:");
		printf("Utilisation: %s [Options]\n", argv[0]);
		printf("Vous pouvez utiliser les espaces afin de séparer les mots et utiliser '_' pour coller les lettres en morse\n");
		printf("Exemple: %s -d ._. ..\n", argv[0]);
		color(CYAN); //On passe la couleur du terminal en cyan
		puts("-d [morse]\t\tDécode le morse passé en paramètre");
		puts("-e [texte]\t\tEncode le texte en morse");
		puts("-g\t\t\tPassage en affichage graphique");
		puts("-a\t\t\tAffichage de la table de morse");
		puts("-f [filename] -d/-e\tDecode ou encode un fichier");
		puts("--help\t\t\tAffiche cette aide");
		resetColor; //On réinitialise la couleur du terminal
	}
	else if(strcmp(argv[1], "-a") == 0) //Si on veut afficher la table de morse
		morseTable(tree);
	else if(strcmp(argv[1], "-g") == 0) //Si on veut lancer le programme en graphique
		return GRAPHIC;
	else if(argc <= 2 || (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-f") != 0)) //Si on a mis un argument différent de -d ou -e ou bien -d ou -e mais pas de texte/morse
	{
		color(RED);
		printf("Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		resetColor;
		return EXIT_FAILURE;
	}
	else if(strcmp(argv[1], "-d") == 0) //Si on veut décoder du morse
	{
		printf("%s",morseDecypher(tree, argv[2]));
		if(argc > 2) //Si on une chaîne avec des espaces
			for(int i = 3; i < argc; i++) //On fait la meme opération pour tout les arguments suivants
			{
				printf("%s",morseDecypher(tree, " \0"));
				printf("%s",morseDecypher(tree, argv[i]));
			}
		printf("\n");
	}
	else if(strcmp(argv[1], "-e") == 0) //Si on veut encoder du texte en morse
	{
		printf("%s", (morseCypher(tree, argv[2])));
		if(argc > 2) //Si on a une chaîne avec des espaces
			for(int i = 3; i < argc; i++) //On fait la meme opération pour tout les arguments suivants
			{
				printf("%s",morseCypher(tree, " \0"));
				printf("%s", morseCypher(tree, argv[i]));
			}
		printf("\n");
	}
	else if(strcmp(argv[1], "-f") == 0)
	{
		if(argc < 4)
		{
			color(RED);
			printf("Usage %s [Option]\n", argv[0]);
			fprintf(stderr, "Use --help as an option to open the help list\n");
			resetColor;
			return EXIT_FAILURE;
		}

		FILE * file = fopen(argv[2], "r");
		if(!file)
		{
			color(RED);
			printf("File opening failure..\n");
			fprintf(stderr, "Unable to open : %s\n", argv[2]);
			fprintf(stderr, "Use --help as an option to open the help list\n");
			resetColor;
			return EXIT_FAILURE;			
		}

		if(strcmp(argv[3], "-e") == 0)
		{
			char * filenameOutput = malloc(sizeof(char) * 60);
			if(!filenameOutput)
			{
				color(RED);
				printf("Unable to allocate memory\n");
				fprintf(stderr, "Insuffisant memory\n");
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;			

			}
			strcpy(filenameOutput, argv[2]);
			strcat(filenameOutput, "_encoded\0");
			FILE * outputFile = fopen(filenameOutput, "w");
			if(!outputFile)
			{
				color(RED);
				printf("File creation failure..\n");
				fprintf(stderr, "Unable to create the file : %s\n", filenameOutput);
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;				
			}
			free(filenameOutput);
			char buff[255];
			while(fgets(buff, 255, file) != NULL)
				fprintf(outputFile, "%s\n", morseCypher(tree, buff));
			fclose(outputFile);
		}

		else if(strcmp(argv[3], "-d") == 0)
		{
			char * filenameOutput = malloc(sizeof(char) * 60);
			if(!filenameOutput)
			{
				color(RED);
				printf("Unable to allocate memory\n");
				fprintf(stderr, "Insuffisant memory\n");
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;			

			}
			strcpy(filenameOutput, argv[2]);
			strcat(filenameOutput, "_decoded\0");
			FILE * outputFile = fopen(filenameOutput, "w");
			if(!outputFile)
			{
				color(RED);
				printf("File creation failure..\n");
				fprintf(stderr, "Unable to create the file : %s\n", filenameOutput);
				fprintf(stderr, "Use --help as an option to open the help list\n");
				resetColor;
				return EXIT_FAILURE;				
			}
			free(filenameOutput);
			char buff[255];
			while(fgets(buff, 255, file) != NULL)
			{
				char * outputDecypher = malloc(sizeof(char) * 255);
				char ** splitted = str_split(buff, " \0");
				if(!splitted)
				{
					color(RED);
					printf("str_split error\n");
					fprintf(stderr, "Unable to split the string\n");
					fprintf(stderr, "Use --help as an option to open the help list\n");
					resetColor;
					return EXIT_FAILURE;				

				}

				for(int i = 0; splitted[i] != NULL; i++)
				{
					strcat(outputDecypher, morseDecypher(tree, splitted[i]));
					if(splitted[i+1] != NULL)
						strcat(outputDecypher, " \0");
				}
				free(splitted); splitted = NULL;

				fprintf(outputFile, "%s\n", outputDecypher);
			}
			fclose(outputFile);
		}

		else
		{
			color(RED);
			printf("Unable to do your options\n");
			fprintf(stderr, "%s is not an argument for the %s option\n", argv[3], argv[1]);
			fprintf(stderr, "Use --help as an option to open the help list\n");
			resetColor;
			return EXIT_FAILURE;						
		}

		fclose(file);	
	}
	return EXIT_SUCCESS;
}

/** Split une chaîne de caractère par un délimiteur (const char * ct) et renvoie sous forme de tableau **/
char ** str_split(char * s, const char * ct)
{
	char ** tab = NULL;
	if(s && ct) //Si les chaînes ne sont pas vides
	{
		int i;
		char * cs = NULL;
		size_t size = 1; // Taille initiale de 1 à notre tableau
		for(i = 0; (cs = strtok(s, ct)); i++) //Tant que strtok(...) ne nous renvoi pas NULL
		{
			if(size <= i + 1) //Si la taille du tableau est inférieure à la prochaine itération
			{
				void * tmp = NULL; //On crée une variable temp pour réallouer notre tableau
				size <<= 1; //On multiplie la taille par 2 (2^1)
				tmp = realloc(tab, sizeof(*tab) * size); //On réalloue via tmp
				if(tmp) //Si tout c'est bien passé tmp != NULL
					tab = tmp;
				else
				{
					fprintf(stderr, "Unable to allocate memory\n");
					free(tab); tab = NULL;
					return NULL;
				}
			}

			tab[i] = cs; //On ajoute à l'indice i la chaîne tronquée
			s = NULL;
		}

		tab[i] = NULL; //On passe à NULL le dernier indice du tableau
	}
	return tab;
}