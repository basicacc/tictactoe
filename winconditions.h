int get_win_condition(int board_size) {

    printf("Enter the number of marks in a row needed to win (min 1, max %d): ", board_size);
    while (1) {

        getlinecustom(input);


        if (input[1]!='\0' || input[0]<'1' || input[0]>(48+board_size)) {
            printf("\n\033[31mInvalid input!\033[0m\n\nPlease enter a number between 1 and %d: ", board_size);
        } else {
            win_condition=input[0]-'0';
            fprintf(fp,"Number of marks needed to win: %d\n\n",win_condition);
            break;  // Valid input, exit loop
        }
    }
}