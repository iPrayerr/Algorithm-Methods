/*
	quickselect: to find the kth largest element
	p: start pos; r: end pos; A: array
	1.  partition(A,p,r)
	2.	if i = pivot, return pivot;
	3.	else if i<pivot, return quickselect(A,p,pivot-1,i)
	4.	else return quickselect(A,q+1,r,i)
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int QuickSelect(int* A,int p,int r,int i);
int Partition(int* A,int p,int r);

int main() {
	srand(time(0));
	
	int n;
	cout << "Number of elements: ";
	cin >> n;
	
	int a[n];
	for(int i=0;i<n;i++){
		a[i] = rand() % 500;
		cout << a[i] << " ";
	} cout << endl;
	
	cout << "The position you want to find: ";
	int i;
	cin >> i;
	
	cout << QuickSelect(a,0,n-1,i);
	return 0;
}

int QuickSelect(int* A,int p,int r,int i) {
	if(p==r)	return A[p];		//only one element
	else {
		int pivot = Partition(A,p,r);	//return the position of pivot after partition
		int k = pivot-p+1;				//将数组下标转换为其在该数组中是第k大元素 
		if(i==k)	return A[pivot];
		else if(i<k)	QuickSelect(A,p,pivot-1,i);
		else	QuickSelect(A,pivot+1,r,i);
	}
}

int Partition(int* A,int p,int r) {
	//select random pivot
	int ran = p + (rand() % (r-p+1));
	int temp;
	temp = A[ran];
	A[ran] = A[r];
	A[r] = temp;
	
	int i = p-1;
	int j;
	int pivot = A[r];
	for(j=p;j<r;j++){
		if(A[j]<=pivot){
			i++;
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	i++;
	temp = A[i];
	A[i] = A[r];
	A[r] = temp;
	
	return i;
}
