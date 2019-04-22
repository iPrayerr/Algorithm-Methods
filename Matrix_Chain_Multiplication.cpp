/*
	�������˷���
	����n������ά��ֵ��b(i-1)=a(i)��,Ѱ����˴�����С�ľ�����˳�򣬴�ʱ��Ӧ�ľ��������n-1�� 
	����˼�룺���Ǿ����Ե׶��ϵĶ�̬�滮�����ٺܶ��ظ���recursive�� 
	1. ��ʼ��m[i,i]
	2. ����m[i,j] = m[i,k] + m[k+1,j] + p(i-1)p(k)p(j), k��[i,j),�Ե׶���,i��jΪ�����ţ�ע���ά�ȱ�����ֿ� 
	3. ����ÿ��õ������Ž⣬��¼����λ�ú����Ž��
	4. ������ž������˷�����������ֵ 
	ע�������ŷ���������趨һ��n*n�ľ���󣬴�1��ʼ�������� 
*/
#include <iostream>
//#include <stdlib.h>
//#include <time.h>
#include <map>

using namespace std;

int min = 1000000;//��С����ֵ�����ϱȽ�����̭֮

int MiniChain(int** m,int n,int* p,int** s);//����k�����У������ô�����Сֵ
void PrintOrder(int** s,map<int, char> &mas,int n,int i,int j);

int main(){
	//srand(time(0));
	
	int n;
	cin >> n;
	
	int p[n];
	/*for(int i=0;i<n;i++){
		p[i] = 1 + rand()%9;
		cout << p[i] << " "; 
	}cout << endl;*/	//��������������� 
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
