#include "graphic.h"

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
