/*
	求最长公共子串： 
	1. 把两个字符串分别以行和列组成一个二维矩阵c，表征各自第i,j个元素之前最大公共子串的长度，全都初始化为0。
	2. 设定初始化子串长度max_length = 0 
	3. 比较二维矩阵中每个点对应行列字符中否相等，相等的话c[i,j]=c[i-1,j-1]+1，否则c[i,j]不变。
	4. 若c[i,j]>max_length，则以c[i,j]替换max_length, 并记录此时的子串末尾位置i（可能有多个i同时满足max_length, 查找过程中可能i会出现重复，故用set结构存储）
	5. 利用substr(stat,length)函数输出子串，其中stat = i-max_length 
*/ 

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main(){
	string a;	cin >> a;
	string b;	cin >> b;
	
	//始终以最长的作为寻子串标准 
	if(a.length()<b.length()){
		string temp = a;
		a = b;
		b = temp;
	}
	int m = a.length()+1;	//length of string a
	int n = b.length()+1;	//length of string b
	int l[m][n];			//长度矩阵 
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			l[i][j] = 0; 
	
	//each part's LCS
	int max_length = 0;
	set<int> stat;		//max对应的i位置集合 
	for(int i=1;i<m;i++){
		for(int j=1;j<n;j++){
			if(a[i-1]==b[j-1]){
				l[i][j] = l[i-1][j-1]+1;
				if(l[i][j]>max_length){
					max_length = l[i][j];
					stat.clear();		//swap()释放内存，clear()仅清除数据 
					stat.insert(i-max_length);
				}//记录最大长度对应位置
				else if(l[i][j]==max_length)	stat.insert(i-max_length);
			}
		}
	}
	for(set<int>::iterator ite=stat.begin();ite!=stat.end();ite++)
		cout << a.substr((*ite),max_length) << endl;
	return 0;
}
