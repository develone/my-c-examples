#include <stdio.h>
#include <stdlib.h> // Required for atoi()

int main(int argc, char *argv[]) {
    // 1. Print the total number of arguments
    printf("Total arguments received (argc): %d\n\n", argc);

    // 2. Print the program name (always stored at index 0)
    printf("Program Name (argv[0]): %s\n\n", argv[0]);

    // 3. Loop through and print any extra arguments provided by the user
    if (argc > 1) {
        printf("--- Extra Arguments Passed ---\n");
        for (int i = 1; i < argc; i++) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
    } else {
        printf("No extra arguments were passed.\n");
    }

    return 0;}
