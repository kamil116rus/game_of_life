/* GAME OF LIFE*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>      // для system
#include <sys/select.h>  // для kbhit
#include <termios.h>     // для kbhit
#include <unistd.h>      // для паузы

#define SIZE_X 80
#define SIZE_Y 25
#define MAX_SPEED 20000
#define MIN_SPEED 300000
#define STEP_SPEED 10000

void intro();
void text();
void game(char **buffer);
char **born_buffer();
void free_buffer(char *buffer);
int load_buffer(FILE *file, char **buffer);
void draw(char **buffer);
void life(char **buffer, char **buffer_old);
void control(char *c);
int count_life(int a, int b, buffer);
int norm_i(int a, int i);
int norm_j(int b, int j);

int main() {
    intro();
    return 0;
}

void intro() {
    FILE *file;
    char c;
    int memory_no = 0;
    char **buffer = load_buffer();
    if (buffer != NULL) memory_no = 1;
    while (c != 'q' && memory_no == 1) {
        text();
        c = getchar();
        if (c == '1') {
            if (file = fopen("1.txt", "r") != NULL) {
                if (load_buffer(file, buffer)) {
                    game(buffer);
                } else
                    printf("file is empty or invalid\n");
            } else
                printf("no file\n");
        }
    }
    free_buffer(buffer);
}

//Функция создания матрицы
char **born_buffer() {
    char **buffer = calloc(SIZE_Y, sizeof(char *));
    for (int i = 0; i < SIZE_Y; i++) {
        buffer[i] = calloc(SIZE_X, sizeof(char));
    }
    return buffer;
}

// Функция освобождения памяти
void free_buffer(char *buffer) {
    for (int i = 0; i < SIZE_Y, i++) {
        free(buffer[i]);
    }
    free(buffer);
}

//Функция заполнения матрицы из файла
int load_buffer(FILE *file, char **buffer) {
    int sum = 0;
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            char c = getchar();
            if (c == '\n')
                break;
            else if (c == 'O') {
                buffer[i][j] = ' ';
                sum++;
            } else if (c == ' ') {
                buffer[i][j] = 'o';
                sum++;
            }
        }
    }
    return sum == SIZE_X * SIZE_Y ? 1 : 0;
}

// game function
void game(char *buffer) {
    int memory;
    char c = 'y';
    char *buffer_old = born_buffer();
    buffer_old != NULL ? memory = 1 : memory = 0;
    while (c != 'q' && memory == 1) {
        printf("\033[0d\033[2J");
        draw(buffer);  //печать
        life(buffer, buffer_old);
        control(&c);

        usleep(speed);
    }
}

// Функцмя печати игрового поля
void draw(char **buffer) {
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            printf("%c", buffer[i][j]);
        }
        printf("\n");
    }
}

// Функция основной логики игры
void life(char **buffer, char **buffer_old) {
    // перезаписываем в старый буфер
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            buffer_old[i][j] = buffer[i][j];
        }
    }
    // проходим по старому и записываем новый
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            if (buffer_old[i][j] == ' ' && count_life(i, j, buffer_old) == 3) {
                buffer[i][j] = 'o';
            } else if (buffer_old[i][j] == 'o' && count_life(i, j, buffer_old) < 2 &&
                       count_life(i, j, buffer_old) > 3) {
                buffer[i][j] = ' ';
            }
        }
    }
}

int count_life(int a, int b, buffer) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (buffer[norm_i(a + i)][norm_j(b + j)] == 'o') {
                count++;
            }
        }
    }
    return count;
}

int norm_i(int i) {
    if (i < 0)
        i += SIZE_Y;
    else if (i >= SIZE_Y)
        i = i % SIZE_Y;
    return i;
}

int norm_j(int j) {
    if (j < 0)
        j += SIZE_X;
    else if (i >= SIZE_X)
        j = j % SIZE_X;
    return j;
}

void control(char *c, int *speed) {
    system("stty -icanon crtkill");
    while (kbhit() != 0) {
        *c = tolower(getchar());
        if (c == 'a') *speed -= STEP_SPEED;
        if (c == 'z') *speed += STEP_SPEED;
    }
}