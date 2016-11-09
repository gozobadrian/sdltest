#include <SDL.h>
#include <stdio.h>
#include <conio.h>

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;

SDL_Window* gWindow=NULL;

SDL_Renderer* gRender=NULL;

bool init()
{
    bool success=true;
    gWindow=SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(!gWindow)
    {
        printf("Failed to initialize window! SDL_Error: %s\n", SDL_GetError());
        success=false;
    }
    else
    {
        gRender=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
        if(!gRender)
        {
            printf("Failed to create render! SDL_Error: %s\n", SDL_GetError());
            success=false;
        }
    }
    return success;
}

bool loadMedia()
{
    bool success=true;
    return success;
}

void close()
{
    SDL_DestroyRenderer(gRender);
    gRender=NULL;
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    SDL_Quit();
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
            while(!quit)
            {
                while(SDL_PollEvent(&e)!=0)
                {
                    if(e.type==SDL_QUIT)
                        quit=true;
                }
                SDL_SetRenderDrawColor(gRender,0xFF,0xFF,0xFF,0xFF);
                SDL_RenderClear(gRender);

                SDL_Rect fillRect={SCREEN_WIDTH/4,SCREEN_HEIGHT/4,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor(gRender,0xFF,0x00,0x00,0xFF);
                SDL_RenderFillRect(gRender,&fillRect);

                SDL_Rect outlineRect={SCREEN_WIDTH/6,SCREEN_HEIGHT/6,SCREEN_WIDTH*2/3,SCREEN_HEIGHT*2/3};
                SDL_SetRenderDrawColor(gRender,0x00,0xFF,0x00,0xFF);
                SDL_RenderDrawRect(gRender,&outlineRect);

                SDL_SetRenderDrawColor(gRender,0x00,0x00,0xFF,0xFF);
                SDL_RenderDrawLine(gRender,0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2);

                SDL_SetRenderDrawColor(gRender,0xFF,0xFF,0x00,0xFF);
                for(int i=0;i<=SCREEN_HEIGHT;i+=2)
                {
                    SDL_RenderDrawPoint(gRender,SCREEN_WIDTH/2,i);
                }

                SDL_RenderPresent(gRender);
            }
        }
    }
    close();
    getch();
	return 0;
}
