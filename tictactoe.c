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
int musicstarted=0;
int gamemode=0; //0=easy 1=hard

char input[200],input2[200];
char Player1[200],Player2[200];

int Player1Score=0,Player2Score=0;
struct queuestruct{
    int x;
    int y;
    struct queuestruct *next;
} Xqueue,Oqueue,emptyforreplay;



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

void handle_sigint(int sig) {
    if(iswindows){
        system("taskkill /IM wmplayer.exe /F > nul 2>&1");
    }
    else{
        system("killall mpg123 >/dev/null");
    }
    exit(0); 
}

#include"wincheck.h"
#include"printarray.h"
#include"wantmusic.h"
#include"playgame.h"

int main(int argc,char* argv[]){
    //remove file name from argument[0]
    int last; //gonna store last / or '\\' location digit
    for(int i=0;i<200 && argv[0][i]!='\0';i++){
        if(argv[0][i]=='\\' || argv[0][i]=='/') last=i; //find last
    }
    argv[0][last]='\0'; //if we make the last one NULL when we specify %s it will read till it see NULL
    
    #ifdef _WIN32 //if program run in windows
        iswindows=1; //making global variable "iswindows" true
        system("chcp 65001 > nul"); //necessary command to run in cmd to be able to see unicode characters
    #endif

    signal(SIGINT, handle_sigint); //(Used chatgpt) Basically SIGINT is equal to Ctrl+C with this command,
                                   // if Ctrl+C is pressed it will run the void handle_sigint
    wantmusic(argv); //Ask if it wants music
    //GAME MODE
    printf("\nGame Mode [easy/hard]:");
    getlinecustom(input);
    while(strcmp(input,"easy") && strcmp(input,"hard")){ //strcmp will compare strings of input, it must be either easy or hard to stop loop
        printf("\nWrong input!!!\n\nGame Mode [easy/hard]:"); //basically strcmp outputs different number of chars in 2 strings
        getlinecustom(input); //my custom getline function to make things easier and stable
    }
    if(strcmp(input,"hard")==0){
        gamemode=1; //going to change global gamemode variable to make game hard
    }

    //Whose turn is it
    char Whoseturn[200];
    printf("\nPlayer 1 [name]:");
    getlinecustom(Player1);
    while(errorforname(Player1)){ //errorforname function needs to be false to stop loop

        printf("\nWrong input!!! Only a/A-z/Z allowed!\n\nPlayer 1 [name]:");
        getlinecustom(Player1);
    }
    printf("Player 2 [name]:");
    getlinecustom(Player2);
    while(errorforname(Player2)){

        printf("\nWrong input!!! Only a/A-z/Z allowed!\n\nPlayer 2 [name]:");
        getlinecustom(Player2);
    }
    strcpy(Whoseturn,Player1); //Automatically makes Player1 first one to start instead of asking who is going to start

    //Game starts
    while(true){
        playgame(Whoseturn); //starts game with who is going to start
        printf("\nDo you want to play again? [Y/N]: ");
        getlinecustom(input);
        //Error check
        while (input[1]!='\0' || (tolower(input[0])!='y'&& tolower(input[0])!='n')){
            printf("\nWrong Input!!! Only Y/N allowed!\n\nDo you want to play again? [Y/N]: ");
            getlinecustom(input);
        }
        //If players wants to exit, game gonna kill every task it started
        if((tolower(input[0])=='n')){ //it asks if we started music or not, then kills process
            if(!iswindows && musicstarted){
                system("killall mpg123");
            }
            else if (musicstarted){
                system("taskkill /IM wmplayer.exe /F"); //(used chatgpt) taskkill will stop process named wmplayer.exe
            }
            printf("Goodbye!");
            break;
        }
        else{ //if player decides to play again we reset everything
            Xqueue=emptyforreplay;
            Oqueue=emptyforreplay;
            turnO=0;
            turnX=0;
            printf("\nPlayers turn will be changed!\n\n"); //also changing who is going to start
            if(strcmp(Whoseturn,Player2)==0){
                strcpy(Whoseturn,Player1);
            }
            else{
                strcpy(Whoseturn,Player2);
            }
        }
    }
}