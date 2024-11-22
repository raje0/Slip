// Write a C program that a string as an argument and return all the files that begins with that name
// in the current directory. For example > ./a.out foo will return all file names that begins with foo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    const char *prefix = argv[1];
    DIR *directory;
    struct dirent *entry;

    directory = opendir(".");
    if (directory == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files starting with '%s':\n", prefix);
    while ((entry = readdir(directory)) != NULL) {
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(directory);
    return 0;
}


