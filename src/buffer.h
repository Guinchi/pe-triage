#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdint.h>

enum buffer_result { BUFFER_OK = 0, BUFFER_COULD_NOT_OPEN = 1, BUFFER_BAD_SIZE = 2, 
    BUFFER_TOO_LARGE = 3, BUFFER_OUT_OF_MEMORY = 4, 
    BUFFER_READ_ERROR = 5 };  

struct buffer {
    uint8_t *data;
    size_t size;
};

enum buffer_result buffer_load(struct buffer *buf, const char *filename);

void buffer_free(struct buffer *buf);

const char *buffer_result_to_string(enum buffer_result result);

#endif // BUFFER_H