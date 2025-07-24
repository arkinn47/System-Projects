#include <stdio.h>  // Standard input and output
#include <errno.h>  // Access to errno and Exxx macros
#include <stdint.h> // Extra fixed-width data types
#include <string.h> // String utilities
#include <err.h>    // Convenience functions for error reporting (non-standard)

static char const b64_alphabet[] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789"
  "+/";

int main(int argc, char *argv[])
{
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
        errx(1, "Too many arguments");
    } else if (argc == 2 && strcmp(argv[1], "-")) {
        FILE input = fopen(argv[1], "r"); /* open FILE */
    } else {
        input = stdin /* use stdin instead */
    }
    for (;;) {
        uint8_t input_bytes[...] = {0};
        size_t n_read = fread(input_bytes, ...)
        if (n_read != 0) {
            /* Have data */
            int alph_ind[...];
            alph_ind[0] = input_bytes[0] >> 2;
            alph_ind[1] = (input_bytes[0] << 4 | input_bytes[1] >> 4) & 0x3Fu;
            ...
            char output[...];
            output[0] = b64_alphabet[alph_ind[0]];
            ...
            
            ... do something ...
            size_t n_write = fwrite(output, ...)
            if (ferror(...)) err(...); /* Write error */
        }
        if (n_read < num_requested) {
        /* Got less than expected */
        if (feof(...)) break; /* End of file */
        if (ferror(...)) err(...); /* Read error */
        }
    }
    if (... != stdin) fclose(...); /* close opened files; */
    /* any other cleanup tasks? */
}