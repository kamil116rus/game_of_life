/* GAME OF LIFE*/

#define SIZE_X 80
#define SIZE_Y 25
#define MAX_SPEED 20000
#define MIN_SPEED 300000
#define STEP_SPEED 10000

#include <stdio.h>

void game();
char *born_buffer();
void free_buffer(char *buffer);

int main() {
    game();

    return 0;
}

void game() {
    FILE *file;
    char c;
    char *buffer, *buffer_old;

    while (c != 'q') {
        c = getchar();
        switch (c) {
            case '1':
                if (file = fopen("1.txt", "r") != EOF) {
                    if (load_buffer(file, buffer)) }
                break;

            default:
                break;
        }
    }
}