/*Программа для создания 
текстовых файлов и их заполнения*/

#include <stdio.h>
#include <string.h>

int main() {
    FILE *file;
    int count = 1;
    while(count < 6) {
        char arr[10];
        sprintf(arr, "%d", count);
        strcat(arr, ".txt");
        file = fopen(arr, "w"); 
        for (size_t i = 0; i < 25; i++) {
            for (size_t j = 0; j < 80; j++) {
                if(j == 79 && i == 24) {
                    fprintf(file, "O");
                } else if (j == 79) {
                    fprintf(file, "O\n");
                } else {
                    fprintf(file, "O");
                }
            }
        }
        fclose(file);
        count++;
    }
    return 0;
}