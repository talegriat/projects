#include <stdio.h>
#define FILENAME "/home/talegria/chessoutput.txt"
void wrtMsg(char *str1){
    FILE *f = fopen(FILENAME, "a");
    *(str1++) = '0';
    fputs(str1,f);
    fclose(f);
}