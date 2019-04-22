/*
	矩阵链乘法：
	给定n个矩阵维度值（b(i-1)=a(i)）,寻找相乘代价最小的矩阵结合顺序，此时对应的矩阵计算有n-1个 
	基本思想：三角矩阵，自底而上的动态规划（减少很多重复的recursive） 
	1. 初始化m[i,i]
	2. 计算m[i,j] = m[i,k] + m[k+1,j] + p(i-1)p(k)p(j), k∈[i,j),自底而上,i和j为矩阵编号，注意和维度编号区分开 
	3. 对于每层得到的最优解，记录最优位置和最优结果
	4. 输出最优矩阵链乘法序列与最优值 
	注：矩阵编号方便起见，设定一个n*n的矩阵后，从1开始给矩阵编号 
*/
#include <iostream>
//#include <stdlib.h>
//#include <time.h>
#include <map>

using namespace std;

int min = 1000000;//最小代价值，不断比较以淘汰之

int MiniChain(int** m,int n,int* p,int** s);//返回k的序列，并设置代价最小值
void PrintOrder(int** s,map<int, char> &mas,int n,int i,int j);

int main(){
	//srand(time(0));
	
	int n;
	cin >> n;
	
	int p[n];
	/*for(int i=0;i<n;i++){
		p[i] = 1 + rand()%9;
		cout << p[i] << " "; 
	}cout << endl;*/	//生成随机测试数据 
	for(int i=0;i<n;i++)	cin >> p[i]; 
	
	//show which matrix it is
	map<int, char> matrixes;
	char c = 'a';
	for(int i=1;i<n;i++,c++)
		matrixes[i] = c;
		
	int m[n][n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			m[i][j] = 0;		//min cost
	
	int s[n][n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			s[i][j] = 100000;		//seperate point
	
	cout << "Min cost: " << MiniChain((int**)m,n,p,(int**)s) << endl;
	cout << "Which obeys: ";
	PrintOrder((int**)s,matrixes,n,1,n-1);
	
	return 0;
}

int MiniChain(int** m,int n,int* p,int** s){
	int temp = 0;
	int min = 100000;
	int num_matrix = n-1; 
	
	//i. initialize each matric's dimension's cost, done before
	
	//ii. calculate each pair of matrixes
	for(int j=2;j<n;j++){
		for(int i=1;i+j-1<n;i++){
			for(int k=i;k<i+j-1;k++){
				temp = *((int*)m+n*i+k)+*((int*)m+n*(k+1)+i+j-1)+p[i-1]*p[k]*p[i+j-1];//temp = m[i][k]+m[k+1][i+j-1]+p[i-1]*p[k]*p[i+j-1];
				if(temp<=min){
					min = temp;
					*((int*)s+(n+1)*i+j-1) = k;//s[i][i+j-1]
				}
			}
		*((int*)m+(n+1)*i+j-1) = min;//m[i][i+j-1]
		min = 100000;
		}
	}
	
	return *((int*)m+n+num_matrix);//m[1][num_matrix]
}

void PrintOrder(int** s,map<int, char> &mas,int n,int i,int j){
	if(i==j)	cout << mas[i];
	else{
		cout << "(";
		PrintOrder(s,mas,n,i,*((int*)s+n*i+j));//s[i][j]
		cout << "*";
		PrintOrder(s,mas,n,*((int*)s+n*i+j)+1,j);//s[i][j]
		cout << ")";
	}
}
