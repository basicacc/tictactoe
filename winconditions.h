int get_win_condition(int board_size) {

    printf("Enter the number of marks in a row needed to win (min 1, max %d): ", board_size);
    while (1) {

        getlinecustom(input);


        if (input[1]!='\0' || input[0]<'1' || input[0]>(48+board_size)) {
            printf("Invalid input. Please enter a number between 1 and %d: ", board_size);
        } else {
            win_condition=input[0]-'0';
            break;  // Valid input, exit loop
        }
    }
}