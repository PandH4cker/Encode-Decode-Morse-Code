#include "../headers/morse.h"
#include "../headers/graphic.h"

int main(int argc, char ** argv)
{
	Arbre tree = initForMorse();
	switch(mainProg(tree, argc, argv))
	{
		case EXIT_FAILURE:
			destroyTree(tree), tree = NULL;
			return EXIT_FAILURE;
		break;
		case GRAPHIC:
			if(graphicInterface(tree) == EXIT_FAILURE)
			{
				destroyTree(tree), tree = NULL;
				return EXIT_FAILURE;
			}
		break;
	}
	destroyTree(tree), tree = NULL;
	return EXIT_SUCCESS;
}