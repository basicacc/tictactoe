#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

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

int main(){
    extern int n;
    printf("Enter N: ");
    scanf("%d",&n);
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
    char now;
    int xx,yy;
    printf("Who is going to start[X/O]:");
    scanf(" %c",&now);

    while(!checkifwin(c,now)){
        printf("%c turn [x,y]:",now);
        scanf("%d,%d",&xx,&yy);
        printf("%d %d\n",Xqueue.x,Xqueue.y);
        printf("%d %d\n",Oqueue.x,Oqueue.y);
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