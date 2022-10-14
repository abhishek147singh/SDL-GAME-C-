/** Flage start => **/

Flage::Flage(int x, int y, int w, int h )
{
    src = new Rectangle(x, y, w, h);
    src->clip = {10, 15, 80, 170};
    src->txt = flagT;
    isSelected = false;
}

void Flage::update()
{
    if( !isSelected && RectVsRect(src, player ))
    {
        isSelected = true;
        timeAtReach = SDL_GetTicks();
    }
}

void Flage::draw()
{
    if(isSelected)
    {
        src->clip.x = 120;
    }
    src->draw();
}

/** Flage end <=  **/

void drawFlages()
{
    for(int i = 0; i < Flages.size(); i++)
    {
        Flages[i]->draw();
        Flages[i]->update();
    }
}
