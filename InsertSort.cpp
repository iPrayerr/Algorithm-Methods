/*
	insert sort
	 - �ӵڶ���Ԫ����Ϊ�����㣬��ȡ������Ԫ����Ϊkey, ��֮ǰԪ�ز�ͣ��key�Ƚϣ������������һλ
    -> ���ָ���ƶ�������λ֮ǰ��λ�ã������λԪ�ص���key, ������� 
*/

#include <iostream>

using namespace std;

int main() {
	//Ԫ�ظ��� 
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
			else break;			//��a[j]���ٴ���key����˵�����б�key���Ԫ�ض���Key���棬��֮��Ȼ����ֹͣ����
								//��ʱ����һ���������� 
		}
		a[j+1] = key;	
	}
	
	for(int i=0;i<n;i++)
		cout << a[i] << " ";
		
	return 0;
}//ʱ�临�Ӷȣ�o(n^2) 
