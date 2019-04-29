#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int *req_que,req,cyl,start;

int absolute(int a,int b)
  {
     int c;
     c=a-b;
     if(c<0)
         return -c;
     else
         return c;
  }

void asc(int *a)
 {
   int i,j,x;
   for(i=0;i<req;i++)
     {
        for(j=0;j<req-i-1;j++)
          {   
            if(a[j]>a[j+1])
              {
                x=a[j];
                a[j]=a[j+1];
                a[j+1]=x;
               }
          }
     }
 }

void desc(int pos,int *a)
 {
   int i,j,x;
   for(i=0;i<pos;i++)
     {  
        for(j=0;j<pos-i-1;j++)
          {
	     if(a[j]<a[j+1])
               {
                 x=a[j];
                 a[j]=a[j+1];
                 a[j+1]=x;
               }
           }
      }
 }

void* fcfs(void *arg)
  {
    int k,*que=(int *)arg,count=0,count1=2,x=start,*res;
    res=(int *)malloc((req+2)*sizeof(int));
    res[1]=x;

    for(k=0;k<req;k++)
       {
          x-=que[k];	    
          if(x<0)
              x=-x;
          count+=x;
	  x=que[k];	    
          res[count1++]=x;	 
       }
     res[0]=count;

    pthread_exit((void *)res);
  }

void* sstf(void *arg)
  {
    int i,j,k,pos,min,*arr=(int *)arg,count=0,count1=2,x=start,*res;
    int que[req];
    for(k=0;k<req;k++)
      {
        que[k]=arr[k]; 
      }    
    res=(int *)malloc((req+2)*sizeof(int));
    res[1]=x;

    for(i=0;i<req;i++)
       {
          min=absolute(que[i],x);
          pos=i;
          for(j=i;j<req;j++)
             {
                if(min>absolute(x,que[j]))
                  {
                    pos=j;
                    min=absolute(x,que[j]);
                  }
             }
           count+=absolute(x,que[pos]);
           x=que[pos];
           que[pos]=que[i];
           que[i]=x;
           res[count1++]=x;
          
       }
      res[0]=count;

    pthread_exit((void *)res);       
  }

void* scan(void *arg)
  {
    int i,k,pos=0,min,*arr=(int *)arg,count=0,count1=2,x=start,*res;
    int que[req];
    for(k=0;k<req;k++)
      {
        que[k]=arr[k]; 
      }    
    res=(int *)malloc((req+3)*sizeof(int));
    res[1]=x;

    asc(que);
    for(i=0;i<req;i++)
       {
          if(que[i]<=start)
            {			    
              pos++;
            }
       }
    
    desc(pos,que);
    
    for(i=0;i<pos;i++)
      {
         count+=absolute(que[i],x);
         x=que[i];
         res[count1++]=x;
      }
    count+=absolute(x,0);
    x=0;
    res[count1++]=0;
    for(i=pos;i<req;i++)
      {
         count+=absolute(que[i],x);
         x=que[i];
         res[count1++]=x;
      }
    res[0]=count;
   
    pthread_exit((void *)res);
  }

void* cscan(void *arg)
  {//z=1
    int i,j,k,pos=0,min,*arr=(int *)arg,count=0,count1=2,x=start,*res;
    int que[req];
    for(k=0;k<req;k++)
      {
        que[k]=arr[k]; 
      }
    res=(int *)malloc((req+2)*sizeof(int));
    res[1]=x;

    asc(que);
    for(i=0;i<req;i++)
      {
         if(que[i]<start)
           {
	     pos++;
           }
      }
    for(i=pos;i<req;i++)
      {
         count+=absolute(x,que[i]);
         x=que[i];
         res[count1++]=x;
      }
    count+=absolute(cyl-1,x);
    x=0;
    res[count1++]=0;
    for(i=0;i<pos;i++)
      {
         count+=absolute(x,que[i]);
         x=que[i];
         res[count1++]=x;
      }
    res[0]=count;

   pthread_exit((void *)res); 
  }

