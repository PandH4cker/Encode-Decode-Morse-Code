#include "../headers/graphic.h"

int graphicInterface(Arbre tree)
{
	if(SDLnIMGnTTF_Initialize() == EXIT_FAILURE)
		return EXIT_FAILURE;

	SDL_Window * window = SDL_CreateWindow("Encode&Decode Morse Code", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
											SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window: %s\n", SDL_GetError());
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create renderer: %s\n", SDL_GetError());
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Texture * background = loadTexture("../images/Background.png", renderer);
	if(!background)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Texture * encode_btn = loadTexture("../images/Encode_btnSprites.png", renderer);
	if(!encode_btn)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	int iWencode = 259, iHencode = 67, xEncode = 0, yEncode = 0;
	SDL_Rect encodeClips[3];
	for(int i = 0; i < 3; i++)
	{
		encodeClips[i].x = i * iWencode; 
		encodeClips[i].y = 0;
		encodeClips[i].w = iWencode;
		encodeClips[i].h = iHencode;
	}

	SDL_Texture * inputText = loadTexture("../images/InputText.png", renderer);
	if(!inputText)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	int xInput = 660, xOutput = 660, yInput = 450, yOutput = 600;

	int quit = 0;
	int hoverEncode = 0, OnClickEncode = 0;
	Uint32 frameStart, frameTime;
	while(!quit)
	{
		frameStart = SDL_GetTicks();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = 1;
				break;

				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if((event.button.x >= 0 && event.button.x <= iWencode) && (event.button.y >= 0 && event.button.y <= iHencode))
						{
							hoverEncode = 0;
							OnClickEncode = 1;
						}
					}
				break;

				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if((event.button.x >= 0 && event.button.x <= iWencode) && (event.button.y >= 0 && event.button.y <= iHencode))
						{
							hoverEncode = 1;
							OnClickEncode = 0;
						}
						else
						{
							hoverEncode = 0;
							OnClickEncode = 0;
						}						
					}
				break;

				case SDL_MOUSEMOTION:
					if((event.motion.x >= 0 && event.motion.x <= iWencode) && (event.motion.y >= 0 && event.motion.y <= iHencode))
					{
						if(!OnClickEncode)
							hoverEncode = 1;
					}
					else
					{
						hoverEncode = 0;
						OnClickEncode = 0;
					}
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		renderTexture(background, renderer, 0, 0, NULL);
		if(hoverEncode)
			renderTexture(encode_btn, renderer, xEncode, yEncode, &encodeClips[1]);			
		else if(OnClickEncode)
			renderTexture(encode_btn, renderer, xEncode, yEncode, &encodeClips[2]);
		else
			renderTexture(encode_btn, renderer, xEncode, yEncode, &encodeClips[0]);
		renderTexture(inputText, renderer, xInput, yInput, NULL);
		renderTexture(inputText, renderer, xOutput, yOutput, NULL);
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;
		if(frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));
	}



	SDL_DestroyTexture(background);
	SDL_DestroyTexture(encode_btn);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}

int SDLnIMGnTTF_Initialize()
{
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	if((initted & flags) != flags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize png images: %s\n", IMG_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	if(TTF_Init() == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize font feature: %s\n", TTF_GetError());
		IMG_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

SDL_Texture * loadTexture(const char * filename, SDL_Renderer * renderer)
{
	SDL_Texture * texture = IMG_LoadTexture(renderer, filename);
	if(!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture: %s\n", SDL_GetError());
		return NULL;
	}

	return texture;
}

void renderTextureClip(SDL_Texture * texture, SDL_Renderer * renderer, SDL_Rect dest, SDL_Rect * clip)
{
	SDL_RenderCopy(renderer, texture, clip, &dest);
}

void renderTexture(SDL_Texture * texture, SDL_Renderer * renderer, int x, int y, SDL_Rect * clip)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	if(!clip)
		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	else
	{
		dest.w = clip->w;
		dest.h = clip->h;
	}
	renderTextureClip(texture, renderer, dest, clip);
}