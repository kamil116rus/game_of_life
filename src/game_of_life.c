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

int kbhit();
void intro();
void text();
void game(char **buffer);
char **born_buffer();
void free_buffer(char **buffer);
int load_buffer(FILE *file, char **buffer);
void draw(char **buffer, int gen, int pop);
void life(char **buffer, char **buffer_old);
void control(char *c, int *speed);
int count_life(int a, int b, char **buffer);
int norm_i(int i);
int norm_j(int j);
void population(int *pop, char **buffer);

int main() {
    intro();
    return 0;
}

// Функция выбора игры///
void intro() {
    printf("\033[0d\033[2J");
    FILE *file;
    int file_number;
    int memory_no = 0;
    char **buffer = born_buffer();
    if (buffer != NULL) memory_no = 1;
    while (file_number != 0 && memory_no == 1) {
        text();
        scanf("%d", &file_number);
        fflush(stdin);
        if (file_number == 1) {
            file = fopen("1.txt", "r");
            if (file != NULL) {
                load_buffer(file, buffer) ? game(buffer) : printf("\n\n\tfile is empty or invalid\n");
            } else
                printf("no file\n");
            fclose(file);
        }
        if (file_number == 2) {
            file = fopen("2.txt", "r");
            if (file != NULL) {
                load_buffer(file, buffer) ? game(buffer) : printf("\n\n\tfile is empty or invalid\n");
            } else
                printf("no file\n");
            fclose(file);
        }
        if (file_number == 3) {
            file = fopen("3.txt", "r");
            if (file != NULL)
                load_buffer(file, buffer) ? game(buffer) : printf("\n\n\tfile is empty or invalid\n");
            else
                printf("no file\n");
            fclose(file);
        }
        if (file_number == 4) {
            file = fopen("4.txt", "r");
            if (file != NULL)
                load_buffer(file, buffer) ? game(buffer) : printf("\n\n\tfile is empty or invalid\n");
            else
                printf("no file\n");
            fclose(file);
        }
        if (file_number == 5) {
            file = fopen("5.txt", "r");
            if (file != NULL)
                load_buffer(file, buffer) ? game(buffer) : printf("\n\n\tfile is empty or invalid\n");
            else
                printf("no file\n");

            fclose(file);
        }
    }
    if (memory_no == 1) free_buffer(buffer);
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
void free_buffer(char **buffer) {
    for (int i = 0; i < SIZE_Y; i++) {
        free(buffer[i]);
    }
    free(buffer);
}

//Функция заполнения матрицы из файла
int load_buffer(FILE *file, char **buffer) {
    int sum = 0;
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            char c = fgetc(file);
            if (c == '\n') c = fgetc(file);
            if (c == 'O') {
                buffer[i][j] = ' ';
                sum++;
            }
            if (c == ' ') {
                buffer[i][j] = 'o';
                sum++;
            }
        }
    }
    // printf("%d  -- %d \n", sum, SIZE_X * SIZE_Y);
    return sum == SIZE_X * SIZE_Y ? 1 : 0;
}

// game function
void game(char **buffer) {
    int memory, gen = 0, pop, speed = 150000;
    char c = 'y';
    char **buffer_old = born_buffer();
    buffer_old != NULL ? memory = 1 : 0;
    while (c != 'q' && memory == 1) {
        population(&pop, buffer);
        draw(buffer, gen, pop);  //печать
        life(buffer, buffer_old);
        control(&c, &speed);
        if (pop == 0) c = 'q';
        usleep(speed);
        gen++;
    }
    if (memory == 1) free_buffer(buffer_old);
}

// Функцмя печати игрового поля
void draw(char **buffer, int gen, int pop) {
    printf("\033[0d\033[2J");
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            printf("%c", buffer[i][j]);
        }
        printf("\n");
    }
    printf("Управление: \"A\" - speed UP,  \"Z\" - speed DOWN,  \"Q\" - QUIT. ");
    printf(" Generation - %d,   population - %d \n", gen, pop);
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
            }
            if (buffer_old[i][j] == 'o' &&
                (count_life(i, j, buffer_old) < 2 || count_life(i, j, buffer_old) > 3)) {
                buffer[i][j] = ' ';
            }
        }
    }
}

// Функция посчета соседних клеток
int count_life(int a, int b, char **buffer) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                if (buffer[norm_i(a + i)][norm_j(b + j)] == 'o') {
                    count++;
                }
            }
        }
    }
    // printf("%d ", count);
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
    else if (j >= SIZE_X)
        j = j % SIZE_X;
    return j;
}

// Функция управления скоростью и выхода
void control(char *c, int *speed) {
    system("stty -icanon crtkill");
    while (kbhit() != 0) {
        *c = tolower(getchar());
        if (*c == 'a') *speed -= STEP_SPEED;
        if (*c == 'z') *speed += STEP_SPEED;
    }
}

// Функция подсчета живых клеток
void population(int *pop, char **buffer) {
    *pop = 0;
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            if (buffer[i][j] == 'o') *pop += 1;
        }
    }
}

int kbhit() {  // Функция kbhit() возвращает истину, если нажата какая-либо
               // клавиша на клавиатуре.
    struct timeval tv;  // В против­ном случае возвращается 0.
    fd_set fds;  //  В любом случае код клавиши не удаляется из входного буфера.
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void text() {
    // printf("\033[0d\033[2J");
    printf("\n\n\t\t Game of life\n\n\n");
    printf("Выберите начальный файл:\n");
    printf("1. Глайдер (Glider)\n");
    printf("2. Планерное ружьё Госпера (Gosper glider gun)\n");
    printf("3. Долгожитель ()\n");
    printf("4. Устойчивые фигуры и периодичные\n");
    printf("5. Сделай сам(открываешь файл 5.txt и ставишь пробел если нужна живая клетка)\n");
    printf("0. Выход (exit)\n");
}