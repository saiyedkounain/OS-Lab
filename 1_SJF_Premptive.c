#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id,at,bt,ct,tat,wt,rt; //usual variables
    int leftTime;//since its premptive
}P;

void sjfPre(P p[], int n){
    //9 ints
    int t=0,left=n,i,ex,sbt,tp[100],pt[100], ti=0,pi=0;
    //3 floats
    float tta, twt, trt; //turn around, waiting, response
    //array initialization
    tp[ti++] = 0;
    while(left){
        //initialization
        sbt=999; ex = -1;

        //find shortest
        for(i=0;i<n;i++){
            if(p[i].at <= t && p[i].leftTime > 0 && p[i].leftTime < sbt){
                sbt = p[i].leftTime;
                ex=i;
            }
        }

        //idle situation
        if(ex == -1){
            pt[pi++] = 0;
            tp[ti++] = t;
            t++;
            continue;
        }

        //first response situation
        if(p[ex].leftTime == p[ex].bt){
            p[ex].rt = t - p[ex].at;
        }

        //move forward a sec
        p[ex].leftTime--;
        t++;
        tp[ti++] = t;
        pt[pi++] = p[ex].id;

        //end situation
        if(p[ex].leftTime == 0){
            //calculate 3+3
            p[ex].ct = t;
            p[ex].tat = p[ex].ct - p[ex].at;
            p[ex].wt = p[ex].tat - p[ex].bt;

            tta+=p[ex].tat;
            twt+=p[ex].wt;
            trt+=p[ex].rt;

            left--;
        }

        
    }

    printf("Observation Table \n");
    printf("id\tat\tbt\tct\ttat\twt\trst \n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d \n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("Gantt Chartt\n");
    for(int i=0;i<pi;i++){
        printf("P%d |", pt[i]);
    }
    printf("\n");

    for(int i=0;i<ti ;i++){
        printf("%d |", tp[i]);
    }
    printf("\n");

    printf("Avg TAT: %.2f \n Avg WT: %.2f \n Avg RT: %.2f \n", tta,twt,trt);

    
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

    sjfPre(p,n);
}