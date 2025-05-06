#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define INF 800000 
typedef struct DATA{
	int height[10];
	int dead;
	int sooth;
	int maxh;
	int h;
	int col;
	int row; 
	int sur;
	int loca;
}DATA;

typedef struct RES{
	int x;
	int type;
	int score;
}RES;

DATA data;
float wd=7.899,w_=3.8556,wh=12.5,w_r=3.218,w_c=9.3487,we = -4.2,wt=0;
float wl=0,ws=0;

int dp[20][10] = {0};

int Z_[2][3] = {0,1,1,0,-1,-30};
int S_[2][3] = {0,0,-1,0,1,-30};
int I_[2][4] = {0,0,0,0,0,-30,-30,-30};
int T_[4][3] = {0,0,0,0,-1,-30,0,1,0,0,1,-30};
int O_[1][2] = {0,0};
int J_[4][3] = {0,0,0,0,-2,-30,0,0,1,0,0,-30};
int L_[4][3] = {0,0,0,0,0,-30,0,-1,-1,0,2,-30};

int Z[2][3][3] = {0,0,0,1,1,0,0,1,1,0,1,0,1,1,0,1,0,0};
int S[2][3][3] = {0,0,0,0,1,1,1,1,0,1,0,0,1,1,0,0,1,0};
int T[4][3][3] = {{0,0,0,0,1,0,1,1,1},{1,0,0,1,1,0,1,0,0},{0,0,0,1,1,1,0,1,0},{0,1,0,1,1,0,0,1,0}};
int I[2][4][4] = {{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0}}; 
int O[1][2][2] = {1,1,1,1};
int J[4][3][3] = {{0,0,0,1,0,0,1,1,1},{1,1,0,1,0,0,1,0,0},{0,0,0,1,1,1,0,0,1},{0,1,0,0,1,0,1,1,0}};
int L[4][3][3] = {{0,0,0,0,0,1,1,1,1},{1,0,0,1,0,0,1,1,0},{0,0,0,1,1,1,1,0,0},{1,1,0,0,1,0,0,1,0}};

int z[2] = {-1,0};
int s[2] = {0,-1};
int t[4] = {0,0,-1,-1};
int _i[2] = {0,0};
int o[1] = {0};
int _j[4] = {0,0,-1,0}; 
int l[4] = {0,0,0,-2};

int zmx[2] = {7,8};
int smx[2] = {7,8};
int imx[2] = {6,9};
int omx[1] = {8};
int tmx[4] = {7,8,7,8};
int jmx[4] = {7,8,7,8};
int lmx[4] = {7,8,7,8};

char generate(int term){
	int x;
	if(term<900000){
		x = rand()%7;
	}
	else{
		x = rand()%8;
	}
	switch(x){
		case 0:return 'Z';
		case 1:return 'S';
		case 2:return 'I';
		case 3:return 'O';
		case 4:return 'L';
		case 5:return 'J';
		case 6:return 'T';
		case 7:return 'X';
	}
}
void f_row(int plane[][10]);

void fetch(int plane[][10]){
	int i,j,flag = 0;
	int flag3=0;//算井 
	data.dead = 0;
	data.sooth = 0;
	data.maxh = 0;
	data.h = 0;
	data.col = 0;
	data.row = 0;
	data.sur=0;
	for(i = 0;i<10;i++){
		data.height[i] = 0;
	}
	for(j = 0;j<10;j++){	//由于这里要按列遍历，因此列索引j在外循环 
		flag = 0;
		int flag1 = 0;
		int flag2 = plane[0][j];
		flag3=0;
		int a=0;
		for(i = 0;i<20;i++){
			if(plane[i][j]!=flag2){
				flag2 = plane[i][j];
				data.col++;
				if(flag3==0)flag3=-1,a=0;
				else flag3*=-1,data.sooth+=(a+1)*a/2,a=0;
			}
			if(i==19&&flag3==1&&plane[i][j]==0){
				data.sooth+=(a+2)*(a+1)/2;
				a=0;
			}
			if(plane[i][j] == 1&&flag1 == 0){
				flag1 = 1;
				data.height[j] = 20-i;
			}
			if(plane[i][j] == 1){
				flag = 1;
			}
			if(plane[i][j] == 0 &&flag == 1){
				data.dead++;//改成了一列上连续空洞算一个空洞 
				//flag=0;
			}
			if(flag3==1){
				if(j>0&&j<9){
					if(plane[i][j-1]==1&&plane[i][j+1]==1)a++;
				}
				else if(j==0){
					if(plane[i][j+1]==1)a++;
				}
				else if(j==9){
					if(plane[i][j-1]==1)a++;
				}
			}
		}
	}
	int max = 0;
	for(i = 0;i<10;i++){
		if(i>0&&i<9){
			int a=data.height[i-1]-data.height[i];
			int b=data.height[i+1]-data.height[i];
			if(a>0&&b>0){
				int c = a<b?a:b;
				data.sooth+=(c+1)*c/2;
			}
			data.sur+=abs(data.height[i-1]-data.height[i+1]);
		}
		data.h += pow(data.height[i],2);
		if(data.height[i]>max){
			max = data.height[i];
		}
	}
	if(data.height[0]<data.height[1]){
		int c = data.height[1]-data.height[0];
		data.sooth+=(c+1)*c/2;
	}
	if(data.height[9]<data.height[8]){
		int c = data.height[8]-data.height[9];
		data.sooth+=(c+1)*c/2;
	}
	data.maxh = max;
	f_row(plane);
	return;
}

