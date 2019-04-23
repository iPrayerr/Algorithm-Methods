/*
	所有最长公共子序列：对于两个子序列a[m], b[n]，扫描每一个字符
	1. 如果a[i] = b[j]，则c[i,j] = c[i-1,j-1] + 1
	2. 否则，c[i,j] = max{c[i-1,j],c[i,j-1]}	=> 说明有一个字符是用不上的
	3. c[i,j]为一个二维矩阵，所有c[0,:]和c[:,0]位置都置0，方便起始从c[1,1]开始按公式计算
	4. 填完后，二维矩阵的含义就是在a[i]和b[j]范围内的LCS长度，故c[m,n]一定最大
	5. 通过backtrack, 输出最长公共子序列函数 
*/ 

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

set<string> reses;		//save conditions 
void backtrack(string a,string b,string res,int** c,int m,int n,int i,int j);

int main(){
	string a;	cin >> a;
	string b;	cin >> b;
	
	int m = a.length()+1;	//length of string a
	int n = b.length()+1;	//length of string b
	int c[m][n]; 
	for(int i=0;i<m;i++)	c[i][0] = 0;
	for(int j=0;j<n;j++)	c[0][j] = 0;
	
	//each part's LCS
	for(int i=1;i<m;i++)
		for(int j=1;j<n;j++){
			if(a[i-1]==b[j-1])	c[i][j] = c[i-1][j-1]+1;
			else{
				if(c[i-1][j]>c[i][j-1])	c[i][j] = c[i-1][j];
				else	c[i][j] = c[i][j-1];
			}
		}
	
	string res;					//save each condition
	backtrack(a,b,res,(int**)c,m,n,m-1,n-1);
	for(set<string>::iterator ite=reses.begin();ite!=reses.end();ite++)
		cout << *ite << endl;
	return 0;
}

void backtrack(string a,string b,string res,int** c,int m,int n,int i,int j){
	while(i>0&&j>0){
		if(a[i-1]==b[j-1]){
			res.push_back(a[i-1]);
			i--;j--;
		}
		else{
			if((*((int*)c+n*(i-1)+j))>(*((int*)c+n*i+j-1)))				i--;//c[i-1][j]>c[i][j-1]
			else if((*((int*)c+n*(i-1)+j))<(*((int*)c+n*i+j-1)))		j--;//c[i-1][j]<c[i][j-1]
			else{
				backtrack(a,b,res,c,m,n,i-1,j);
				backtrack(a,b,res,c,m,n,i,j-1);
				return;
			}
		}
	}
	reverse(res.begin(),res.end());
	reses.insert(res);
}

/*
	notes:
	1. 这里为多情况分支问题，所以需要把每一种情况先记录下来，再输出，否则对于情况的分岔口，它们不能被输出多次
	2. 不同情况的分支结果可能相同，因此需要一种可去重的数据结构存储各个结果，这里用到了set（基于树的结构）
	3. 任何类型的数据（包括int, char, string）都分为传值传递、引用传递和指针传递！ 
		 - 传值传递不会改变原内存空间中的数值，因此适于多情况分支问题
		 	 - 相当于将母函数中该值的情况拷贝到递归函数中，分情况处理后保存，不会影响母函数中的值
		 - 引用和指针传递都会改变原内存空间中的数值
		 	 - 引用被创建的同时必须被初始化（指针则可以在任何时候被初始化）。 
			 - 引用传递不能有NULL引用，引用必须与合法的存储单元关联（指针则可以是NULL）。 
			 - 一旦引用被初始化，就不能改变引用的关系（指针则可以随时改变所指的对象）。  
*/
