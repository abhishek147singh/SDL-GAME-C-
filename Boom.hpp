Boom::Boom(int x, int y, int w, int h)
{
    this->src  = { x - camera.x, y  - camera.y, w, h};
    this->clip = { 0, 0, 200, 180};
    this->frame = 0;
    this->timer = 0;
    this->totalFrame = 4;
    this->txt = boomT;
}

void Boom::draw()
{
    if(this->timer % 4 == 0)
    {
        this->frame++;
    }
    this->timer++;
    this->clip.x = this->frame * this->clip.w;
    SDL_RenderCopy(gRenderer, this->txt, &this->clip, &this->src);
}

void drawBooms()
{
    for(unsigned int i = 0; i < Booms.size(); i++)
    {
        Booms[i]->draw();
        if(Booms[i]->frame == Booms[i]->totalFrame)
        {
            delete Booms[i];
            Booms[i] = NULL;
            Booms.erase(Booms.begin() + i);
        }
    }
}

void createBoom(int x, int y)
{
    Boom *bm = new Boom(x - 50, y - 50, 100, 100);
    Booms.push_back(bm);
    bm = NULL;
}