void f_row(int plane[][10]){
	int i,j;
	for(i = 0;i<20;i++){
		int flag = plane[i][0];
		for(j = 0;j<10;j++){
			if(flag!=plane[i][j]){
				flag = plane[i][j];
				data.row++;
			}
		}
	}
}


void print_dp(){
	int i,j;
	for(i = 0;i<20;i++){
		for(j = 0;j<10;j++){
			printf("%d",dp[i][j]);
		}
		printf("\n");
	}
}

int elimiate(){
	int sum[20] = {0};
	int tmp[20][10] = {0};
	int i,j,k = 0;
	for(i = 0;i<20;i++){
		for(j = 0;j<10;j++){
			sum[i] +=dp[i][j];
		}
	}
	for(i = 19;i>3;i--){
		if(sum[i] == 10){
			int m;
			for(m = 0;m<4;m++){
				if(sum[i-m]!=10){
					break;
				}
				k++;
				sum[i-m] = 0;
			}
		} 
		for(j = 0;j<10;j++){
			tmp[i][j] = dp[i-k][j];
		}
	}
	memmove(dp,tmp,sizeof(tmp));
	switch(k){
		case 0:return 0;
		case 1:return 100;
		case 2:return 300;
		case 3:return 500;
		case 4:return 800;
	}
}

void print_h(){
	int i;
	for(i = 0;i<10;i++){
		printf("%d ",data.height[i]);
	}
	printf("\n");
}

