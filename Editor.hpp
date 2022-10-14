/** editor class start **/

   Editor::Editor(int pMargin , int BottTabH , int noRow , int noCol){
       margin = pMargin;
       Width = SCREEN_WIDTH - 2*margin;
       Height = SCREEN_HEIGHT - 2*margin - BottTabH;
       editorCamera = { 0 , 0 , Width , Height};
       src = { margin , margin , Width , Height };
       BottomTabH = BottTabH;
       C_W =  50;
       C_H =  50;
       selectedID = '.';

       for(int i = 0; i <noRow; i++ ){
         std::string st = "";
         for(int j = 0; j < noCol; j++ ){
            if(i == 0 || j == 0 || i == noRow - 1 || j ==  noCol - 1)
               st.push_back('#');
            else
               st.push_back('.');
         }
         stage.push_back(st);
       }

       tabButtons[0] = new Button2( margin ,          418 , 50 , 50 , { 499 , 355 , 68 , 66}  , TileMapT , 'g');
       tabButtons[1] = new Button2( margin + 52 ,     418 , 50 , 50 , { 782 , 571 , 68 , 66}  , TileMapT , '#');
       tabButtons[2] = new Button2( margin + 52 * 2 , 418 , 50 , 50 , { 571 , 1 , 67 , 66}  , TileMapT , '*');
       tabButtons[3] = new Button2( margin + 52 * 3,  418 , 50 , 50 , { 143 , 285 , 68 , 70 }  , TileMapT , '@');
       tabButtons[4] = new Button2( margin + 52 * 4,  418 , 50 , 50 , { 285, 355 , 68 , 70 }  , TileMapT , 't');
       tabButtons[5] = new Button2( margin + 52 * 5,  418 , 50 , 50 , { 0  , 0   , 32 , 32 }  , emptyT , '.');
       tabButtons[6] = new Button2( margin + 52 * 6,  418 , 50 , 50 , {  0 , 0 , 50 , 60 }  , redSmile , 'f');
       tabButtons[7] = new Button2( margin + 52 * 7,  418 , 50 , 50 , {  0 , 0 , 50 , 60 }  , blueSmile , 'e');

       tabButtons[8]  = new Button2( margin ,  475 , 50 , 50 , {230 , 160 , 40 , 40 }  , TileMapT , 'n');
       tabButtons[9]  = new Button2( margin + 52 ,  475 , 50 , 50 , { 0 , 0 , 68 , 68}  , TileMapT , 'p');
       tabButtons[10] = new Button2( margin + 52 * 2 ,  475 , 50 , 50 , { 215 , 0 , 68 , 68}  , TileMapT , 'c');
       tabButtons[11] = new Button2( margin + 52 * 3,  475  , 50 , 50 , { 440 , 140 ,56 , 66}  , TileMapT , 'm');
       tabButtons[12] = new Button2( margin + 52 * 4,  475  , 50 , 50 , {0 , 0 , 120 , 280}  , flagT , 's');
       tabButtons[13] = new Button2( margin + 52 * 5,  475  , 50 , 50 , {0 , 0 , 64 , 64}  , fireT , 'o');

       ArrowButton[0] = new Button2( Width - margin / 2 ,  SCREEN_HEIGHT / 2 , 30 , 30 , { 0 , 0 , 50 , 50 }  , ArrowT , '$');
       ArrowButton[1] = new Button2( 0     ,  SCREEN_HEIGHT / 2 , 30 , 30 , { 50 , 0 , 50 , 50 }  , ArrowT , '$');
       ArrowButton[2] = new Button2( SCREEN_WIDTH / 2 - margin / 2 ,  Height - margin /2 , 30 , 30 , { 0 , 50 , 50 , 50 }  , ArrowT , '$');
       ArrowButton[3] = new Button2( SCREEN_WIDTH / 2 - margin / 2 ,  0 , 30 , 30 , { 50 , 50 , 50 , 50 }  , ArrowT , '$');
       ArrowButton[4] = new Button2( margin ,        -8 , 30 , 30 ,        { 110 , 0 , 30 , 50 }  , ArrowT , '$');
       ArrowButton[5] = new Button2( margin + 60  ,  -8 , 30 , 30 ,        { 110 , 50 , 30 , 50 }  , ArrowT , '$');
       ArrowButton[6] = new Button2( margin + Width - 22  ,  10 , 30 , 30 , { 140 , 58 , 50 , 50 }  , ArrowT , '$');
       ArrowButton[7] = new Button2( margin + Width - 70  ,  margin + Height ,  65 , 40 , { 0 , 340 , 75 , 32 }  , buttonT , '$');
       ArrowButton[8] = new Button2( margin + Width - 140  ,  margin + Height ,  65 , 40 , { 0 , 370, 75 , 32 }  , buttonT , '$');
       ArrowButton[9] = new Button2( margin + 100 ,    -9 , 30 , 20 ,        { 180 , 0 , 60 , 30 }  , ArrowT , '$');
       ArrowButton[10] = new Button2( margin + 140  ,  -4 , 30 , 20 ,        { 180  , 40 , 70 , 30 }  , ArrowT , '$');
       ArrowButton[11] = new Button2( margin + 180  ,  -9 , 30 , 20 ,        { 240  , 0 , 60 , 30 }   , ArrowT , '$');
       ArrowButton[12] = new Button2( margin + 220  ,  -4 , 30 , 20 ,        { 180  , 72 , 70 , 30 }  , ArrowT , '$');
       ArrowButton[13] = new Button2( margin + 52 * 8,  418 , 50 , 50 ,      { 0 , 50 , 50 , 50 }  , ArrowT , '$');
       ArrowButton[14] = new Button2( margin + 52 * 8,  475 , 50 , 50 ,      { 50  , 50 , 50 , 50 }  , ArrowT , '$');

       Width  = C_W * stage[0].length();
       Height = C_H * stage.size();
       for(int i = 0; i < 14; i++){
           Txts[tabButtons[i]->id] = tabButtons[i];
       }
   }

   Editor::~Editor(){
       for(int i = 0; i < 14; i++){
          delete tabButtons[i];
       }
       for(int i = 0; i < 15; i++){
          delete ArrowButton[i];
       }
   }
   void Editor::reset(){
      for(int i = 0; i < stage.size(); i++){
         for(int j = 0; j < stage[0].length(); j++){
            if(i == 0 || j == 0 || i == stage.size() - 1 || j ==  stage[0].length() - 1)
               stage[i][j] = '#';
            else
               stage[i][j] = '.';
         }
      }
   }

   void Editor::update(){
       for(int i = 0; i < 14; i++){
          if(tabButtons[i]->isSelected){
             printf("%c ", tabButtons[i]->id);
             selectedID = tabButtons[i]->id;
          }
       }
       bool onButtonClick = false;

       for(int i = 0; i < 15; i++){
          if(mouseDown && ArrowButton[i]->isSelected){
              onButtonClick = true;
              if(i == 0){
                 editorCamera.x += C_W;
              }else if(i == 1){
                editorCamera.x  -= C_W;
              }else if(i == 2){
                 editorCamera.y += C_H;
              }else if(i == 3){
                editorCamera.y  -= C_H;
              }
              else if(i == 4){
                 C_W += 1;
                 C_H += 1;
                 Width  = C_W * stage[0].length();
                 Height = C_H * stage.size();
              }
              else if(i == 5){
                 C_W -= 1;
                 C_H -= 1;
                 Width  = C_W * stage[0].length();
                 Height = C_H * stage.size();
              }else if(i == 6){
                 editorMode = false;
              }else if(i == 7){
                 std::string st =  std::__cxx11::to_string(levelNo);
                 std::string path = "Levels/Level" + st + ".txt";
                 printf(path.c_str());
                 saveLevelPath("Data/levelPaths.txt" , path);
                 if(savePlateform(stage , path)){
                    editorMode = false;
                 }
                 levelNo++;
              }else if(i == 8){
                 reset();
               }else if(i == 9){
                  reSize(stage.size() , stage[0].length() + 1);
               }else if(i == 10){
                  reSize(stage.size() + 1 , stage[0].length());
               }else if(i == 11){
                  reSize(stage.size() , stage[0].length() - 1);
               }
                else if(i == 12){
                  reSize(stage.size() - 1, stage[0].length());
               }
               else if(i == 13){
                  for(int i = 0; i < 8; i++){
                    tabButtons[i]->src.y = 475;
                  }
                  for(int i = 8; i < 14; i++){
                    tabButtons[i]->src.y = 418;
                  }

                  SDL_Delay(100);
                  ArrowButton[13]->src.y = 475;
                  ArrowButton[14]->src.y = 418;
               }
               else if(i == 14){
                  for(int i = 0; i < 8; i++){
                    tabButtons[i]->src.y = 418;
                  }
                  for(int i = 8; i < 14; i++){
                    tabButtons[i]->src.y = 475;
                  }
                  SDL_Delay(100);
                  ArrowButton[13]->src.y = 418;
                  ArrowButton[14]->src.y = 475;
               }
              break;
          }
       }

      int x = (mouseX - margin + editorCamera.x) / C_W;
      int y = (mouseY - margin + editorCamera.y) / C_H;

      if( PointVsRect2({mouseX , mouseY} , src) && !onButtonClick && y < stage.size() && y >= 0 && x < stage[0].length() && x >= 0){
         SDL_Rect dst = { x * C_W + margin - editorCamera.x  , y * C_H + margin - editorCamera.y , C_W , C_H };
         SDL_SetRenderDrawColor(gRenderer ,0 , 0xFF , 0xFF , 0xFF);
         SDL_RenderDrawRect(gRenderer , &dst );
         if(mouseDown){
             stage[y][x] = selectedID;
         }
      }

   }

   void Editor::reSize(int row , int col){
       if(row <= 0 || col <= 0) return;
       std::vector<std::string> Helper;

       for(int i = 0; i <row; i++ ){
          std::string st = "";
          for(int j = 0; j < col; j++ ){
            if(i == 0 || j == 0 || i == row - 1 || j ==  col - 1)
               st.push_back('#');
            else
                if(i > 8)
                   st.push_back('*');
                else
                   st.push_back('.');
          }
          Helper.push_back(st);
       }

       for(int i = 1; i < stage.size() - 1; i++){
          if( i >= row ) break;
          for(int j = 1; j < stage[0].length() - 1; j++){
              if(j >= col) break;
              Helper[i][j] = stage[i][j];
          }
       }

      stage.clear();
      stage = Helper;
      Width  = C_W * stage[0].length();
      Height = C_H * stage.size();
   }

   void Editor::loadEditor(){
      stage = plateform;
      Width  = C_W * stage[0].length();
      Height = C_H * stage.size();
   }
   void Editor::show(){
        drawRect({200 , 200 , 200 , 0xFF} , src);

        for(int i = 0; i <= stage.size(); i++){
           drawLine({ margin - editorCamera.x  , margin + i * C_H - editorCamera.y } , { margin +  Width - editorCamera.x  , margin  + i * C_H - editorCamera.y } , { 0 , 0 , 0 , 0xFF } );
        }

        for(int i = 0; i <= stage[0].length(); i++){
            drawLine({ margin + i * C_W  - editorCamera.x , margin - editorCamera.y } , { margin + i * C_W  - editorCamera.x , margin + Height - editorCamera.y } , { 0 , 0 , 0 , 0xFF } );
        }
        SDL_Rect dst;
        for(int i = 0; i < stage.size(); i++){
            for(int j = 0; j < stage[0].length(); j++){
                dst = { j * C_W + margin - editorCamera.x , i * C_H + margin - editorCamera.y , C_W , C_H };
                if(Txts.find(stage[i][j]) != Txts.end() && stage[i][j] != '.'){
                    SDL_RenderCopy(gRenderer , Txts[stage[i][j]]->nTex , &Txts[stage[i][j]]->nClip , &dst);
                }
            }
        }
        for(int i = 0;i < 14; i++){
            tabButtons[i]->show();
            tabButtons[i]->onClick({mouseX , mouseY});
        }

        for(int i = 0;i < 15; i++){
            ArrowButton[i]->show();
            ArrowButton[i]->onClick({mouseX , mouseY});
        }

        update();
   }
/** editor class end **/

