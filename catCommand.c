#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
    char ch;
    FILE *fp1, *fp2;

    if(argc < 3){
        printf("Too less arguements");
        exit(1);
    }

    fp1 = fopen(argv[1], "a");
    fp2 = fopen(argv[2], "r");

    if(fp2 == NULL){
        printf("Nothing to append\n");
        exit(0);
    }

    while((ch =fgetc(fp2))!=EOF){
        fprintf(fp1,"%c",ch);
    }
    fclose(fp1);
    fclose(fp2);

    printf("Do you now want to read the file f1?\n");
    int choice;
    printf("1.Yes 2.No: "); scanf("%d", &choice);
    if(choice){
        FILE *f1 = fopen(argv[1], "r");

        while((ch=fgetc(f1))!=EOF){
            printf("%c", ch);
        }

    }

}
