AnimNum::AnimNum()
{
    x = 0;
    y = 0;
    h = 0;
    k = 0;
    meg = 0;
    offx = 0;
    offy = 0;
}

void AnimNum::setPositon(int x,int y,int h,int k,int meg)
{
    this->x = x;
    this->y = y;
    this->h = h;
    this->k = k;
    this->meg = meg;
    this->accDist = (x - h) * (x - h) + (y - k) * (y * k);
}

void AnimNum::getNum(int c_x,int c_y)
{
    this->currDist   =  (x - c_x) * (x - c_x) + (y - c_y) * (y * c_y);
    if(this->accDist != 0.0f)
        this->percentage = this->currDist / this->accDist;
    this->temp = this->percentage - 0.5;
    if(this->percentage >= 0.5f) this->percentage -= (this->temp * 2);

    if(this->percentage <= 0.0f)
    {
        aOffsetX = this->offx * 2;
        aOffsetY = this->offy * 2;

    }
    else
    {
        aOffsetX = this->offx * (this->percentage * this->meg + 2);
        aOffsetY = this->offy * (this->percentage * this->meg + 2);
    }
}

