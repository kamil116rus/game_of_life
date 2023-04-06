/* GAME OF LIFE*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE_X 80
#define SIZE_Y 25
#define MAX_SPEED 20000
#define MIN_SPEED 300000
#define STEP_SPEED 10000

void game();
void intro();
void life(char **buffer);
char **born_buffer();
void free_buffer(char *buffer);
int load_buffer(FILE *file, char **buffer);

int main() {
    game();
    return 0;
}

void game() {
    FILE *file;
    char c;
    int memory_no = 0;
    char **buffer = load_buffer();
    if (buffer != NULL) memory_no = 1;
    while (c != 'q' && memory_no == 1) {
        intro();
        c = getchar();
        if (c == '1') {
            if (file = fopen("1.txt", "r") != NULL) {
                if (load_buffer(file, buffer)) {
                    life(buffer);
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
            if (c == '\n') break;
            if (c == 'O') {
                buffer[i][j] = ' ';
                sum++;
            } else if (c == ' ') {
                buffer[i][j] = 'o';
                sum++;
            }
        }
    }
    return sum == 0 ? 1 : 0;
}

void life(char *buffer);