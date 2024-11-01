#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
int turnX=0;
int turnO=0;
int n;

struct queuee{
    int x;
    int y;
    struct queuee *next;
} Xqueue,Oqueue;



void findnullandadd(struct queuee *queueee,int row,int x,int y){
    if (queueee->x==-100){
        queueee->x=x;
        queueee->y=y;
        return;
    }
    while (queueee->next != NULL && row!=n) {
        queueee = queueee->next;
        row++;
    }
    queueee->next=(struct queuee *)malloc(sizeof(struct queuee));
    queueee->next->x = x;
    queueee->next->y = y;
    queueee->next->next = NULL;
}

void pushlist(struct queuee *queueee){
    if (queueee == NULL || queueee->next == NULL){
        return;
    }
    struct queuee *current=queueee;
    while(current->next !=NULL){
        current->x=current->next->x;
        current->y=current->next->y;
        current=current->next;
    }
    return;
}

int checkifwin(char x[][n],char c){
    bool horizontaltest=true, verticaltest=true, obiritest=true;
    int loc=-1;
    if (c=='O' && turnX==n){

        for (int i=0;i<n;i++){
            if (x[0][i]=='X'){
                loc=i;
                break;
            }
        }
        if (loc==0){
            for (int i=0;i<n;i++){
                if(x[0][i]!='X'){
                    horizontaltest=false;
                }
                if(x[i][0]!='X'){
                    verticaltest=false;
                }
                if(x[i][i]!='X'){
                    obiritest=false;
                }
            }
            return horizontaltest | verticaltest | obiritest;
        }
        else if (loc==n-1){
            for (int i=n-1;i>=0;i--){
                if(x[i][n-1]!='X'){
                    horizontaltest=false;
                }
                if(x[0][i]!='X'){
                    verticaltest=false;
                }
                if(x[i][n-i+1]!='X'){
                    obiritest=false;
                }
            }
            return horizontaltest | verticaltest | obiritest;

        }
        else if(loc!=-1){
            for (int i=0;i<n;i++){
                if(x[i][loc]!='X'){
                    verticaltest=false;
                }
            }
            return verticaltest;

        }
        return 0;
    }
    else if (c=='X' && turnO==n){
        for (int i=0;i<n;i++){
            if (x[0][i]=='O'){
                loc=i;
                break;
            }
        }
        if (loc==0){
            for (int i=0;i<n;i++){
                if(x[0][i]!='O'){
                    horizontaltest=false;
                }
                if(x[i][0]!='O'){
                    verticaltest=false;
                }
                if(x[i][i]!='O'){
                    obiritest=false;
                }
            }
            return horizontaltest | verticaltest | obiritest;
        }
        else if (loc==n-1){
            for (int i=n-1;i>=0;i--){
                if(x[i][n-1]!='O'){
                    horizontaltest=false;
                }
                if(x[0][i]!='O'){
                    verticaltest=false;
                }
                if(x[i][n-i-1]!='O'){
                    obiritest=false;
                }
            }
            return horizontaltest | verticaltest | obiritest;

        }
        else if(loc!=-1){
            for (int i=0;i<n;i++){
                if(x[i][loc]!='O'){
                    verticaltest=false;
                }
            }
            return verticaltest;

        }
        return 0;
    }
    return 0;
}

void print_charry(char x[][n], int length){
    for (int i=0;i<length;i++){
        for (int j=0;j<n;j++){
            printf("--");
        }

        printf("-\n|");
        for (int j=0;j<length;j++){
            printf("%c|",x[i][j]);
        }
        printf("\n");
    }
    for (int j=0;j<n;j++){
        printf("--");
    }
    printf("-\n");
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
    extern struct queuee Xqueue,Oqueue;
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