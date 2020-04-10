#include<stdio.h>
#include<stdlib.h>

// Safety algorithm

void print(int x[][10],int n,int m);
int safety(int A[][10],int N[][10],int AV[1][10],int n,int m,int a[]);

void input(int A[][10],int N[][10],int M[10][10],int W[1][10],int *n,int *m);

int banker(int A[][10],int N[][10],int W[1][10],int n,int m){
	int j,i,a[10];
	j=safety(A,N,W,n,m,a);
	if(j != 0 ){
		printf("\n\n");
		for(i=0;i<n;i++)
		     printf(" P%d  ",a[i]);
		printf("\n System is in safe state.\n");
		return 1;
	}
	printf("\n System is not in safe state.\n");
	return 0;
}

int main(){
	int Allocation[10][10];
	int MaxAvail[10][10];
	int Need[10][10];
	int Available[1][10];		// letter uses W
	int n,m;

	do{

		printf("\t\t\tDeadlock Detection Algorithm\n");
		printf("\n\t1. Default input");
		printf("\n\t2. Custom input");
		printf("\n\t3. Exit\n >");
		int c;
		scanf("%d",&c);
		switch(c){
			case 1:
				n = 5; 
				m = 4;
				int Alloc[][10] = {{0,0,1,2},
      						            {1,0,0,0},
   	    					            {1,3,5,4},
   		    				            {0,6,3,2},
   			    			            {0,0,1,4}};

				int MaxAv[][10] = {{0,0,1,2},
							{1,7,5,0},
							{2,3,5,6},
							{0,6,5,2},
							{0,6,5,6}};

				int Avail[][10] = {{1},{5},{2},{0}} ;
				for(int i=0;i<n;i++)
					for(int j=0;j<m;j++)
						Need[i][j] = MaxAv[i][j] - Avail[i][j] ;

				banker( Alloc, Need, Avail, n, m);
				break;
			case 2:
				input( Allocation, Need, MaxAvail, Available, &n, &m);
				banker( Allocation, Need, Available, n, m);
				break;
			case 3:
				exit(0);
		}
	
	}while(1);
	return 0;
}

void print(int x[][10],int n,int m){
	int i,j;
	for(i=0;i<n;i++){
		printf("\n");
		for(j=0;j<m;j++){
			printf("%d\t",x[i][j]);
		}
	}	
}

int safety(int A[][10],int N[][10],int AV[1][10],int n,int m,int a[]){

	int i,j,k,x=0;
	int F[10],W[1][10];
	int pflag=0,flag=0;
	for(i=0;i<n;i++)
		F[i]=0;
	for(i=0;i<m;i++)
		W[0][i]=AV[0][i];

	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			if(F[i] == 0){
				flag=0;
				for(j=0;j<m;j++){
					if(N[i][j] > W[0][j])
						flag=1;
				}
				if(flag == 0 && F[i] == 0){
					for(j=0;j<m;j++)
						W[0][j]+=A[i][j];
					F[i]=1;
					pflag++;
					a[x++]=i;
				}
			}
		}
		if(pflag == n)
			return 1;
	}
	return 0;
}

void input(int A[][10],int N[][10],int M[10][10],int W[1][10],int *n,int *m){
	int i,j;
	printf("\n\tEnter Total no. of Rrocesses : ");
	scanf("%d",n);
	printf("\n\tEnter Total no. of Resources : ");
	scanf("%d",m);

	for(i=0;i<*n;i++){
		printf("\n Process %d\n",i+1);
		for(j=0;j<*m;j++){
			printf(" Allocation for Resource %d : ",j+1);
			scanf("%d",&A[i][j]);
			printf(" Maximum for Resource %d : ",j+1);
			scanf("%d",&M[i][j]);
		}
	}

	printf("\n\tAvailable resources : \n");
	for(i=0;i<*m;i++){
		printf("\tResource %d : ",i+1);
		scanf("%d",&W[0][i]);
	}

	for(i=0;i<*n;i++)
		for(j=0;j<*m;j++)
			N[i][j] = M[i][j]-A[i][j];

	printf("\n\tAllocation Matrix");
	print(A,*n,*m);
	printf("\n\tMaximum Requirement Matrix");
	print(M,*n,*m);
	printf("\n\tNeed Matrix");
	print(N,*n,*m);

}