// Write a C program to find file properties such as inode number, number of hard link, File
// permissions, File size, File access and modification time and so on of a given file using stat()
// system call.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void printFilePermissions(mode_t mode) {
    printf("Permissions: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Inode Number: %lu\n", fileStat.st_ino);
    printf("Number of Hard Links: %lu\n", fileStat.st_nlink);
    printf("File Size: %ld bytes\n", fileStat.st_size);
    
    printFilePermissions(fileStat.st_mode);

    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group  *gr = getgrgid(fileStat.st_gid);
    printf("Owner: %s (UID: %d)\n", pw->pw_name, fileStat.st_uid);
    printf("Group: %s (GID: %d)\n", gr->gr_name, fileStat.st_gid);
    printf("Access Time: %s", ctime(&fileStat.st_atime));
    printf("Modification Time: %s", ctime(&fileStat.st_mtime));
    printf("Change Time: %s", ctime(&fileStat.st_ctime));

    return 0;
}


