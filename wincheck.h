int checkifwin(char board[n][n], char player, int winCondition) {
    if(player=='X') player='O';
    else player='X';

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == player) {
                int upline=1,straightline=1,righthorizontal=1,lefthorizontal=1;

                for(int k=0;k<winCondition;k++){
                    if(board[i+k][j]!=player || i+k==n) upline=0;
                    if(board[i][j+k]!=player || j+k==n) straightline=0;
                    if(board[i+k][j+k]!=player || i+k==n || j+k==n) righthorizontal=0;
                    if(board[i+k][j-k]!=player || i+k==n || j-k==-1) lefthorizontal=0;
                } //bit check, if any of them true return true
                return upline | straightline | righthorizontal | lefthorizontal;
                
            }
        }
    }

    return 0;  // No win found
}