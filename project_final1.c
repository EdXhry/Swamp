#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

void generateHills(int swamp[][10], int n, int m, int waterCount) {
    while (waterCount > 0) {
        int hillX = rand() % n;
        int hillY = rand() % m;

        if (swamp[hillX][hillY] == 0) {
            swamp[hillX][hillY] = 3;
            waterCount--;
        }
    }
}

int main() {
    int n, m;
    int fX, fY;
    int win, mX, mY;
    srand(time(NULL));

    int game;
    printf("Rules: \n 1.You can move diagonally \n 2.You can jump straight in any direction up to 5 blocks\n");
    printf("3.When you predicts mosqiuto next move and jumps on mosquito's block - you win\n");
    printf("4.When you on water block(~) you loses\n5.Swamp size max is 10;");
    printf("Star a new game?\n************|Yes - 1|************\n************|No - 0|************\n"),scanf("%d",&game);

    do{
        printf("Enter the size of the field (N M): ");
        scanf("%d %d", &n, &m);
        int waterCount= n * m / 2;
        int swamp[n][m],oldSw;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                swamp[i][j] = 0;
            }
        }
        generateHills(swamp, n, m, waterCount);
        fX = 0;
        fY = 0;
        do {
            mX = rand() % n;
            mY = rand() % m;
        } while (mX != fX && mY != fY);
        oldSw = swamp[mX][mY];
        int gameCnt;
        while(1){
            printf("");
            for (int j = 0; j < m+1; j++) {
                if(j == 0){printf("  ");}
                else{printf("%d ", j);}
            }
            printf("\n");
            for (int i = 0; i < n; i++) {
                printf("%2d ", i+1);
                for (int j = 0; j < m; j++) {
                    if (swamp[i][j] == 0) {
                        printf("^ ");
                    } else if (swamp[i][j] == 1) {
                        printf("F ");
                    } else if (swamp[i][j] == 2) {
                        printf("M ");
                    } else if (swamp[i][j] == 3) {
                        printf("~ ");
                    }
                }
                printf("\n");
            }
            int jumpX, jumpY,legit = 1,oldfX,oldfY;
            do{
                printf("Enter the coordinates for the frog's jump (x y): ");
                scanf("%d %d", &jumpX, &jumpY);
                jumpX--;jumpY--;
                if (jumpX < 0 || jumpX >= m || jumpY < 0 || jumpY >= n){ //&& (gameCnt != 0)//(((jumpX != fX)&& ((jumpX != fX)))&&(oldfX - jumpX == oldfY - jumpY)&& gameCnt != 0)
                    printf("Wrong move - retry\n");
                    legit = 1;
                }
                else{
                    legit = 0;
                    if (swamp[jumpX][jumpY] != 3 ) { //&& (jumpX != mX || jumpY != mY)
                        swamp[fX][fY] = 0;
                        oldfX =fX;
                        oldfY =fY;
                        fX = jumpX;
                        fY = jumpY;
                        swamp[fX][fY] = 1;
                    } else {
                        legit = 0;
                        printf("You Lose\n");
                        break;
                    }
                }
            }while(legit);
            for(int i = 1; i < (abs(fX - oldfX)+1); i++) {
                if (((abs(oldfX - fX) == i && oldfY == fY) || (abs(oldfY - fY) == i && oldfX == fX)) &&
                    (abs(mX - fX) <= 1 && abs(mY - fY) <= 1)) {
                    printf("Frog caught the mosquito! Game over.\n");
                    win = 1;
                    break;
                }
            }

            int mMoveX = mX + (rand() % 3) - 1;
            int mMoveY = mY + (rand() % 3) - 1;
            if (mMoveX >= 0 && mMoveX < n && mMoveY >= 0 && mMoveY < m && ((mMoveX != mX)||(mMoveY != mY))) { //&& swamp[mMoveX][mMoveY] != 3
                swamp[mX][mY] = oldSw;
                mX = mMoveX;
                mY = mMoveY;
                oldSw = swamp[mMoveX][mMoveY];
                swamp[mX][mY] = 2;
            }
            gameCnt++;
            if(win == 1){
                win = 0;
                break;

            }
        }

        printf("Star a new game?\nYes - 1\nNo - 0\n"),scanf("%d",&game);
    }while(game == 1);
    return 0;
}