int operate(char block1,int type,int x){
	int n; 
	int i,j;
	int score = 0;
	fetch(dp);
	x++;
	int max = 0;
	switch(block1){
		case 'Z':{
			n = 3;
			int tmp;
			max = 0;
			/*计算落点，max*/
			for(i = 0;i<n;i++){
				if(x+i-1>9){
					break;
				}
				tmp = data.height[x+i-1]+Z_[type][i];
				if(tmp>max){
					max = tmp;
				}
			}
			data.loca = max;
			max = 19-max;
			/*更新dp数组*/
			for(i = n-1;i>=0;i--){
				for(j = 0;j<n;j++){
					if(dp[max+i-(n-1)-z[type]][x+j-1]==0&&x+j-1<10){
						dp[max+i-(n-1)-z[type]][x+j-1] = Z[type][i][j];
					}
				}
			}
			break;
		}
		case 'S':{
			n = 3;		
			int tmp,max = 0;
			/*计算落点，max*/
			for(i = 0;i<n;i++){
				if(x+i-1>9){
					break;
				}
				tmp = data.height[x+i-1]+S_[type][i];
				if(tmp>max){
					max = tmp;
				}
			}
			data.loca = max;
			max = 19-max;
			/*更新dp数组*/
			for(i = n-1;i>=0;i--){
				for(j = 0;j<n;j++){
					if(dp[max+i-(n-1)-s[type]][x+j-1]==0&&x+j-1<10){
						dp[max+i-(n-1)-s[type]][x+j-1] = S[type][i][j];
					}
				}
			}
			break;
		}
		case 'T':{
			n = 3;
			
			int tmp,max = 0;
			/*计算落点，max*/
			for(i = 0;i<n;i++){
				if(x+i-1>9){
					break;
				}
				tmp = data.height[x+i-1]+T_[type][i];
				if(tmp>max){
					max = tmp;
				}
			}
			data.loca = max;
			max = 19-max;
			/*更新dp数组*/
			for(i = n-1;i>=0;i--){
				for(j = 0;j<n;j++){
					if(dp[max+i-(n-1)-t[type]][x+j-1]==0&&x+j-1<10){
						dp[max+i-(n-1)-t[type]][x+j-1] = T[type][i][j];
					}
				}
			}
			break;
		}
		case 'I':{
			n = 4;
			
			int tmp,max = 0;
			/*计算落点，max*/
			for(i = 0;i<n;i++){
				if(x+i-1>9){
					break;
				}
				tmp = data.height[x+i-1]+I_[type][i];/**/
				if(tmp>max){
					max = tmp;
				}
			}
			data.loca = max;
			max = 19-max;
			/*更新dp数组*/
			for(i = n-1;i>=0;i--){
				for(j = 0;j<n;j++){
					if(dp[max+i-(n-1)-_i[type]][x+j-1]==0&&x+j-1<10){
						dp[max+i-(n-1)-_i[type]][x+j-1] = I[type][i][j];/**/
					}
				}
			}
			break;
		}
		case 'O':{
			n = 2;
			
			int tmp,max = 0;
			/*计算落点，max*/
			for(i = 0;i<n;i++){
				if(x+i-1>9){
					break;
				}
				tmp = data.height[x+i-1]+O_[type][i];/**/
				if(tmp>max){
					max = tmp;
				}
			}
			data.loca = max;
			max = 19-max;
			/*更新dp数组*/
			for(i = n-1;i>=0;i--){
				for(j = 0;j<n;j++){
					if(dp[max+i-(n-1)-o[type]][x+j-1]==0&&x+j-1<10){
						dp[max+i-(n-1)-o[type]][x+j-1] = O[type][i][j];/**/
					}
				}
			}
			break;
		}
		case 'J':{
			n = 3;
				
			int tmp,max = 0;
			/*计算落点，max*/
			for(i = 0;i<n;i++){
				if(x+i-1>9){
					break;
				}
				tmp = data.height[x+i-1]+J_[type][i];/**/
				if(tmp>max){
					max = tmp;
				}
			}
			data.loca = max;
			max = 19-max;
			/*更新dp数组*/
			for(i = n-1;i>=0;i--){
				for(j = 0;j<n;j++){
					if(dp[max+i-(n-1)-_j[type]][x+j-1]==0&&x+j-1<10){
						dp[max+i-(n-1)-_j[type]][x+j-1] = J[type][i][j];/**/
					}
				}
			}
			break;
		}
		case 'L':{
			n = 3;
			
			int tmp,max = 0;
			/*计算落点，max*/
			for(i = 0;i<n;i++){
				if(x+i-1>9){
					break;
				}
				tmp = data.height[x+i-1]+L_[type][i];/**/
				if(tmp>max){
					max = tmp;
				}
			}
			data.loca = max;
			max = 19-max;
			/*更新dp数组*/
			for(i = n-1;i>=0;i--){
				for(j = 0;j<n;j++){
					if(dp[max+i-(n-1)-l[type]][x+j-1]==0&&x+j-1<10){
						dp[max+i-(n-1)-l[type]][x+j-1] = L[type][i][j];/**/
					}
				}
			}
			break;
		}
		default:break;
	}
	score+=elimiate();
	return score;
}


