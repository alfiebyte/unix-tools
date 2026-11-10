#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <dirent.h>

#include <linux/limits.h>

#include <string.h>

#include <errno.h>

int main(int argc, char* argv[]) {
    char dir[PATH_MAX];
    if(argc > 1 && strlen(argv[1]) < PATH_MAX) {
        strcpy(dir, argv[1]);
    }
    else if(getcwd(dir, sizeof(dir)) == NULL) {
        perror("Couldn't find cwd");
        exit(1);
    }

    printf("Reading Directory: %s\n", dir);

    DIR* dirp = opendir(dir);

    if(dirp == NULL) {
        perror("Couldn't open dir");
        exit(1);
    }

    struct dirent* dirent;

    while((dirent = readdir(dirp)) != NULL) {
        printf("%s ", dirent->d_name);
    }

    printf("\n");

    /*
    DIR* dirp = opendir(dir);

    if(dirp == NULL) exit(1);
    
    struct dirent* dirent = readdir(dirp);

    if(dirent == NULL) exit(1);
    
    printf("dir type: %s name: %s", dirent->d_type, dirent->d_name);
    */
}