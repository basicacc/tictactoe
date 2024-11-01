int checkifwin(char x[][n],char c){
    bool horizontaltest=true, verticaltest=true, obiritest=true;
    int loc=-1;
    if (c=='O') c='X';
    else c='O';
    for (int i=0;i<n;i++){
        if (x[0][i]==c){
            loc=i;
            break;
        }
    }
    if (loc==0){
        for (int i=0;i<n;i++){
            if(x[0][i]!=c){
                horizontaltest=false;
            }
            if(x[i][0]!=c){
                verticaltest=false;
            }
            if(x[i][i]!=c){
                obiritest=false;
            }
        }
        return horizontaltest | verticaltest | obiritest;
    }
    else if (loc==n-1){
        for (int i=n-1;i>=0;i--){
            if(x[i][n-1]!=c){
                horizontaltest=false;
            }
            if(x[0][i]!=c){
                verticaltest=false;
            }
            if(x[i][n-i+1]!=c){
                obiritest=false;
            }
        }
        return horizontaltest | verticaltest | obiritest;

    }
    else if(loc!=-1){
        for (int i=0;i<n;i++){
            if(x[i][loc]!=c){
                verticaltest=false;
            }
        }
        return verticaltest;
    }
    return 0;
}