/**
  1. Booms object vector handler.
  2. delete the object from Booms vector when it's life over.
  3. draw all the Boom object from Boom vector.
**/
void drawBooms();

/**
  1. it takes position on screen.
  2. create Boom object and store it in Booms vector.
**/
void createBoom(int x, int y);

/**
  1. it's call the draw and update function of all the object of Boxes vector.
**/
void handelBoxs();

/**
  1. it's take z vector and player rectangle object as parameter.
  2. check collision between player and all the Box object.
  3. if any one is collided with player then store it into Boxs vector with it's contact time and rectangle object.
**/
void resoleForBoxHelper(std::vector<std::pair< float, Rectangle *>> &z, Rectangle* Rect);

/**
  1. it's take index of Rockets vector object and check collision with Boxes object.
  2. if any box if collided
      a) erase Rocket from Rockets object
      b) check Box object type and erase them accordingly.
**/
bool checkRockerWithBox( int i);

/**
  1. it's take x and y coordinate of explosion box and box id.
  2. imp explosion physics between explosion box and normal box.
**/
void explosionBoxVsBox(float x, float y, int id);

/**
  1. move camera with player.
  2. handle all the function of camera.
**/
void cameraHandler();

/**
  1. it draw and update all the object of Coins vector
  2. if coin have collected then erase from Coins vector.
**/
void DrawCoins();

/**
  1. read current level stage(grid 2D) vector from file and update plateform vector.
  2. after read stage then create required object and store push into object vectors respectively.
**/
void createPlateform();

/**
  1. reset player position.
  2. clear all object vectors.
  3. free the memory which is allocated.
**/
void clearObjects();

/**
  1. update the position of player
  2. select tiles rectangle that inside the screen and draw them
  3. update the player score
  4. call for resolve collision function to resolve collision between player and stage.
  5. if player life is over then reset position of player position with recent flag position.
**/
void drawRectangles();

/**
  1.show the player score , max score and collected coins on screen.
**/
void drawScore();

/**
  1. draw the start screen with buttons and handle mouse event.
**/
void drawStartWindow();

/**
  1. show the available level with number.
  2. handle mouse event.
**/
void drawLevels();

/**
  1. check the distance player and allEnemeys vector object if distance is less than 300 then push into Enemeys vector.
**/
void updateEnemeys();

/**
  1. compare between two Enemy object based on their distance between player and themself.
**/
bool comparetor(Enemey *e1, Enemey *e2);

/**
  1. first sort the all the Enemy object based on their distance from player.
  2. draw and update all Enemy object.
  3. if life of Enemy is less than 0 then erase from Enemy Vector.
**/
void drawEnemeys();

/**
  1. it take z  vector as refrences and player rectangle.
  2. check collision between Enemy objects and player if collision happed then push that Enemy rectangle into z vector with their contact time.
**/
void resoleForEnemeyHelper(std::vector<std::pair< float, Rectangle *>> &z, Rectangle* Rect);

/**
  1. it take index of rocket vector object.
  2. check collision between Enemy and Rocket. if collision then
        a) remove that rocket
        b) create Boom object
        c) decrement the life of Enemy
**/
void checkROcketWithEnemey( int i);

/**
  1. to handle mouse and keyboard event.
**/
void EventHandling(SDL_Event *e);

/**
  1. save the file at given path which given as platefrom vector formate.
**/
bool savePlateform(std::vector<std::string> plateform, std::string path );

/**
  1. read the file from given path and store it into plateform vector.
**/
void readPlateForm(std::string path);

/**
  1. read the level no , highScore , coins from given file path.
**/
void readGameData(std::string path);

/**
  1.save the game data(player score , coins , highScore ) in the from of file
**/
void writeGameData(std::string path);

/**
  1. save the level path in given file before create that level file.
**/
void saveLevelPath(std::string path, std::string levelPath);

/**
   1. to read the level file path which available in memory and push them into Level paths vector.
**/
void readLevelPaths(std::string path, std::vector<std::string> &LevelPaths);

/**
  1. it create the four rectangle of red color at the given position and push them into B_Cells vector.
**/
void cleateBlood(int x, int y);

/**
  1. it Draw and erase from B_Cells vector when life is over.
**/
void DrawBloodCells();

/**
   to feel that tiles is breaking into small pieces.
   1. it create four object of Brick class and push them into Bricks vector.
**/
void cleateBrick(int x, int y);

/**
  1. draw and delete(when life is over) all the object of Bricks vector.
**/
void DrawBricks();

/**
  1. draw and update all the object of Flags vector.
**/
void drawFlages();

/**
  1. it take player rectangle(to calculate required position) and direction(to hit the target).
  2. it create GunBullet object and push them into Bullets vector.
**/
void fireBullet(Rectangle *Rect, vec2d dir);

/**
 1. it draw , update the position and check the collision of all the object of Bullets vector with other object of game.
**/
void drawBullets();


/** collision check functions **/
bool PointVsRect(vec2d p, Rectangle* r);

bool PointVsRect2(vec2d p, SDL_Rect src);

bool RectVsRect(Rectangle* r1, Rectangle* r2);

bool sepreateAxies(Rectangle *r1, SDL_Rect r2);

bool RectVsRect2(rect r1, Rectangle* r2);

/**
  1. it takes follower rectangle , position of creation , player id
  2. it create Rocket object and push them into Rockets vector.

**/
void fireRocket(Rectangle *flw, int x, int y, int id);

/**
  1. it draw , update , check collision with other and erase them when life if over (objects of Rockets).
**/
void RocketHandler();

/**
  1. this function handle collision between enemy rectangle and other rectangle (ex:- player rectangle and enemy rectangles ).
  2. And to resolve collision , this function uses by ResolveDynamicRectVsRect function.
**/
void resoleForEnemeyHelper(std::vector<std::pair< float, Rectangle *>> &z, Rectangle* Rect);

/**
  1. this function handle collision between box rectangle and other rectangle (ex:- player rectangle and box rectangles  and enemy rectangles and box rectangles ).
  2. And to resolve collision , this function uses by ResolveDynamicRectVsRect function.
**/
void resoleForBoxHelper(std::vector<std::pair< float, Rectangle *>> &z, Rectangle* Rect);
