/*
	流水线调度问题
	问题背景：
		两条并行的流水线1和2
		每条流水线有n个作业站（Si,1, Si,2, … Si,n）, i = 1, 2
		对于j∈[1,n], S1,j 和 S2,j 工作内容相同，但工作时间 ai,j (i = 1,2)或许存在差异
		对于i∈{1, 2}, j∈[1,n-1], 离开流水线i的第j个工作站（跨流水线转移时存在此时间）耗时ti,j
		进入流水线i的时间为ei, 退出流水线i的时间为xi
		求整个作业完成的最短时间
	Ps: 算法导论的算法有误
		如果按照各个初始化节点均算上工作登陆时间的话，那么动态分析中默认计算了每个登录时间 
		然而实际上是么？实际上有一个节点压根不存在登录时间，因为工作永远只从一条流水线开始，另一条不登陆 
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int* Minit(int n,int spos,int **S,int *e,int* x,int **t,int **l);

int main(){
	srand(time(0));
	
	int n;
	cin >> n;
	
	int S[2][n];		//n is the number of stations
	int e[2],x[2];		//enter || exit time
	int t[2][n-1];		//transfer time
	int li[2][n-1];		//route while enter point is line1
	int lii[2][n-1]; 	//route while enter point is line2
	
	//init enter||exit time
	e[0] = 1+rand()%10;
	e[1] = 1+rand()%10;
	x[0] = 1+rand()%10;
	x[1] = 1+rand()%10;
	
	for(int i=0;i<n;i++)
		S[0][i] = 1+rand()%10;		//work time
	for(int i=0;i<n;i++)
		S[1][i] = 1+rand()%10;		//work time
	for(int i=0;i<n-1;i++){
		t[0][i] = 1+rand()%10; 		//transfer time
		t[1][i] = 1+rand()%10;
	}
	
	cout << "Line1 enter time: " << e[0] << endl << "Line1 work time: ";
	for(int i=0;i<n;i++)
		cout << S[0][i] << " ";
	cout << endl << "Line1 transfer time: ";
	for(int i=0;i<n-1;i++)
		cout << t[0][i] << " ";
	cout << endl << "Line1 exit time: " << x[0] << endl;
	
	cout << endl << "Line2 enter time: " << e[1] << endl << "Line2 work time: ";
	for(int i=0;i<n;i++)
		cout << S[1][i] << " ";
	cout << endl << "Line2 transfer time: ";
	for(int i=0;i<n-1;i++)
		cout << t[1][i] << " ";
	cout << endl << "Line2 exit time: " << x[1] << endl << endl;
	
	//seperately land on line 1&2
	int spos;
	spos = 0;	int* res1 = Minit(n,spos,(int**)S,e,x,(int**)t,(int**)li);
	spos = 1;	int* res2 = Minit(n,spos,(int**)S,e,x,(int**)t,(int**)lii);
	
	//compare which time is smaller
	int sht,finaline;		//shortest time&final line
	if(res1[0]<res2[0])		{ sht = res1[0];	finaline = res1[1]; spos = 0; }			//spos is to record which line corresponded
	else	{ sht = res2[0];	finaline = res2[1]; spos = 1; }
	cout << "The shortest time is: " << sht << "," << endl << "which follows the reverse route: " << finaline+1 << " <- ";
	if(!spos){
		for(int i=n-2;i>=0;i--){
			if(!i)	cout << *((int*)li+(n-1)*finaline+i)+1;
			else	cout << *((int*)li+(n-1)*finaline+i)+1 << " <- ";//li[finaline][i]
			finaline = *((int*)li+(n-1)*finaline+i);//li[finaline][i]
		}
	} else {
		for(int i=n-2;i>=0;i--){
			if(!i)	cout << *((int*)lii+(n-1)*finaline+i)+1;
			else	cout << *((int*)lii+(n-1)*finaline+i)+1 << " <- ";//lii[finaline][i]
			finaline = *((int*)lii+(n-1)*finaline+i);//lii[finaline][i]
		}
	}
	return 0;
}

int* Minit(int n,int spos,int **S,int *e,int* x,int **t,int **l){
	//init enter minitime
	int s[2][n];
	s[spos][0] = e[spos]+*((int*)S+n*spos);		//S[spos][0], standing for the line the work'll land on
	s[1-spos][0] = -1;							//another line without step 1, pos's time = -1, semaphore
	
	for(int i=1;i<n;i++){
		//line1 plus compare
		int min11,min12;
		if(s[0][i-1]==-1)		min11 = 1000000;				//infinite, so another value must be smaller
		else	min11 = s[0][i-1];					
		if(s[1][i-1]==-1)		min12 = 1000000;
		else	min12 = s[1][i-1]+*((int*)t+n+i-2);				//s[1][i-1]+t[1][i-1]
		if(min11<=min12) {
			s[0][i] = *((int*)S+i)+min11;						//S[0][i]
			*((int*)l+i-1) = 0;									//l[0][i-1]
		} else {
			s[0][i] = *((int*)S+i)+min12;						//S[0][i]
			*((int*)l+i-1) = 1;		
		}
		//line2 plus compare
		int min21,min22;
		if(s[1][i-1]==-1)		min22 = 1000000;
		else	min22 = s[1][i-1];
		if(s[0][i-1]==-1)		min21 = 1000000;						//infinite, so another value must be smaller
		else	min21 = s[0][i-1]+*((int*)t+i-1);				//s[0][i-1]+t[0][i-1]
		if(min21<=min22) {
			s[1][i] = *((int*)S+n+i)+min21;						//S[1][i]
			*((int*)l+n+i-2) = 0;								//l[1][i-1]
		} else {
			s[1][i] = *((int*)S+n+i)+min22;						//S[1][i]
			*((int*)l+n+i-2) = 1;
		}

	}
	//final out
	int o1 = *((int*)s+n-1)+x[0];	//s[0][n-1]+x[0]
	int o2 = *((int*)s+2*n-1)+x[1];	//s[1][n-1]+x[1]
	int o,fl;	//mini & final line
	if(o1<=o2){ o = o1;	fl = 0; }
	else	{ o = o2;	fl = 1; }
	
	//return output&final line
	int* info = new int[2];		info[0] = o;	info[1] = fl;
	return info;
}
//Be patient! Test codes with the wrong data patiently! Step by step!
