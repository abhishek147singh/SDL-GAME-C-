/**GunBullet start =>  **/

GunBullet::GunBullet() { }

GunBullet::GunBullet( float x, float y, int Pw, int Ph, vec2d v, vec2d d)
{
    src = {x, y, 10, 10 };
    dir = { ( x + ( Pw * 0.5 ) - d.x - camera.x - 5 ),( y + ( Ph * 0.5) - d.y - camera.y - 5 )};
    float len = sqrt( dir.x * dir.x + dir.y * dir.y );
    dir.x /= len;
    dir.y /= len;
    dir.x *= v.x;
    dir.y *= v.y;
}
void GunBullet::update()
{
    src.x -= dir.x;
    src.y -= dir.y;
    SDL_SetRenderDrawColor( gRenderer, 20, 22, 100, 0xFF );
    dst = {src.x - camera.x, src.y - camera.y, src.w, src.h };
    SDL_RenderFillRect( gRenderer, &dst );
}

/**GunBullet end  =>  **/

void fireBullet(Rectangle *Rect, vec2d dir)
{
    if(Bullets.size() > 4) return;
    GunBullet *blts = new GunBullet(Rect->src.x  + Rect->src.w /2, Rect->src.y + Rect->src.h /2, Rect->src.w, Rect->src.h,  { 7.5f, 7.5f }, { dir.x, dir.y });
    blts->id = Rect->id;
    Bullets.push_back(blts);
    Mix_PlayChannel( -1, gGunShotS, 0 );
}

void drawBullets()
{
    for(int i = 0; i < Bullets.size(); i++)
    {
        Bullets[i]->update();
        int x = Bullets[i]->src.x / CELL_W;
        int y = Bullets[i]->src.y / CELL_H;
        if(x < 0 || y < 0 || x > plateform[0].length() || y > plateform.size()) continue;
        if( plateform[y][x] == '#' || plateform[y][x] == 'g')
        {
            delete Bullets[i];
            Bullets[i] = NULL;
            Bullets.erase(Bullets.begin() + i );
        }
        else if(plateform[y][x] == '*')
        {
            Rects[y][x]->life--;
            if(Rects[y][x]->life < 1)
            {
                plateform[y][x] = '$';
                cleateBrick(Bullets[i]->src.x, Bullets[i]->src.y );
                createBoom(Bullets[i]->src.x, Bullets[i]->src.y );
            }
            delete Bullets[i];
            Bullets[i]  = NULL;
            Bullets.erase(Bullets.begin() + i );
        }
        else if(Bullets[i]->id != player->id && (PointVsRect({ Bullets[i]->src.x, Bullets[i]->src.y }, player )) )
        {
            player->life--;
            cleateBlood(Bullets[i]->src.x, Bullets[i]->src.y );
            delete Bullets[i];
            Bullets[i]  = NULL;
            Bullets.erase(Bullets.begin() + i );
        }
        else
        {
            for(int j = 0; j < Boxs.size(); j++)
            {
                if(PointVsRect({ Bullets[i]->src.x, Bullets[i]->src.y }, Boxs[j]->src ))
                {
                    if(Boxs[j]->isBoomBox )
                    {
                        Boxs[j]->explosion();
                        Mix_PlayChannel( -1, gExplosionS, 0 );
                        delete Boxs[j];
                        Boxs[j] = NULL;
                        Boxs.erase(Boxs.begin() + j);
                    }
                    else
                    {
                        Boxs[j]->src->vel = { Bullets[i]->dir.x * -0.2, Bullets[i]->dir.y * -0.2 };
                    }
                    delete Bullets[i];
                    Bullets[i]  = NULL;
                    Bullets.erase(Bullets.begin() + i );
                    j = i;
                    break;
                }
            }

            if(Bullets[i] != NULL )
            {
                for(int j = 0; j < Enemeys.size(); j++)
                {
                    if( Bullets[i]->id != Enemeys[j]->src->id)
                    {
                        if(PointVsRect({ Bullets[i]->src.x, Bullets[i]->src.y }, Enemeys[j]->src ))
                        {
                            Enemeys[j]->src->life--;
                            cleateBlood(Bullets[i]->src.x, Bullets[i]->src.y );
                            playerScore += 10;
                            if(Enemeys[j]->src->life < 0)
                            {
                                delete Enemeys[j];
                                Enemeys[j] = NULL;
                                Enemeys.erase(Enemeys.begin() + j);
                            }
                            delete Bullets[i];
                            Bullets[i]  = NULL;
                            Bullets.erase(Bullets.begin() + i );
                            break;
                        }
                    }
                }
            }
        }
    }
}
