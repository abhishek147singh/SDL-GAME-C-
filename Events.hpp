void EventHandling(SDL_Event *e)
{
    if( e->type == SDL_KEYDOWN  && !isAnimationTime)
    {
        //Adjust the velocity
        switch( e->key.keysym.sym )
        {
        case SDLK_UP:
            if(player_jump > 0)
            {
                player->acc.y = -0.8f;
                player->vel.y = -5.0f;
                player_jump--;
            }

            break;
        case SDLK_DOWN:
            player->vel.y += 2;
            break;
        case SDLK_LEFT:
            player->vel.x  -= 4;
            break;
        case SDLK_RIGHT:
            player->vel.x  += 4;
            break;
        }
    }

    if( e->type == SDL_KEYUP )
    {
        if(e->key.keysym.sym == SDLK_UP)
        {
            player->acc.y = 0;
            upButton = false;
        }
    }

    if(e->type == SDL_MOUSEBUTTONDOWN )
    {
        mouseDown = true;
        if(gStart && ! isAnimationTime)
        {
            fireBullet(player, {mouseX, mouseY});
        }
    }
    else
    {
        mouseDown = false;
    }

    if(e->type == SDL_MOUSEMOTION)
    {
        SDL_GetMouseState( &mouseX, &mouseY);
    }

    if(player->vel.x > 7)       player->vel.x = 7;
    else if(player->vel.x < -7) player->vel.x = -7;
    if(player->vel.y > 5)       player->vel.y = 5;
    if(player->acc.y < 0)       player->acc.y += 0.22f;
    else if(player->acc.y > 0)  player->acc.y -= 0.06;
}
