#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]){
    DIR *dp;
    struct dirent *dirp;

    if(argc < 2){
        printf("Tooo less arguemnts \n");
        exit(1);
    }

    if((dp=opendir(argv[1])) == NULL){
        printf("Directory doesnt exist!!\n");
        exit(0);

    }
    while((dirp = readdir(dp))!= NULL){
        printf("%s\n", dirp->d_name);
    }

    return 0;
}