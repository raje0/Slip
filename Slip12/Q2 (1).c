// Write a C program which receives file names as command line arguments and display those
// filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, …)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    char *filename;
    off_t size;
} FileInfo;

int compare(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;
    return (fileA->size - fileB->size);
}

int main(int argc, char *argv[]) {
    int i;
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    FileInfo *files = malloc((argc - 1) * sizeof(FileInfo));
    if (files == NULL) {
        perror("malloc");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        struct stat fileStat;
        if (stat(argv[i], &fileStat) == -1) {
            perror(argv[i]);
            free(files);
            continue; 
        }
        files[i - 1].filename = argv[i];
        files[i - 1].size = fileStat.st_size;
    }
    qsort(files, argc - 1, sizeof(FileInfo), compare);

    printf("Files sorted by size (ascending order):\n");
    for ( i= 0; i < argc - 1; i++) {
        printf("%s: %ld bytes\n", files[i].filename, files[i].size);
    }

    free(files);
    return 0;
}