void* look(void *arg)
  {//z=1
    int i,k,j,pos=0,min,*arr=(int *)arg,count=0,count1=2,x=start,*res;
    int que[req];
    for(k=0;k<req;k++)
      {
        que[k]=arr[k]; 
      }
    res=(int *)malloc((req+2)*sizeof(int));
    res[1]=x; 
    
    asc(que);
    for(i=0;i<req;i++)
      {
	 if(que[i]<=start)
           {
   	     pos++;
           } 
      }	    
    desc(pos,que);
    for(i=0;i<pos;i++)
      {
         count+=absolute(que[i],x);
         x=que[i];
         res[count1++]=x;
      }
    for(i=pos;i<req;i++)
      {
         count+=absolute(que[i],x);
         x=que[i];
         res[count1++]=x;
      }
    res[0]=count;

    pthread_exit((void *)res);
  }

void* clook(void *arg)
  {//z=1
    int i,k,j,pos=0,min,*arr=(int *)arg,count=0,count1=2,x=start,*res;
    int que[req];
    for(k=0;k<req;k++)
      {
        que[k]=arr[k]; 
      }    
    res=(int *)malloc((req+2)*sizeof(int));
    res[1]=x;
    asc(que);
    for(i=0;i<req;i++)
      {
          if(que[i]<start)
            {
	      pos++;
            }
      } 
    for(i=pos;i<req;i++)
      {
        count+=absolute(x,que[i]);
        x=que[i];
        res[count1++]=x;
      }
    for(i=0;i<pos;i++)
      {
         count+=absolute(x,que[i]);
         x=que[i];
         res[count1++]=x;
      }
     res[0]=count;

    pthread_exit((void *)res);
 }


//********************************MAIN*****************************************

