#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <SDL_mixer.h>
#include <cmath>
#include <fstream>
#include <SDL_ttf.h>
#include <vector>


//#include <ofstream>
using namespace std;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;

const int MAX = 2048;

int board [4][4]={0};
static int step;
 int score=10;

int random_index_generate(){
    int random_index = rand() % 4;
    return random_index;
}

int new_random_element(){
    int random_element = rand() % 10;
    random_element = (random_element==0) ? 4 : 2;
    return random_element;
}
bool is_win(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(board[i][j]==MAX){
                return 1;
            }
        }
    }
    return 0;
}

bool game_over(){
    bool is_game_over = true;
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]==0 || board[i][j+1]==0 || board[i][j] == board[i][j+1]){
                is_game_over = false;
                break;
            }
        }
    }
    for(int j=0; j<4; j++){
        for(int i=0; i<3; i++){
            if(board[i][j]==0 || board[i+1][j]==0 || board[i][j] == board[i+1][j]){
                is_game_over = false;
                break;
            }
        }
    }
    return is_game_over;
}

void display(){
    int index_i1, index_j1, index_i2, index_j2;
    while(1){
        index_i1 = random_index_generate();
        index_j1 = random_index_generate();
        index_i2 = random_index_generate();
        index_j2 = random_index_generate();
        if(index_i1==index_i2 && index_j1==index_j2){
            continue;
        }
        else
            break;
    }
    if(step == 0){

        for(int i=0; i<4; i++){

            for(int j=0; j<4; j++){

                if(i==index_i1 && j==index_j1){
                    board[i][j]=2;

                }
                else if(i==index_i2 && j==index_j2){
                    int temp = new_random_element();
                    board[i][j] = temp;
                }
            }
        }

    }
}

