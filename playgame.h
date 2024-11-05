void playgame(char Whoseturn[200]){
    extern int n;
    extern char Player1[200],Player2[200];
    extern int Player1Score,Player2Score;
    char now,input[200],input2[200];
    char NowPlayer[200];
    strcpy(NowPlayer,Whoseturn);
    printf("Enter N:");
    getlinecustom(input);

    //Error check
    while(true){
        if(input[1]!='\0'|| input[0]>'9' || input[0]<='0'){
            printf("Wrong input!!! Only 1-9 allowed.\nEnter N:");
            getlinecustom(input);
        }
        else{
            break;
        }
    }
    n=input[0]-'0';
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
    printf("What is %s? [X/O]:",NowPlayer);
    getlinecustom(input);

    //Error check
    while (input[1]!='\0' || (input[0]!='X' && input[0]!='x' && input[0]!='O' && input[0]!='o')){
        printf("Wrong Input!!!\n\nWhat is %s? [X/O]:",NowPlayer);
        getlinecustom(input);
    }
    now=toupper(input[0]);
    while(!checkifwin(c,now)){
        printf("%s's [%c] turn [\033[31mX \033[32mY\033[0m]:",NowPlayer,now);
        getlinecustom(input);
        //Error check
        while (true){
            while(errorcheck(input,input2)){
                printf("\nBe careful with format! Wrong input!\n%s's turn [\033[31mX \033[32mY\033[0m]:",NowPlayer);
                getlinecustom(input);
            }
            xx=string_to_num(input);
            yy=string_to_num(input2);
            if(xx>0 && xx<=n && yy>0 && yy<=n && c[yy-1][xx-1]==' '){
                break;
            }
            input[0]='\0'; //creating error so loop can repeat
        }
        //Error check ends here

        if(now=='X' && turnX==n){
            c[Xqueue.y][Xqueue.x]=' ';
            c[yy-1][xx-1]='X';
            findnullandadd(&Xqueue,1,yy-1,xx-1);
            pushlist(&Xqueue);
            now='O';
        }
        else if(now=='O' && turnO==n){
            

            c[Oqueue.y][Oqueue.x]=' ';
            c[yy-1][xx-1]='O';
            findnullandadd(&Oqueue,1,yy-1,xx-1);
            pushlist(&Oqueue);
            now='X';
        }
        else if (now=='X'){
            turnX++;
            c[yy-1][xx-1]='X';
            findnullandadd(&Xqueue,1,yy-1,xx-1);
            now='O';
        }
        else{
            turnO++;
            c[yy-1][xx-1]='O';
            findnullandadd(&Oqueue,1,yy-1,xx-1);
            now='X';
        }
        if(strcmp(NowPlayer,Player1)==0){
            strcpy(NowPlayer,Player2);
        }
        else{
            strcpy(NowPlayer,Player1);
        }
        print_charry(c,n);
    }
    if(strcmp(NowPlayer,Player2)==0){
        strcpy(NowPlayer,Player1);
        Player1Score++;
    }
    else{
        strcpy(NowPlayer,Player2);
        Player2Score++;
    }
    printf("%s's Score:%d\n%s's Score:%d\n\n%s is the Winner!\n",Player1,Player1Score,Player2,Player2Score,NowPlayer);
}