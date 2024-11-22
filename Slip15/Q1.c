// Display all the files from current directory whose size is greater that n Bytes Where n is accept
// from user.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    long n;

    printf("Enter the size limit (in bytes): ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid number.\n");
        return 1;
    }

    DIR *directory;
    struct dirent *entry;
    struct stat fileStat;

    directory = opendir(".");
    if (directory == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files larger than %ld bytes:\n", n);
    while ((entry = readdir(directory)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        if (fileStat.st_size > n) {
            printf("%s: %ld bytes\n", entry->d_name, fileStat.st_size);
        }
    }

    closedir(directory);
    return 0;
}

