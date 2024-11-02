#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int turnX=0;
int turnO=0;
int n;

struct queuestruct{
    int x;
    int y;
    struct queuestruct *next;
} Xqueue,Oqueue;

#include"wincheck.h"

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


void print_charry(char x[][n], int length){
    printf("\u2554");
    for (int j=0;j<n-1;j++){
        printf("\u2550\u2550\u2550\u2566");
    }
    printf("\u2550\u2550\u2550\u2557\n");
    for (int i=0;i<length-1;i++){
        printf("\u2551");
        for (int j=0;j<length;j++){
            printf(" %c \u2551",x[i][j]);
        }
        printf("\n\u2560");
        for(int j=0;j<length-1;j++){
            printf("\u2550\u2550\u2550\u256C");
        }
        printf("\u2550\u2550\u2550\u2563\n");
    }
    printf("\u2551");
    for (int j=0;j<length;j++){
        printf(" %c \u2551",x[length-1][j]);
    }
    printf("\n\u255A");
    for (int j=0;j<n-1;j++){
        printf("\u2550\u2550\u2550\u2569");
    }
    printf("\u2550\u2550\u2550\u255D\n");
}

int string_to_num(char astring[1000]){
    int k=0;
    for(int i=0;i<1000 && astring[i]!='\0';i++){
        k*=10;
        k+=astring[i]-'0';
    }
    return k;
}

bool errorcheck(char inputtocheck[1000]){
    if(inputtocheck[0]=='\0') return 1;
    for (int i=0;i<1000 && inputtocheck[i]!='\0';i++){
        if (inputtocheck[i]<'0'|| inputtocheck[i]>'9'){
            return 1;
        }
    }
    return 0;
}

int main(){
    extern int n;
    char now,input[1000],input2[1000];
    printf("Enter N:");
    scanf("%s",&input);

    //Error check
    bool errorcase=false;
    while(true){
        for(int i=0;i<1000 && input[i]!='\0';i++){
            if(input[i]<'0' || input[i]>'9'){
                errorcase=true;
                break;
            }
        }
        if(errorcase){
            errorcase=false;
            printf("%s\nOnly numbers allowed!!!\nEnter N: ",input);
            scanf("%s",&input);
        }
        else{
            break;
        }
    }
    n=string_to_num(input);
    //Error check ends here

    char c[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            c[i][j]=' ';
        }
    }
    print_charry(c, n);
    extern struct queuestruct Xqueue,Oqueue;
    Xqueue.x=-100;
    Oqueue.x=-100;
    int xx,yy;
    printf("Who is going to start[X/O]:");
    scanf(" %s",input);

    //Error check
    while (input[1]!='\0' || (input[0]!='X' && input[0]!='x' && input[0]!='O' && input[0]!='o')){
        printf("Wrong Input!!!\n\nWho is going to start[X/O]:");
        scanf(" %s",&input);
    }
    now=toupper(input[0]);
    //Error check ends here
    printf("\nIMPORTANT: FOR GOD SAKE IF YOU ACCIDENTLY WRITE WRONG INPUT\nWRITE SOME NUMBER OR SOMETHING TILL IT ENDS\n");
    printf("\nEXPLANATION:Program wants you to input comma as a seperator \nfor 2 different inputs, when you don't specify it,\nit will search for infinity\n\n");
    while(!checkifwin(c,now)){
        printf("%c turn [x y]:",now);
        scanf("%s %s",&input,&input2);
        
        //Error check
        while (true){
            while(errorcheck(input) || errorcheck(input2)){
                printf("\nBe careful with format! Wrong input!\n%c turn [x y]:",now);
                scanf("%s %s",&input,&input2);
            }
            xx=string_to_num(input);
            yy=string_to_num(input2);
            if(xx>0 && xx<=n && yy>0 && yy<=n){
                break;
            }
            input[0]='\0'; //creating error so loop can repeat
        }
        //Error check ends here

        if(now=='X' && turnX==n){
            c[Xqueue.x][Xqueue.y]=' ';
            c[xx-1][yy-1]='X';
            findnullandadd(&Xqueue,1,xx-1,yy-1);
            pushlist(&Xqueue);
            now='O';
        }
        else if(now=='O' && turnO==n){
            

            c[Oqueue.x][Oqueue.y]=' ';
            c[xx-1][yy-1]='O';
            findnullandadd(&Oqueue,1,xx-1,yy-1);
            pushlist(&Oqueue);
            now='X';
        }
        else if (now=='X'){
            turnX++;
            c[xx-1][yy-1]='X';
            findnullandadd(&Xqueue,1,xx-1,yy-1);
            now='O';
        }
        else{
            turnO++;
            c[xx-1][yy-1]='O';
            findnullandadd(&Oqueue,1,xx-1,yy-1);
            now='X';
        }
        print_charry(c,n);
    }
    if(now=='X'){
        now='O';
    }
    else{
        now='X';
    }
    printf("%c is the winner!",now);
}