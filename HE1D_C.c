#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define  M       20
#define  Time    10
#define  dt      0.01
#define  dx      0.1
#define  D       0.1
//=========================
void DisplayArray(float *T, int size)
{
  int i;
  for(i=0;i<size;i++)
    printf("  %.2f",*(T+i));
  printf("\n");
  
}
//=========================
void Write2File(float *T, int size)
{
FILE *result=fopen("result2.txt", "a");
int i;

for(i=0;i<size;i++) 
{
fprintf(result, "%lf", *(T+i));
fprintf(result, "\n");
}

fclose(result);
}
//=========================
void KhoiTao(float *T)
{
  int i,j;
for (  i = 0 ; i < M ; i++ )
     *(T+i) = 25.0;
}
//=========================
void Daoham(float *T, float *dT,int stt,int stp)
{
int i;
float c,l,r;
for (  i = 0 ; i < M ; i++ )
    {
      c = *(T+i);
      l = (i==0)   ? 100.0 : *(T+(i-1));
      r = (i==M-1) ? 25.0  : *(T+(i+1));
      *(dT+i) = (r-2*c+l)/(dx*dx);
    }
}
//=========================
int main()
{
	int i,t, Ntime;
	float *T,*dT;
	int id, stt, stp;
	T  = (float *) malloc ((M)*sizeof(float));
	dT = (float *) malloc ((M)*sizeof(float));
	KhoiTao(T);
	printf("Gia tri khoi tao:\n");
	DisplayArray(T, M);
	Write2File(T,M);
	Ntime = Time/dt;
	omp_set_num_threads(5);
	#pragma omp parallel private(id,i,stt,stp)
	{
		id = omp_get_thread_num();
		stt = id*Ntime; stp = id*Ntime+Ntime;
    for (t=stt;t<stp;t++){
	  Daoham(T, dT,stt,stp);
	  for (  i = 0 ; i < M ; i++ )
	      *(T+i) = *(T+i) + D*dt*(*(dT+i));
	  Write2File(T,M);
	}
	}

	printf("Result of C:\n");
	DisplayArray(T, M);
return 0;
}

