/**

You will write a program that will gather various information about a directory, specifically:
list all the files in the directory
specify which files are directories (if any)
show the total size of all the regular files the directory
note that you do not have to recursively go through any subdirectories to find their size for this part (unless you want to, but that is not a simple task)
Have the program scan the current directory
Possible enhancements:
Recursively list the files in any subdirectories, update the total to include the total size of subdirectories
Print out the size in a more readable format (like using KB, MB, GB for -byte prefixes)

**/

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <sys/stat.h>

int isFile(char *file) {
    struct stat tmp;
    stat(file, &tmp);
    return S_ISREG(tmp.st_mode);
}

int isDir(char *file) {
    struct stat tmp;
    stat(file, &tmp);
    return S_ISDIR(tmp.st_mode);
}

int main() {

    DIR *dummy = opendir(".");
    struct dirent *temp = readdir(dummy);
    struct stat buf;
    int dirSize = 0;

    printf("\nStatistics for Directory : .\n");
    printf("DIRECTORIES :\n");
    while (temp) {
        if(isDir(temp->d_name))
            printf("%s\n", temp->d_name);
        temp = readdir(dummy);
    }
    
    rewinddir(dummy);
    temp = readdir(dummy);
    
    printf("REGULAR FILES :\n");
    while (temp) {
        if(isFile(temp->d_name)){
            printf("%s\n", temp->d_name);
            stat(temp->d_name,&buf);
            dirSize += buf.st_size;
        }
        temp = readdir(dummy);
    }
    
    closedir(dummy);
    
    printf("Total Directory Size : %d bytes\n", dirSize);

    return 0;
}