int main()
{
  int i,*r1,*r2,*r3,*r4,*r5,*r6,choice;
  pthread_t FCFS,SSTF,SCAN,CSCAN,LOOK,CLOOK;

  printf("**************DISK SCHEDULING***************");
  printf("\nEnter the number of Cylinders/Tracks : ");
  scanf("%d",&cyl);
  printf("\nEnter the number of requests : ");
  scanf("%d",&req);
  printf("\nEnter current position of read/write head: ");
  scanf("%d",&start);
  
  req_que=(int *)malloc(req*sizeof(int));

  printf("\nEnter the request queue : ");
      for(i=0;i<req;i++)
        {
          scanf("%d",&req_que[i]);
          if(req_que[i]>=cyl)
              {
                 printf("\ninvalid input");
                 scanf("%d",&req_que[i]);
              }
        }
  
  int *copy_que,j;
  copy_que=(int *)malloc(req*sizeof(int));
    for(j=0;j<req;j++)
        {
         copy_que[j]=req_que[j]; 
        }
  
  pthread_create(&FCFS,NULL,fcfs,(void *)copy_que);
  pthread_create(&SSTF,NULL,sstf,(void *)copy_que);
  pthread_create(&SCAN,NULL,scan,(void *)copy_que);
  pthread_create(&CSCAN,NULL,cscan,(void *)copy_que); 
  pthread_create(&LOOK,NULL,look,(void *)copy_que);
  pthread_create(&CLOOK,NULL,clook,(void *)copy_que);
  
  pthread_join(FCFS,(void **)&r1);
  pthread_join(SSTF,(void **)&r2);
  pthread_join(SCAN,(void **)&r3);
  pthread_join(CSCAN,(void **)&r4);
  pthread_join(LOOK,(void **)&r5);
  pthread_join(CLOOK,(void **)&r6);


do
   {
      printf("\n\nDISK SCHEDULING ALGORITHMS\n1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK");
      printf("\nEnter no of choices : ");
      scanf("%d",&choice);
      int r,c[choice],minn,cmin;
      printf("\nEnter the choices : ");
      for(r=0;r<choice;r++)
        {
           scanf("%d",&c[r]);
        }
     /* minn=99999999;
      for(r=0;r<choice;r++)
        {
           if(minn>c[r])
             {  cmin=r;
                minn=c[r];
             }    
        }*/
      printf("\n\nREQUESTED QUEUE IS:");
      for(i=0;i<req;i++)
        {
           printf("\t%d", copy_que[i]);
        }
      /*switch(cmin)
      {
        case 1:printf("\n\n Best working algorithm : FCFS ");
               break;
      }*/
     for(r=0;r<choice;r++)
      {
        switch(c[r])
         {
           case 1:printf("\n\n\t\t***************FCFS****************\n\n");
                  printf("\nTotal Head Movement : %d Cylinders\n\n",r1[0]);
                  printf("Scheduling services the request in the order that follows:\n");
                  int f1;
                  for (f1=1;f1<(req+2);f1++)
                    {
                      printf("%d ",r1[f1]);
                    }
                  
                  FILE *fp1;
                  
                  fp1=fopen("fcfs.dat","w");
                  if(fp1 == NULL)
                    {
                      printf("unable to open file");
                      return 0;
                    }
                  
                  for (f1=1;f1<(req+2);f1++)
                    {
                      fprintf(fp1,"%d %d\n",f1,r1[f1]);
                    }
                  fclose(fp1);

                  FILE *pipe_gp1 = popen("gnuplot -p", "w");
                  //fputs("set xlabel \n",pipe_gp1);
                  fputs("set border linewidth 1.5\n",pipe_gp1);
                  fputs("set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 2\n",pipe_gp1);
                  fputs("set xrange [-2:7]\n",pipe_gp1);
                  fputs("set yrange [-2:7]\n",pipe_gp1);
                  fputs("plot  'fcfs.dat' with linespoints ls 1\n", pipe_gp1);
                  pclose(pipe_gp1);
                  

            	  break;

          case 2:printf("\n\n\t\t***************SSTF***************\n\n");
                 printf("\nTotal Head Movement: %d Cylinders\n\n",r2[0]);
                 printf("Scheduling services the request in the order that follows:\n");
                 int f2;
                 for (f2=1;f2<(req+2);f2++)
                    {
                      printf("%d ",r2[f2]);
                    }                                   

                 FILE *fp2;
          
                 fp2=fopen("sstf.dat","w");
                 if(fp2 == NULL)
                   {
                      printf("unable to open file");
                      return 0;
                   }
                 
                 for (f2=1;f2<(req+2);f2++)
                   {
                     fprintf(fp2,"%d %d\n",f2,r2[f2]);
                   }
                 fclose(fp2);

                 FILE *pipe_gp2 = popen("gnuplot -p", "w");
                 //fputs("set xlabel \n",pipe_gp2);
                 fputs("set border linewidth 1.5\n",pipe_gp2);
                 fputs("set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 2\n",pipe_gp2);
                 fputs("set xrange [-2:7]\n",pipe_gp2);
                 fputs("set yrange [-2:7]\n",pipe_gp2);
                 fputs("plot  'sstf.dat' with linespoints ls 1\n", pipe_gp2);
                 pclose(pipe_gp2);

	         break;

          case 3:printf("\n\n\t\t***************SCAN**************\n\n");
                 printf("\nTotal Head Movement: %d Cylinders\n\n",r3[0]);
                 printf("Scheduling services the request in the order that follows:\n");
                 int f3;
                 for (f3=1;f3<(req+3);f3++)
                   {
                     printf("%d ",r3[f3]);
                   }

                 FILE *fp3;
          
                 fp3=fopen("scan.dat","w");
                 if(fp3 == NULL)
                   {
                      printf("unable to open file");
                      return 0;
                   }
                 
                 for (f3=1;f3<(req+3);f3++)
                   {
                     fprintf(fp3,"%d %d\n",f3,r3[f3]);
                   }
                 fclose(fp3);

                 FILE *pipe_gp3 = popen("gnuplot -p", "w");
                 //fputs("set xlabel \n",pipe_gp3);
                 fputs("set border linewidth 1.5\n",pipe_gp3);
                 fputs("set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 2\n",pipe_gp3);
                 fputs("set xrange [-2:7]\n",pipe_gp3);
                 fputs("set yrange [-2:7]\n",pipe_gp3);
                 fputs("plot  'scan.dat' with linespoints ls 1\n", pipe_gp3);
                 pclose(pipe_gp3);
                        
                 break;

          case 4:printf("\n\n\t\t***************C-SCAN************\n\n");
                 printf("\nTotal Head movement: %d Cylinders\n\n",r4[0]);
                 printf("Scheduling Services the request in the order that follows:\n");
                 int f4;
                 for (f4=1;f4<(req+3);f4++)
                   {
                     printf("%d ",r4[f4]);
                   }

                 FILE *fp4;
          
                 fp4=fopen("cscan.dat","w");
                 if(fp4 == NULL)
                   {
                      printf("unable to open file");
                      return 0;
                   }
                 
                 for (f4=1;f4<(req+3);f4++)
                   {
                     fprintf(fp4,"%d %d\n",f4,r4[f4]);
                   }
                 fclose(fp4);

                 FILE *pipe_gp4 = popen("gnuplot -p", "w");
                 //fputs("set xlabel \n",pipe_gp4);
                 fputs("set border linewidth 1.5\n",pipe_gp4);
                 fputs("set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 2\n",pipe_gp4);
                 fputs("set xrange [-2:7]\n",pipe_gp4);
                 fputs("set yrange [-2:7]\n",pipe_gp4);
                 fputs("plot  'cscan.dat' with linespoints ls 1\n", pipe_gp4);
                 pclose(pipe_gp4);                
      
                 break;

          case 5:printf("\n\n\t\t*****************LOOK**********\n\n");
                 printf("\nToal Head Movement: %d Cylinders\n\n",r5[0]);
                 printf("\nScheduling services the request in the order as follows :\n");
                 int f5;
                 for (f5=1;f5<(req+2);f5++)
                   {
                     printf("%d ",r5[f5]);
                   }

                 FILE *fp5;
          
                 fp5=fopen("look.dat","w");
                 if(fp5 == NULL)
                   {
                      printf("unable to open file");
                      return 0;
                   }
                 
                 for (f5=1;f5<(req+2);f5++)
                   {
                     fprintf(fp5,"%d %d\n",f5,r5[f5]);
                   }
                 fclose(fp5);

                 FILE *pipe_gp5 = popen("gnuplot -p", "w");
                 //fputs("set xlabel \n",pipe_gp5);
                 fputs("set border linewidth 1.5\n",pipe_gp5);
                 fputs("set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 2\n",pipe_gp5);
                 fputs("set xrange [-2:7]\n",pipe_gp5);
                 fputs("set yrange [-2:7]\n",pipe_gp5);
                 fputs("plot  'look.dat' with linespoints ls 1\n", pipe_gp5);
                 pclose(pipe_gp5);
                 
                 break;

          case 6:printf("\n\n\t\t***************C-LOOK***********\n\n");
                 printf("\nToal Head Movement: %d Cylinders\n\n",r6[0]);
                 printf("\nScheduling services the request in the order as follows :\n");
                 int f6;
                 for (f6=1;f6<(req+2);f6++)
                   {
                     printf("%d ",r6[f6]);
                   }

                 FILE *fp6;
          
                 fp6=fopen("clook.dat","w");
                 if(fp6 == NULL)
                   {
                      printf("unable to open file");
                      return 0;
                   }
                 
                 for (f6=1;f6<(req+2);f6++)
                   {
                     fprintf(fp6,"%d %d\n",f6,r6[f6]);
                   }
                 fclose(fp6);

                 FILE *pipe_gp6 = popen("gnuplot -p", "w");
                 //fputs("set xlabel \n",pipe_gp6);
                 fputs("set border linewidth 1.5\n",pipe_gp6);
                 fputs("set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 2\n",pipe_gp6);
                 fputs("set xrange [-2:7]\n",pipe_gp6);
                 fputs("set yrange [-2:7]\n",pipe_gp6);
                 fputs("plot  'clook.dat' with linespoints ls 1\n", pipe_gp6);
                 pclose(pipe_gp6);			   
                 break;

         }
      }

        printf("\n\nDo you want to continue(1 to continue) :");
        scanf("%d",&choice);
 }while(choice==1);

return 0;
}
