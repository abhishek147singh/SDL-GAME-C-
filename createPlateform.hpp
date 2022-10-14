void printHello()
{
    printf("Hello\n");
}

void startButtonHander()
{
    gStart = true;
    editorMode = false;
    levelsOpen = false;
    editPrev   = false;
    gameOver   = false;
    gameWin    = false;
    isWinSP    = false;
    isLSP      = false;
    isAnimationTime = false;
    createPlateform();
}

void rePlayFun()
{
    gStart = true;
    editorMode = false;
    levelsOpen = false;
    editPrev   = false;
    gameOver   = false;
    gameWin    = false;
    isAnimationTime = false;
    clearObjects();
    createPlateform();
}

void nextFun()
{
    if(selectedLevel + 1 < LevelPaths.size())
    {
        selectedLevel++;
    }
    rePlayFun();
}

void EditorButtonHandler()
{
    editorMode = true;
    gStart     = false;
    editPrev   = false;
    gameOver   = false;
    gameWin    = false;
    isWinSP    = false;
    isLSP      = false;
    isAnimationTime = false;
}

void EditPrevHandler()
{
    gStart = false;
    editorMode = false;
    editPrev = true;
    gameOver   = false;
    gameWin    = false;
    isWinSP    = false;
    isLSP      = false;
    levelsOpen = true;
}

void HelpHandler()
{
    gStart = false;
    editorMode = false;
    editPrev = true;
    gameOver   = false;
    gameWin    = false;
    isWinSP    = false;
    isLSP      = false;
    levelsOpen = false;
    Help = true;
}

void ExitButtonHandler()
{
    clearObjects();
    quit = true;
}

void BackHButtonHander()
{
    gStart = false;
    editorMode = false;
    levelsOpen = false;
    editPrev   = false;
    gameOver   = false;
    gameWin    = false;
    isWinSP    = false;
    isLSP      = false;
    isAnimationTime = false;
    Help = false;
    clearObjects();
}

void LevelsButtonHandler()
{
    gStart = false;
    editorMode = false;
    levelsOpen = true;
    editPrev   = false;
    gameOver   = false;
    gameWin    = false;
    isWinSP    = false;
    isLSP      = false;
    isAnimationTime = false;
    readLevelPaths("Data/levelPaths.txt", LevelPaths );
}

void upBtnHandler()
{
    if(gH->getY() >= 40)
        gH->setY(-5);
}

