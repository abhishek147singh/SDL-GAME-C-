#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include "AllClassDisciption.hpp"
#include "AlllFunctionDiscription.hpp"
#include "requiredVerialbes.hpp"
#include "requiredFunction.hpp"
#include "FileHandling.hpp"
#include "Rectangle.hpp"
#include "Button.hpp"
#include "ResolveCollision.hpp"
#include "Boom.hpp"
#include "Rocket.hpp"
#include "Enemey.hpp"
#include "Box.hpp"
#include "Number.hpp"
#include "Coins.hpp"
#include "Flage.hpp"
#include "Editor.hpp"
#include "Fire.hpp"
#include "GunBullets.hpp"
#include "CreatePlateform.hpp"
#include "Events.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "AnimationNum.hpp"

void playMode(bool ready)
{
    if(ready)
    {
        bgSky.y = -camera.y;
        SDL_SetRenderDrawColor(gRenderer, 0x53, 0xb7, 0xed, 0xFF );
        SDL_RenderFillRect(gRenderer, &bgSky);

        bgGroound.y = 400 - camera.y;
        SDL_SetRenderDrawColor(gRenderer, 0xf5, 0xa3, 0x6c, 0xFF );
        SDL_RenderFillRect(gRenderer, &bgGroound);

        for(auto txtRec : onlyForDraw)
        {
            txtRec->draw();
        }

        updateEnemeys();
        handelBoxs();
        RocketHandler();
        drawFlages();
        drawRectangles();
        drawBullets();
        drawBooms();
        drawEnemeys();
        Back->show();
        Back->onClick({mouseX, mouseY});
        DrawCoins();
        DrawBloodCells();
        DrawBricks();
        cameraHandler();
        if(gameOver)
        {
            gO->draw();
        }
        else if(gameWin)
        {
            gW->draw();
        }
    }
    else
    {
        SDL_RenderCopy(gRenderer, BackgroundT, NULL, NULL );
        drawStartWindow();
    }
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            SDL_Log("Failed to load media!\n" );
        }
        else
        {
            //Event handler
            SDL_Event e;

            ed = new  Editor(15, 50, 5, 10);
            editorMode = false;

            gW = new win(150, 100, 350, 300);
            gO = new GOver(150, 100, 350, 300);
            gH = new HelpWin(90, 80, 450, 310);

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent(&e) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    EventHandling(&e);
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //================================

                if(!editorMode)
                {
                    if(!levelsOpen)
                    {
                        if(!Help)
                        {
                            playMode(gStart);
                            drawScore();
                        }
                        else
                        {
                            SDL_RenderCopy(gRenderer, BackgroundT, NULL, NULL );
                            gH->draw();
                        }
                    }
                    else
                    {
                        SDL_RenderCopy(gRenderer, BackgroundT, NULL, NULL );
                        drawLevels();
                    }
                }
                else
                {
                    ed->show();
                }

                //==================================

                //Update screen
                SDL_RenderPresent( gRenderer );

                SDL_Delay(20);

            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
