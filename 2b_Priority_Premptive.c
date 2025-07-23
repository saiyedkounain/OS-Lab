#include <stdio.h>

typedef struct {
    int id,at,bt,ct,leftTime,tat,wt,rt, pri;
}P;

void priorityPremptive(P p[], int n){
    int t=0,left=n,i,ex,tp[100],pt[100],minP,ti=0,pi=0;
    float tta, twt, trt;
    tp[ti++] = 0;
    while(left){
        //init
        minP = 9999; ex =-1;
        for(i=0;i<n;i++){
            if(p[i].at <= t && p[i].pri < minP && p[i].leftTime > 0){
                ex =i;
                minP = p[i].pri;
            }
        }

        //if idle
        if(ex == -1){
            pt[pi++] = 0;
            t++;
            tp[ti++] = t;
        }

        //response time
        if(p[ex].leftTime == p[ex].bt){
            p[ex].rt = t - p[ex].at;
        }

        //move forward
        t++;
        p[ex].leftTime--;
        pt[pi++] = p[ex].id;
        tp[ti++] = t;

        //end process
        if(p[ex].leftTime == 0){
            //calculate
            p[ex].ct = t;
            p[ex].tat = p[ex].ct - p[ex].at;
            p[ex].wt = p[ex].tat - p[ex].bt;
            tta+=p[ex].tat;
            twt+=p[ex].wt;
            trt+=p[ex].rt;
            left--;
        }


    }

    printf("Observation Table \n ID \t AT\t BT \t CT \t TAT \t WT \t RT \t Priority \n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t,%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt, p[i].pri);
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
        printf("Priority: "); scanf("%d", &p[i].pri);
        p[i].leftTime = p[i].bt;
        p[i].id = i+1;//initialize id and left time
    }

    priorityPremptive(p,n);

    return 0;
}