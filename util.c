

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

// Prints an error of the format "error: <error message>" and exits the
// program with a non-zero error code
void exit_with_error(char *error) {
  fprintf(stderr, "error: %s\n", error);
  exit(EXIT_FAILURE);
}

// TODO: Add any more miscelaneous functions required in your program
