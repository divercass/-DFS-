//
//  main.c
//  马踏棋盘(DFS)
//
//  Created by Cass on 2017/4/1.
//  Copyright © 2017年 cass. All rights reserved.
//

#include <stdio.h>
#include <time.h>

#define X 8
#define Y 8

int chess[X][Y];

//找到基于（x，y）位置的下一个可走位置
int nextstep (int *x, int *y, int count)
{
    switch (count) {
        case 0:
            if (*x+2 <= X-1 && *y-1 >= 0 && chess[*x+2][*y-1] == 0) {
                *x += 2;
                *y -= 1;
                return 1;
            }
            break;
        case 1:
            if (*x+2 <= X-1 && *y+1 <= Y-1 && chess[*x+2][*y+1] == 0) {
                *x += 2;
                *y += 1;
                return 1;
            }
            break;
        case 2:
            if (*x+1 <= X-1 && *y-2 >= 0 && chess[*x+1][*y-2] == 0) {
                *x += 1;
                *y -= 2;
                return 1;
            }
            break;
        case 3:
            if (*x+1 <= X-1 && *y+2 <= Y-1 && chess[*x+1][*y+2] == 0) {
                *x += 1;
                *y += 2;
                return 1;
            }
            break;
        case 4:
            if (*x-2 >= 0 && *y-1 >= 0 && chess[*x-2][*y-1] == 0) {
                *x -= 2;
                *y -= 1;
                return 1;
            }
            break;
        case 5:
            if (*x-2 >= 0 && *y+1 <= Y-1 && chess[*x-2][*y+1] == 0) {
                *x -= 2;
                *y += 1;
                return 1;
            }
            break;
        case 6:
            if (*x-1 >= 0 && *y-2 >= 0 && chess[*x-1][*y-2] == 0) {
                *x -= 1;
                *y -= 2;
                return 1;
            }
            break;
        case 7:
            if (*x-1 >= 0 && *y+2 <= Y-1 && chess[*x-1][*y+2] == 0) {
                *x -= 1;
                *y += 2;
                return 1;
            }
            break;
        default:
            break;
    }
    
    return 0;
}

void printChess() {
    int i, j;
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            printf("%2d\t",chess[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//DFS 遍历
//x，y 为位置坐标，tag 为标记变量
int TravelChessBoard(int x, int y,int tag) {
    int x1 = x, y1 = y, flag = 0, count = 0;
    chess[x][y] = tag;
    
    if (X*Y == tag) {
        printChess();
        return 1;
    }
    
    flag = nextstep(&x1, &y1, count);
    
    while (0 == flag && count < 7) {
        count++;
        flag = nextstep(&x1, &y1, count);
    }
    
    //找到下一个可走坐标
    while (flag) {
        if (TravelChessBoard(x1, y1, tag+1)) {
            return 1;
        }
        
        x1 = x;
        y1 = y;
        count++;
        
        flag = nextstep(&x1, &y1, count);
        
        while (0 == flag && count < 7) {
            count++;
            flag = nextstep(&x1, &y1, count);
        }
        
    }
    
    if (0 == flag) {
        chess[x][y] = 0;
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    int i,j;
    
    clock_t start, end;
    
    start = clock();
    
    for (i = 0; i < X; i++) {
        for (j = 0; j < Y; j++) {
            chess[i][j] = 0;
        }
    }
    
    if (!TravelChessBoard(2, 0, 1)) {
        printf("遍历失败");
    }
    
    end = clock();
    
    double time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("本次计算耗时：%f秒",time);
    
    
    return 0;
}
