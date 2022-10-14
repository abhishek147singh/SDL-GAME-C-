bool savePlateform(std::vector<std::string> plateform, std::string path )
{
    bool flag = true;
    FILE *fp;
    fp = fopen(path.c_str(), "w+");
    if(fp == NULL) flag = false;
    for(int i = 0; i < plateform.size(); i++)
    {
        plateform[i].push_back('\n');
        fprintf(fp, plateform[i].c_str() );
    }
    fclose(fp);
    printf("your data save successfully\n");
    return flag;
}

void readPlateForm(std::string path)
{
    FILE *fp;
    fp = fopen(path.c_str(), "r");

    plateform.clear();

    std::string str = "";
    char ch;
    while(1)
    {
        ch = fgetc(fp);

        if(ch == EOF || ch == '\n')
        {
            plateform.push_back(str);
            str = "";
            if(ch == EOF)
            {
                break;
            }
        }
        else
        {
            str.push_back(ch);
        }
    }

    fclose(fp);
    LEVEL_WIDTH  = CELL_W * plateform[0].length();
    LEVEL_HEIGHT = CELL_H * plateform.size();

}


void readGameData(std::string path)
{
    FILE *file;

    if (file = fopen(path.c_str(), "r"))
    {
        fscanf(file,"%d \t %d \t %d ", &levelNo, &HighScore, &coins );
    }

    fclose(file);
}


void writeGameData(std::string path)
{
    FILE *file;

    if (file = fopen(path.c_str(), "w"))
    {
        fprintf(file,"%d \t %d \t %d ", levelNo, HighScore, coins);
    }

    fclose(file);
}

void saveLevelPath(std::string path, std::string levelPath)
{
    FILE *file;
    if (file = fopen(path.c_str() , "a" ))
    {
        fprintf(file,"\t%s", levelPath.c_str());
    }
    fclose(file);
}

void readLevelPaths(std::string path, std::vector<std::string> &LevelPaths)
{
    FILE *file;
    char Buff[255];
    if (file = fopen(path.c_str(), "r"))
    {
        LevelPaths.clear();
        while (fscanf(file, "\t%s", Buff) != EOF)
        {
            std::string st(Buff);
            LevelPaths.push_back(st);
        }
    }
}
