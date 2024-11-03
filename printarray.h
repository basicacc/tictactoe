void print_charry(char x[][n], int length){
    printf("\n   ");
    for (int j=0;j<n-1;j++){
        printf("  \033[31m%d\033[0m ",j+1);
    }
    printf("  \033[31m%d\033[0m\n",n);
    printf("   \u2554");
    for (int j=0;j<n-1;j++){
        printf("\u2550\u2550\u2550\u2566");
    }
    printf("\u2550\u2550\u2550\u2557\033[0m\n");
    for (int i=0;i<length-1;i++){
        printf(" \033[32m%d\033[0m \u2551\033[0m",i+1);
        for (int j=0;j<length;j++){
            printf(" %c \u2551\033[0m",x[i][j]);
        }
        printf("\n   \u2560");
        for(int j=0;j<length-1;j++){
            printf("\u2550\u2550\u2550\u256C");
        }
        printf("\u2550\u2550\u2550\u2563\n");
    }
    printf(" \033[32m%d\033[0m \u2551\033[0m",n);
    for (int j=0;j<length;j++){
        printf(" %c \u2551\033[0m",x[length-1][j]);
    }
    printf("\n   \u255A");
    for (int j=0;j<n-1;j++){
        printf("\u2550\u2550\u2550\u2569");
    }
    printf("\u2550\u2550\u2550\u255D\033\033[0m\n\n");
}