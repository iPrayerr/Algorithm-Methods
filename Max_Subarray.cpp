/*
	���������ͣ�(greedy algorithm)
	1. ������������b�Դ洢b[i]֮ǰ������������
	2. ����������stat�Դ洢�����������ʼλ��,sum��¼Ŀǰ������ 
	3. ԭʼ����Ϊa[n],b[0] = a[0]
	4. ��b[i-1]>0, b[i] = b[i-1]+a[i]������b[i] = a[i],����֮ǰ��� 
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
	srand(time(0));
	
	int n;
	cin >> n;
	
	int a[n];
	/*for(int i=0;i<n;i++){
		a[i] = -9 + rand()%29;
		cout << a[i] << " ";
	}cout << endl;*/
	for(int i=0;i<n;i++)
		cin >> a[i];
	
	int b[n];	b[0] = a[0];
	int stat = 0;
	int end = 0;
	int sum = 0; 
	for(int i=1;i<n;i++){
		if(b[i-1]>0)	b[i] = b[i-1]+a[i];
		else{
			b[i] = a[i];
			stat = i;
		}
		if(b[i]>sum){
			sum = b[i];
			end = i;
		}
	}
	
	cout << "Max: " << sum << endl;
	cout << "Array: ";
	for(int i=stat;i<=end;i++)
		cout << a[i] << " ";
	return 0;
}
