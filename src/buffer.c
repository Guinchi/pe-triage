#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_MAX_SIZE (256L * 1024 * 1024) // 256 MB


enum buffer_result buffer_load(struct buffer *buf, const char *filename){

    buf->data = NULL;
    buf->size = 0;

    // Open the file in binary mode
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return BUFFER_COULD_NOT_OPEN;
    }

    // Move the file pointer to the end to determine the size
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return BUFFER_BAD_SIZE;
    }

    long len = ftell(f);

    // Check for errors in determining the file size
    if (len <= 0) {
        fclose(f);
        return BUFFER_BAD_SIZE;
    }

    // Check if the file size exceeds the maximum allowed size
    if (len > BUFFER_MAX_SIZE) {
        fclose(f);
        return BUFFER_TOO_LARGE;
    }

    // Move the file pointer back to the beginning of the file
    if (fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return BUFFER_BAD_SIZE;
    }

    // Allocate memory for the buffer
    uint8_t *data = malloc((size_t)len);

    // Check if memory allocation was successful
    if (data == NULL) {
        fclose(f);
        return BUFFER_OUT_OF_MEMORY;
    }

    // Read the file contents into the allocated buffer
    if (fread(data, 1, (size_t)len, f) != (size_t)len) {
        free(data);
        fclose(f);
        return BUFFER_READ_ERROR;
    }

    buf->data = data;
    buf->size = (size_t)len;

    fclose(f);

    return BUFFER_OK;

}


void buffer_free(struct buffer *buf){

    free(buf->data);
    buf->data = NULL;
    buf->size = 0;
}


const char *buffer_result_to_string(enum buffer_result result) {
    switch (result) {
        case BUFFER_OK:
            return "BUFFER_OK";
        case BUFFER_COULD_NOT_OPEN:
            return "could not open file";
        case BUFFER_BAD_SIZE:
            return "file is empty or the size could not be determined";
        case BUFFER_TOO_LARGE:
            return "file is too large";
        case BUFFER_OUT_OF_MEMORY:
            return "out of memory";
        case BUFFER_READ_ERROR:
            return "could not read file";
        default:
            return "UNKNOWN_BUFFER_RESULT";
    }
}
