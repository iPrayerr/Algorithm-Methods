/*
	Bucket Sort:
	1. 建立以vector为元素的vector
	2. 将[0,1)范围内的数按第一位映射进每个bucket vector
	3. 对每个bucket排序
	4. comcat directly 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
	srand(time(0));
	
	int n;
	cin >> n;
	
	vector<vector<float> > buckets;
	//set buckets
	for(int i=0;i<10;i++){
		vector<float> bucket;
		buckets.push_back(bucket);
	}
	//drop elements into buckets
	vector<float> a;
	for(int i=0;i<n;i++){
		a.push_back(rand()%1000/(float)1000);
														//生成(0,1)范围内n位小数，则采用rand()%2^n/(float)2^n实现 
		cout << a[i] << " ";
		int temp = a[i]*10;		//decide which bucket to put in
		buckets[temp].push_back(a[i]);
	}
	cout << endl;
	a.clear();
	
	//Sort each bucket
	for(int i=0;i<10;i++){
		stable_sort(buckets[i].begin(),buckets[i].end());
		for(int j=0;j<buckets[i].size();j++){
			a.push_back(buckets[i][j]);
			cout << buckets[i][j] << " ";
		}
	}
	
	return 0;
} 