void downBtnHandler()
{
    if(gH->getY() <= 1420)
        gH->setY(5);
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    readGameData("Data/Score.txt");
    readLevelPaths("Data/levelPaths.txt", LevelPaths);

    boomT = loadTexture("img/boom.png");
    rocketT = loadTexture("img/Rocket.png");
    TileMapT = loadTexture("img/tiles_spritesheet.png");
    redSmile = loadTexture("img/redSmile.png");
    blueSmile = loadTexture("img/blueSmile.png");
    RedDotT = loadTexture("img/whiteDot.png");
    BackgroundT = loadTexture("img/greenBack.png");
    emptyT = loadTexture("img/empty.png");
    buttonT = loadTexture2("img/ButtonsTexture.png");
    buttonT2 = loadTexture2("img/ButtonsTexture2.png");
    starT    = loadTexture2("img/starts.png");
    flagT   = loadTexture2("img/Flages.png");
    ArrowT  = loadTexture2("img/arrows.png");
    NumberT = loadTexture("img/numbers.png");
    fireT   = loadTexture("img/Fire.png");
    wordsT  = loadTexture("img/GameWords2.png");
    BwordsT = loadTexture("img/GameWords.png");
    HelpT   = loadTexture("img/Help.png");

    //load sound Effects
    gExplosionS = loadSoundEffect("Music/explosion1.mp3");
    gExplosionS2   = loadSoundEffect("Music/explosion2.mp3");
    gLooseS     = loadSoundEffect("Music/loose.mp3");
    gGunShotS   = loadSoundEffect("Music/gunshot1.mp3");
    gCoinS      = loadSoundEffect("Music/coin.mp3");

    HighScoreR = new Rectangle(250, 10, 130, 40 );
    HighScoreR->txt = wordsT;
    HighScoreR->clip = { 208, 60, 110, 30};

    ScoreR = new Rectangle(10, 10, 130, 40 );
    ScoreR->txt = wordsT;
    ScoreR->clip = { 208, 30, 110, 30};

    CoinsR = new Rectangle(500, 10, 70, 40 );
    CoinsR->txt = wordsT;
    CoinsR->clip = { 208, 90, 64, 30};

    //HeartR
    HeartR = new Rectangle(28, 75, 25, 18 );
    HeartR->txt = ArrowT;
    HeartR->clip = { 300, 2, 142, 42};
//{ 10 , 260 , 65 , 60 } , { 420 , 260 , 65 , 60 }

    start  = new Button( 450, 100, 100, 40, { 195, 30, 100, 30 }, { 70, 30, 100, 30 }, BwordsT, &startButtonHander);
    Exit   = new Button( 450, 150, 50, 38,  { 195, 60, 50, 30 }, {  70, 60, 50, 30 }, BwordsT, &ExitButtonHandler);
    EditorBtn = new Button( 450, 200, 65, 40, { 195,120, 65, 30 }, { 70,120, 65, 30 }, BwordsT, &EditorButtonHandler);
    Levels = new Button( 450, 250, 65, 40, { 195,90, 65, 30 }, { 70,90, 65, 30 }, BwordsT,  &LevelsButtonHandler);
    Back   = new Button( 520, 50, 65, 40, { 197, 150,70, 30 }, { 70, 150,70, 30 }, BwordsT, &BackHButtonHander);
    EditPrev = new Button( 450, 300, 110, 40, { 195, 210, 110, 30 }, { 70, 210, 110, 30 }, BwordsT, &EditPrevHandler);
    HelpB  = new Button( 50, 400, 65, 30, { 210, 140, 50, 30}, { 90, 140, 50, 30}, wordsT, &HelpHandler);

    redDot = new Button2( 50, 50, 50, 50, { 0, 0, 64, 64}, RedDotT, '$' );

    nber = new Number({ 100, 100, 10, 10 },  0, 48, 10, 240 );

    AnimNumber = new AnimNum();

    player->txt = TileMapT;
    player->clip = { 710, 640, 50, 70};

    //Nothing to load
    return success;
}

