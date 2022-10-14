/** Button class start => **/
 Button::Button(){
     nTex = NULL;
     isSelected = false;
   }

Button::Button(int x , int y , int w , int h , SDL_Rect nCip , SDL_Rect hCip , SDL_Texture *nTexture , void (*fun )(void)){
      src = { x , y , w , h};
      nTex = nTexture;
      nClip = nCip;
      hClip = hCip;
      func = fun;
      isSelected = false;
   }

void Button::onClick(SDL_Point p ){
        if(p.x >= src.x && p.y >= src.y && p.x < src.x + src.w && p.y < src.y + src.h){
            isSelected = true;
            if(mouseDown){
                func();
            }
        }else{
            isSelected = false;
        }
   }

void Button::show(){
        if(isSelected){
            SDL_RenderCopy(gRenderer , nTex , &hClip , &src );
        }else{
            SDL_RenderCopy(gRenderer , nTex , &nClip , &src );
        }
   }

/** Button class end <= **/

/** Button2 class start => **/
 Button2::Button2(){
     nTex = NULL;
     isSelected = false;
   }

Button2::Button2(int x , int y , int w , int h , SDL_Rect Cip , SDL_Texture *nTexture , char ID){
      src = { x , y , w , h};
      nTex = nTexture;
      nClip = Cip;
      isSelected = false;
      id = ID;
   }
void Button2::onClick(SDL_Point p ){
        if(p.x >= src.x && p.y >= src.y && p.x < src.x + src.w && p.y < src.y + src.h){
             if(mouseDown){
                 isSelected = true;
             }
             hover = true;
        }else{
             isSelected = false;
             hover = false;
        }
   }

void Button2::show(){
        SDL_RenderCopy(gRenderer , nTex , &nClip , &src );
        if(hover){
            SDL_SetRenderDrawColor(gRenderer ,0 , 0xFF , 0xFF , 0xFF);
            SDL_RenderDrawRect(gRenderer , &src );
        }
   }
/** Button2 class end <= **/
