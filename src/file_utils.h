#pragma once

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

ssize_t read_file(char* buf, ssize_t size, const char* file);
ssize_t write_file(char* buff, ssize_t size, const char* file);
long get_size_of_file(FILE *file);