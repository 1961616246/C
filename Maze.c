#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct {
	int a[10000];
	int ve;
}Edge;
typedef struct {
	int a[10000];
	int n;
}Stack;
int maze[100][100];
void Init_maze(int n,Edge *e);
void Show_maze(int n);
void Add_Edge(Edge *e,int n);
int Del_Edge(Edge *e,int k);
void Kruskal(int n,Edge *e); 
int AddToDs(int Ds[],int v1,int v2);
void Path(int n);
void Push(Stack *s,int n);
int main()
{
	Edge e;
	e.ve=-1;
	int n;
	printf("Please enter a number in 4 to 100(q to quit):");
	while(scanf("%d",&n)==1)
	{
		if(n>=4&&n<=100)
		{
			Init_maze(n,&e);
			Kruskal(n,&e);
			Show_maze(n);
			Path(n);
			printf("\nThe answer is:\n\n");
			Show_maze(n);
		}
		printf("\nPlease enter a number in 4 to 100(q to quit):");
	}
	system("pause"); 
	return 0;
}
void Init_maze(int n,Edge *e)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==0||j==0||i==n-1||j==n-1)
				maze[i][j]=-1;
			else if((i%2==1&&j%2==1)||(n%2==0&&i==n-2&&j==n-2))  //Vertex
				maze[i][j]=1;
			else if((i%2==1&&j%2==0)||(i%2==0&&j%2==1)) //Edge
			{
				maze[i][j]=0; 
				Add_Edge(e,i*n+j);
			}
			else if(i%2==0&&j%2==0)
				maze[i][j]=-1;
		}
	} 
}
void Show_maze(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		printf("%3d ",i);
		for(j=0;j<n;j++)
		{
			if(maze[i][j]==1)	printf("  ");       //Road
			else if(maze[i][j]==-1)	printf("▇");   //Wall 
			else if(maze[i][j]==0)	printf("●");   //Path
		}
		printf("\n");
	}	
}
void Add_Edge(Edge *e,int n)
{
	e->ve++;
	e->a[e->ve]=n;
}
int Del_Edge(Edge *e,int k)
{
	int i;
	int tmp=e->a[k];
	for(i=k;i<=e->ve-1;i++)
		e->a[i]=e->a[i+1];
	e->ve--;
	return tmp;
}
void Kruskal(int n,Edge *e)
{
	int Ds[10000];
	int i,v;
	for(i=0;i<=n*n;i++)
		Ds[i]=-1;
	srand(time(NULL));
	while(e->ve>=0)
	{
		int k=rand()%(e->ve+1);
		v=Del_Edge(e,k);
		if((v/n)%2==1)
		{
			if(AddToDs(Ds,v-1,v+1)==1)  //不属于同一颗生成树 
				maze[v/n][v%n]=1;
			else maze[v/n][v%n]=-1;
		}
		else
		{
			if(AddToDs(Ds,v-n,v+n)==1)
				maze[v/n][v%n]=1;
			else maze[v/n][v%n]=-1;
		}
	}
}
int AddToDs(int Ds[],int v1,int v2)
{
	int t1=v1;
	int t2=v2;
	while(Ds[t1]>=0)
		t1=Ds[t1];
	while(Ds[t2]>=0)
		t2=Ds[t2];
	if(t1==t2)
		return 0;
	else
	{
		if(t1<t2)
		{
			Ds[t1]=Ds[t1]+Ds[t2];
			Ds[t2]=t1;
		}
		else
		{
			Ds[t2]=Ds[t1]+Ds[t2];
			Ds[t1]=t2;
		}
		return 1;
	}
}
void Path(int n)
{
	int now=n+1;
	int direction[10000]={0};
	Stack s;
	s.n=-1;
	int flag;
	do{
		if(maze[now/n][now%n]==1)
		{
			Push(&s,now);   //push
			if(now==n*n-n-2)
				break;
			else
			{
				if(now+1!=s.a[s.n-1])
				{
					direction[now]++;
					now=now+1;
				}
				else if(now+n!=s.a[s.n-1])
				{
					direction[now]+=2;
					now=now+n;
				}
			} 
		}
		else
		{
			flag=0;
			if(s.n>=0&&direction[s.a[s.n]]<4)
			{
				if(direction[s.a[s.n]]==1)  //go to south
				{
					if((s.a[s.n])/n!=n-1&&(s.a[s.n])+n!=s.a[(s.n)-1])   
					{
						now=s.a[s.n]+n;
						flag=1;
					}
					else direction[s.a[s.n]]++;
				}
				if(direction[s.a[s.n]]==2)  //go to west
				{
					if((s.a[s.n])%n!=0&&(s.a[s.n])-1!=s.a[(s.n)-1])
					{
						flag=1;
						now=s.a[s.n]-1;
					}
					else direction[s.a[s.n]]++;
				}
				if(direction[s.a[s.n]]==3)  // go to north
				{
					if((s.a[s.n])/n!=0&&(s.a[s.n])-n!=s.a[(s.n)-1])
					{
						now=s.a[s.n]-n;
						flag=1;
					}
					else  direction[s.a[s.n]]++;
				}
				if(flag==1)
					direction[s.a[s.n]]++;
			}
			if(flag!=1)
				while(s.n>=0&&direction[s.a[s.n]]>=4)
					s.n--;    //pop
		}
	}while(s.n>=0);
	int i;
	for(i=0;i<=s.n;i++)
		maze[(s.a[i])/n][(s.a[i])%n]=0;
}
void Push(Stack *s,int n)
{
	s->n++;
	s->a[s->n]=n;
}
