#include "LTexture.h"

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;

	//Get pointer of screen from framework
	m_pRenderer = g_pFramework->GetRenderer();
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;

			m_Rect.w = loadedSurface->w *g_pFramework->getScreenWidthScale();	//
			m_Rect.h = loadedSurface->h *g_pFramework->getScreenHeightScale();	//
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(g_pFramework->GetFont(), textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(g_pFramework->GetRenderer(), textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;

			m_Rect.w = textSurface->w *g_pFramework->getScreenWidthScale();		//
			m_Rect.h = textSurface->h *g_pFramework->getScreenHeightScale();		//
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::SetPos(float fX_pos, float fY_pos)
{
	//Update rect
	m_Rect.x = static_cast<int>(fX_pos);
	m_Rect.y = static_cast<int>(fY_pos);

	//std::cout << "Texture pos X set at: " << m_Rect.x << std::endl;
	//std::cout << "Texture pos Y set at: " << m_Rect.y << std::endl;
}

void LTexture::render()
{
	SDL_RenderCopy(m_pRenderer, mTexture, NULL, &m_Rect);
}

void LTexture::rendertest()
{
	SDL_RenderCopy(m_pRenderer, mTexture, NULL, NULL);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (mWidth <= 0.0f || mHeight <= 0.0f)
	{
		printf("Error rendering Texture. mWidth/mHeight was <= 0.0f. No Texture loaded?\n");
		std::cin.get();
	}
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth , mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		if (clip->w <= 0 || clip->h <= 0)
		{
			printf("clip->w || clip->h was <= 0! Everything loaded correctly?\n");
			std::cin.get();
		}

		renderQuad.w = clip->w * g_pFramework->getScreenWidthScale();
		renderQuad.h = clip->h * g_pFramework->getScreenHeightScale();
	}

	//clip->x = clip->x / g_pFramework->getScreenWidthScale();
	//clip->y = clip->y / g_pFramework->getScreenHeightScale();
	//clip->w = clip->w / g_pFramework->getScreenWidthScale();
	//clip->h = clip->h / g_pFramework->getScreenHeightScale();

	//std::cout << "clip.x: " << clip->x << std::endl;
	//std::cout << "clip.y: " << clip->y << std::endl;
	//std::cout << "clip.w: " << clip->w << std::endl;
	//std::cout << "clip.h: " << clip->h << std::endl << std::endl;

	//std::cout << "renderQuad.x: " << renderQuad.x << std::endl;
	//std::cout << "renderQuad.y: " << renderQuad.y << std::endl;
	//std::cout << "renderQuad.w: " << renderQuad.w << std::endl;
	//std::cout << "renderQuad.h: " << renderQuad.h << std::endl << std::endl;


	SDL_RenderCopyEx(m_pRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}