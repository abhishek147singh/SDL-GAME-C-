//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//to clear all object
void clearObjects(void);

//Frees media and shuts down SDL
void close();

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
        gWindow = SDL_CreateWindow( "THE WAR OF GREEN SMILE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
                    success = false;
                }
                //Initialize SDL_mixer
                //44100 is default sound frequency
                //2 number of chanels
                //2KB size of chunks
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}




void close()
{
    writeGameData("Data/Score.txt");
    clearObjects();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    Mix_FreeChunk( gExplosionS );
    Mix_FreeChunk( gGunShotS );
    Mix_FreeChunk( gExplosionS2 );
    Mix_FreeChunk( gLooseS );
    Mix_FreeChunk( gCoinS );
    gExplosionS = NULL;
    gExplosionS2 = NULL;
    gGunShotS   = NULL;
    gLooseS = NULL;
    gCoinS  = NULL;
    gWindow = NULL;

    gRenderer = NULL;

    //Free the music
    //Mix_FreeMusic( gMusic );

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}



SDL_Texture* loadTexture( std::string path  )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

SDL_Texture* loadTextureWithColorKey( std::string path, SDL_Color col )
{
    void* mPixels = NULL;
    int mPitch;

    //Image dimensions
    int mWidth;
    int mHeight;
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to display format
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0 );
        if( formattedSurface == NULL )
        {
            printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
        }
        else
        {
            //Create blank streamable texture
            newTexture = SDL_CreateTexture( gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
            if( newTexture == NULL )
            {
                printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Enable blending on texture
                SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );

                //Lock texture for manipulation
                SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch );

                //Copy loaded/formatted surface pixels
                memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

                //Get image dimensions
                mWidth = formattedSurface->w;
                mHeight = formattedSurface->h;

                //Get pixel data in editable format
                Uint32* pixels = (Uint32*)mPixels;
                int pixelCount = ( mPitch / 4 ) * mHeight;

                //Map colors
                Uint32 colorKey = SDL_MapRGB( formattedSurface->format, 0x00, 0xFF, 0xFF );
                Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00 );
                Uint32 oldColor = SDL_MapRGB( formattedSurface->format, 0x00, 0x00, 0x00);
                Uint32 newColor = SDL_MapRGB( formattedSurface->format, col.r, col.b, col.g );

                //Color key pixels
                for( int i = 0; i < pixelCount; ++i )
                {
                    if( pixels[ i ] == colorKey )
                    {
                        pixels[ i ] = transparent;
                    }
                    else if(pixels[ i ] == oldColor )
                    {
                        pixels[ i ] = newColor;
                    }
                }

                //Unlock texture to update
                SDL_UnlockTexture( newTexture );
                mPixels = NULL;
            }

            //Get rid of old formatted surface
            SDL_FreeSurface( formattedSurface );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}


SDL_Texture* loadTexture2( std::string path)
{
    void* mPixels = NULL;
    int mPitch;

    //Image dimensions
    int mWidth;
    int mHeight;
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to display format
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0 );
        if( formattedSurface == NULL )
        {
            printf( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
        }
        else
        {
            //Create blank streamable texture
            newTexture = SDL_CreateTexture( gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
            if( newTexture == NULL )
            {
                printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Enable blending on texture
                SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );

                //Lock texture for manipulation
                SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch );

                //Copy loaded/formatted surface pixels
                memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

                //Get image dimensions
                mWidth = formattedSurface->w;
                mHeight = formattedSurface->h;

                //Get pixel data in editable format
                Uint32* pixels = (Uint32*)mPixels;
                int pixelCount = ( mPitch / 4 ) * mHeight;

                //Map colors
                Uint32 colorKey = SDL_MapRGB( formattedSurface->format, 0xFF, 0xFF, 0xFF );
                Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 0xFF, 0xFF, 0xFF, 0x00 );

                //Color key pixels
                for( int i = 0; i < pixelCount; ++i )
                {
                    if( pixels[ i ] == colorKey )
                    {
                        pixels[ i ] = transparent;
                    }
                }

                //Unlock texture to update
                SDL_UnlockTexture( newTexture );
                mPixels = NULL;
            }

            //Get rid of old formatted surface
            SDL_FreeSurface( formattedSurface );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void loadMusic(Mix_Music *gMusic,std::string path)
{
    gMusic = Mix_LoadMUS(path.c_str());
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

Mix_Chunk *loadSoundEffect(std::string path)
{
    Mix_Chunk *gSound = Mix_LoadWAV(path.c_str());
    if( gSound == NULL )
    {
        printf( "Failed to load beat SoundEffect ! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    return gSound;
}


void drawPoints(SDL_Color Color, SDL_Point  p)
{
    SDL_SetRenderDrawColor( gRenderer,Color.r, Color.b, Color.g, Color.a );
    SDL_RenderDrawPoint( gRenderer, p.x, p.y );
}

void drawRect(SDL_Color Color, SDL_Rect fillRect)
{
    SDL_SetRenderDrawColor( gRenderer,Color.r, Color.b, Color.g, Color.a );
    SDL_RenderFillRect( gRenderer, &fillRect );
}


void drawLine(SDL_Point p1, SDL_Point  p2, SDL_Color Color)
{
    SDL_SetRenderDrawColor( gRenderer,Color.r, Color.b, Color.g, Color.a );
    SDL_RenderDrawLine( gRenderer, p1.x, p1.y, p2.x, p2.y );
}


void drawLife( SDL_Rect src, float currLife, float maxLife)
{
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0, 0xFF );
    SDL_RenderFillRect( gRenderer, &src );
    float w = (currLife / maxLife) *  (float)src.w;
    src.w  =  w;
    src.x  =  src.x - 1;
    src.y  =  src.y - 1;
    src.h  =  src.h - 1;
    SDL_SetRenderDrawColor( gRenderer, 0, 0xFF, 0xFF, 0xFF );
    SDL_RenderFillRect( gRenderer, &src );
}


