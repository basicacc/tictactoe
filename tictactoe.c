#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
int turnX=0;
int turnO=0;
int n;

char Player1[200],Player2[200];
int Player1Score=0,Player2Score=0;
struct queuestruct{
    int x;
    int y;
    struct queuestruct *next;
} Xqueue,Oqueue,emptyforreplay;

#include"wincheck.h"
#include"printarray.h"

void findnullandadd(struct queuestruct *currentqueue,int row,int x,int y){
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




int string_to_num(char astring[200]){
    int k=0;
    for(int i=0;i<200 && astring[i]!='\0';i++){
        k*=10;
        k+=astring[i]-'0';
    }
    return k;
}

bool errorcheck(char inputtocheck[200]){
    if(inputtocheck[0]=='\0') return 1;
    for (int i=0;i<200 && inputtocheck[i]!='\0';i++){
        if (inputtocheck[i]<'0'|| inputtocheck[i]>'9'){
            return 1;
        }
    }
    return 0;
}

bool errorforname(char inputtocheck[200]){
    for(int i=0;i<200 && inputtocheck[i]!='\0';i++){
        if (isalpha(inputtocheck[i])==0){
            return true;
        }
    }
    return false;
}

#include"playgame.h"

int main(){
    #ifdef _WIN32
        system("chcp 65001");
    #endif
    
    char Whoseturn[200];
    printf("Player 1 [name]:");
    scanf("%s",Player1);
    while(errorforname(Player1)){

        printf("\nWrong input!!! Only a/A-z/Z allowed!\nPlayer 1 [name]:");
        scanf("%s",Player1);
    }
    printf("Player 2 [name]:");
    scanf("%s",Player2);
    while(errorforname(Player2)){

        printf("\nWrong input!!! Only a/A-z/Z allowed!\nPlayer 1 [name]:");
        scanf("%s",Player2);
    }
    strcpy(Whoseturn,Player1);
    while(true){
        char input[100];
        playgame(Whoseturn);
        printf("\nDo you want to play again? [Y/N]: ");
        scanf("%s",input);
        while (input[1]!='\0' || (input[0]!='y' && input[0]!='Y' && input[0]!='n' && input[0]!='N')){
            printf("Wrong Input!!! Only Y/N allowed!\nDo you want to play again? [Y/N]: ");
            scanf("%s",input);
        }
        if(input[0]=='n' || input[1]=='N'){
            printf("Goodbye!");
            break;
        }
        else{
            Xqueue=emptyforreplay;
            Oqueue=emptyforreplay;
            turnO=0;
            turnX=0;
            printf("Players turn will be changed!\n\n");
            if(strcmp(Whoseturn,Player2)==0){
                strcpy(Whoseturn,Player1);
            }
            else{
                strcpy(Whoseturn,Player2);
            }
        }
    }
}