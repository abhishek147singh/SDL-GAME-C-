/** Coin start => **/
Coin::Coin(int x, int y, int diameter, int val)
{
    src =  new Rectangle(x, y, diameter, diameter);
    value = val;
    collected = false;
    rad = diameter / 2;
}

void Coin::update(Rectangle *Rect)
{
    if(RectVsRect(Rect, src))
    {
        collected = true;
        playerScore += value;
        coins++;
    }
}

bool Coin::isCollected()
{
    return collected;
}

void Coin::show()
{
    src->draw();
}

void DrawCoins()
{
    for(int i = 0; i < Coins.size(); i++)
    {
        Coins[i]->show();
        Coins[i]->update(player);
        if(Coins[i]->isCollected())
        {
            Mix_PlayChannel( -1, gCoinS, 0 );
            delete Coins[i];
            Coins[i] = NULL;
            Coins.erase(Coins.begin() + i);
        }
    }
}
