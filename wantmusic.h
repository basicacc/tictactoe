void wantmusic(char **argv){
    printf("Want some music? [Y/N]:");
    getlinecustom(input);
    while (input[1]!='\0' || (tolower(input[0])!='y' && tolower(input[0])!='n')){
        printf("\nWrong Input!!! Only Y/N allowed!\n\nWant some music? [Y/N]:");
        getlinecustom(input);
    }
    if(tolower(input[0]=='y')){
        char systemcommand[200];
        musicstarted=1;
        if(!iswindows){
            sprintf(systemcommand,"ls --color \"%s/Musics\"",*argv);
            printf("\n");
            system(systemcommand);
            printf("\nWhich music you want? [name]:");
            getlinecustom(input);
            sprintf(systemcommand,"mpg123 %s/Musics/%s -q 1 > /dev/null 2>%s/.ErrorFile &",*argv,input,*argv);
            system(systemcommand);
            printf("\nIn case you don't hear anything check %s/.ErrorFile\n",*argv);
        }
        else{ //(Only some windows commands like start wmplayer from chatgpt) everything else mine
            sprintf(systemcommand,"dir \"%s\\Musics\" /B",*argv); //using sprintf to format a string easily and use it as system command
            printf("\n");
            system(systemcommand);
            printf("\nWhich music you want? [name]:");
            getlinecustom(input);
            sprintf(systemcommand,"start wmplayer \"%s\\Musics\\%s\" 2>\"%s\\ErrorFile\"",*argv,input,*argv);
            system(systemcommand);
            printf("\nIn case you don't hear anything check %s\\ErrorFile\n",*argv);
        }
    }
}