#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Window* gWindow=NULL;

SDL_Surface* gScreenSurface=NULL;

SDL_Surface* gImage=NULL;

bool init()
{
    bool success=true;

	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success=false;
	}
	else
	{
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n",SDL_GetError());
			success=false;
		}
		else
		{
			gScreenSurface=SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
    bool success=true;
    gImage=SDL_LoadBMP("cio.bmp");
    if(gImage==NULL)
    {
        printf("Could not load image %s, SDL_Error: %s","cio.bmp",SDL_GetError());
        success=false;
    }
    return success;
}

void close()
{
    SDL_FreeSurface(gImage);
    gImage=NULL;
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    SDL_Quit();
}

int main(int argc, char* args[])
{
    bool quit=false;
    SDL_Event e;
    if(!init())
    {
        printf("Failed to initialise\n");
    }
    if(!loadMedia())
    {
        printf("Could not load media\n");
    }
    else
    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;
        }
        SDL_BlitSurface(gImage,NULL,gScreenSurface,NULL);
        SDL_UpdateWindowSurface(gWindow);
    }
    close();
	return 0;
}
