/*
	counting sort:
	need: an unsorted array A, a counter array C & a space for saving sourted array B
	1. counting the num of each element in A and record in C's corresponding position
	2. let C[i+1] += C[i]
	3. scan A in reverse, add each element to B's position saved in C, then minus 1 in the corresponding pos of C
	4. repeat step 3 until A is all sorted in B
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void Counting_Init(int* A,int* C,int n,int l);					//init counter
void Counting_Sort(int* A,int* B,int* C,int n,int l);		//counting sort

int main() {
	srand(time(0));
	
	int n;
	cin >> n;
	
	int a[n],b[n];
	int largest = 0;								//record the largest element
	for(int i=0;i<n;i++){
		a[i] = rand()%10;
		cout << a[i] << " ";
		if(a[i]>largest)	largest = a[i];
	} cout << endl;
	
	int c[largest+1];
	for(int i=0;i<largest+1;i++)	c[i] = 0; 		//£¡£¡£¡ 
	Counting_Sort(a,b,c,n,largest+1);
	
	for(int i=0;i<n;i++)
		cout << b[i] << " ";
	return 0;
}

void Counting_Sort(int* A,int* B,int* C,int n,int l) {
	Counting_Init(A,C,n,l);					
	
	for(int i=n-1;i>=0;i--){
		B[C[A[i]]-1] = A[i];											//continuous mapping(minus 1 when mapping to B's corresponding position)
		C[A[i]]--;
	}
}

void Counting_Init(int* A,int* C,int n,int l) {
	for(int i=0;i<n;i++)	C[A[i]]++;									//counting
	for(int i=1;i<l;i++)	C[i] += C[i-1];								//accumulate
}
