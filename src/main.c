#include <stdio.h>
#include "buffer.h"

enum { EXIT_OK = 0, EXIT_USAGE = 1, EXIT_INVALID_PE = 2 , EXIT_FILE_READ_ERROR = 3};

int main(int argc, char *argv[]) {


    if (argc != 2) {
        fprintf(stderr, "Usage: pe-triage <filename>\n");
        return EXIT_USAGE;
    } 

    struct buffer buf;
    enum buffer_result result = buffer_load(&buf, argv[1]);
    if (result != BUFFER_OK) {
        fprintf(stderr, "Error loading file '%s': %s\n", argv[1], buffer_result_to_string(result));
        return EXIT_FILE_READ_ERROR;
    }
        
    printf("Successfully loaded file '%s' into buffer. Size: %zu bytes\n", argv[1], buf.size);

    buffer_free(&buf);
    return EXIT_OK;
   
}