void add_element(){
    int index_i3, index_j3;
    int flag=0;
    while(1){
        if(flag==1)break;
        index_i3 = random_index_generate();
        index_j3 = random_index_generate();
        if(board[index_i3][index_j3]==0){
            board[index_i3][index_j3] = new_random_element();
            flag=1;
        }
    }
}
void move_left(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=0; j<4; j++)
        {
            if (n==board[i][j] && n!=0){
                board[i][prev] = 2*n;
                board[i][j] = 0;
               score+=5;
                n = 0;
                flag++;
                continue;
            }
            if (board[i][j]!=0){
                n = board[i][j];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<3; k++){
                if(board[i][k]==0 && board[i][k+1]!=0){
                    board[i][k]=board[i][k]^board[i][k+1];
                    board[i][k+1]=board[i][k]^board[i][k+1];
                    board[i][k]=board[i][k]^board[i][k+1];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}

void move_right(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=3; j>=0; j--)
        {
            if (n==board[i][j] && n!=0){
                board[i][prev] = 2*n;
                board[i][j] = 0;
              score+=5;
                n = 0;
                flag++;
                continue;
            }
            if (board[i][j]!=0){
                n = board[i][j];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=3; k>0; k--){
                if(board[i][k]==0 && board[i][k-1]!=0){
                    board[i][k]=board[i][k]^board[i][k-1];
                    board[i][k-1]=board[i][k]^board[i][k-1];
                    board[i][k]=board[i][k]^board[i][k-1];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}

void move_up(){
    int flag=0;
    for(int i=0; i<4; i++){int n=0;
        int prev=0;
        for (int j=0; j<4; j++)
        {
            if (n==board[j][i] && n!=0){
                board[prev][i] = 2*n;
                board[j][i] = 0;
              score+=5;
                n = 0;
                flag++;
                continue;
            }
            if (board[j][i]!=0){
                n = board[j][i];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<3; k++){
                if(board[k][i]==0 && board[k+1][i]!=0){
                    board[k][i]=board[k][i]^board[k+1][i];
                    board[k+1][i]=board[k][i]^board[k+1][i];
                    board[k][i]=board[k][i]^board[k+1][i];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}

void move_down(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=3; j>=0; j--)
        {
            if (n==board[j][i] && n!=0){
                board[prev][i] = 2*n;
                board[j][i] = 0;
                score+=15;
                 n = 0;
                flag++;
                continue;
            }
            if (board[j][i]!=0){
                n = board[j][i];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=3; k>0; k--){
                if(board[k][i]==0 && board[k-1][i]!=0){
                    board[k][i]=board[k][i]^board[k-1][i];
                    board[k-1][i]=board[k][i]^board[k-1][i];
                    board[k][i]=board[k][i]^board[k-1][i];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
    display();
}
// có tham khảo lazyfoo

class LTexture
{
	public:
		LTexture();
		~LTexture();
		bool loadFromFile( std::string path );
		bool loadFromRenderedText(std::string textureText,SDL_Color textColor);
		void free();
		void render( int x, int y );
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};
class drawscore
{
	public:
		drawscore();
		~drawscore();
		bool loadFromFile( std::string path );
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		void free();
		void setColor();
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha();
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

bool init();
bool loadMedia();
void close();
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture gamemenu;
LTexture gFooTexture[4][4];
LTexture gBackgroundTexture;
LTexture ggameover;
drawscore Drawscore;
LTexture menu_button_play;
LTexture menu_button_exit;

Mix_Music *gMusic=NULL;

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface( loadedSurface );
	}
	mTexture = newTexture;
	return mTexture != NULL;
}
void LTexture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( int x, int y )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
drawscore::drawscore()
{
    mTexture=NULL;
    mWidth=0;
    mHeight=0;
}
drawscore::~drawscore()
{
    free();
}
bool drawscore::loadFromFile(std::string path)
{
    free();
    SDL_Texture *newtexture=NULL;
    SDL_Surface *loadedSurface=IMG_Load(path.c_str());
    SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
    newtexture=SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
    mWidth=loadedSurface->w;
    mHeight=loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    mTexture=newtexture;
    return mTexture !=NULL;
}
bool drawscore::loadFromRenderedText(std::string textureText,SDL_Color textColor )
{
    free();
    SDL_Surface *textSurface=TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return mTexture != NULL;
}
void drawscore ::free()
{
    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void drawscore::setColor()
{
    SDL_SetTextureColorMod(mTexture,0,0,200);

}
void drawscore::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture,blending);
}
void drawscore::setAlpha()
{
    SDL_SetTextureAlphaMod(mTexture,5);
}
void drawscore::render(int x,int y,SDL_Rect *clip,double angle,SDL_Point *center,SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}
int drawscore::getWidth()
{
    return mWidth;
}
int drawscore::getHeight()
{
    return mHeight;
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "game 2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if (TTF_Init()==-1)
                {
                    printf("SDL_ttf could not initislize?");
                    success=false;
                }
                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
                {
                    printf("SDL_mixer could not initialize!");
                    success =false;
                }
			}
		}
	}

	return success;
}

void loadscore()
{
    std::string scorestring=std::to_string(score);
    SDL_Color textcolor={0,0,100};
    gFont =TTF_OpenFont("lazy.ttf",40);
    Drawscore.loadFromRenderedText(scorestring,textcolor);

}
//void savescore()
//{
//
//    std::string save_score=std::to_string(score);
//   fstream pi("output.txt");
//    pi<<save_score;
//   pi>>score;
//
// std::getline(pi,save_score);
//   pi.close();
//   fo.close();
//}

bool loadMedia()
{
	bool success = true;
	//load backgroud game
	if( !gBackgroundTexture.loadFromFile( "anhnen.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}


	gMusic =Mix_LoadMUS("nhacnen.wav");
if(!ggameover.loadFromFile("gameover.png"))
     {
         printf("failed to load image game over\n");
         success=false;
     }
	return success;
}
void loadmenu()
{
    if (!gamemenu.loadFromFile("menu.png"))
    printf("failed to load menu image!\n");

}

void load_number()
{
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        { if (board[i][j]==0)
        {
            if (!gFooTexture[i][j].loadFromFile("0.png"))
            {
                printf("failed to load image \n");
            }
        }
            if(board[i][j]==2)
            {
                if (!gFooTexture[i][j].loadFromFile("2.png"))
                {
                    printf("failed to load image\n");
                }
            }
            if(board[i][j]==4)
            {
                if (!gFooTexture[i][j].loadFromFile("4.png"))
                {
                    printf("failed to load image\n");
                }
            }
            if(board[i][j]==8)
            {
                if (!gFooTexture[i][j].loadFromFile("8.png"))
                {
                    printf("failed to load image\n");
                }
            }if(board[i][j]==16)
            {
                if (!gFooTexture[i][j].loadFromFile("16.png"))
                {
                    printf("failed to load image\n");
                }
            }if(board[i][j]==32)
            {
                if (!gFooTexture[i][j].loadFromFile("32.png"))
                {
                    printf("failed to load image\n");
                }
            }if(board[i][j]==64)
            {
                if (!gFooTexture[i][j].loadFromFile("64.png"))
                {
                    printf("failed to load image\n");
                }
            }if(board[i][j]==128)
            {
                if (!gFooTexture[i][j].loadFromFile("128.png"))
                {
                    printf("failed to load image\n");
                }
            }if(board[i][j]==256)
            {
                if (!gFooTexture[i][j].loadFromFile("256.png"))
                {
                    printf("failed to load image\n");
                }
            }if(board[i][j]==512)
            {
                if (!gFooTexture[i][j].loadFromFile("512.png"))
                {
                    printf("failed to load image\n");
                }
            }if(board[i][j]==1024)
            {
                if (!gFooTexture[i][j].loadFromFile("1024.png"))
                {
                    printf("failed to load image\n");
                }
            }
            if(board[i][j]==2048)
            {
                if (!gFooTexture[i][j].loadFromFile("2048.png"))
                {
                    printf("failed to load image\n");
                }
            }
        }
    }
}
void close()
{
	for (int i=0;i<4;i++)
    {
	for (int j=0;j<4;j++){gFooTexture[i][j].free();}}
	gBackgroundTexture.free();
    ggameover.free();
    gamemenu.free();
//    gButtonSpriteSheetTexture.free();
menu_button_play.free();
menu_button_exit.free();
    Mix_FreeMusic(gMusic);
gMusic=NULL;
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
void gameplay()
{
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

// if (Mix_PlayingMusic()==0)
//                            {
//                                Mix_PlayMusic(gMusic,-1);
//                            }

					else if (e.type==SDL_KEYUP)
                   {
//                        if (e.key.keysym.sym==SDLK_9)
//                        {
//
//
//                                    Mix_PauseMusic();
//
//
//                        }
                        if (e.key.keysym.sym==SDLK_RIGHT)
                        {
                            move_down();
                       quit =true;
                        }
                        if (e.key.keysym.sym==SDLK_LEFT)
                        {
                            move_up();
                            quit=true;

                        }
                        if (e.key.keysym.sym==SDLK_UP)
                           {
                            move_left();
                        quit =true;}
                        if (e.key.keysym.sym==SDLK_DOWN)
                        {
                            move_right();

                            quit=true;
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
SDL_Delay(35);
SDL_RenderClear(gRenderer);
if (game_over()==1)
{
    goto deptrai;
//    SDL_RenderClear(gRenderer);
//    ggameover.render(0,0);
//    SDL_RenderPresent(gRenderer);
//    quit=true;

//    a2048=false;
//   QUIT=true;

if(e.type==SDL_QUIT)
                    {
                       // quit=true;
                        a2048=false;
                         QUIT=true;

                    }
}

			}
deptrai:
			    SDL_RenderClear(gRenderer);


			    while(check_)
                {
                    ggameover.render(0,0);
                    SDL_RenderPresent(gRenderer);
                    if(e.type==SDL_QUIT)
                    {
                        check_=false;
                        a2048=false;
                        QUIT=true;
                    }
                }
		}


	}



}
int main( int argc, char* argv[] )
{board [1][2]=2;
	board [2][4]=2;


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
			printf( "Failed to load media!\n" );
		}
		else
		{
 menu_button_play.loadFromFile("menu_button_play.png");
 menu_button_exit.loadFromFile("menu_button_exit.png");
		    bool game=true;
		    loadmenu();
		    SDL_Event event;
		    SDL_SetRenderDrawColor(gRenderer,0XFF,0XFF,0XFF,0XFF);
		    SDL_RenderClear(gRenderer);

		    gamemenu.render(0,0);
		    SDL_RenderPresent(gRenderer);
		    while (game)
		   {

		    while (SDL_PollEvent(&event)!=0)
            {
if(event.type==SDL_QUIT)
{
    game=false;
}

                else if(event.type==SDL_MOUSEMOTION)
                {
                    if(event.button.y>320&&event.button.y<422&&event.button.x>250&&event.button.x<640)
                       {
//                          menu_button_play.loadFromFile("menu_button_play.png");
                          SDL_SetRenderDrawColor(gRenderer,0XFF,0XFF,0XFF,0XFF);
                          SDL_RenderClear(gRenderer);
                          menu_button_play.render(0,0);
                          SDL_RenderPresent(gRenderer);
                       }

                      else if (event.button.x>252&&event.button.x<650&&event.button.y<581&&event.button.y>480)
                       {
//                           menu_button_exit.loadFromFile("menu_button_exit.png");
                           SDL_SetRenderDrawColor(gRenderer,0XFF,0XFF,0XFF,0XFF);
                           SDL_RenderClear(gRenderer);
                           menu_button_exit.render(0,0);
                           SDL_RenderPresent(gRenderer);
                       }
                       else{
                        SDL_SetRenderDrawColor(gRenderer,0XFF,0XFF,0XFF,0XFF);
                          SDL_RenderClear(gRenderer);
                          gamemenu.render(0,0);
                          SDL_RenderPresent(gRenderer);
                       }

                }
                else if (event.type==SDL_MOUSEBUTTONUP)
                {
                    if (event.button.y>320&&event.button.y<422&&event.button.x>250&&event.button.x<640)
                    {
                        gameplay();
                        game=false;
                    }
                    else if(event.button.x>252&&event.button.x<650&&event.button.y<581&&event.button.y>480)
                    {
                        game=false;
                        close();
                    }
                }

            }
		   }
}
	close();

	}

	return 0;
	}

