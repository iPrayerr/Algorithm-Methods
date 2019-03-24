/*
	insert sort
	 - 从第二个元素作为出发点，提取出发点元素作为key, 其之前元素不停与key比较，比它大，则后移一位
    -> 如此指针移动到插入位之前的位置，令插入位元素等于key, 排序完成 
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
}//时间复杂度：o(n^2) 
