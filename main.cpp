#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <conio.h>

const int SCREEN_WIDTH=320;
const int SCREEN_HEIGHT=240;

enum keyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow=NULL;

SDL_Surface* gScreenSurface=NULL;

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface* gCurrentSurface=NULL;

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* optimizedSurface=NULL;
    SDL_Surface* loadedSurface=IMG_Load(path.c_str());
    if(loadedSurface==NULL)
    {
        printf("Failed to load image %s. SDL_Error: %S\n",path.c_str(),SDL_GetError());
    }
    else
    {
        optimizedSurface=SDL_ConvertSurface(loadedSurface,gScreenSurface->format,NULL);
        if(optimizedSurface==NULL)
        {
            printf("Could not optimize surface! SDL_Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool loadMedia()
{
    bool success=true;
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]=loadSurface("default.png");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]==NULL)
    {
        printf("Failed to load default image\n");
        success=false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP]=loadSurface("up.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP]==NULL)
    {
        printf("Failed to load up image\n");
        success=false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN]=loadSurface("down.jpg");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN]==NULL)
    {
        printf("Failed to load down image\n");
        success=false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]=loadSurface("left.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]==NULL)
    {
        printf("Failed to load left image\n");
        success=false;
    }
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]=loadSurface("right.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]==NULL)
    {
        printf("Failed to load right image\n");
        success=false;
    }
    return success;
}

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
            int imgFlags=IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&imgFlags))
            {
                printf("IMG could not initialise. IMG_Error: %s\n",IMG_GetError());
                success=false;
            }
            else
            {
			    gScreenSurface=SDL_GetWindowSurface(gWindow);
            }
		}
	}
	return success;
}

void close()
{
    for(int i=0;i<KEY_PRESS_SURFACE_TOTAL;i++)
    {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i]=NULL;
    }
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    SDL_Quit();
}

void blitImage(SDL_Surface* gStretchedSurface, SDL_Surface* gScreenSurface)
{
    SDL_Rect stretchRect;
    stretchRect.x=0;
    stretchRect.y=0;
    stretchRect.w=SCREEN_WIDTH;
    stretchRect.h=SCREEN_HEIGHT;
    SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);
}

int main(int argc, char* args[])
{
    if(!init())
    {
        printf("Failed to initialise\n");
    }
    else
    {
        if(!loadMedia())
            printf("Failed to load media\n");
        else
        {
            bool quit=false;
            SDL_Event e;
            gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            while(!quit)
            {
                while(SDL_PollEvent(&e)!=0)
                {
                    if(e.type==SDL_QUIT)
                        quit=true;
                    else if(e.type==SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_UP:
                            gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;
                            case SDLK_DOWN:
                            gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;
                            case SDLK_LEFT:
                            gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;
                            case SDLK_RIGHT:
                            gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;
                            case SDLK_ESCAPE:
                            quit=true;
                            break;
                            default:
                            gCurrentSurface=gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                blitImage(gCurrentSurface,gScreenSurface);
                ///SDL_BlitSurface(gCurrentSurface,NULL,gScreenSurface,NULL);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    close();
    getch();
	return 0;
}
