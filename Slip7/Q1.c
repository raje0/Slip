// Write a C Program that demonstrates redirection of standard output to a file

#include <stdio.h>
#include <stdlib.h>

int main() {
    
    FILE *file = freopen("output.txt", "w", stdout);
    
    if (file == NULL) {
        perror("Error redirecting output");
        return EXIT_FAILURE;
    }

    printf("Hello, World!\n");
    printf("This is an example of output redirection.\n");
    printf("All this text will be written to the file 'output.txt'.\n");

    fclose(file);

    return EXIT_SUCCESS;
}
