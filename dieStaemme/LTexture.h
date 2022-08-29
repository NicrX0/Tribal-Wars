#pragma once
#include<string>
#include "Framework.h"

class LTexture
{
public:
	//Init variables
	LTexture();

	//Deallocate memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//Create image from font string
	#if defined(SDL_TTF_MAJOR_VERSION)
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	#endif

	//Deallocate texture
	void free();

	//Render texture without animation
	void render();

	void rendertest();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Get image position and dimensions
	int getXPos() { return m_Rect.x; };
	int getYPos() { return m_Rect.y; };
	int getWidth() { return m_Rect.w; };
	int getHeight() { return m_Rect.h; };

	float getWidthOld() { return mWidth; };
	float getHeightOld() { return mHeight; };

	SDL_Rect GetRect() { return m_Rect; }

	void SetPos(float fX_pos, float fY_pos);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	float mWidth;
	float mHeight;

	//Rect of sprite
	SDL_Rect m_Rect;

	SDL_Renderer* m_pRenderer;
};