/* GAME OF LIFE*/

#define SIZE_X 80
#define SIZE_Y 25
#define MAX_SPEED 20000
#define MIN_SPEED 300000
#define STEP_SPEED 10000

#include <stdio.h>

void game();
void intro();
void life(char *buffer);
char *born_buffer();
void free_buffer(char *buffer);
int load_buffer(FILE *file, char *buffer);

int main() {
    game();
    return 0;
}

void game() {
    FILE *file;
    char c;
    char *buffer = load_buffer();
    if (buffer != NULL) {
        while (c != 'q') {
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
    } else
        printf("no memory\n");
}