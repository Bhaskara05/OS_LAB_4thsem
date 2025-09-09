#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char fn[100], pat[100], temp[512];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%99s", fn);  // limit input size

    printf("Enter pattern to be searched: ");
    scanf("%99s", pat);

    fp = fopen(fn, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("\nLines containing \"%s\":\n", pat);

    while (fgets(temp, sizeof(temp), fp)) {
        if (strstr(temp, pat)) {
            printf("%s", temp);
        }
    }

    fclose(fp);
    return 0;
}
