#include<stdio.h>
#include <stdlib.h>

main(){

	int np,i,j,temp,tempp,tempb,twt=0;
	printf("Enter the No.of process: ");
	scanf("%d",&np);


	int pno[np],at[np],bt[np],ct[np],tat[np],wt[np];
	float awt;

	

	for(i=0;i<np;i++){
		printf("Enter Process No: ");
		scanf("%d",&pno[i]);
		
		printf("Enter the Arival Time: ");
		scanf("%d",&at[i]);

		printf("Enter the Burst Time: ");
		scanf("%d",&bt[i]);
		

	}

    //sort on the basis of arrival time.
    for(i=0;i<np;i++){
		for(j=i;j<np;j++){
            if(at[i]>at[j]){
            tempb=bt[i];
				temp=at[i];
                tempp=pno[i];
                
                bt[i]=bt[j];
				at[i]=at[j];
                pno[i]=pno[j];
                
                bt[j]=tempb;
				at[j]=temp;
                pno[j]=tempp;   
        }
    }
}

    ct[0]=bt[0];
	tat[0]=ct[0]-at[0];
	wt[0]=tat[0]-bt[0];
    twt=twt+wt[0];

    
    

    

	//sort on the basis of burst time.
	for(i=1;i<np;i++){
		for(j=i;j<np;j++){
			if(bt[i]>bt[j]){
                tempb=bt[i];
				temp=at[i];
                tempp=pno[i];
                
                bt[i]=bt[j];
				at[i]=at[j];
                pno[i]=pno[j];
                
                bt[j]=tempb;
				at[j]=temp;
                pno[j]=tempp;
			}
		}		
	}


	//calculation of ct,tat,wt
	
	for(i=1;i<np;i++){
		ct[i]=ct[i-1]+bt[i];
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt[i];	
	}
    
	//calculation of average waiting time.

	for(i=1;i<np;i++){
		twt=twt+wt[i];
	}
	awt=(float)twt/np;

	system("clear");

	printf("\n+---------------------------------------------------------------------------------------+\n");
	printf("|P.No\t|\tAT\t|\tBT\t|\tCT\t|\tTAT\t|\tWT\t|\n");
	printf("+---------------------------------------------------------------------------------------+\n");
	for(i=0;i<np;i++){
		printf("|P%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n",pno[i],at[i],bt[i],ct[i],tat[i],wt[i]);
	}
	printf("+---------------------------------------------------------------------------------------+\n");
	printf("\nAverage Waiting Time = %f\n\n",awt);
}
