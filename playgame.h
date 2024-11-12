void playgame(char Whoseturn[200]){
    char now;
    char NowPlayer[200];
    strcpy(NowPlayer,Whoseturn); // we create second char named NowPlayer so we can say who is going to start
                                 // question is why not just Whoseturn char, because we gonna also use NowPlayer
                                 // to print out who is going to start, basically it would be bad idea to use it
                                 // dont forget whoseturn is for who is going to start first, this one for who is
                                 // going to continue
    
    printf("Enter N:"); //length and width of tictactoe
    getlinecustom(input); 

    //Error check
    while(true){
        if(input[1]!='\0'|| input[0]>'9' || input[0]<='0'){
            printf("\n\033[31mWrong input!!! Only 1-9 allowed.\033[0m\n\nEnter N:");
            getlinecustom(input);
        }
        else{
            break;
        }
    }
    n=input[0]-'0';
    //Error check ends here

    fprintf(fp,"Size of table: %d\n",n); //log file


    char c[n][n]; //this is what we going to store our Xs and Os inside
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            c[i][j]=' '; //creating empty array with ' '
        }
    }

    get_win_condition(n);

    Xqueue.x=-100; //later it will be checked if it is first time Xqueue changning or not
    Oqueue.x=-100; //same for Oqueue
    int xx,yy;
    printf("What is %s? [X/O]:",NowPlayer); //asking what first player gonna be X or O just for visual
    getlinecustom(input);

    //Error check
    while (input[1]!='\0' || (tolower(input[0])!='x' && tolower(input[0])!='o')){
        printf("\n\033[31mWrong Input!!!\033[0m\n\nWhat is %s? [X/O]:",NowPlayer);
        getlinecustom(input);
    }
    now=toupper(input[0]);
    //Error check ends here

    print_charry(c, n); //Just to show players how it looks
    while(!checkifwin(c,now,win_condition)){ //The moment someone wins it will end
        printf("\n%s's [%c] turn [\033[34mX \033[32mY\033[0m]:",NowPlayer,now); // we use now variable to let player know if he is X or O
        getlinecustom(input);

        //Error check
        while((xx=(input[0]-'0')) && (yy=(input[2]-'0'))){
            if(input[1]==' ' && input[3]=='\0' && xx>0 && xx<=n && yy>0 && yy<=n && c[yy-1][xx-1]==' ') break;
            print_charry(c, n); //if player makes mistake repeatively, they will not forget how game looks, it will not disappear from screen
            printf("\n\033[31mBe careful with format! Wrong input!\033[0m\n\n%s's turn [\033[34mX \033[32mY\033[0m]:",NowPlayer);
            getlinecustom(input);
        }
        //Error check ends here
        time(&t);
        current_time = localtime(&t); //localizing time
        fprintf(fp,"[%02d:%02d:%02d] %s placed %c to: %d %d\n",current_time->tm_hour,current_time->tm_min,current_time->tm_sec,NowPlayer,now,xx,yy);

        if(now=='X' && turnX==n){ //if we reached limit, turnX is basically equal to length/width of array then we have to remove first X
            c[Xqueue.y][Xqueue.x]=' '; // Xqueue.y/x always gonna be first X to be deletedfrom array
            c[yy-1][xx-1]='X'; //we put last X in array that we inputed before
            findnullandadd(&Xqueue,1,yy-1,xx-1); //adding last X to queue
            pushlist(&Xqueue); //we remove the first Xqueue we deleted from array and push queue forward
            now='O'; //change player
        }
        else if(now=='O' && turnO==n){ //same as X
            

            c[Oqueue.y][Oqueue.x]=' ';
            c[yy-1][xx-1]='O';
            findnullandadd(&Oqueue,1,yy-1,xx-1);
            pushlist(&Oqueue);
            now='X';
        }
        else if (now=='X'){ //if turnX is not equal to n then we dont have to push list just add
            turnX++; 
            c[yy-1][xx-1]='X';
            findnullandadd(&Xqueue,1,yy-1,xx-1);
            now='O';
        }
        else{ //same as X
            turnO++;
            c[yy-1][xx-1]='O';
            findnullandadd(&Oqueue,1,yy-1,xx-1);
            now='X';
        }
        if(strcmp(NowPlayer,Player1)==0){ //changing player
            strcpy(NowPlayer,Player2);
        }
        else{
            strcpy(NowPlayer,Player1);
        }
        print_charry(c,n);
    }
    if(strcmp(NowPlayer,Player2)==0){ //we always player at the end, so even someone wins, nowplayer will be equal to other play, 
        strcpy(NowPlayer,Player1);    //nowplayer = player2 when player 1 wins and same for other player
        Player1Score++; //increasing player score
    }
    else{
        strcpy(NowPlayer,Player2);
        Player2Score++;
    }
    printf("%s's Score:%d\n%s's Score:%d\n\n%s is the Winner!\n",Player1,Player1Score,Player2,Player2Score,NowPlayer);

    fprintf(fp,"\n%s's Score:%d\n%s's Score:%d\n\n%s is the Winner!\n",Player1,Player1Score,Player2,Player2Score,NowPlayer);
}