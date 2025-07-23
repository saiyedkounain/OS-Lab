#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id,at,bt,ct,tat,wt,rt; //usual variables
    int leftTime;//since its premptive
}P;

void sort(P p[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;i<n;i++){
            if(p[i].at > p[j].at){
                P temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void fcfs(P p[], int n){
    //initn
    int t=0,left=n,i,ex,tp[100], pt[100], ti=0,pi=0;
    float tta,twt,trt;

    sort(p,n);
    tp[ti++] = 0;

    for( i=0;i<n;i++){
        //idle
        if(t < p[i].at){
            while (t < p[i].at)
            {
                pt[pi++] = 0;
                t++;
                tp[ti++] = t;
            }   
        }

         //response
        p[i].rt = t - p[i].at;

        //process array fill
        pt[pi++] = p[i].id;
        for(int j=1;j<p[i].bt;j++){
             pt[pi++] = p[i].id;   
        }

        //time array fill
        t+=p[i].bt;
        tp[ti++] = t;
        
        //calculations
        p[i].ct = t;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        tta+=p[i].tat;
        twt+=p[i].wt;
        trt+=p[i].rt;

    }
    printf("Observation Table: \n");
    printf("ID\t AT\t BT\t CT\t TAT\t WT\t RT\t \n");

    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }

}
int main(){
    int n = 2;
    P p[n];
    printf("Enter details\n ");
    for(int i=0;i<n;i++){
        printf("ID: %d \n", i+1);
        printf("AT: "); scanf("%d", &p[i].at);
        printf("BT: "); scanf("%d", &p[i].bt);
        p[i].leftTime = p[i].bt;
        p[i].id = i+1;//initialize id and left time
    }

    fcfs(p,n);
}