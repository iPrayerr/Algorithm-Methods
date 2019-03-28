/*
	divide&conquer
	1. 根据数组规模划分成偶数组固定长度的子数组（每个数组规模为10），多余元素单独考虑 
	2. 对每个子数组采用insert sort
	3. 两个子数组的排头进行比较，每次取小者加入大数组，并移进小数值所在数组的排头，由此组合回大数组
*/ 

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
 
int* conquer(int a[],int size);
int* insert_sort(int sub[],int length);
int* combine(int a1[],int a1s,int a2[],int a2s);

int main() {
	srand(time(0));	
	
	//元素个数 
	int n;
	cin >> n;
	
	int* a = new int[n];
	for(int i=0;i<n;i++) {
		a[i] = rand() % 500;
		cout << a[i] << " ";
	}
	cout << endl;
	
	//conquer
	a = conquer(a,n);
	
	//output
	for(int i=0;i<n;i++)
		cout << a[i] << " ";
	
	return 0;
}

int* conquer(int a[],int size) {
	int* arr = NULL;
	if(size>10) {
		int subs = size/2;							//子数组规模折半 
		int* suba = new int[subs+1];
		int* subb = new int[size-subs+1];
		for(int i=0;i<subs;i++) {
			suba[i] = a[i];
			subb[i] = a[i+subs]; 
		}
		subb[size-subs-1] = a[size-1];
		suba[subs] = 10000;subb[size-subs] = 10000;	//由于子数组在合并时需要两两排头比较取其小，伴随两个指针的移进
													//因此数据末尾应额外设置一个无穷量，防止其中一个指针到末尾继续移进后置空，造成与另一个指针指向的值无法比较 
		if(subs>10) {								//尚未达到规模要求 
			suba = conquer(suba,subs);				//递归分治
			subb = conquer(subb,size-subs);
		}
		else {
			suba = insert_sort(suba,subs+1);
			subb = insert_sort(subb,size-subs+1);
		}
		arr = combine(suba,subs+1,subb,size-subs+1);			//分治完毕的返回数组 
	}
	else {
		arr = insert_sort(a,size);
	}
	
	return arr;

}
int* insert_sort(int sub[],int length) {
	int key;
	for(int i=1;i<length;i++) {
		key = sub[i];
		int j;
		for(j=i-1;j>=0;j--) {
			if(sub[j]>key)
				sub[j+1] = sub[j];
			else break;					//若a[j]不再大于key，则说明所有比key大的元素都在key后面，反之亦然；故停止遍历
		}
		sub[j+1] = key;	
	}
	
	return sub;
}
int* combine(int a1[],int a1s,int a2[],int a2s) {	//动态数组不能采用sizeof()相除的办法求数组规模
	int* arr = new int[a1s+a2s-1];
	int i = 0;							//初始化第一个子数组合并的排头
	int j = 0;							//初始化第二个子数组合并的排头
										//两个排头每次比较，始终择最小者剔除，存在最小者的数组排头移进，与另一数组的排头继续比较，保证每次剔除的值都是全局最小 
	for(int k=0;k<a1s+a2s-2;k++) {
		if(a1[i]<a2[j]) {
			arr[k] = a1[i];
			i++;
		}
		else {
			arr[k] = a2[j];
			j++;
		}
	}
	
	arr[a1s+a2s-2] = 10000;				//若combine在递归过程中，则跳出递归后的子数组仍然需要这样一个避免置空的无穷量
										//若combine得到最终数组，则可在main函数中将这个无穷量处理掉 
	return arr;	
}
/*
	测试样例：
	给定元素个数n，生成n个[0,500)范围内的随机数作为样例 
*/
