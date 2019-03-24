/*
	divide&conquer
	1. ���������ģ���ֳ�ż����̶����ȵ������飨ÿ�������ģΪ10��������Ԫ�ص������� 
	2. ��ÿ�����������insert sort
	3. �������������ͷ���бȽϣ�ÿ��ȡС�߼�������飬���ƽ�С��ֵ�����������ͷ���ɴ���ϻش�����
*/ 

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
 
int* conquer(int a[],int size);
int* insert_sort(int sub[],int length);
int* combine(int a1[],int a1s,int a2[],int a2s);

int main() {
	srand(time(0));				//ʹrand()������1970.1.1��ʼ����������������Ϊ���ӵ������
								//rand()ͨ��һ���̶��ĺ�����ϵʽ����һ���������seedֵ�����������С
								//srand(int) = set rand's seed
	//Ԫ�ظ��� 
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
		int subs = size/2;							//�������ģ�۰� 
		int* suba = new int[subs+1];
		int* subb = new int[size-subs+1];
		for(int i=0;i<subs;i++) {
			suba[i] = a[i];
			subb[i] = a[i+subs]; 
		}
		subb[size-subs-1] = a[size-1];
		suba[subs] = 10000;subb[size-subs] = 10000;	//�����������ںϲ�ʱ��Ҫ������ͷ�Ƚ�ȡ��С����������ָ����ƽ�
													//�������ĩβӦ��������һ������������ֹ����һ��ָ�뵽ĩβ�����ƽ����ÿգ��������һ��ָ��ָ���ֵ�޷��Ƚ� 
		if(subs>10) {								//��δ�ﵽ��ģҪ�� 
			suba = conquer(suba,subs);				//�ݹ����
			subb = conquer(subb,size-subs);
		}
		else {
			suba = insert_sort(suba,subs+1);
			subb = insert_sort(subb,size-subs+1);
		}
		arr = combine(suba,subs+1,subb,size-subs+1);			//������ϵķ������� 
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
			else break;					//��a[j]���ٴ���key����˵�����б�key���Ԫ�ض���key���棬��֮��Ȼ����ֹͣ����
		}
		sub[j+1] = key;	
	}
	
	return sub;
}
int* combine(int a1[],int a1s,int a2[],int a2s) {	//��̬���鲻�ܲ���sizeof()����İ취�������ģ
	int* arr = new int[a1s+a2s-1];
	int i = 0;							//��ʼ����һ��������ϲ�����ͷ
	int j = 0;							//��ʼ���ڶ���������ϲ�����ͷ
										//������ͷÿ�αȽϣ�ʼ������С���޳���������С�ߵ�������ͷ�ƽ�������һ�������ͷ�����Ƚϣ���֤ÿ���޳���ֵ����ȫ����С 
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
	
	arr[a1s+a2s-2] = 10000;				//��combine�ڵݹ�����У��������ݹ�����������Ȼ��Ҫ����һ�������ÿյ�������
										//��combine�õ��������飬�����main�����н��������������� 
	return arr;	
}
/*
	����������
	����Ԫ�ظ���n������n��[0,500)��Χ�ڵ��������Ϊ���� 
*/