RES juece1(char block1){
	RES ans;
	int *mx1,*mx2;
	int n1,m1,n2,m2;
	int tmp2[20][10] = {0};
	//int best[20][10] = {0};
	int i,j;
	memmove(tmp2,dp,sizeof(dp));
	
	int ax1,ax2;
	int at1,at2;
	float bad = 0;
	int ds = 0;
	int maxds = 0;
	float minbad = INF;
	switch(block1){
		case 'Z':{
			n1 = 3;m1 = 2;mx1 = zmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					ds+=operate(block1,at1,ax1);
					fetch(dp);
					bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
					if(minbad>bad){
						minbad = bad;
						ans.type = at1;
						ans.x = ax1;
					}
					memmove(dp,tmp2,sizeof(tmp2));
					ds = 0;
				}
			}
			break;
		}
		case 'S':{
			n1 = 3;m1 = 2;mx1 = smx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					ds+=operate(block1,at1,ax1);
					fetch(dp);
					bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
					if(minbad>bad){
						minbad = bad;
						ans.type = at1;
						ans.x = ax1;
					}
					memmove(dp,tmp2,sizeof(tmp2));
					ds = 0;
				}
			}
			break;
		}
		case 'O':{
			n1 = 2;m1 = 1;mx1 = omx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					ds+=operate(block1,at1,ax1);
					fetch(dp);
					bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
					if(minbad>bad){
						minbad = bad;
						ans.type = at1;
						ans.x = ax1;
					}
					memmove(dp,tmp2,sizeof(tmp2));
					ds = 0;
				}
			}
			break;
		}
		case 'I':{
			n1 = 4;m1 = 2;mx1 = imx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					ds+=operate(block1,at1,ax1);
					fetch(dp);
					bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
					if(minbad>bad){
						minbad = bad;
						ans.type = at1;
						ans.x = ax1;
					}
					memmove(dp,tmp2,sizeof(tmp2));
					ds = 0;
				}
			}
			break;
		}
		case 'T':{
			n1 = 3;m1 = 4;mx1 = tmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					ds+=operate(block1,at1,ax1);
					fetch(dp);
					bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
					if(minbad>bad){
						minbad = bad;
						ans.type = at1;
						ans.x = ax1;
					}
					memmove(dp,tmp2,sizeof(tmp2));
					ds = 0;
				}
			}
			break;
		}
		case 'J':{
			n1 = 3;m1 = 4;mx1 = jmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					ds+=operate(block1,at1,ax1);
					fetch(dp);
					bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
					if(minbad>bad){
						minbad = bad;
						ans.type = at1;
						ans.x = ax1;
					}
					memmove(dp,tmp2,sizeof(tmp2));
					ds = 0;
				}
			}
			break;
		}
		case 'L':{
			n1 = 3;m1 = 4;mx1 = lmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1]-1;ax1++){
					//外循环 转内循环 
					ds+=operate(block1,at1,ax1);
					fetch(dp);
					bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
					if(minbad>bad){
						minbad = bad;
						ans.type = at1;
						ans.x = ax1;
					}
					memmove(dp,tmp2,sizeof(tmp2));
					ds = 0;
				}
			}
			break;
		}
	}
	return ans;
}


