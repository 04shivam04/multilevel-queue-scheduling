#include<stdio.h>
#include<stdlib.h>

int i,currTime=0,queueQuantum=10,total;
struct processStruct{
	int pid;
	int compTime;
	int arrival;
	int start;
	int priority;
	int brustTime;
	int store;
};
void roundRobinAlgorithm(struct processStruct p[],int queueNo)
{		printf("Round Robin Running @ %d sec\n",currTime);
		int timeQuantum=2;
		for( i=0;i<queueNo;i++)
		{	
			if(timeQuantum<=queueQuantum&&p[i].arrival<=currTime)
			{
			if(p[i].start==-1)
			{
			p[i].start=currTime;
			}
			if(p[i].brustTime>=timeQuantum)//4
			{
			p[i].brustTime=p[i].brustTime-timeQuantum;
			currTime=currTime+timeQuantum;
			queueQuantum-=timeQuantum;
			}
			if(p[i].brustTime<timeQuantum&&p[i].brustTime>0) //4
			{
			currTime=currTime+p[i].brustTime;
			queueQuantum-=p[i].brustTime;
			p[i].brustTime=0;
			}
			if(p[i].brustTime==0&&p[i].compTime==-1)
			{
				p[i].compTime=currTime;
				total--;
			}
			}
		}
		queueQuantum=10;
}
void firstComeFirstServe(struct processStruct p[],int r)
{
	printf("First Come First Serve Running @ %d sec\n",currTime);
		for(i=0;i<r;i++)
		{	
			if(p[i].brustTime<=queueQuantum&&p[i].arrival<=currTime&&p[i].brustTime>0)
			{			
			if(p[i].start==-1)
			p[i].start=currTime;
			p[i].brustTime=0;
			currTime=currTime+p[i].brustTime;
			queueQuantum-=p[i].brustTime;
			if(p[i].brustTime==0&&p[i].compTime==-1)
			{
				p[i].compTime=currTime;
				total--;
			}
			
			}
			else
			{
				if((p[i].brustTime-queueQuantum>0)&&p[i].arrival<=currTime&&p[i].brustTime>0)
				{
				if(p[i].start==-1)
				p[i].start=currTime;
				p[i].brustTime=p[i].brustTime-queueQuantum;
				currTime=currTime+queueQuantum;
				queueQuantum=0;
				if(p[i].brustTime==0&&p[i].compTime==-1)
				{
					p[i].compTime=currTime;
					total--;
				}
				}
			}
		}
		queueQuantum=10;
}
int priorityAlgo(struct processStruct p[],int r,int remain)
{
	printf("Priority Queue Running @ %d sec \n",currTime);
	int smallest;
	while(remain!=0&&queueQuantum>0)
	{
	smallest=r;
	for(i=0;i<r;i++)
	{
		
	if(p[i].arrival<=currTime && p[i].priority<p[smallest].priority && p[i].brustTime>0)
	{
		
	smallest=i;
	}
	}
	if(p[smallest].start==-1)
	{
	
	p[smallest].start=currTime;

	}
	queueQuantum-=1;
	p[smallest].brustTime-=1;
	if(p[smallest].brustTime==0&&p[smallest].compTime==-1)
	{
	
	p[smallest].compTime=currTime;
	total--;
	remain--;
	}
	currTime+=1;
	}
	queueQuantum=10;
	
}
int main()
{	
	int n,i,rr=0,pr=0,fcfs=0;
	total=n;

	
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	total=n;
	struct processStruct ps[n];
    for(i=0;i<n;i++)
    {
    	printf("PROCESS %d :\n",i+1);
		ps[i].pid=i+1;
		printf("Enter the Arrival Time: ");
    	scanf("%d",&ps[i].arrival);
    	printf("Enter the priority 1 for Round Robin \n 2 for First Come First Serve \n Other for Priority: ");
    	scanf("%d",&ps[i].priority);
    	ps[i].compTime=-1;
    	ps[i].start=-1;
    	if(ps[i].priority==1)
		rr++;
		else if(ps[i].priority==2)
		fcfs++;
		else 
		pr++;
		printf("Enter burst time: ");
    	scanf("%d",&ps[i].brustTime);	
		ps[i].store=ps[i].brustTime;
		ps[i].start=-1;
    	ps[i].compTime=-1;
	}
	int rrid=0,prid=0,fcfsid=0;
	struct processStruct roundqueue[rr],priorqueue[pr+1],fcfsqueue[fcfs];
	for(i=0;i<n;i++)
	{
		if(ps[i].priority==1)
		{
			roundqueue[rrid]=ps[i];
			rrid++;
		}
		else if(ps[i].priority==2)
		{
			fcfsqueue[fcfsid]=ps[i];
			fcfsid++;
		}
		else
		{
			priorqueue[prid]=ps[i];
			prid++;
		}
	}
	priorqueue[pr].priority=32767;
	priorqueue[pr].arrival=-1;
	priorqueue[pr].brustTime=-1;
	priorqueue[pr].compTime=-1;
	int remain=pr;
	while(total>0)
	{
		roundRobinAlgorithm(roundqueue,rr);
		remain=priorityAlgo(priorqueue,pr,remain);
		firstComeFirstServe(fcfsqueue,fcfs);
	}
	
	printf("Process Id\tArrival Time\tBrust Time\tStarting Time\tComplition Time\n");
	for(i=0;i<rr;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",roundqueue[i].pid,roundqueue[i].arrival,roundqueue[i].store,roundqueue[i].start,roundqueue[i].compTime);
	}
	for(i=0;i<fcfs;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",roundqueue[i].pid,roundqueue[i].arrival,roundqueue[i].store,roundqueue[i].start,roundqueue[i].compTime);
	}
	for(i=0;i<pr;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",roundqueue[i].pid,roundqueue[i].arrival,roundqueue[i].store,roundqueue[i].start,roundqueue[i].compTime);
	}
}
