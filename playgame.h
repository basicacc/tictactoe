void playgame(){
    extern int n;
    char now,input[1000],input2[1000];
    printf("Enter N:");
    scanf("%s",input);

    //Error check
    while(true){
        if(input[1]!='\0'|| input[0]>'9' || input[0]<='0'){
            printf("Wrong input!!! Only 1-9 allowed.\nEnter N:");
            scanf("%s",input);
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
    printf("Who is going to start[X/O]:");
    scanf(" %s",input);

    //Error check
    while (input[1]!='\0' || (input[0]!='X' && input[0]!='x' && input[0]!='O' && input[0]!='o')){
        printf("Wrong Input!!!\n\nWho is going to start[X/O]:");
        scanf(" %s",input);
    }
    now=toupper(input[0]);
    //Error check ends here
    printf("\n\033[31mIMPORTANT: FOR GOD SAKE IF YOU ACCIDENTLY WRITE WRONG INPUT\nWRITE SOME NUMBER OR SOMETHING TILL IT ENDS\n");
    printf("\nEXPLANATION:Program wants you to input comma as a seperator \nfor 2 different inputs, when you don't specify it,\nit will search for infinity\033[0m\n\n");
    while(!checkifwin(c,now)){
        printf("%c's turn [\033[32mX \033[31mY\033[0m]:",now);
        scanf("%s %s",input,input2);
        
        //Error check
        while (true){
            while(errorcheck(input) || errorcheck(input2)){
                printf("\nBe careful with format! Wrong input!\n%c turn [\033[32mX \033[31mY\033[0m]:",now);
                scanf("%s %s",input,input2);
            }
            xx=string_to_num(input);
            yy=string_to_num(input2);
            if(xx>0 && xx<=n && yy>0 && yy<=n && c[xx-1][yy-1]==' '){
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
    printf("%c is the Winner!",now);
}