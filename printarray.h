void print_charry(char x[][n], int length){ //disgusting looking print array (might make it look better I dont know) :D basically it only prints things
    printf("\n   \u2554");
    for (int j=0;j<n-1;j++){
        printf("\u2550\u2550\u2550\u2566");
    }
    printf("\u2550\u2550\u2550\u2557\033[0m\n");
    int i;
    for (i=length-1;i>0;i--){
        printf(" \033[32m%d\033[0m \u2551\033[0m",i+1);
        for (int j=0;j<length;j++){
            if(!gamemode && ((Xqueue.x==j && Xqueue.y==i) || (Oqueue.x==j && Oqueue.y==i))){ //checks if game mode is easy, if it is, it will output the X/O colored
                printf(" \033[1m\033[31m%c \033[0m\u2551",x[i][j]);                          //which is going to be deleted next round
            }
            else{
                printf(" %c \u2551",x[i][j]);
            }
        }
        printf("\n   \u2560");
        for(int j=0;j<length-1;j++){
            printf("\u2550\u2550\u2550\u256C");
        }
        printf("\u2550\u2550\u2550\u2563\n");
    }
    printf(" \033[32m1\033[0m \u2551\033[0m");
    for (int j=0;j<length;j++){
            if(!gamemode && ((Xqueue.x==j && Xqueue.y==i) || (Oqueue.x==j && Oqueue.y==i))){ //same here, I had to split last part for some printing problems
                printf(" \033[1m\033[31m%c \033[0m\u2551",x[0][j]);                          //but I believe it doesnt cause any problems
            }
            else{
                printf(" %c \u2551",x[0][j]);
            }
    }
    printf("\n   \u255A");
    for (int j=0;j<n-1;j++){
        printf("\u2550\u2550\u2550\u2569");
    }
    printf("\u2550\u2550\u2550\u255D\033\033[0m");
    printf("\n   ");
    for (int j=0;j<n-1;j++){
        printf("  \033[31m%d\033[0m ",j+1);
    }
    printf("  \033[31m%d\033[0m\n\n",n);
}