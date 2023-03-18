#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define WIDTH 80 
#define HEIGHT 25

void view(int a[HEIGHT][WIDTH], int *flag);
int neighbors(int a[HEIGHT][WIDTH], int x, int y);
void make_new(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);
void swap(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);
int speed(int *flag);

int main() {
    int current_array[HEIGHT][WIDTH] = {{current_array[0][0] = 0}};
    int new_array[HEIGHT][WIDTH] = {{new_array[0][0] = 0}};

//    FILE *file = fopen("HEART.txt", "r");
//    for (int i = 0; i < HEIGHT; i++) {
//        for (int j = 0; j < WIDTH; j++) {
//            fgetc(file, "%d", current_array[i][j]);
//        }
//    }
//    fclose(file);
    
    int flag = 0;
    initscr();
    int seed = speed(&flag);
    halfdelay (seed);

    while(flag == 0) {
        view (current_array, &flag);
//        scanf("%c", &tap);
	int tr = getch();
	switch(tr) {
            case ERR: 
                make_new(current_array, new_array);
                swap(current_array, new_array);
	        break;
            default:
                flag = 1;
        }
    }
    endwin();
    printf("Game over!");
    return 0;
}

void view(int a[HEIGHT][WIDTH], int *flag) {
    int count = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (a[i][j] == 0) {
                printf(" ");
            }
            if (a[i][j] == 1) {
                printf("*");
                count++;
            }
        }
        printf("\n");
    }
    if (count == 0) {
        *flag = 1;
    }
}

int neighbors(int a[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    int string = 0; 
    int column = 0; 
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i < 0) {
                string = HEIGHT - 1;
                column = j;
            } else if (i >= HEIGHT) {
                string = 0;
                column = j;
            } else if (j < 0) {
                column = WIDTH - 1;
                string = i;
            } else if (j >= WIDTH) {
                column = 0;
                string = i;
            } else {
                string = i;
                column = j;
            } 
            count += a[string][column];
        }
    }
    count -= a[y][x];
    return count;
}

void make_new(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]) {
    int neighbor = 0; 
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            neighbor = neighbors(a, j, i);
            if (a[i][j] == 0) {
                if (neighbor == 3) {
                    b[i][j] = 1;
                }
            } else {
                if (neighbor < 2 || neighbor > 3) {
                    b[i][j] = 0;
                }
                if (neighbor == 2 || neighbor == 3) {
                    b[i][j] = 1;
                }
            }
        }
    }
}

void swap(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            a[i][j] = b[i][j];
        }
    }    
}

int speed(int *flag) {
    int res;
    int speed;
    printf("Enter a speed from 1 to 5:\n");
    scanf("%d", &speed);
    if (speed == 5) {
	res = 1;
    } else if (speed == 4) {
	res = 5;
    } else if (speed == 3) {
	res = 10;
    } else if (speed == 2) {
	res = 25;
    } else if (speed == 1) {
	res = 50;
    } else
	*flag = 1;
    return res;
}
