int checkifwin(char board[n][n], char player, int winCondition) {
    // Check rows and columns
    if(player=='X') player='O';
    else player='X';

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == player) {
                int upline=1,downline=1,straightline=1,backline=1,righthorizontal=1,lefthorizontal=1;

                for(int k=0;k<winCondition;k++){
                    if(board[i+k][j]!=player || i+k==n) upline=0;
                    if(board[i-k][j]!=player || i-k==-1) downline=0;
                    if(board[i][j+k]!=player || j+k==n) straightline=0;
                    if(board[i][j-k]!=player || j-k==-1) backline=0;
                    if(board[i+k][j+k]!=player || i+k==n || j+k==n) righthorizontal=0;
                    if(board[i-k][j-k]!=player || i-k==-1 || j-k==-1) lefthorizontal=0;
                }
                if(upline | downline | straightline | backline | righthorizontal | lefthorizontal) return 1;
                
            }
        }
    }

    return 0;  // No win found
}