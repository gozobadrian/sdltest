#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <conio.h>

const int SCREEN_WIDTH=320;
const int SCREEN_HEIGHT=240;

SDL_Window* gWindow=NULL;

SDL_Renderer* gRender=NULL;

SDL_Texture* gTexture=NULL;

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
        else
        {
            SDL_SetRenderDrawColor(gRender,0xFF,0xFF,0xFF,0xFF);
            int imgFlags=IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&imgFlags))
            {
                printf("SDL_Image could not initialize! SDL_Error: %s\n",SDL_GetError());
                success=false;
            }
        }
    }
    return success;
}

SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture=NULL;
    SDL_Surface* loadedImage=IMG_Load(path.c_str());
    if(!loadedImage)
    {
        printf("Failed to load image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        newTexture=SDL_CreateTextureFromSurface(gRender,loadedImage);
        if(!newTexture)
        {
            printf("Failed to create teture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedImage);
    }
    return newTexture;
}

bool loadMedia()
{
    bool success=true;
    gTexture=loadTexture("texture.png");
    if(!gTexture)
    {
        printf("Failed to load texture image!\n");
        success=false;
    }
    return success;
}

void close()
{
    SDL_DestroyTexture(gTexture);
    gTexture=NULL;
    SDL_DestroyRenderer(gRender);
    gRender=NULL;
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    IMG_Quit();
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
                SDL_RenderClear(gRender);
                SDL_RenderCopy(gRender,gTexture,NULL,NULL);
                SDL_RenderPresent(gRender);
            }
        }
    }
    close();
    getch();
	return 0;
}
