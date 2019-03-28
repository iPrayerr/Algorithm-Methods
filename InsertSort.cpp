/*
	Insert Sort
	1. Set the second element as key
	2. compare with previous elements one by one, if larger, move it a step behind
	3. if smaller, the current progress exits, and the key is inserted in the blank area due to moving
	4. repeat until all the elements in the array(except the first one) are sorted
*/

#include <iostream>

using namespace std;

int main() {
	//元素个数 
	int n;
	cin >> n;
	
	int a[n];
	for(int i=0;i<n;i++)
		cin >> a[i];
		 
	//sort
	int key;
	for(int i=1;i<n;i++) {
		key = a[i];
		int j;
		for(j=i-1;j>=0;j--) {
			if(a[j]>key)
				a[j+1] = a[j];
			else break;			//若a[j]不再大于key，则说明所有比key大的元素都在Key后面，反之亦然；故停止遍历
								//此时产生一个遍历次数 
		}
		a[j+1] = key;	
	}
	
	for(int i=0;i<n;i++)
		cout << a[i] << " ";
		
	return 0;
} 
