/*
	The Maximum-Subarray Problem
	1. divide
	2. for left part & right part, keep on division
	3. for the middle cross element, use crossing_subarray algorithm
	4. compare step 2&3 and choose the larger one
	note: only continus subarray is available
*/ 

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int* submax(int *a, int low, int high);
int* croarr(int *a, int low, int mid, int high);

int main(){
	srand(time(0));
	
	int n;
	cin >> n;
	
	int a[n];
	for(int i=0;i<n;i++){
		a[i] = (rand()%500)-100;
		cout << a[i] << " ";
	} cout << endl;
	
	int* res = submax(a,0,n-1);
	cout << res[0] << endl;
	for(int i=res[1];i<=res[2];i++)
		cout << a[i] << " ";
		
	return 0;
}

int* submax(int *a, int low, int high){
	if(low==high){
		int* res0 = new int[3];
		res0[0] = a[low];
		res0[1] = low;
		res0[2] = high;
		return res0;
	}
	else{
		int mid = (low + high) * 0.5;				//crossing point
		int* res1 = submax(a,low,mid);				//inside max in left
		int* res2 = submax(a,mid+1,high);			//inside max in right
		int* res3 = croarr(a,low,mid,high);			//crossing max
		
		if(res1[0]>res2[0]&&res1[0]>res3[0])		return res1;
		else if(res2[0]>res1[0]&&res2[0]>res3[0])	return res2;
		return res3;
	}
}
int* croarr(int *a, int low, int mid, int high){
	int suml = -1000000;
	int count = 0;
	int left = mid;							//lower bound
	for(int i=mid;i>=low;i--){				//check left's max
		count += a[i];
		if(count>suml){
			suml = count;
			left = i;
		}
	}
	
	int sumr = -1000000;
	count = 0;
	int right = mid+1;						//upper bound
	for(int i=mid+1;i<=high;i++){			//check left's max
		count += a[i];
		if(count>sumr){
			sumr = count;
			right = i;
		}
	}
	
	int* res3 = new int[3];
	res3[0] = suml + sumr;
	res3[1] = left;	res3[2] = right;
	return res3;
}
