#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<signal.h> 
#include<unistd.h> 
#include<time.h>

//time

time_t t;
struct tm *current_time;

//time

FILE *fp;

int win_condition;
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
    if (currentqueue->x==-100){ //default value for x if it is first time changing
        currentqueue->x=x;
        currentqueue->y=y;
        return;
    }
    while (currentqueue->next != NULL && row!=n) { //moving on row
        currentqueue = currentqueue->next;
        row++;
    }
    currentqueue->next=(struct queuestruct *)malloc(sizeof(struct queuestruct)); //allocating space for a pointer
    currentqueue->next->x = x;
    currentqueue->next->y = y;
    currentqueue->next->next = NULL; //setting next pointer as NULL just in case
}

void pushlist(struct queuestruct *currentqueue){
    if (currentqueue == NULL || currentqueue->next == NULL){
        return;
    }
    while(currentqueue->next !=NULL){
        currentqueue->x=currentqueue->next->x; //assign next struct's x to current one (pushing behind to front)
        currentqueue->y=currentqueue->next->y;
        currentqueue=currentqueue->next;
    }
    return;
}


void getlinecustom(char result[200]){ //custom getline to make things easier
    char inputnow;
    int i=0;
    for(i=0;(inputnow=getchar())!='\n' && inputnow!=EOF && i<200;i++){
        result[i]=inputnow;
    }
    result[i]='\0';
    if(inputnow==EOF){
        if(iswindows){
            system("taskkill /IM wmplayer.exe /F > nul 2>&1");
        }
        else{
            system("killall mpg123");

        }
        printf("\nEOF detected!");
        exit(0);
    }

}


bool errorforname(char inputtocheck[200]){
    for(int i=0;i<200 && inputtocheck[i]!='\0';i++){ //Move till it see NULL
        if (isalpha(inputtocheck[i])==0){ //must be alpha else return true (meaning there is error)
            return true;
        }
    }
    if(inputtocheck[0]=='\0'){
        return true; //if input is empty
    }
    return false;
}

void handle_sigint() { //thats the function going to run when Ctrl + C is pressed
    putchar('\n');
    if(iswindows){
        system("taskkill /IM wmplayer.exe /F > nul 2>&1");
    }
    else{
        system("killall mpg123");

    }
    time(&t);
    current_time = localtime(&t); //localizing time
    printf("\nGoodbye!\n");
    fprintf(fp,"\nGame ended! [%d-%02d-%02d %02d:%02d]\n***\n",
    current_time->tm_year + 1900,
    current_time->tm_mon + 1,
    current_time->tm_mday,
    current_time->tm_hour,                       //print out time in log file
    current_time->tm_min
    );
    exit(0); 
}

#include"winconditions.h"
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

    sprintf(input,"%s/log_file.log", argv[0]); //location of log file
    fp = fopen(input,"a"); //open log file
    
    #ifdef _WIN32 //if program run in windows
        iswindows=1; //making global variable "iswindows" true
        system("chcp 65001 > nul"); //necessary command to run in cmd to be able to see unicode characters
    #endif

    signal(SIGINT, handle_sigint); // Basically SIGINT is equal to Ctrl+C with this command,
                                   // if Ctrl+C is pressed it will run the void handle_sigint
    
    wantmusic(argv); //Ask if player wants music
    
    //GAME MODE
    printf("\nGame Mode [easy/hard]:");
    getlinecustom(input);
    while(strcasecmp(input,"easy") && strcasecmp(input,"hard")){ //strcmp will compare strings of input, it must be either easy or hard to stop loop
        printf("\n\033[31mWrong input!!!\033[0m\n\nGame Mode [easy/hard]:"); //basically strcmp outputs different number of chars in 2 strings
        getlinecustom(input); //my custom getline function to make things easier and stable
    }
    if(strcasecmp(input,"hard")==0){
        gamemode=1; //going to change global gamemode variable to make game hard
    }

    //Whose turn is it
    char Whoseturn[200];
    printf("\nPlayer 1 [name]:");
    getlinecustom(Player1);
    while(errorforname(Player1)){ //errorforname function needs to be false to stop loop

        printf("\n\033[31mWrong input!!! Only a/A-z/Z allowed!\033[0m\n\nPlayer 1 [name]:");
        getlinecustom(Player1);
    }
    printf("Player 2 [name]:");
    getlinecustom(Player2);
    while(errorforname(Player2) || !strcmp(Player1,Player2)){

        if (strcmp(Player1, Player2) == 0) {
            printf("\n\033[31mWrong input!!! Names must be unique!\033[0m\n\nPlayer 2, please choose a different name: ");
            getlinecustom(Player2);
        } else {
            printf("\n\033[31mWrong input!!! Only a/A-z/Z allowed!\033[0m\n\nPlayer 2 [name]:");
            getlinecustom(Player2);
        }
    }
    strcpy(Whoseturn,Player1); //Automatically makes Player1 first one to start instead of asking who is going to start


    //Game starts
    time(&t);
    current_time = localtime(&t); //localizing time
    fprintf(fp,"\n***\nGame started!  [%d-%02d-%02d %02d:%02d]\n",
           current_time->tm_year + 1900,
           current_time->tm_mon + 1,
           current_time->tm_mday,
           current_time->tm_hour,                       //print out time in log file
           current_time->tm_min);

    while(true){
        playgame(Whoseturn); //starts game with who is going to start
        
        printf("\nDo you want to play again? [Y/N]: ");
        getlinecustom(input);
        //Error check
        while (input[1]!='\0' || (tolower(input[0])!='y'&& tolower(input[0])!='n')){
            printf("\n\033[31mWrong Input!!! Only Y/N allowed!\033[0m\n\nDo you want to play again? [Y/N]: ");
            getlinecustom(input);
        }
        //If players wants to exit, game gonna kill every task it started
        if((tolower(input[0])=='n')){ //it asks if we started music or not, then kills process
            if(!iswindows && musicstarted){
                char systemcomm[400];
                system("killall mpg123");
            }
            else if (musicstarted){
                system("taskkill /IM wmplayer.exe /F"); //taskkill will stop process named wmplayer.exe
            }
            printf("\nGoodbye!\n");

            time(&t);
            current_time = localtime(&t); //localizing time
            fprintf(fp,"\nGame ended! [%d-%02d-%02d %02d:%02d]\n***\n",
            current_time->tm_year + 1900,
            current_time->tm_mon + 1,
            current_time->tm_mday,
            current_time->tm_hour,                       //print out time in log file
            current_time->tm_min
            );

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
            fprintf(fp,"\nReplaying! [%d-%02d-%02d %02d:%02d]\n\n",
            current_time->tm_year + 1900,
            current_time->tm_mon + 1,
            current_time->tm_mday,
            current_time->tm_hour,                       //print out time in log file
            current_time->tm_min
            );
        }
    }
}