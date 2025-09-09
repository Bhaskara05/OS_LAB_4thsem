#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 30

int main() {
    int fd = open("myfile.txt", O_RDWR);
    int n;
    char buffer[BUFFER_SIZE];

    printf("File descriptor is %d\n", fd);
    if (fd == -1) {
        printf("Failed to open file.\n");
        exit(1);
    }

    // Read first 10 characters
    printf("\nReading first 10 characters from file:\n");
    n = read(fd, buffer, 10);
    write(1, buffer, n);

    // Skip 5 characters and read next 10
    printf("\n\nSkipping 5 characters from current position in the file:\n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);

    // Go 10 characters back from current and read 10
    printf("\n\nGoing 10 characters before the current position in the file:\n");
    lseek(fd, -10, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);

    // Go to 5th last character in the file
    printf("\n\nGoing to 5th last character in the file:\n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buffer, 5);
    write(1, buffer, n);

    // Go to the 3rd character in the file
    printf("\n\nGoing to the 3rd character in the file:\n");
    lseek(fd, 3, SEEK_SET);
    n = read(fd, buffer, 5);
    write(1, buffer, n);

    printf("\n");

    close(fd); // Always close file
    return 0;
}
