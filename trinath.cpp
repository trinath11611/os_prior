#include<stdio.h>
#include<stdlib.h>
int time,flag=0;
struct process
{
   int pid;
   int runtime;
   float prior;
   int wt;
   int remaining_time;
   int arrival;
};
void priorityassign(struct process* s,int n)
{
  for(int i=0;i<n;i++)
 {
   if(s[i].wt<0)
   s[i].prior=-1;
   else if(s[i].runtime!=0)
  {
    s[i].prior=1.0+(((float)s[i].wt)/s[i].runtime);
    printf("priority of process with pid %d: %.1f\n",s[i].pid,s[i].prior);
  }
 }
}
void waitassign(struct process*s,int n,int x)
{
  for(int i=0;i<n;i++)
  {
    if(i!=x)
    s[i].wt++;
  }
}
int processassign(struct process*s,int n)
{
   float max=s[0].prior;
   float temp;
   int m=n,i=0,count=0;
   while(m)
  {
    if(s[i].wt<0)
    count++;
    i=i+1;
    m--;
  }
   if(count==n)
   return -1;
   else
 {
  flag++;
  count=0;
   for( int j=0;j<n;j++)
  {
   if(s[j].prior>max)
   {
    max=s[j].prior;
    temp=j;
   }
  }
  return temp;
 }
}
void firstprocessassign(struct process*s,int n)
{
   int a[n],temp;
   for(int i=0;i<n;i++)
   {
      a[i]=s[i].runtime;
   }
   for(int i=0;i<n-1;i++)
   {
    for(int j=0;j<n-i-1;j++)
      {
         if(a[j]>a[j+1])
	    {
	      temp=a[j];
	      a[j]=a[j+1];
	      a[j+1]=temp;
	    }
       }
    }
   for(int j=0;j<n;j++)
   {
     if(a[0]==s[j].runtime && s[j].wt>=0)
     {   
      s[j].remaining_time=s[j].runtime;
      while((s[j].remaining_time)--)
      {
      printf("**process running is p id %d: %d**\n",s[j].pid,s[j].remaining_time);
      waitassign(s,n,j);
      priorityassign(s,n);
      }
      s[j].runtime=0; 
      s[j].prior=-1;
     }
   }
}
main()
{ 
  printf("\nEnter the no. of process");
  int n;
  scanf("%d",&n);
  struct process p[n];
  p[0].pid=0;
  for(int i=1;i<n;i++)
  {
    p[i].pid=p[i-1].pid+1;
  }
  printf("\nEnter the process run time");   
  for(int i=0;i<n;i++)
  {
    printf("\nProcess %d :",i);
    scanf("%d",&p[i].runtime);
  } 
  int temp;
  printf("\nEnter the arrival time");        
  for(int i=0;i<n;i++)
  {
    printf("\nProcess %d :",i);
    scanf("%d",&p[i].arrival);
  }
  for(int i=0;i<n;i++)                      
  {
    p[i].wt=-p[i].arrival;
  }
  priorityassign(p,n);
  int m=n;
  int x;
  time=0;
  while(m)
  {
    int count=0;
    for(int i=0;i<n;i++)
    {
       if(p[i].runtime==0)
       count++;
    }
    if(count==n)
    break;
    x=processassign(p,n);
    if(x==-1)
    {
       time++;
       printf("time:%d\n",time);
       waitassign(p,n,-1);
       priorityassign(p,n);
    }
    else
    {
      if(flag==1)
      firstprocessassign(p,n);
      p[x].remaining_time=p[x].runtime;
      while((p[x].remaining_time)--)
      {
        time++;
        printf("time:%d\n\n",time); //last time shows total burst time
        printf("*process is p id %d: %d*\n\n",p[x].pid,p[x].remaining_time);
        waitassign(p,n,x);
        priorityassign(p,n);
      }
      p[x].runtime=0;
      p[x].prior=-1;
      m=m-1;
    }
} 
}

