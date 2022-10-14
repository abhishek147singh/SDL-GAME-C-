class vec2d
{
public:
    float x;
    float y;
    vec2d();

    vec2d(float px, float py);

};


class rect
{
public:
    float x;
    float y;
    float w;
    float h;

    rect();

    rect(float px, float py, float pw,float ph);

};

class Rectangle
{
public:
    rect src;
    SDL_Rect dst;
    SDL_Rect clip;
    vec2d vel;
    vec2d acc;
    SDL_Texture *txt;
    int id;
    int life;
    bool isRigid;

    Rectangle();

    Rectangle( float x, float y, float w, float h);

    void calDst();

    void draw();

};

class Boom
{
public:
    SDL_Rect src;
    SDL_Rect clip;
    int frame;
    int totalFrame;
    int timer;
    SDL_Texture *txt;

    Boom(int x, int y, int w, int h);

    void draw();
};



class Box
{
public:
    Rectangle* src;
    bool isBoomBox;
    bool isFire;
    vec2d collV;
    Box( int x, int y, int w, int h);

    void draw();

    void seek(Rectangle* Rect);

    void explosion();

    void update();
};

class Coin
{
public:
    Rectangle *src;
    int value;
    bool collected;
    float rad;

    Coin(int x, int y, int diameter, int val);

    void update(Rectangle *Rect);

    bool isCollected();

    void show();
};


class Enemey
{
public:
    Rectangle* src;
    int maxSpeed;
    int totalLife;
    bool canFireGun;
    int timer;
    float dist;
    vec2d dir;

    Enemey( int x, int y, int w, int h);

    void draw();

    void seek();

    void update();
};



class BloodCell
{
public:
    Rectangle *src;
    int life;

    BloodCell(int x, int y, int w, int h);

    void Draw();
};


class Brick
{
public:
    Rectangle *src;
    int life = 255;
    Brick(int x, int y, int w, int h, int type);

    void draw();
};

class Flage
{
public:
    Rectangle *src;
    bool isSelected;
    Uint32 timeAtReach;

    Flage(int x, int y, int w, int h );

    void update();

    void draw();
};

class GunBullet
{
public:
    rect src;
    vec2d vel;
    vec2d dir;
    SDL_Rect dst;
    int id;

    GunBullet();

    GunBullet( float x, float y, int Pw, int Ph, vec2d v, vec2d d);

    void update();
};

class Rocket
{
public:
    rect src;
    SDL_Rect dst;
    Rectangle* follow;
    vec2d vel;
    int maxSpeed;
    int id;
    int initialBost;
    int life;

    Rocket(float x, float y, Rectangle *flw);

    void draw();

    void seek();

    void update();

};

class Button
{
    SDL_Texture* nTex;
    SDL_Rect src;
    SDL_Rect nClip;
    SDL_Rect hClip;
    bool isSelected;
    void (*func)();

public:

    Button();

    Button(int x, int y, int w, int h, SDL_Rect nCip, SDL_Rect hCip, SDL_Texture *nTexture, void (*fun )(void));

    void onClick(SDL_Point p );

    void show();
};

class Button2
{
public:
    SDL_Texture* nTex;
    SDL_Rect src;
    SDL_Rect nClip;
    char id;
    bool isSelected;
    bool hover;


    Button2();

    Button2(int x, int y, int w, int h, SDL_Rect Cip, SDL_Texture *nTexture, char ID);

    void onClick(SDL_Point p );

    void show();
};

class Editor{
   public:
   int margin;
   int Width;
   int Height;
   int C_W;
   int C_H;
   int BottomTabH;
   char selectedID;
   SDL_Rect src;
   SDL_Rect editorCamera;
   Button2* tabButtons[14];
   Button2* ArrowButton[15];
   int tabCameraY = 0;
   std::map<char , Button2*> Txts;
   std::vector<std::string> stage;

    Editor(int pMargin , int BottTabH , int noRow , int noCol);

   ~Editor();

   void reset();

   void update();

   void reSize(int row , int col);

   void loadEditor();

   void show();
};


class Stars
{
    SDL_Rect src;
    SDL_Rect clip[3];
    int RatingIndex;

public:
    Stars();

    Stars(int x,int y,int w,int h);

    void draw();

    void setIndex(int index);
};

class win
{
    SDL_Rect MainRect;
    SDL_Rect topBar;
    SDL_Rect textSrc;
    SDL_Rect textClip;
    Button* cancel;
    Button* rePlay;
    Button* next;
    Stars*  stars[3];

public:

    win(int x,int y, int w, int h);

    void draw();

    void setStars(int rating);
};

class GOver
{
    SDL_Rect MainRect;
    SDL_Rect topBar;
    SDL_Rect textSrc;
    SDL_Rect textClip;
    Button* cancel;
    Button* rePlay;
    Stars*  stars[3];

public:

    GOver(int x,int y, int w, int h);

    void draw();

    void setStars(int rating);
};

class Number
{
    SDL_Texture *numT;
    SDL_Rect src;
    SDL_Rect clips[10];
    int clipW;
    int clipH;
    int fontW;
    int x, y;

public:
    Number( SDL_Rect sr, int sx, int sy,int sw, int sh);

    void render(std::string number, int c_x, int c_y, int c_w, int c_h);
};


class AnimNum
{
    int x, y; //start position
    int h, k; //end position
    int meg;//need to increment
    float accDist, currDist, percentage, temp;

public:
    float offx, offy;

    AnimNum();//to set the default value

    void setPositon(int x,int y,int h,int k,int meg);    // to set required value for calculaation

    void getNum(int c_x,int c_y); //this function generate the number based on percentage how much camera was travel path.
};


class HelpWin
{
    SDL_Rect MainRect;
    SDL_Rect topBar;
    SDL_Rect textSrc;
    SDL_Rect textClip;
    Button* cancel;
    Button* up;
    Button* down;

public:

    HelpWin(int x,int y, int w, int h);
    void draw();
    int getY();
    void setY(int y);
};


