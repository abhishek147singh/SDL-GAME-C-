/** Enemey  start => **/
Enemey::Enemey( int x, int y, int w, int h)
{
    src = new Rectangle(x, y, w, h );
    canFireGun = false;
    maxSpeed = 2;
    timer = 0;
    dist = 9999999.0;

}

void Enemey::draw()
{
    src->draw();
    drawLife({ src->src.x - camera.x, src->src.y  - camera.y  - 10, src->src.w, 8 }, src->life, totalLife );
}

void Enemey::seek()
{
    dir.x /= dist;
    dir.y /= dist;
    if(dist > 200) maxSpeed = -2;
    else if(dist  < 200 && dist > 100)
    {
        if(timer > 40)
        {
            if(canFireGun)
            {
                fireBullet(src, {player->src.x + player->src.w/2 - camera.x, player->src.y + player->src.h /2 - camera.y});
            }
            else
            {
                fireRocket(player,src->src.x, src->src.y, src->id );
            }
            timer = 0;
        }
        timer++;
    }
    else if(dist< 100) maxSpeed = 4;

    src->vel.x =  dir.x * maxSpeed;
}

void Enemey::update()
{
    dir = { src->src.x - player->src.x, src->src.y - player->src.y};
    dist = sqrt(dir.x * dir.x + dir.y * dir.y);
    if(dist > 300) return;
    src->vel.y += gravity;
    seek();
    ResolveDynamicRectVsRect(src);
    src->src.x += src->vel.x;
    src->src.y += src->vel.y;
}


/** Enemey  <= end  **/

void updateEnemeys()
{
    for(int i = 0; i < allEnemeys.size(); i++ )
    {
        float x = (allEnemeys[i]->src->src.x - player->src.x);
        float y = (allEnemeys[i]->src->src.y - player->src.y);
        allEnemeys[i]->dist = x * x + y * y ;
        if(allEnemeys[i]->dist <  90000)
        {
            Enemeys.push_back(allEnemeys[i]);
            allEnemeys.erase(allEnemeys.begin() + i);
        }
    }
}


bool comparetor( Enemey* e1, Enemey* e2 )
{
    return e1->dist < e2->dist;
}

void drawEnemeys()
{
    sort( Enemeys.begin(), Enemeys.end(), comparetor );
    for(int i = 0; i < Enemeys.size(); i++)
    {
        Enemeys[i]->draw();
        Enemeys[i]->update();
        if(Enemeys[i]->src->life < 0)
        {
            delete Enemeys[i];
            Enemeys[i] = NULL;
            Enemeys.erase(Enemeys.begin() + i);
        }
    }
}
void resoleForEnemeyHelper(std::vector<std::pair< float, Rectangle *>> &z, Rectangle* Rect)
{
    vec2d contact_point, contact_normal;
    float contact_time = 0.0f;
    for(int i = 0; i < Enemeys.size(); i++)
    {
        if(Enemeys[i]->src->id != Rect->id)
        {
            if(DynamicRectVsRect( player, Enemeys[i]->src, contact_point, contact_normal, contact_time))
            {
                if(Rect->id == player->id && contact_normal.y != 1) player_jump = 2;
                z.push_back({ contact_time, Enemeys[i]->src });
            }
        }
    }
}

void checkROcketWithEnemey( int i)
{
    for(int j = 0; j < Enemeys.size(); j++)
    {
        if(Rockets[i]->id != Enemeys[j]->src->id && RectVsRect2( Rockets[i]->src, Enemeys[j]->src ))
        {
            Enemeys[j]->src->life--;
            playerScore += 10;
            if(Enemeys[j]->src->life < 0)
            {
                delete Enemeys[j];
                Enemeys[j] = NULL;
                Enemeys.erase(Enemeys.begin() + j);
            }
            createBoom(Rockets[i]->src.x, Rockets[i]->src.y);
            delete Rockets[i];
            Rockets[i]  = NULL;
            Rockets.erase(Rockets.begin() + i );
            Mix_PlayChannel( -1, gExplosionS2, 0 );
            break;
        }
    }
}




