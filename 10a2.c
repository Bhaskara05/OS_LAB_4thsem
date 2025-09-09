#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char ch;

    if (argc < 3) {
        printf("Insufficient number of arguments\n");
        printf("Usage: %s <target_file> <source_file>\n", argv[0]);
        exit(1);
    }

    fp1 = fopen(argv[1], "a");  // target file (append mode)
    if (fp1 == NULL) {
        printf("Error opening target file %s\n", argv[1]);
        exit(1);
    }

    fp2 = fopen(argv[2], "r");  // source file (read mode)
    if (fp2 == NULL) {
        printf("Error opening source file %s\n", argv[2]);
        fclose(fp1);
        exit(1);
    }

    while ((ch = fgetc(fp2)) != EOF)
        fputc(ch, fp1);

    fclose(fp1);
    fclose(fp2);

    printf("Contents of %s appended to %s successfully.\n", argv[2], argv[1]);

    return 0;
}