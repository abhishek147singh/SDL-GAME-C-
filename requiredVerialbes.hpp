//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int CELL_W = 50;
const int CELL_H = 50;

int mouseX;
int mouseY;
bool mouseDown;
bool editorMode = false;
bool editPrev   = false;
bool levelsOpen = false;
bool gameWin = false;
bool gameOver = false;
bool Help     = false;
float aOffsetX = 0;
float aOffsetY = 0;
int pDist      = 0;
int flagX  = 0;
int flagY  = 0;
bool isAnimationTime = false;


//Main loop flag
bool quit = false;

std::vector<std::string> plateform  =
{
    "####################################################",
    "#..................................................#",
    "#..................................................#",
    "#...........****...................********........#",
    "#....****...............#..@.................#.....#",
    "#.....@@..............###***####...................#",
    "#..m.@.t.p#.......c...#........#..p......m......c..#",
    "#gggggggggg....ggggggggg......ggggggg..ggggg...gggg#",
    "#..................................................#",
    "#..........................................****....#",
    "#...............******.t..........*******..........#",
    "#...................t..tt....**....................#",
    "#......******.......******.........................#",
    "#..f.t..e..........................................#",
    "####################################################"
};

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
int LEVEL_WIDTH  = CELL_W * plateform[0].length();
int LEVEL_HEIGHT = CELL_H * plateform.size();
int levelNo;
int HighScore    = 0;
int coins       = 0;
int totalChance = 6;
int totalEnemeys = 0;

std::vector<std::string> LevelPaths =
{
    "Levels/Level1.txt"
};
int selectedLevel = 0;


SDL_Texture *boomT = NULL;
SDL_Texture *rocketT = NULL;
SDL_Texture *TileMapT = NULL;
SDL_Texture *redSmile = NULL;
SDL_Texture *blueSmile = NULL;
SDL_Texture *buttonT = NULL;
SDL_Texture *buttonT2 = NULL;
SDL_Texture *NumberT = NULL;
SDL_Texture *ArrowT  = NULL;
SDL_Texture *RedDotT = NULL;
SDL_Texture *BackgroundT = NULL;
SDL_Texture *emptyT    = NULL;
SDL_Texture *flagT    = NULL;
SDL_Texture *fireT    = NULL;
SDL_Texture *starT    = NULL;
SDL_Texture *wordsT   = NULL;
SDL_Texture *BwordsT  = NULL;
SDL_Texture *HelpT    = NULL;

//The sound effects that will be used
Mix_Chunk *gExplosionS = NULL;
Mix_Chunk *gGunShotS = NULL;
Mix_Chunk *gExplosionS2 = NULL;
Mix_Chunk *gLooseS = NULL;
Mix_Chunk *gCoinS = NULL;

//required Buttons
Button *start  = NULL;
Button *EditorBtn = NULL;
Button *EditPrev = NULL;
Button *Levels = NULL;
Button *Exit   = NULL;
Button *Back   = NULL;
Button *HelpB   = NULL;

Button2 *redDot = NULL;

Rectangle *HighScoreR = NULL;
Rectangle *ScoreR     = NULL;
Rectangle *CoinsR     = NULL;
Rectangle *HeartR     = NULL;

Editor* ed   = NULL;
HelpWin* gH  = NULL;
win* gW      = NULL;
GOver* gO    = NULL;
Number* nber = NULL;
AnimNum *AnimNumber = NULL;

//player
int playerScore = 0;
int playerLife  = 6;
int prevPlayerLife = 6;
const float gravity = 0.45;
int player_jump = 2;
bool gStart = false;
bool upButton = false;
bool isWinSP  = false;
bool isLSP    = false;


std::vector<Rectangle *> onlyForDraw;

std::vector<Boom *> Booms;

std::vector<Box *> Boxs;

std::vector<Coin *> Coins;

std::vector<Enemey *> Enemeys;

std::vector<Enemey *> allEnemeys;

std::vector<BloodCell *> B_Cells;

std::vector<Brick *> Bricks;

std::vector<Flage *> Flages;

std::vector<GunBullet *> Bullets;

std::vector<Rocket *> Rockets;

std::map< int, std::map< int, Rectangle*>> Rects;

Rectangle *player = new Rectangle( 100, 80, 40, 40 );
SDL_Rect bgSky = { 0, 0, SCREEN_WIDTH, 400 };
SDL_Rect bgGroound = { 0, 400, SCREEN_WIDTH, 400 };

vec2d directions[8] = {{ 0, 1 }, {0, -1}, { 1, 0}, {-1, 0}, { 1, 1}, {-1, -1}, { -1, 1 }, {1, -1}};

