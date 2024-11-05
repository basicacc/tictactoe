#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<signal.h> //chatgpt
#include<unistd.h> //chatgpt

int turnX=0;
int turnO=0;
int n;
int iswindows=0;

int gamemode=0; //0=easy 1=hard

char Player1[200],Player2[200];
int Player1Score=0,Player2Score=0;
struct queuestruct{
    int x;
    int y;
    struct queuestruct *next;
} Xqueue,Oqueue,emptyforreplay;

#include"wincheck.h"
#include"printarray.h"


void findnullandadd(struct queuestruct *currentqueue,int row,int y,int x){
    if (currentqueue->x==-100){
        currentqueue->x=x;
        currentqueue->y=y;
        return;
    }
    while (currentqueue->next != NULL && row!=n) {
        currentqueue = currentqueue->next;
        row++;
    }
    currentqueue->next=(struct queuestruct *)malloc(sizeof(struct queuestruct));
    currentqueue->next->x = x;
    currentqueue->next->y = y;
    currentqueue->next->next = NULL;
}

void pushlist(struct queuestruct *currentqueue){
    if (currentqueue == NULL || currentqueue->next == NULL){
        return;
    }
    struct queuestruct *current=currentqueue;
    while(current->next !=NULL){
        current->x=current->next->x;
        current->y=current->next->y;
        current=current->next;
    }
    return;
}


void getlinecustom(char result[200]){
    char inputnow;
    int i;
    for(i=0;(inputnow=getchar())!='\n' && i<200;i++){
        result[i]=inputnow;
    }
    result[i]='\0';
}


int string_to_num(char astring[200]){
    int k=0;
    for(int i=0;i<200 && astring[i]!='\0';i++){
        k*=10;
        k+=astring[i]-'0';
    }
    return k;
}

bool errorcheck(char inputtocheck[200],char input2[200]){
    if(inputtocheck[3]!='\0') return 1;
    if(inputtocheck[0]<'1' || inputtocheck[0]>'9' || \
        inputtocheck[1]!=' ' || inputtocheck[2]<'1' ||\
        inputtocheck[2]>'9') return 1;
    inputtocheck[1]='\0';
    input2[0]=inputtocheck[2];
    input2[1]='\0';
    return 0;
}

bool errorforname(char inputtocheck[200]){
    for(int i=0;i<200 && inputtocheck[i]!='\0';i++){
        if (isalpha(inputtocheck[i])==0){
            return true;
        }
    }
    if(inputtocheck[0]=='\0'){
        return true; //if input is empty
    }
    return false;
}

void handle_sigint(int sig) { // Used Chatgpt to learn :(
    if(iswindows){
        system("taskkill /IM wmplayer.exe /F > nul 2>&1");
    }
    else{
        system("killall mpg123 1>/dev/null 2>&1");
    }
    exit(0); 
}

#include"playgame.h"

int main(int argc,char* argv[]){
    extern int gamemode;
    //remove file name from argument[0]
    int last;
    for(int i=0;i<200 && argv[0][i]!='\0';i++){
        if(argv[0][i]=='\\' || argv[0][i]=='/') last=i;
    }
    argv[0][last]='\0';
    char input[200];
    #ifdef _WIN32
        iswindows=1;
        system("chcp 65001 > nul");
    #endif

    signal(SIGINT, handle_sigint); //Chatgpt

    printf("Want some music? [Y/N]:");
    getlinecustom(input);
    while (input[1]!='\0' || (input[0]!='y' && input[0]!='Y' && input[0]!='n' && input[0]!='N')){
        printf("\nWrong Input!!! Only Y/N allowed!\n\nWant some music? [Y/N]:");
        getlinecustom(input);
    }
    if(input[0]=='y' || input[0]=='Y'){
        char systemcommand[200];
        if(!iswindows){
            sprintf(systemcommand,"ls --color \"%s/Musics\"",argv[0]);
            printf("\n");
            system(systemcommand);
            printf("\nWhich music you want? [name]:");
            getlinecustom(input);
            sprintf(systemcommand,"mpg123 %s/Musics/%s -q 1 > /dev/null 2>%s/.ErrorFile &",argv[0],input,argv[0]);
            system(systemcommand);
            printf("\nIn case you don't hear anything check %s/.ErrorFile\n",argv[0]);
        }
        else{ //Only some windows commands like start wmplayer from chatgpt others me
            sprintf(systemcommand,"dir \"%s\\Musics\" /B",argv[0]);
            printf("\n");
            system(systemcommand);
            printf("\nWhich music you want? [name]:");
            getlinecustom(input);
            sprintf(systemcommand,"start wmplayer \"%s\\Musics\\%s\" 2>\"%s\\ErrorFile\"",argv[0],input,argv[0]);
            system(systemcommand);
            printf("\nIn case you don't hear anything check %s\\ErrorFile\n",argv[0]);
        }
    }
    //GAME MODE

    printf("\nGame Mode [easy/hard]:");
    getlinecustom(input);
    while(strcmp(input,"easy") && strcmp(input,"hard")){
        printf("\nWrong input!!!\n\nGame Mode [easy/hard]:");
        getlinecustom(input);
    }
    if(strcmp(input,"hard")==0){
        printf("its hard");
        gamemode=1;
    }

    char Whoseturn[200];
    printf("\nPlayer 1 [name]:");
    getlinecustom(Player1);
    while(errorforname(Player1)){

        printf("\nWrong input!!! Only a/A-z/Z allowed!\n\nPlayer 1 [name]:");
        getlinecustom(Player1);
    }
    printf("Player 2 [name]:");
    getlinecustom(Player2);
    while(errorforname(Player2)){

        printf("\nWrong input!!! Only a/A-z/Z allowed!\n\nPlayer 2 [name]:");
        getlinecustom(Player2);
    }
    strcpy(Whoseturn,Player1);
    while(true){
        playgame(Whoseturn);
        printf("\nDo you want to play again? [Y/N]: ");
        getlinecustom(input);
        while (input[1]!='\0' || (input[0]!='y' && input[0]!='Y' && input[0]!='n' && input[0]!='N')){
            printf("\nWrong Input!!! Only Y/N allowed!\n\nDo you want to play again? [Y/N]: ");
            getlinecustom(input);
        }
        if(input[0]=='n' || input[1]=='N'){
            if(!iswindows){
                system("killall mpg123");
            }
            else{
                system("taskkill /IM wmplayer.exe /F"); //also this windows command from chatgpt
            }
            printf("Goodbye!");
            break;
        }
        else{
            Xqueue=emptyforreplay;
            Oqueue=emptyforreplay;
            turnO=0;
            turnX=0;
            printf("\nPlayers turn will be changed!\n\n");
            if(strcmp(Whoseturn,Player2)==0){
                strcpy(Whoseturn,Player1);
            }
            else{
                strcpy(Whoseturn,Player2);
            }
        }
    }
}