void createPlateform()
{
    readPlateForm(LevelPaths[selectedLevel]);
    bgGroound.h = LEVEL_HEIGHT - bgSky.h;
    for(unsigned int i = 0; i < plateform.size(); i++)
    {
        for(unsigned int j = 0; j < plateform[i].length(); j++ )
        {
            if(plateform[i][j] == '#')
            {
                Rectangle *rec = new Rectangle(j * CELL_W, i * CELL_H, CELL_W, CELL_H );
                rec->isRigid = true;
                rec->txt = TileMapT;
                rec->clip = { 782, 571, 68, 66};
                Rects[i][j] = rec;
            }
            else if(plateform[i][j] == 'g')
            {
                Rectangle *rec = new Rectangle(j * CELL_W, i * CELL_H, CELL_W, CELL_H );
                rec->isRigid = true;
                rec->txt = TileMapT;
                rec->clip = { 499, 355, 68, 66};
                Rects[i][j] = rec;
            }

            else if(plateform[i][j] == '*')
            {
                Rectangle *rec = new Rectangle(j * CELL_W, i * CELL_H, CELL_W, CELL_H );
                rec->txt = TileMapT;
                rec->clip = { 571, 1, 67, 66};
                rec->life = 4;
                Rects[i][j] = rec;
            }
            else if(plateform[i][j] == '@')
            {
                Box *bx = new Box(j * CELL_W, i * CELL_H, 40, 40);
                bx->src->txt = TileMapT;
                bx->src->clip = { 143, 285, 68, 70 };
                Boxs.push_back(bx);
            }
            else if(plateform[i][j] == 't')
            {
                Box *bx = new Box(j * CELL_W, i * CELL_H, 40, 40);
                bx->src->txt = TileMapT;
                bx->isBoomBox = true;
                bx->src->clip = { 285, 355, 68, 70 };
                Boxs.push_back(bx);
            }
            else if(plateform[i][j] == 'o')
            {
                Box *bx = new Box(j * CELL_W, i * CELL_H, 40, 40);
                bx->src->txt = fireT;
                bx->isFire = true;
                bx->src->clip = { 0, 0, 64, 64};
                Boxs.push_back(bx);
            }
            else if(plateform[i][j] == 'e')
            {
                Enemey *en = new Enemey(j * CELL_W, i * CELL_H, 40, 40);
                en->src->txt = blueSmile;
                en->src->clip = { 0, 0, 50, 60};
                en->totalLife = 6;
                allEnemeys.push_back(en);
            }
            else if(plateform[i][j] == 'f')
            {
                Enemey *en = new Enemey(j * CELL_W, i * CELL_H, 40, 40);
                en->canFireGun = true;
                en->src->txt = redSmile;
                en->src->clip = { 0, 0, 50, 60};
                en->totalLife = 6;
                allEnemeys.push_back(en);
            }
            else if(plateform[i][j] == 'p')
            {
                Rectangle *rec = new Rectangle(j * CELL_W, i * CELL_H, CELL_W, CELL_H );
                rec->txt = TileMapT;
                rec->clip = { 0, 0, 68, 68};
                onlyForDraw.push_back(rec);
            }
            else if(plateform[i][j] == 'c')
            {
                Rectangle *rec = new Rectangle(j * CELL_W, i * CELL_H, CELL_W, CELL_H );
                rec->txt = TileMapT;
                rec->clip = { 215, 0, 68, 68};
                onlyForDraw.push_back(rec);
            }
            else if(plateform[i][j] == 'm') //=
            {
                Rectangle *rec = new Rectangle(j * CELL_W, i * CELL_H, CELL_W, CELL_H );
                rec->txt = TileMapT;
                rec->clip = { 440, 140,56, 66};
                onlyForDraw.push_back(rec);
            }
            else if(plateform[i][j] == 'n')
            {
                Coin *cn = new Coin( j * CELL_W, i * CELL_H, 50, 10);
                cn->src->txt = TileMapT;
                cn->src->clip = {230, 160, 40, 40 };
                Coins.push_back(cn);
            }
            else if(plateform[i][j] == 's')
            {
                Flage *f = new Flage( j * CELL_W, i * CELL_H - 50, 50, 100);
                Flages.push_back(f);
            }
        }
    }

    totalEnemeys = allEnemeys.size();
}

void clearObjects()
{
    player->src.x = 100;
    player->src.y = 80;
    playerScore   = 0;
    playerLife    = 6;
    totalChance   = 6;
    int i;

    for(auto itr = Rects.begin(); itr != Rects.end(); itr++)
    {
        for(auto it = itr->second.begin(); it != itr->second.end(); it++)
        {
            delete it->second;
            it->second = NULL;
        }
        itr->second.clear();
    }

    for(i = 0; i < onlyForDraw.size(); i++)
    {
        delete onlyForDraw[i];
        onlyForDraw[i] = NULL;
    }
    onlyForDraw.clear();

    for(i = 0; i < Boxs.size(); i++)
    {
        delete Boxs[i]->src;
        delete Boxs[i];
        Boxs[i] = NULL;
    }
    Boxs.clear();

    for(i = 0; i < allEnemeys.size(); i++)
    {
        delete allEnemeys[i]->src;
        delete allEnemeys[i];
        allEnemeys[i] = NULL;
    }
    allEnemeys.clear();

    for(i = 0; i < Enemeys.size(); i++)
    {
        delete Enemeys[i]->src;
        delete Enemeys[i];
        Enemeys[i] = NULL;
    }

    Enemeys.clear();

    for(i = 0; i < Coins.size(); i++)
    {
        delete Coins[i]->src;
        delete Coins[i];
        Coins[i] = NULL;
    }
    Coins.clear();

    for(i = 0; i < Flages.size(); i++)
    {
        delete Flages[i]->src;
        delete Flages[i];
        Flages[i] = NULL;
    }
    Flages.clear();

    for(int i = 0; i < Bullets.size(); i++)
    {
        delete Bullets[i];
        Bullets[i] = NULL;
    }
    Bullets.clear();

    for(int i = 0; i < Rockets.size(); i++)
    {
        delete Rockets[i];
        Rockets[i] = NULL;
    }
    Rockets.clear();

    for(int i = 0; i < Bricks.size(); i++)
    {
        delete Bricks[i]->src;
        delete Bricks[i];
        Bricks[i] = NULL;
    }
    Bricks.clear();
}

