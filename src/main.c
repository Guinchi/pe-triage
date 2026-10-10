#include <stdio.h>

enum { EXIT_OK = 0, EXIT_USAGE = 1, EXIT_INVALID_PE = 2 };

int main(int argc, char *argv[]) {


    if (argc != 2) {
        fprintf(stderr, "Usage: pe-triage <filename>\n");
        return EXIT_USAGE;
    } 

    printf("Processing file: %s\n", argv[1]);
    return EXIT_OK;
   
}