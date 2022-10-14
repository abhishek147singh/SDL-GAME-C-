/** BloodCell start => **/
BloodCell::BloodCell(int x, int y, int w, int h)
{
    src = new Rectangle(x, y,w, h);
    life = 25;
}

void  BloodCell::Draw()
{
    src->calDst();
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0, 0xFF );
    SDL_RenderFillRect( gRenderer, &(src->dst) );

    life--;
    src->vel.x = src->acc.x;
    src->vel.y += src->acc.y;
    src->src.x += src->vel.x;
    src->src.y += src->vel.y;
    src->acc.y += 0.04f;
}

/**  BloodCell end <= **/

void cleateBlood(int x, int y)
{
    BloodCell *b1 = new BloodCell(x + 2, y - 2, 2, 2);
    b1->src->acc = { -0.5, -0.3};
    BloodCell *b2 = new BloodCell(x + 2, y + 2, 2, 3);
    b2->src->acc = { 0.5, -0.3};
    BloodCell *b3 = new BloodCell(x - 2, y - 2, 3, 2);
    b3->src->acc = { -0.5, -0.2};
    BloodCell *b4 = new BloodCell(x - 2, y + 2, 2, 2);
    b4->src->acc = { 0.5, -0.2};

    B_Cells.push_back(b1);
    B_Cells.push_back(b2);
    B_Cells.push_back(b3);
    B_Cells.push_back(b4);
}

void DrawBloodCells()
{

    for(int i = 0; i < B_Cells.size(); i++)
    {
        B_Cells[i]->Draw();
        if(B_Cells[i]->life < 0)
        {
            delete B_Cells[i]->src;
            delete B_Cells[i];
            B_Cells[i] = NULL;
            B_Cells.erase( B_Cells.begin() + i);
        }
    }
}

/** Brick start => **/

Brick::Brick(int x, int y, int w, int h, int type)
{
    src = new Rectangle(x, y, w, h);
    src->txt = TileMapT;
    if(type)
    {
        src->clip = {570, 780, 20, 20};
    }
    else
    {
        src->clip = {590, 780, 20, 10};
    }

}

void Brick::draw()
{
    src->draw();
    life--;
    src->vel.x = src->acc.x;
    src->vel.y += src->acc.y;

    int x = src->src.x / CELL_W;
    int y = (src->src.y + CELL_H / 2) / CELL_H;
    if(x < 0 || y < 0 || y >= plateform.size() || x >= plateform[0].length()) return;
    if(plateform[y][x] == '#' || plateform[y][x] == '*' || plateform[y][x] == 'g')
    {
        y = y * CELL_H - src->src.h;
        src->src.y = y;
    }
    else
    {
        src->src.x += src->vel.x;
        src->src.y += src->vel.y;
        src->acc.y += 0.04f;
        if(src->acc.y > 0.8f) src->acc.y = 0.8f;
    }
}

/** Brick end <= **/
void cleateBrick(int x, int y)
{
    Brick *b1 = new Brick(x + 2, y - 2, 10, 15, 1);
    b1->src->acc = { -0.5, -0.3};
    Brick *b2 = new Brick(x + 2, y + 2, 15, 10, 0);
    b2->src->acc = { 0.5, -0.3};
    Brick *b3 = new Brick(x - 2, y - 2, 12, 15, 1);
    b3->src->acc = { -0.5, -0.2};
    Brick *b4 = new Brick(x - 2, y + 2, 12, 12, 0);
    b4->src->acc = { 0.5, -0.2};
    Brick *b5 = new Brick(x, y, 15, 15, 0);
    b5->src->acc = { 0.0, -0.2};

    Bricks.push_back(b1);
    Bricks.push_back(b2);
    Bricks.push_back(b3);
    Bricks.push_back(b4);
    Bricks.push_back(b5);
}

void DrawBricks()
{
    for(int i = 0; i < Bricks.size(); i++)
    {
        Bricks[i]->draw();
        if(Bricks[i]->life < 0)
        {
            delete Bricks[i]->src;
            delete Bricks[i];
            Bricks[i] = NULL;
            Bricks.erase( Bricks.begin() + i);
        }
    }
}


