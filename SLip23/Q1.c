// Read the current directory and display the name of the files, no of files in current directory

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main()
{
    struct dirent *entry;
    int fileCount = 0;

    DIR *directory = opendir(".");
    if (directory == NULL)
    {
        perror("Unable to open the directory");
        return 1;
    }

    printf("Files in the current directory:\n");
    while ((entry = readdir(directory)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            printf("%s\n", entry->d_name);
            fileCount++;
        }
    }

    closedir(directory);

    printf("\nTotal number of files: %d\n", fileCount);

    return 0;
}