int counter = 0;
void drawRectangles()
{

    player->vel.x += player->acc.x;
    player->vel.y += player->acc.y;
    player->vel.y += gravity;
    player->draw();

    int x = (camera.x + SCREEN_WIDTH / 2 )/ CELL_W;
    int y = (camera.y + SCREEN_HEIGHT / 2)/ CELL_H;
    int n = 10, m = 12;

    if(player->src.x < SCREEN_WIDTH || player->src.x > LEVEL_WIDTH - SCREEN_WIDTH)
    {
        m = 12;
    }
    else
    {
        m = 7;
    }
    if(player->src.y < SCREEN_HEIGHT || player->src.y > LEVEL_HEIGHT - SCREEN_HEIGHT / 2)
    {
        n = 10;
    }
    else
    {
        n = 6;
    }

    if(isAnimationTime)
    {
        int p_x = player->src.x - camera.x - SCREEN_WIDTH / 2;
        int p_y = player->src.y - camera.y - SCREEN_HEIGHT / 2;
        int dist = sqrt(p_x * p_x + p_y * p_y);
        AnimNumber->getNum(camera.x + SCREEN_WIDTH / 2, camera.y + SCREEN_HEIGHT / 2);

        if(pDist < dist)
        {
            isAnimationTime = false;
        }
        pDist = dist;
    }

    for(int i = -n; i < n; i++)
    {
        for(int j = -m; j < m; j++ )
        {
            int px = x - j;
            int py = y - i;

            if(px >= 0 && py >= 0 && py < plateform.size() && px < plateform[0].length())
            {
                if(plateform[py][px] == '#' || plateform[py][px] == '*' || plateform[py][px] == 'g')
                {
                    Rects[py][px]->draw();
                }
            }
        }
    }



    if(counter > 100 && Enemeys.size() > 0 && Enemeys[0]->dist < 300)
    {
        fireRocket(Enemeys[0]->src, player->src.x, player->src.y, player->id);
        counter = 0;
    }
    counter++;
    ResolveDynamicRectVsRect(player);
    player->src.x += player->vel.x;
    player->src.y += player->vel.y;
    if(player->vel.x > 0) player->vel.x -= 0.08;
    else if(player->vel.x < 0) player->vel.x += 0.08;

    SDL_Rect playerLifeRect = { 25, 55, 120, 15};
    drawLife(playerLifeRect, player->life,6);
    for(int i = 0; i < 6; i++)
    {
        HeartR->dst.x = 26 + 20 * i;
        if(totalChance <= i ) HeartR->clip.y = 46;
        else HeartR->clip.y = 2;
        SDL_RenderCopy(gRenderer, HeartR->txt, &HeartR->clip, &HeartR->dst  );
    }

    if(playerScore > HighScore ) HighScore = playerScore;
    if(Coins.size() == 0)
    {
        gameWin = true;
        int rating = floor((((float)(totalEnemeys - Enemeys.size() - allEnemeys.size()))/ totalEnemeys) * 7 );
        gW->setStars(rating);
        if(!isWinSP)
            isWinSP = true;
    }
    else if(player->life < 0)
    {
        totalChance--;
        if(totalChance > 0)
        {
            player->life = 6;
            int index = 0;
            Uint32 MaxTime = 0;
            for(int i = 0; i < Flages.size(); i++)
            {
                if(Flages[i]->isSelected)
                {
                    if(Flages[i]->timeAtReach > MaxTime)
                    {
                        MaxTime = Flages[i]->timeAtReach;
                        index = i;
                    }
                }
            }

            if(Flages.size() > 0)
            {
                AnimNumber->setPositon(Flages[index]->src->src.x, Flages[index]->src->src.y, camera.x + SCREEN_WIDTH / 2, camera.y + SCREEN_HEIGHT / 2, 10);
                aOffsetX =  Flages[index]->src->src.x - camera.x - SCREEN_WIDTH / 2;
                aOffsetY =  camera.y + SCREEN_HEIGHT / 2 - Flages[index]->src->src.y;
                float dist = sqrt(aOffsetX * aOffsetX + aOffsetY * aOffsetY);
                aOffsetX /= dist;
                aOffsetY /= dist;
                pDist = dist;
                aOffsetX *= 6;
                aOffsetY *= 6;
                AnimNumber->offx = aOffsetX;
                AnimNumber->offy = aOffsetY;
                isAnimationTime = true;
                player->src.x = Flages[index]->src->src.x ;
                player->src.y = Flages[index]->src->src.y ;
            }
        }
        else
        {
            gameOver = true;
            int rating = floor((((float)(totalEnemeys - Enemeys.size() - allEnemeys.size()))/ totalEnemeys) * 7 );
            gO->setStars(rating);
            if(!isLSP) Mix_PlayChannel( -1, gLooseS, 0 );
            isLSP = true;
        }
    }
}

