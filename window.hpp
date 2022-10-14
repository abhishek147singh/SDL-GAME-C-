/** Stars class start**/
Stars::Stars() { }

Stars::Stars(int x,int y,int w,int h)
{
    this->src = {x, y, w, h};
    this->RatingIndex = 0;
    this->clip[0] = {0, 0, 100, 100};
    this->clip[1] = {100, 0, 100, 100};
    this->clip[2] = {200, 0, 100, 100};
}

void Stars::setIndex(int index){
    this->RatingIndex = index;
}

void Stars::draw()
{
    SDL_RenderCopy(gRenderer, starT, &this->clip[this->RatingIndex] , &this->src);
}

/** stars class end**/

/**Game win window start */
win::win(int x,int y, int w, int h)
{
    this->MainRect = { x, y, w, h };
    this->topBar   = { x, y, w, 25};
    this->textSrc  = { x + 145, y + 175, 80, 30};
    this->textClip = { 10, 580, 180, 35};
    this->cancel = new Button( x + w - 28, y, 25, 25, { 140, 50, 40, 50 }, { 140, 10, 40, 50 }, ArrowT, &BackHButtonHander);
    this->rePlay = new Button( x + 65, y + 240, 100, 25, { 0, 640, 150, 50 }, { 400, 640, 150, 50 }, buttonT2, &rePlayFun);
    this->next   = new Button( x + 200, y + 240, 100, 25, { 0, 705, 150, 50 }, { 400, 705, 150, 50 }, buttonT2, &nextFun);
    this->stars[0]  = new Stars(x + 75, y + 100, 70, 70);
    this->stars[1]  = new Stars(x + 145, y + 50, 70, 70);
    this->stars[2]  = new Stars(x + 215, y + 100, 70, 70);
}

void win::draw()
{
    SDL_SetRenderDrawColor(gRenderer, 232, 232, 232, 0xFF );
    SDL_RenderFillRect(gRenderer, &this->MainRect);
    SDL_SetRenderDrawColor(gRenderer, 220, 220, 220, 0xFF );
    SDL_RenderFillRect(gRenderer, &this->topBar);
    this->cancel->onClick({mouseX, mouseY});
    this->cancel->show();
    this->rePlay->onClick({mouseX, mouseY});
    this->rePlay->show();
    this->next->onClick({mouseX, mouseY});
    this->next->show();

    for(int i = 0; i < 3; i++)
        this->stars[i]->draw();
    SDL_RenderCopy(gRenderer, buttonT2, &this->textClip, &this->textSrc);
}

void win::setStars(int rating){
    if(rating < 1){
       this->stars[0]->setIndex(2);
       this->stars[1]->setIndex(2);
       this->stars[2]->setIndex(2);
    }
    else if( rating < 2){
       this->stars[0]->setIndex(1);
       this->stars[1]->setIndex(2);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 3){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(2);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 4){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(1);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 5){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(0);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 6){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(0);
       this->stars[2]->setIndex(1);
    }
    else {
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(0);
       this->stars[2]->setIndex(0);
    }
}


/**
 Game win window end
**/

/**
 Game Over window start
**/
GOver::GOver(int x,int y, int w, int h)
{
    this->MainRect = { x, y, w, h };
    this->topBar   = { x, y, w, 25};
    this->textSrc  = { x + 145, y + 175, 80, 30};
    this->textClip = { 0, 540, 180, 35};
    this->cancel = new Button( x + w - 28, y, 25, 25, { 140, 50, 40, 50 }, { 140, 10, 40, 50 }, ArrowT, &BackHButtonHander);
    this->rePlay = new Button( x + 135, y + 240, 100, 25, { 0, 640, 150, 50 }, { 400, 640, 150, 50 }, buttonT2, &rePlayFun);
    this->stars[0]  = new Stars(x + 75, y + 100, 70, 70);
    this->stars[1]  = new Stars(x + 145, y + 50, 70, 70);
    this->stars[2]  = new Stars(x + 215, y + 100, 70, 70);
}

void GOver::setStars(int rating){
    if(rating < 1){
       this->stars[0]->setIndex(2);
       this->stars[1]->setIndex(2);
       this->stars[2]->setIndex(2);
    }
    else if( rating < 2){
       this->stars[0]->setIndex(1);
       this->stars[1]->setIndex(2);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 3){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(2);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 4){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(1);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 5){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(0);
       this->stars[2]->setIndex(2);
    }
    else if(rating < 6){
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(0);
       this->stars[2]->setIndex(1);
    }
    else {
       this->stars[0]->setIndex(0);
       this->stars[1]->setIndex(0);
       this->stars[2]->setIndex(0);
    }
}

void GOver::draw()
{
    SDL_SetRenderDrawColor(gRenderer, 232, 232, 232, 0xFF );
    SDL_RenderFillRect(gRenderer, &this->MainRect);
    SDL_SetRenderDrawColor(gRenderer, 220, 220, 220, 0xFF );
    SDL_RenderFillRect(gRenderer, &this->topBar);
    this->cancel->onClick({mouseX, mouseY});
    this->cancel->show();
    this->rePlay->onClick({mouseX, mouseY});
    this->rePlay->show();
    for(int i = 0; i < 3; i++)
        this->stars[i]->draw();
    SDL_RenderCopy(gRenderer, buttonT2, &this->textClip, &this->textSrc);
}

/**
 Game Over window end
**/


/**
 Help window start
 */

HelpWin::HelpWin(int x,int y, int w, int h)
{
    this->MainRect = { x, y, w, h };
    this->topBar   = { x, y, w, 25};
    this->textSrc  = { x + 10, y + 30, w - 20, h - 40 };
    this->textClip = { 0, 40, 395, h - 50 };
    this->cancel = new Button( x + w - 28, y, 25, 25, { 140, 50, 40, 50 }, { 140, 10, 40, 50 }, ArrowT, &BackHButtonHander);
    this->up   = new Button( x + w - 28, y + 25, 25, 25, { 0, 50, 50, 50 }, { 0, 46, 52, 54 }, ArrowT, &upBtnHandler);
    this->down = new Button( x + w - 28, y + h - 30, 25, 25, { 50, 50, 50, 50 }, { 50, 50, 52, 54 }, ArrowT, &downBtnHandler);
}

void HelpWin:: draw()
{
    SDL_SetRenderDrawColor(gRenderer, 232, 232, 232, 0xFF );
    SDL_RenderFillRect(gRenderer, &this->MainRect);
    SDL_SetRenderDrawColor(gRenderer, 220, 220, 220, 0xFF );
    SDL_RenderFillRect(gRenderer, &this->topBar);
    SDL_RenderCopy(gRenderer, HelpT, &this->textClip, &this->textSrc);
    this->cancel->onClick({mouseX, mouseY});
    this->cancel->show();
    this->up->onClick({mouseX, mouseY});
    this->up->show();
    this->down->onClick({mouseX, mouseY});
    this->down->show();
}

int HelpWin::getY()
{
    return this->textClip.y;
}

void HelpWin::setY(int y)
{
    this->textClip.y += y;
}

/**
 Help window end
 */



