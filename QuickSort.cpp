/*
	QuickSort:
	1. select a pivot
	2. add two pointers(i,j), which j is in front of i
	3. a[j]<=pivot, i +=1, exchange a[i] <-> a[j] 
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int *a;

void QuickSort(int n);
void Partition(int pos[]);

int main(){
	srand(time(0));
	
	int n;
	cin >> n;
	
	a = new int[n];
	for(int i=0;i<n;i++){
		a[i] = rand()%500;
		cout << a[i] << " "; 
	}
	cout << endl;
	
	QuickSort(n);
	
	for(int i=0;i<n;i++)
		cout << a[i] << " ";
	return 0;
}

void QuickSort(int n){
	int pos[2];
	pos[0] = 0;	pos[1] = n-1;					//p和r 

	Partition(pos);
}
void Partition(int pos[]){						//如果要用randomized partition, 则也需要将随机位置的pivot换到队尾，然后仍然沿用本算法
	//randomly select pivot
	int ran = pos[0]+(rand()%(pos[1]-pos[0]+1));
	int temp = a[ran];
	a[ran] = a[pos[1]];
	a[pos[1]] = temp;
	
	int pivot = a[pos[1]];
	int i = pos[0]-1;
	for(int j=pos[0];j<pos[1];j++){
		if(a[j]<=pivot){
			i++;
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	i++; 
	temp = a[pos[1]];
	a[pos[1]] = a[i];
	a[i] = temp;
	
	int p[2],q[2];
	p[0] = pos[0];		//p
	p[1] = i-1;
	if(p[0]<p[1]){
		Partition(p);
	}
	q[0] = i+1;
	q[1] = pos[1];		//r	
	if(q[0]<q[1]){
		Partition(q);
	}
	
}