RES juece(char block1,char block2){
	RES ans;
	int *mx1,*mx2;
	int n1,m1,n2,m2;
	int tmp2[20][10] = {0};
	int best[20][10] = {0};
	int i,j;
	for(i = 0;i<20;i++){
		for(j = 0;j<10;j++){
			tmp2[i][j] = dp[i][j];
		}
	}
	int ax1,ax2;
	int at1,at2;
	float bad = 0;
	int ds = 0;
	float minbad = INF;
	switch(block1){
		case 'Z':{
			n1 = 3;m1 = 2;mx1 = zmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					switch(block2){
						case 'X':{
							ds+=operate(block1,at1,ax1);
							fetch(dp);
							bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
							if(minbad>bad){
								minbad = bad;
								ans.type = at1;
								ans.x = ax1;
							}
							for(i = 0;i<20;i++){
								for(j = 0;j<10;j++){
									dp[i][j] = tmp2[i][j];
								}
							}
							ds = 0;
							break;
						}
						case 'Z':{
							n2 = 3;m2 = 2;mx2 = zmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'S':{
							n2 = 3;m2 = 2;mx2 = smx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0; 
								}
							}
							break;
						}
						case 'O':{
							n2 = 2;m2 = 1;mx2 = omx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'I':{
							n2 = 4;m2 = 2;mx2 = imx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'T':{
							n2 = 3;m2 = 4;mx2 = tmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 	
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;								
								}
							}
							break;
						}
						case 'J':{
							n2 = 3;m2 = 4;mx2 = jmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 	
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;								
								}
							}
							break;
						}
						case 'L':{
							n2 = 3;m2 = 4;mx2 = lmx;
							for(at2 = 0;at2<m1;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 	
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;								
								}
							}
							break;
						}			
					}
				}
			}
			break;
		}
		case 'S':{
			n1 = 3;m1 = 2;mx1 = smx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					switch(block2){
						case 'X':{
							ds+=operate(block1,at1,ax1);
							fetch(dp);
							bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+ws*data.sur+wt*data.h+wl*data.loca;
							if(minbad>bad){
								minbad = bad;
								ans.type = at1;
								ans.x = ax1;
							}
							memmove(dp,tmp2,sizeof(tmp2));
							ds = 0;
							break;
						}
						case 'Z':{
							n2 = 3;m2 = 2;mx2 = zmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'S':{
							n2 = 3;m2 = 2;mx2 = smx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'O':{
							n2 = 2;m2 = 1;mx2 = omx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'I':{
							n2 = 4;m2 = 2;mx2 = imx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'T':{
							n2 = 3;m2 = 4;mx2 = tmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
						case 'J':{
							n2 = 3;m2 = 4;mx2 = jmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 	
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;								
								}
							}
							break;
						}
						case 'L':{
							n2 = 3;m2 = 4;mx2 = lmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
					} 
				}
			}
			break;
		}
		case 'O':{
			n1 = 2;m1 = 1;mx1 = omx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					switch(block2){
						case 'X':{
							ds+=operate(block1,at1,ax1);
							fetch(dp);
							bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+ws*data.sur+wt*data.h+wl*data.loca;
							if(minbad>bad){
								minbad = bad;
								ans.type = at1;
								ans.x = ax1;
							}
							memmove(dp,tmp2,sizeof(tmp2));
							ds = 0;
							break;
						}
						case 'Z':{
							n2 = 3;m2 = 2;mx2 = zmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'S':{
							n2 = 3;m2 = 2;mx2 = smx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'O':{
							n2 = 2;m2 = 1;mx2 = omx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'I':{
							n2 = 4;m2 = 2;mx2 = imx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									
									ds+=operate(block2,at2,ax2);
									//printf("%d ",ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'T':{
							n2 = 3;m2 = 4;mx2 = tmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
						case 'J':{
							n2 = 3;m2 = 4;mx2 = jmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 	
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;								
								}
							}
							break;
						}
						case 'L':{
							n2 = 3;m2 = 4;mx2 = lmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
					} 
				}
			}
			break;
		}
		case 'I':{
			n1 = 4;m1 = 2;mx1 = imx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					switch(block2){
						case 'X':{
							ds+=operate(block1,at1,ax1);
								fetch(dp);
								bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+ws*data.sur+wt*data.h+wl*data.loca;
							if(minbad>bad){
								minbad = bad;
								ans.type = at1;
								ans.x = ax1;
							}
							memmove(dp,tmp2,sizeof(tmp2));
							ds = 0;
							break;
						}
						case 'Z':{
							n2 = 3;m2 = 2;mx2 = zmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'S':{
							n2 = 3;m2 = 2;mx2 = smx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'O':{
							n2 = 2;m2 = 1;mx2 = omx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'I':{
							n2 = 4;m2 = 2;mx2 = imx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'T':{
							n2 = 3;m2 = 4;mx2 = tmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
						case 'J':{
							n2 = 3;m2 = 4;mx2 = jmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
						case 'L':{
							n2 = 3;m2 = 4;mx2 = lmx;
							for(at2 = 0;at2<m1;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0; 									
								}
							}
							break;
						}
					} 	
				}
			}
			break;
		}
		case 'T':{
			n1 = 3;m1 = 4;mx1 = tmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					switch(block2){
						case 'X':{
							ds+=operate(block1,at1,ax1);
							
								fetch(dp);
								bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+ws*data.sur+wt*data.h+wl*data.loca;
								if(minbad>bad){
									minbad = bad;
									ans.type = at1;
									ans.x = ax1;
								}
							
							memmove(dp,tmp2,sizeof(tmp2));
							ds = 0;
							break;
						}
						case 'Z':{
							n2 = 3;m2 = 2;mx2 = zmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'S':{
							n2 = 3;m2 = 2;mx2 = smx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0; 
								}
							}
							break;
						}
						case 'O':{
							n2 = 2;m2 = 1;mx2 = omx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'I':{
							n2 = 4;m2 = 2;mx2 = imx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0; 
								}
							}
							break;
						}
						case 'T':{
							n2 = 3;m2 = 4;mx2 = tmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 	
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;								
								}
							}
							break;
						}
						case 'J':{
							n2 = 3;m2 = 4;mx2 = jmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0; 									
								}
							}
							break;
						}
						case 'L':{
							n2 = 3;m2 = 4;mx2 = lmx;
							for(at2 = 0;at2<m1;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
					} 
				}
			}
			break;
		}
		case 'J':{
			n1 = 3;m1 = 4;mx1 = jmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					switch(block2){
						case 'X':{
							ds+=operate(block1,at1,ax1);
							fetch(dp);
							bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+ws*data.sur+wt*data.h+wl*data.loca;
							if(minbad>bad){
								minbad = bad;
								ans.type = at1;
								ans.x = ax1;
							}
							memmove(dp,tmp2,sizeof(tmp2));
							ds = 0;
							break;
						}
						case 'Z':{
							n2 = 3;m2 = 2;mx2 = zmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'S':{
							n2 = 3;m2 = 2;mx2 = smx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'O':{
							n2 = 2;m2 = 1;mx2 = omx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'I':{
							n2 = 4;m2 = 2;mx2 = imx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0; 
								}
							}
							break;
						}
						case 'T':{
							n2 = 3;m2 = 4;mx2 = tmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0; 									
								}
							}
							break;
						}
						case 'J':{
							n2 = 3;m2 = 4;mx2 = jmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
						case 'L':{
							n2 = 3;m2 = 4;mx2 = lmx;
							for(at2 = 0;at2<m1;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
					} 	
				}
			}
			break;
		}
		case 'L':{
			n1 = 3;m1 = 4;mx1 = lmx;
			for(at1 = 0;at1<m1;at1++){
				for(ax1 = 0;ax1<=mx1[at1];ax1++){
					//外循环 转内循环 
					switch(block2){
						
						case 'Z':{
							n2 = 3;m2 = 2;mx2 = zmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'S':{
							n2 = 3;m2 = 2;mx2 = smx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'O':{
							n2 = 2;m2 = 1;mx2 = omx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'I':{
							n2 = 4;m2 = 2;mx2 = imx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;
								}
							}
							break;
						}
						case 'T':{
							n2 = 3;m2 = 4;mx2 = tmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
						case 'J':{
							n2 = 3;m2 = 4;mx2 = jmx;
							for(at2 = 0;at2<m2;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 	
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;								
								}
							}
							break;
						}
						case 'L':{
							n2 = 3;m2 = 4;mx2 = lmx;
							for(at2 = 0;at2<m1;at2++){
								for(ax2 = 0;ax2<=mx2[at2];ax2++){
									//开始评分 
									ds+=operate(block1,at1,ax1);
									ds+=operate(block2,at2,ax2);
									fetch(dp);
									bad = wd*data.dead+w_*data.sooth+wh*data.maxh+w_r*data.row+w_c*data.col+we*ds+ws*data.sur+wt*data.h+wl*data.loca;
									if(minbad>bad){
										minbad = bad;
										ans.type = at1;
										ans.x = ax1;
									}
									//评分结束 
									memmove(dp,tmp2,sizeof(tmp2));
									ds = 0;									
								}
							}
							break;
						}
					} 	
				}
			}
			break;
		}
	}
	return ans;
}
int main(){
	int i,j,n,res = 0;
	char block1 = ' ',block2 = ' ';
	int score = 0; 
	int step = 1;
	char prev; 
	for(i = 0;i<20;i++){
		for(j = 0;j<10;j++){
			dp[i][j] = 0;
		}
	}
	prev = generate(step);
	int a1=0,b1 = 0;
	fetch(dp);
	scanf("%c",&block1);
	while(data.maxh<15){
		scanf("%c",&block2);
		getchar();
		//printf("%c %c",block1,block2);
		fetch(dp);
		RES ans;
		if(data.maxh>=7&&step<3500){
			wd=6.899,w_=3.3856,wh=12.6,w_r = 3.217,w_c = 9.3489,we = -5.15,ws=0,wt=0.0652,wl=2.37;
			if(data.row>22)w_r+=1.24;
			if(data.col>22)w_c+=2.91;
			if(data.col>25)w_c+=0.32;
			if(data.row>25)w_r+=0.16;
			if(data.maxh>10)wh+=4.88;
			if(data.maxh>12)wh+=1.01;
			if(data.sooth>17)w_+=1.107;
			if(data.dead>13)wd+=0.203;
			ans = juece(block1,block2);
			a1++;
		}
		else{
			wd=6.899,w_=3.3856,wh=12.6,w_r = 3.217,w_c = 9.3489,we = -5.15,ws=0,wt=0.0652,wl=2.37;
			ans = juece1(block1);
			b1++;
		}
		ans.score = operate(block1,ans.type,ans.x);
		score+=ans.score;
		fetch(dp);
		printf("%d %d\n",ans.type*90,ans.x);
		printf("%d\n",score);
		print_dp();
		step++;
		fflush(stdout);
		block1=block2;
		if(block1=='X')break;
	}
}

