#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEVEL 5

#define MAX_ROW 100
#define MAX_COL 100

int room[MAX_ROW][MAX_COL];
int vbar[MAX_ROW][MAX_COL];
int hbar[MAX_ROW][MAX_COL];
int visited[MAX_ROW][MAX_COL];
char string[MAX_COL];


void merge(int ri, int rj, int r);
void resetV(int m, int n);

int main(void){
	int n, m, i, j, rnum=1, random, cnt=0,temp;
	FILE *fp;
	
	printf("너비 : ");
	scanf("%d", &n);
	printf("높이 : ");
	scanf("%d", &m);
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++){
			room[i][j]=0;
			vbar[i][j]=1;
			hbar[i][j]=1;
		}
	}
	srand(time(NULL));


	//행 생성
	for(i=0;i<m-1;i++){
		//열 생성
		for(j=0;j<=n;j++){
			if(room[i][j]==0){
				room[i][j] = rnum++;
			}	
		}
		//세로 벽 제거

			for(j=0;j<n-1;j++){
				if(room[i][j]!=room[i][j+1]){
					random = rand()%10;
					if(random>=LEVEL){
						vbar[i][j+1]=0;

						resetV(m,n);
						merge(i,j,room[i][j]);
					}
				}
			}
		//가로 벽 제거
		for(j=0;j<n-1;j++){
			random = rand()%10;
			if(random>LEVEL){
				hbar[i+1][j]=0;
				room[i+1][j]=room[i][j];
			}
		}
		//가로 남은 벽 제거
		for(j=0;j<n-1;j++){
			if(hbar[i+1][j]==0){cnt++;}
			if(room[i][j]!=room[i][j+1]){
				if(cnt==0){
					hbar[i+1][j]=0;
					room[i+1][j]=room[i][j];
				}
				cnt=0;
			}
		}
		if(cnt==0){
			hbar[i+1][n-1]=0;
			room[i+1][n-1]=room[i][n-1];
		}
		cnt=0;
		printf("h\n");
		for(j=0;j<n;j++){
			printf("%d",hbar[i][j]);
		}
		printf("\nv\n");
		for(j=0;j<n;j++){
			printf("%d",vbar[i][j]);
		}
		printf("\n");

	}
	//마지막 행 생성
	for(j=0;j<n;j++){
		if(room[m-1][j]==0){room[m-1][j]=rnum++;}
	}
	//마지막 행 세로벽 제거

	for(j=0;j<n-1;j++){
		if(room[m-1][j]!=room[m-1][j+1]){
			vbar[m-1][j+1]=0;

			resetV(m,n);
			merge(m-1,j,room[m-1][j]);
		}
	}
	fp=fopen("maze.maz","w");
	for(i=0;i<2*m;i++){
		//한행씩 그리기
		for(j=0;j<2*n+1;j++){
			if(i%2==0){
				if(j%2==0){
					string[j]='+';	
				}else{
					if(hbar[i/2][j/2]==1){string[j]='-';}
					else{string[j]=' ';}
				}		
			}else{
				if(j%2==0){
					if(vbar[i/2][j/2]==1){string[j]='|';}
					else{string[j]=' ';}
				}else{
					string[j]=' ';
				}
				string[2*n]='|';
				
			}
			string[2*n+1]='\n';
			string[2*n+2]='\0';
		}
		
		//파일에 한 행 씩 쓰기
		//fprintf("%s",string);
		fputs(string,fp);
		printf("%s",string);

	}
	for(j=0;j<2*n+1;j++){
		if(j%2==0){
			string[j]='+';
		}else{
			string[j]='-';
		}
	}
	string[2*n+1]='\n';
	string[2*n+2]='\0';
//	fprintf("%s\n",string);
	fputs(string,fp);
	printf("%s\n",string);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("%3d",room[i][j]);
		}
		printf("\n");
	}


	fclose(fp);
	return 0;
}



void merge(int ri, int rj, int r){
	visited[ri][rj]=1;
	room[ri][rj]=r;
	if(ri>0 && rj>0){
		if(hbar[ri][rj]==0){
			if(visited[ri-1][rj]==0){merge(ri-1,rj,r);}//else{return;}
		}
		if(hbar[ri+1][rj]==0){
			if(visited[ri+1][rj]==0){merge(ri+1,rj,r);}//else{return;}
		}
		if(vbar[ri][rj]==0){
			if(visited[ri][rj-1]==0){merge(ri,rj-1,r);}//else{return;}
		}
		if(vbar[ri][rj+1]==0){
			if(visited[ri][rj+1]==0){merge(ri,rj+1,r);}//else{return;}
		}
	}else{
		if(ri==0&&rj!=0){
			if(vbar[ri][rj]==0){
				if(visited[ri][rj-1]==0){merge(ri,rj-1,r);}//else{return;}
			}
			if(vbar[ri][rj+1]==0){
				if(visited[ri][ri+1]==0){merge(ri,rj+1,r);}//else{return;}
			}
			if(hbar[ri+1][rj]==0){
				if(visited[ri+1][rj]==0){merge(ri+1,rj,r);}//else{return;}
			}
		}
		if(ri!=0&&rj==0){
			if(hbar[ri][rj]==0){
				if(visited[ri-1][rj]==0){merge(ri-1,rj,r);}//else{return;}
			}
			if(hbar[ri+1][rj]==0){
				if(visited[ri+1][rj]==0){merge(ri+1,rj,r);}//else{return;}
			}
			if(vbar[ri][rj+1]==0){
				if(visited[ri][rj+1]==0){merge(ri,rj+1,r);}//else{return;}
			}
		}
		if(ri==0&&rj==0){
			if(hbar[ri+1][rj]==0){
				if(visited[ri][rj+1]==0){merge(ri,rj+1,r);}//else{return;}
			}
			if(vbar[ri][rj+1]==0){
				if(visited[ri+1][rj]==0){merge(ri+1,rj,r);}//else{return;}
			}
		}
	}
}

void resetV(int m, int n){
	int i,j;
	for(i=0;i<=m;i++){
		for(j=0;j<=n;j++){
			visited[i][j]=0;
		}
	}
}