void drawScore()
{
    SDL_RenderCopy(gRenderer, HighScoreR->txt, &HighScoreR->clip, &HighScoreR->dst  );
    std::string st =  std::__cxx11::to_string(HighScore);
    nber->render(st, HighScoreR->src.x + HighScoreR->src.w, 22, 14, 30 );

    SDL_RenderCopy(gRenderer, ScoreR->txt, &ScoreR->clip, &ScoreR->dst  );
    st =  std::__cxx11::to_string(playerScore);
    nber->render(st, ScoreR->src.x + ScoreR->src.w, 22, 14, 30 );

    SDL_RenderCopy(gRenderer, CoinsR->txt, &CoinsR->clip, &CoinsR->dst  );
    st =  std::__cxx11::to_string(coins);
    nber->render(st, CoinsR->src.x + CoinsR->src.w, 22, 14, 28 );
}

void drawStartWindow()
{
    start->onClick({mouseX, mouseY});
    start->show();
    Exit->onClick({mouseX, mouseY});
    Exit->show();
    EditorBtn->onClick({mouseX, mouseY});
    EditorBtn->show();
    Levels->onClick({mouseX, mouseY});
    Levels->show();
    EditPrev->onClick({mouseX, mouseY});
    EditPrev->show();
    HelpB->onClick({mouseX, mouseY});
    HelpB->show();
}

void drawLevels()
{
    for(int i = 0; i < LevelPaths.size(); i++)
    {
        redDot->src.x = 50 + i * 80;
        redDot->src.y = 50;
        if(redDot->src.x > 400)
        {
            int y = redDot->src.x / 400;
            redDot->src.y = y * 80 + 50;
            redDot->src.x = redDot->src.x%400;
        }
        redDot->onClick({mouseX, mouseY});
        redDot->show();
        std::string st =  std::__cxx11::to_string(i + 1);
        nber->render(st, redDot->src.x + 15, redDot->src.y + 10, 14, 28 );
        if(redDot->isSelected && mouseDown)
        {
            selectedLevel = i;
            if(editPrev)
            {
                readPlateForm(LevelPaths[selectedLevel]);
                ed->loadEditor();
                editorMode = true;
                editPrev   = false;
            }
            else
            {
                startButtonHander();
            }
        }
        Back->show();
        Back->onClick({mouseX, mouseY});
    }
}



