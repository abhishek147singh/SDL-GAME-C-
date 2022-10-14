/** Rocket start => **/

Rocket::Rocket(float x, float y, Rectangle *flw)
{
    src = { x, y, 50, 30};
    follow = flw;
    maxSpeed = 5;
    initialBost = 10;
    life = 50;
}

void Rocket::draw()
{
    dst = { src.x - camera.x, src.y - camera.y, src.w, src.h };
    SDL_SetRenderDrawColor( gRenderer, 150, 150, 100, 0xFF );
    double angle = atan2( vel.y, vel.x ) * (180 / M_PI);
    SDL_RenderCopyEx(gRenderer, rocketT, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void Rocket::seek()
{
    vec2d dir = { src.x - follow->src.x, src.y - follow->src.y};
    float len = sqrt(dir.x * dir.x + dir.y * dir.y);
    dir.x /= len;
    dir.y /= len;
    vel =  { dir.x * maxSpeed, dir.y * maxSpeed };
    if(initialBost > 0)
    {
        vel.y += initialBost;
        initialBost -= 2;
    }
}
void Rocket::update()
{
    seek();
    src.x -= vel.x;
    src.y -= vel.y;
    draw();
    life--;
}

/** Rocket end <=  **/

void fireRocket(Rectangle *flw, int x, int y, int id)
{
    Rocket *rkt = new Rocket(x, y, flw);
    rkt->id = id;
    Rockets.push_back(rkt);
}
void RocketHandler()
{
    for(int i = 0; i < Rockets.size(); i++)
    {
        Rockets[i]->update();
        Rockets[i]->draw();
        int x = Rockets[i]->src.x / CELL_W;
        int y = Rockets[i]->src.y / CELL_H;
        if(x < 0 || y < 0 || x > plateform[0].length() || y > plateform.size()) continue;
        if( plateform[y][x] == '#' || plateform[y][x] == 'g')
        {
            createBoom(Rockets[i]->src.x, Rockets[i]->src.y);
            delete Rockets[i];
            Rockets[i] = NULL;
            Rockets.erase(Rockets.begin() + i );
            Mix_PlayChannel( -1, gExplosionS2, 0 );
        }
        else if(plateform[y][x] == '*')
        {
            Rects[y][x]->life--;
            if(Rects[y][x]->life < 1)
            {
                plateform[y][x] = '$';
            }
            createBoom(Rockets[i]->src.x, Rockets[i]->src.y);
            delete Rockets[i];
            Rockets[i]  = NULL;
            Rockets.erase(Rockets.begin() + i );
            Mix_PlayChannel( -1, gExplosionS2, 0 );
        }
        else if(Rockets[i]->id != player->id && RectVsRect2( Rockets[i]->src, player ))
        {
            player->life--;
            createBoom(Rockets[i]->src.x, Rockets[i]->src.y);
            delete Rockets[i];
            Rockets[i]  = NULL;
            Rockets.erase(Rockets.begin() + i );
            Mix_PlayChannel( -1, gExplosionS2, 0 );
        }
        else
        {
            bool check = checkRockerWithBox(i );
            if(!check)
            {
                if(Rockets[i]->life < 0)
                {
                    createBoom(Rockets[i]->src.x, Rockets[i]->src.y);
                    delete Rockets[i];
                    Rockets[i]  = NULL;
                    Rockets.erase(Rockets.begin() + i );
                    Mix_PlayChannel( -1, gExplosionS2, 0 );
                }
                else
                    checkROcketWithEnemey( i);
            }
        }
    }
}

