#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sumRes=0, prodRes=1;

void *sum(void *arg){
    int n = atoi(arg);
    for(int i=0;i<=n;i++){
        sumRes+=i;
    }
    printf("Sum thread complete \n");
    return NULL;
}

void *mul(void *arg){
    int n = atoi(arg);
    for(int i=0;i<=n;i++){
        prodRes*=i;
    }
    printf("Mul thread complete \n");
    return NULL;
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Less Arguements\n");
        return 0;
    }
    
    pthread_t t1,t2;
    
    pthread_create(&t1,NULL,sum,argv[1]);
    pthread_create(&t2,NULL,mul,argv[1]);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
