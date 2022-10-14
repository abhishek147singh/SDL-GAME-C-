
class centiped{
     std::string centiped_name = "";
     int x , y;
     int w , h;
     char Dir;
     std::string name;
     public:
     centiped(){
         x = y = w = h =0;
         Dir = 'N';
         name = "";
     }
     centiped( std::string n, int x1 ,int y1 , int x2 , int y2 , char D){
         x = x1;
         y = y1;
         w = abs(x2 - x1) + 1;
         h = abs(y2 - y1) + 1;
         char Dir = D;
         name = n;
     }

    std::string getName(){
        return name;
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }

    void inRangeMove(){
        drawRect({0xFF , 0 , 0 , 0xFF } , { x , y , 40 , 40});
        switch (Dir)
        {
        case 'N':
            if(y - 1 < 0) Dir = 'S';
            else y--;

            break;
        case 'S':
            if(y + 1 > N - 1) Dir = 'N';
            else y++;

            break;
        case 'W':
            if(x - 1 < 0) Dir = 'E';
            else x--;

            break;
        case 'E':
            if(x + 1 > N - 1) Dir = 'W';
            else x++;

            break;
        default:
            break;
        }
    }

    bool collided(int x2 , int y2 , int w2 , int h2){
        return (x < x2 + w2 && x + w > x2 && y < y2 + h2 && y + h > y2);
    }

};
