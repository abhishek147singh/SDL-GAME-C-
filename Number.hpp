Number::Number( SDL_Rect sr , int sx , int sy ,int sw , int sh){
      src = sr;
      x = sr.x;
      y = sr.y;
      numT = NumberT;
      clipW = sw / 10;
      clipH = sh / 10;
      clips[0] = {10 , 10 , 12 , 20};
      clips[1] = {25 , 10 , 10 , 20};
      clips[2] = {35 , 10 , 12 , 20};
      clips[3] = {48 , 10 , 12 , 20};
      clips[4] = {60 , 10 , 12 , 20};
      clips[5] = {75 , 10 , 12 , 20};
      clips[6] = {87 , 10 , 12 , 20};
      clips[7] = {102 , 10 , 12 , 20};
      clips[8] = {112 , 10 , 12 , 20};
      clips[9] = {129 , 10 , 12 , 20};
      fontW = 20;
}

void Number::render(std::string number , int c_x , int c_y , int c_w , int c_h){
       for(int i = 0; i < number.length(); i++){
          int n = number[i] - '0';
          if( n >= 0 && n <= 9){
              src = {  c_x +  i * c_w , c_y , c_w , c_h };
              SDL_RenderCopy( gRenderer , numT , &clips[n]  , &src);
        }
    }
}

