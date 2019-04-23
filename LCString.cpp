/*
	��������Ӵ��� 
	1. �������ַ����ֱ����к������һ����ά����c���������Ե�i,j��Ԫ��֮ǰ��󹫹��Ӵ��ĳ��ȣ�ȫ����ʼ��Ϊ0��
	2. �趨��ʼ���Ӵ�����max_length = 0 
	3. �Ƚ϶�ά������ÿ�����Ӧ�����ַ��з���ȣ���ȵĻ�c[i,j]=c[i-1,j-1]+1������c[i,j]���䡣
	4. ��c[i,j]>max_length������c[i,j]�滻max_length, ����¼��ʱ���Ӵ�ĩβλ��i�������ж��iͬʱ����max_length, ���ҹ����п���i������ظ�������set�ṹ�洢��
	5. ����substr(stat,length)��������Ӵ�������stat = i-max_length 
*/ 

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main(){
	string a;	cin >> a;
	string b;	cin >> b;
	
	//ʼ���������ΪѰ�Ӵ���׼ 
	if(a.length()<b.length()){
		string temp = a;
		a = b;
		b = temp;
	}
	int m = a.length()+1;	//length of string a
	int n = b.length()+1;	//length of string b
	int l[m][n];			//���Ⱦ��� 
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			l[i][j] = 0; 
	
	//each part's LCS
	int max_length = 0;
	set<int> stat;		//max��Ӧ��iλ�ü��� 
	for(int i=1;i<m;i++){
		for(int j=1;j<n;j++){
			if(a[i-1]==b[j-1]){
				l[i][j] = l[i-1][j-1]+1;
				if(l[i][j]>max_length){
					max_length = l[i][j];
					stat.clear();		//swap()�ͷ��ڴ棬clear()��������� 
					stat.insert(i-max_length);
				}//��¼��󳤶ȶ�Ӧλ��
				else if(l[i][j]==max_length)	stat.insert(i-max_length);
			}
		}
	}
	for(set<int>::iterator ite=stat.begin();ite!=stat.end();ite++)
		cout << a.substr((*ite),max_length) << endl;
	return 0;
}
