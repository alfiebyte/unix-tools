#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <errno.h>

#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    char* name = argv[1];
    if(!name) {
        exit(0);
    }

    int fd = open(name, O_RDONLY);
    if(fd < 0) {
        exit(1);
    }

    const int READ_AMOUNT = 1000 * sizeof(char);

    int len = 0;
    int buffer_capacity = 0; 
    void* buffer = NULL;

    int bytes_read;
    do {
        if(len == buffer_capacity) {
            buffer_capacity += READ_AMOUNT;
            buffer = realloc(buffer, buffer_capacity);
        }
        bytes_read = read(fd, buffer + len, READ_AMOUNT);
        len = len + bytes_read;
        printf("Bytes Read: %d\n", bytes_read);
    } while(bytes_read != 0);

    write(STDOUT_FILENO, buffer, buffer_capacity);
    printf("\n");

    int status = close(fd);
    exit(status);
}