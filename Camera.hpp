void cameraHandler()
{
    if(isAnimationTime)
    {
        camera.x += aOffsetX;
        camera.y -= aOffsetY;
    }
    else
    {
        camera.x = ( player->src.x + player->src.w / 2 )  -  SCREEN_WIDTH / 2 ;
        camera.y = ( player->src.y + player->src.h / 2 )  -  SCREEN_HEIGHT / 2 ;
    }

    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
        if(isAnimationTime) isAnimationTime = false;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
        if(isAnimationTime) isAnimationTime = false;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}
