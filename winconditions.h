int get_win_condition(int board_size) {
    char input[100];  // Buffer to hold user input
    // Ask user for win condition with proper bounds
    printf("Enter the number of marks in a row needed to win (min 1, max %d): ", board_size);
    while (1) {
        // Get input as a string to handle non-integer input properly
        fgets(input, sizeof(input), stdin);
        // Try to parse the number from input
        if (sscanf(input, "%d", &win_condition) != 1 || win_condition < 1 || win_condition > board_size) {
            printf("Invalid input. Please enter a number between 1 and %d: ", board_size);
        } else {
            break;  // Valid input, exit loop
        }
    }
}