#include "game_play.h"
void gameplay()
{
SDL_Event wine;
display();
     bool check_=true;
bool check=true;
    	bool a2048=true;
bool QUIT=false;
		    while (!QUIT){
		    while (a2048){
		    load_number();
		    loadscore();
			bool quit = false;
			SDL_Event e;
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if(e.type==SDL_QUIT)
                    {
                        quit=true;
                        a2048=false;
                         QUIT=true;
                    }



					else if (e.type==SDL_KEYUP)
                   {
                      if (e.key.keysym.sym==SDLK_9)
                      {

                                   Mix_PauseMusic();

                      }
                        if (e.key.keysym.sym==SDLK_RIGHT)
                        {
                            movebottom();
                       quit =true;
                        }
                        if (e.key.keysym.sym==SDLK_LEFT)
                        {
                            moveup();
                            quit=true;

                        }
                        if (e.key.keysym.sym==SDLK_DOWN)
                           {
                            moveleft();
                        quit =true;}
                        if (e.key.keysym.sym==SDLK_UP)
                        {
                            moveright();

                            quit=true;
                        }
           }
           else if(e.type==SDL_MOUSEBUTTONUP)
           {
               if (e.button.x<770&&e.button.x>700&&e.button.y>121&&e.button.y<200)
               {
                   Mix_PauseMusic();
               }
               else if (e.button.x<875&&e.button.x>800&&e.button.y>10&&e.button.y<85){

               }
           }
				}
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
gBackgroundTexture.render( 0, 0 );
for (int i=0;i<4;i++)
    for(int j=0;j<4;j++)
{
   gFooTexture[i][j].render((i+1)*100,(j+1)*100);
}
Drawscore.render(230,33);
				//Update screen
				SDL_RenderPresent( gRenderer );
//SDL_Delay(35);
SDL_RenderClear(gRenderer);
if (check_over()==1)
{
 //   goto deptrai;
 loadgameover(e);
 quit=true;
 a2048=false;
 QUIT=true;

}


			}

		}


	}



}
