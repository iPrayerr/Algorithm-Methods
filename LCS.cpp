/*
	��������������У���������������a[m], b[n]��ɨ��ÿһ���ַ�
	1. ���a[i] = b[j]����c[i,j] = c[i-1,j-1] + 1
	2. ����c[i,j] = max{c[i-1,j],c[i,j-1]}	=> ˵����һ���ַ����ò��ϵ�
	3. c[i,j]Ϊһ����ά��������c[0,:]��c[:,0]λ�ö���0��������ʼ��c[1,1]��ʼ����ʽ����
	4. ����󣬶�ά����ĺ��������a[i]��b[j]��Χ�ڵ�LCS���ȣ���c[m,n]һ�����
	5. ͨ��backtrack, �������������к��� 
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
	1. ����Ϊ�������֧���⣬������Ҫ��ÿһ������ȼ�¼������������������������ķֲ�ڣ����ǲ��ܱ�������
	2. ��ͬ����ķ�֧���������ͬ�������Ҫһ�ֿ�ȥ�ص����ݽṹ�洢��������������õ���set���������Ľṹ��
	3. �κ����͵����ݣ�����int, char, string������Ϊ��ֵ���ݡ����ô��ݺ�ָ�봫�ݣ� 
		 - ��ֵ���ݲ���ı�ԭ�ڴ�ռ��е���ֵ��������ڶ������֧����
		 	 - �൱�ڽ�ĸ�����и�ֵ������������ݹ麯���У����������󱣴棬����Ӱ��ĸ�����е�ֵ
		 - ���ú�ָ�봫�ݶ���ı�ԭ�ڴ�ռ��е���ֵ
		 	 - ���ñ�������ͬʱ���뱻��ʼ����ָ����������κ�ʱ�򱻳�ʼ������ 
			 - ���ô��ݲ�����NULL���ã����ñ�����Ϸ��Ĵ洢��Ԫ������ָ���������NULL���� 
			 - һ�����ñ���ʼ�����Ͳ��ܸı����õĹ�ϵ��ָ���������ʱ�ı���ָ�Ķ��󣩡�  
*/
