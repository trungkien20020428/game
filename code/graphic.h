#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED
#include <SDL.h>
#include <SDL_main.h>
#include<SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "logic.h"
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
LTexture gamewin;
Mix_Music *gMusic=NULL;



#endif // GRAPHIC_H_INCLUDED
