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

void moveHorizontalLine(int &lineY,bool &lineYDown)
{
    if(lineY==SCREEN_HEIGHT||lineY==0)
    {
        if(lineYDown)
        {
            lineYDown=false;
        }
        else
        {
                lineYDown=true;
        }
    }
    if(lineY<SCREEN_HEIGHT&&lineYDown)
    {
        lineY++;
    }
    else
    {
        lineY--;
    }
}

void moveVerticalDots(int &dotX, bool &dotXRight)
{
    if(dotX==SCREEN_WIDTH||dotX==0)
    {
        if(dotXRight)
        {
            dotXRight=false;
        }
        else
        {
            dotXRight=true;
        }
    }
    if(dotX<SCREEN_WIDTH&&dotXRight)
    {
        dotX++;
    }
    else
    {
        dotX--;
    }
}

void moveOutlineRect(int &x,int &y,int &xx,int &yy, bool &down)
{
    if(x==0)
    {
        down=true;
    }
    else if(x==SCREEN_WIDTH)
    {
        down=false;
    }
    if(down)
    {
        x++;y++;
        xx-=2;yy-=2;
    }
    else
    {
       x--;y--;
       xx+=2;yy+=2;
    }
}

int main(int argc, char* args[])
{
    int lineY=0,dotX=0;
    int outlineRectX=SCREEN_WIDTH/4;
    int outlineRectY=SCREEN_HEIGHT/4;
    int outlineRectXX=SCREEN_WIDTH/2;
    int outlineRectYY=SCREEN_HEIGHT/2;
    bool lineYDown=false,dotXRight=false,rectDown=false;
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

                ///Fill rect
                SDL_Rect fillRect={SCREEN_WIDTH/4,SCREEN_HEIGHT/4,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor(gRender,0xFF,0x00,0x00,0xFF);
                SDL_RenderFillRect(gRender,&fillRect);

                ///Outline rect
                SDL_Rect outlineRect={outlineRectX,outlineRectY,outlineRectXX,outlineRectYY};
                SDL_SetRenderDrawColor(gRender,0x00,0xFF,0x00,0xFF);
                SDL_RenderDrawRect(gRender,&outlineRect);
                moveOutlineRect(outlineRectX,outlineRectY,outlineRectXX,outlineRectYY,rectDown);


                ///Horizontal line
                SDL_SetRenderDrawColor(gRender,0x00,0x00,0xFF,0xFF);
                SDL_RenderDrawLine(gRender,0,lineY,SCREEN_WIDTH,lineY);
                moveHorizontalLine(lineY,lineYDown);

                ///Vertical dots
                SDL_SetRenderDrawColor(gRender,0x00,0x00,0xFF,0xFF);
                for(int i=0;i<=SCREEN_HEIGHT;i+=2)
                {
                    SDL_RenderDrawPoint(gRender,dotX,i);
                }
                moveVerticalDots(dotX,dotXRight);

                SDL_RenderPresent(gRender);
            }
        }
    }
    close();
    getch();
	return 0;
}
