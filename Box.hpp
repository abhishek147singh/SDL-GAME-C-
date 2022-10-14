/** Box start=> **/

Box::Box( int x, int y, int w, int h)
{
    src = new Rectangle(x, y, w, h );
    isBoomBox = false;
    isFire = false;
}

void Box::draw()
{
    src->draw();
}

void Box::seek(Rectangle* Rect)
{
    vec2d dir = {src->src.x - Rect->src.x, src->src.y - Rect->src.y};
    float len = sqrt(dir.x * dir.x + dir.y * dir.y);

    if(len <  Rect->src.w + 1)
    {
        dir.x /= len;
        dir.y /= len;
        src->vel =  { dir.x * 2, dir.y * 2 };
        if(isFire )  Rect->life--;
    }
}

void Box::explosion()
{
    int x = src->src.x / CELL_W;
    int y = src->src.y / CELL_H;
    int px, py;
    for(int i = 0; i < 8; i++)
    {
        px = directions[i].x;
        py = directions[i].y;
        if(plateform[y + py][x + px] == '*')
        {
            Rects[y + py][x + px]->life = -1;
            plateform[y + py][x + px] = '$';
        }
    }
    x  = src->src.x + src->src.w * 0.5;
    y  = src->src.y + src->src.h * 0.5;
    createBoom(x, y);
    px = player->src.x + player->src.w * 0.5;
    py = player->src.y + player->src.h * 0.5;
    float dist = sqrt((x - px) * (x - px) + (y - py) * (y - py));
    if(dist < 150)
    {
        vec2d dir = { x - px, y - py};
        dir.x /= dist;
        dir.y /= dist;
        dir = { dir.x * 5, dir.y * 5};
        player->vel.x -= dir.x;
        player->vel.y -= dir.y;
        player->life -= 2;
    }
    explosionBoxVsBox(x, y, src->id);
    for(int i = 0; i < Enemeys.size(); i++)
    {
        px = (x - Enemeys[i]->src->src.x);
        py = (y - Enemeys[i]->src->src.y);
        dist = sqrt( px * px + py * py );
        if(dist < 150)
        {
            vec2d dir = { x - Enemeys[i]->src->src.x, y - Enemeys[i]->src->src.y};
            dir.x /= dist;
            dir.y /= dist;
            dir = { dir.x * 5, dir.y * 5};
            Enemeys[i]->src->vel.x -= dir.x;
            Enemeys[i]->src->vel.y -= dir.y;
            Enemeys[i]->src->life -= 2;

        }
    }
}

void Box::update()
{
    if(abs( (int)player->src.x) - 500 > abs((int)src->src.x)) return;
    if(abs( (int)player->src.y) - 300 > abs((int)src->src.y)) return;

    src->vel.y += gravity;
    seek(player);
    for(int i = 0; i < Enemeys.size(); i++)
    {
        seek(Enemeys[i]->src);
    }
    ResolveDynamicRectVsRect(src);
    src->src.x += src->vel.x;
    src->src.y += src->vel.y;
    if(src->vel.x > 0)
    {
        src->vel.x -= 0.2;
    }
    else if(src->vel.x < 0)
    {
        src->vel.x += 0.2;
    }
}

/** Box  <= end **/

void handelBoxs()
{
    for(int i = 0; i < Boxs.size(); i++)
    {
        Boxs[i]->draw();
        Boxs[i]->update();
    }
}

void resoleForBoxHelper(std::vector<std::pair< float, Rectangle *>> &z, Rectangle* Rect)
{
    vec2d contact_point, contact_normal;
    float contact_time = 0.0f;
    for(int i = 0; i < Boxs.size(); i++)
    {
        if(Boxs[i]->src->id !=  Rect->id)
        {
            if (DynamicRectVsRect( Rect, Boxs[i]->src, contact_point, contact_normal, contact_time))
            {
                if(Rect->id == player->id && contact_normal.y != 1) player_jump = 2;
                z.push_back({contact_time, Boxs[i]->src });
            }
        }
    }
}

bool checkRockerWithBox( int i)
{
    bool check = false;
    for(int j = 0; j < Boxs.size(); j++)
    {

        if(RectVsRect2( Rockets[i]->src, Boxs[j]->src ))
        {
            if(Boxs[j]->isBoomBox )
            {
                Mix_PlayChannel( -1, gExplosionS, 0 );
                Boxs[j]->explosion();
                delete Boxs[j];
                Boxs[j] = NULL;
                Boxs.erase(Boxs.begin() + j);
                createBoom(Rockets[i]->src.x, Rockets[i]->src.y);
            }
            delete Rockets[i];
            Rockets[i]  = NULL;
            Rockets.erase(Rockets.begin() + i );
            check = true;
            break;
        }
    }
    return check;
}
void explosionBoxVsBox(float x, float y, int id)
{
    float px, py;

    for(int i = 0; i < Boxs.size(); i++)
    {
        if(Boxs[i]->src->id != id)
        {
            px = Boxs[i]->src->src.x + Boxs[i]->src->src.w * 0.5;
            py = Boxs[i]->src->src.y + Boxs[i]->src->src.h * 0.5;
            float dist = sqrt((x - px) * (x - px) + (y - py) * (y - py));
            if(dist < 150)
            {
                vec2d dir = { x - px, y - py};
                dir.x /= dist;
                dir.y /= dist;
                dir = { dir.x * 5, dir.y * 5};
                Boxs[i]->src->vel.x -= dir.x;
                Boxs[i]->src->vel.y -= dir.y;

            }
        }
    }
}


