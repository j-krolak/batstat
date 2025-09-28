#include "file_utils.h"

#include <unistd.h>

ssize_t read_file(char* buf, ssize_t size, const char* file) {
    const int fd = open(file, O_RDONLY);
    if(fd >= 0) {
        ssize_t nread = read(fd, buf, size);
        close(fd);
        buf[nread] = '\0';
        return nread;
    }
    return -1;
}

ssize_t write_file(char* buf, ssize_t size, const char* file) {
    const int fd = open(file, O_CREAT | O_WRONLY);
    if(fd >= 0) {
        ssize_t nwrite = write(fd, buf, size);
        return nwrite;
    }
    return -1;
}


long get_size_of_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

int copy_file(const char *inputFile, const char *outputFile) {
    FILE *src = fopen(inputFile, "rb");
    if(!src) {
        perror("Failed to open source file");
        return -1;
    }

    FILE *dst = fopen(outputFile, "w+b");
    if(!dst) {
        perror("Failed to open/create destination file");
        return -1;
    }
    char buffer[256];
    size_t n;
    while((n = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if(fwrite(buffer, 1, n, src) != n) {
            perror("Write to destination error");
            fclose(src);
            fclose(dst);
            return -1;
        } 
    }

    if(ferror(src)) {
        perror("Read error");
    }

    fclose(src);
    fclose(dst);
    return 0;
}