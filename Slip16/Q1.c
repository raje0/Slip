// Display all the files from current directory which are created in particular month

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void display_files_in_month(const char *month_name) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(".")) == NULL) {
        perror("Unable to open directory");
        return;
    }

    printf("Files created/modified in %s:\n", month_name);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { 
            if (stat(entry->d_name, &file_stat) == -1) {
                perror("stat failed");
                continue;
            }

            struct tm *timeinfo = localtime(&file_stat.st_mtime);
            char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

            if (strcmp(months[timeinfo->tm_mon], month_name) == 0) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir); 

int main() {
    char month[4];
    printf("Enter the month (e.g., Jan, Feb, ...): ");
    scanf("%3s", month);

    display_files_in_month(month);

    return 0;
}

