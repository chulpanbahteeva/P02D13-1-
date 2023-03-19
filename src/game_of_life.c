#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25

void read_file(int a[HEIGHT][WIDTH], int *flag);
void view(int a[HEIGHT][WIDTH], int *flag);
int neighbors(int a[HEIGHT][WIDTH], int x, int y);
void make_new(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);
void swap(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);
int speed(int *flag);

int main() {
    int current_array[HEIGHT][WIDTH] = {{current_array[0][0] = 0}};
    int new_array[HEIGHT][WIDTH] = {{new_array[0][0] = 0}};
    int flag = 0;

    read_file(current_array, &flag);
//    initscr();
    int seed = speed(&flag);
//    halfdelay (seed);
//    endwin();
    

    while (flag == 0) {
        //scanf("%c", &tap);
        if (99999 < seed < 5000001) {
            view(current_array, &flag);
	    usleep (seed);
//            int tr = getch();
//	        switch(tr) {
//                case ERR: 
//		    initscr();
//		    clear();
//		    endwin();
            make_new(current_array, new_array);
            swap(current_array, new_array);
//	                break;
//                default:
//                    flag = 1;
//            }
        } else {
            flag = 1;
        }
    }
    
    return 0;
}

void read_file(int a[HEIGHT][WIDTH], int *flag) {
    int figure = 1;
    printf("Выбери начальную инициализацию (от 1 до 5): ");
    int b = scanf("%d", &figure);
    FILE *file = NULL;
    if (b != 1) {
        printf("Вводи целое число от 1 до 5!:)\n");
        *flag = 1;
    } else {
        if (figure == 1) {
            file = fopen("GLIDER.txt", "r");
        } else if (figure == 2) {
            file = fopen("HEART.txt", "r");
        } else if (figure == 3) {
            file = fopen("DIAMOND.txt", "r");
        } else if (figure == 4) {
            file = fopen("LETTER.txt", "r");
        } else if (figure == 5) {
            file = fopen("CUSTOM.txt", "r");
        }
    }
 
    if (file == NULL) {
        printf("Файл не найден\n");
        *flag = 1;
    } else {
        char c;
        int cnt = 0;
        while ((c = getc(file)) != EOF) {
            if (c == '0') {
                a[cnt / WIDTH][cnt % WIDTH] = 0;
                cnt += 1;
            }
            if (c == '1') {
                a[cnt / WIDTH][cnt % WIDTH] = 1;
                cnt += 1;
            }
        }
    }
    fclose(file);
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
    int score;
    printf("Enter a speed from 1 to 5: ");
    scanf("%d", &score);
    if (score == 5) {
	res = 100000;
    } else if (score == 4) {
	res = 500000;
    } else if (score == 3) {
	res = 1000000;
    } else if (score == 2) {
	res = 2500000;
    } else if (score == 1) {
	res = 5000000;
    } else
	*flag = 1;
    return res;
}

