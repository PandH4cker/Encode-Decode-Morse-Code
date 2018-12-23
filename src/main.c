#include "../headers/morse.h"

int main(int argc, char ** argv)
{
	Arbre tree = initForMorse();
	inorder(tree);
	/*if(argc <= 1)
	{
		fprintf(stderr, "Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		return EXIT_FAILURE;
	}
	if(strcmp(argv[1], "--help") == 0)
	{
		puts("Bienvenu dans l'aide de Code&EncodeMorse, voici les options utilisables:");
		printf("Usage: %s [Options]\n", argv[0]);
		puts("-d [morse]\t\tDécode le morse passé en paramètre");
		puts("-e [texte]\t\tEncode le texte en morse");
		puts("-g\t\t\tPassage en affichage graphique");
		puts("-a\t\t\tAffichage de la table de morse");
		puts("--help\t\t\tAffiche cette aide");
	}
	else if(strcmp(argv[1], "-a") == 0)
		morseTable();
	else if(argc <= 2 || (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-e") != 0))
	{
		fprintf(stderr, "Usage: %s [Option]\n", argv[0]);
		fprintf(stderr, "Use --help as an option to open the help list\n");
		return EXIT_FAILURE;
	}
	else if(strcmp(argv[1], "-d") == 0)
		puts(morseDecypher(tree, argv[2]));*/
	destroyTree(tree), tree = NULL;
	return EXIT_SUCCESS;
}