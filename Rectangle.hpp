#include <algorithm>
#include <functional>

/** vec2d class discription  start =>**/
vec2d::vec2d(){
    this->x  = 0;
    this->y  = 0;
}

vec2d::vec2d(float px , float py){
   this->x = px;
   this->y = py;
 }

/** vec2d class discription <= end**/


/** rect class discription  start =>**/

rect::rect(){
    this->x = 0.0f;
    this->y = 0.0f;
    this->w = 0.0f;
    this->h = 0.0f;
  }

rect::rect(float px , float py , float pw ,float ph){
    this->x = px;
    this->y = py;
    this->w = pw;
    this->h = ph;
  }

/** rect class discription <= end**/

/** rectangle class discription  start =>**/

Rectangle::Rectangle(){
      this->src = { 0 , 0 , 0 , 0};
      this->vel = { 0 , 0};
      this->acc = { 0 , 0};
      this->txt = NULL;
      this->id = rand();
      this->life = 5;
      isRigid = false;
}

Rectangle::Rectangle( float x , float y , float w , float h){
    this->src = { x , y , w , h };
    this->dst = { x , y , w , h };
    this->vel = { 0 , 0};
    this->acc = { 0 , 0};
    this->txt = NULL;
    this->id = rand();
    this->life = 5;
    this->isRigid = false;
 }

void Rectangle::calDst(){
    this->dst = {src.x - camera.x , src.y - camera.y , src.w , src.h };
}

void Rectangle::draw(){
    calDst();
    SDL_RenderCopy(gRenderer , txt , &clip , &dst );
}

/** rectangle class discription <= end**/

bool PointVsRect(vec2d p, Rectangle* r)
{
    return (p.x >= r->src.x && p.y >= r->src.y && p.x < r->src.x + r->src.w && p.y < r->src.y + r->src.h);
}

bool PointVsRect2(vec2d p, SDL_Rect src)
{
    return (p.x >= src.x && p.y >= src.y && p.x < src.x + src.w && p.y < src.y + src.h);
}

bool RectVsRect(Rectangle* r1, Rectangle* r2)
{
    return (r1->src.x < r2->src.x + r2->src.w && r1->src.x + r1->src.w > r2->src.x && r1->src.y < r2->src.y + r2->src.h && r1->src.y + r1->src.h > r2->src.y);
}

bool RectVsRect2(rect r1, Rectangle* r2)
{
    return (r1.x < r2->src.x + r2->src.w && r1.x + r1.w > r2->src.x && r1.y < r2->src.y + r2->src.h && r1.y + r1.h > r2->src.y);
}




