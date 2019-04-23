/*
	最大子数组和：(greedy algorithm)
	1. 建立辅助数组b以存储b[i]之前的最大子数组和
	2. 设置整型量stat以存储最大子数组起始位置,sum记录目前的最大和 
	3. 原始数组为a[n],b[0] = a[0]
	4. 若b[i-1]>0, b[i] = b[i-1]+a[i]；否则b[i] = a[i],摒弃之前结果 
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
