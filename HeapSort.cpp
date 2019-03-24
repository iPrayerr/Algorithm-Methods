/*
	heap sort:
	1. �����鰴�նѵĶ��彨����ȫ������
	2. ����������һ�ε�������ɴ󶥶�
	3. ���󶥶ѵĸ������һ����Ҷ���������޳����������Ҷ
	4. �ظ�23��ֱ������Ԫ�ر��޳�����õ�sorted array 
*/
//���ĺ��ģ�recurrence 
//��������Ϊn������α�������nΪ�˹��趨
 
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

struct BTree{
	int value;
	struct BTree *parent,*left,*right;
}*bt;
vector<int> a;
int n;

void Heap_Sort();
void CreateTree(BTree* &b,int i);
void Big_Heap(BTree* &b);
void Exchange(int length);

int main(){
	srand(time(0));

	cin >> n;
	
	for(int i=0;i<n;i++) {
		a.push_back(rand()%500);
		cout << a[i] << " ";
	}
	cout << endl;
		
	Heap_Sort();
	for(int i=0;i<n;i++)
		cout << a[i] << " ";
	
	return 0;
}

void Heap_Sort(){
	CreateTree(bt,1);
	Exchange(n);
}

void CreateTree(BTree* &b,int i){ 
	if(i<=n){
		b = new BTree;
		BTree* pos;		pos = bt;	//Ѱ�Ҹ��ڵ� 
		
		int temp = i;
		if(i>3){
			vector<int> mov;		//�켣�㷨�����ڶѹ�������ȫ��������������i����ģ2�õ�����Ĳ��ҹ켣
									//0����ǰ������Ϊ���ӣ�1����ǰ������Ϊ�Һ��� 
			while(temp>1){
				mov.push_back(temp%2);
				temp/=2;
			}
		
			for(int j=mov.size()-1;j>=1;j--){  
				if(!mov[j])
					pos = pos->left;
				else
					pos = pos->right;
			}	
		}
		b->parent = pos;
		b->value = a[i-1];
		CreateTree(b->left,2*i);
		CreateTree(b->right,2*i+1);
	}
	else
		b = NULL;
}

bool fin = true;			//������ɱ�־ 
void Big_Heap(BTree* &b){	//�󶥶�Ӧ�ô������ϵ� 
							//����NULL, �Һ��ӱض�NULL 
	int temp;			//����ֵ�������м����
	if((b->left)!=NULL)
		Big_Heap(b->left);
	//compare
	if((b->parent->left)==b&&(b->parent->right)!=NULL){		//���������Һ��Ӳ�Ϊ�� 
		if((b->value)>(b->parent->right->value)&&(b->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->value;
			b->value = temp;
			fin = false;
		}//���ӵ�swap 
		else if((b->value)<=(b->parent->right->value)&&(b->parent->right->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->parent->right->value;
			b->parent->right->value = temp;
			fin = false;
		}//�Һ��ӵ�swap
	}
	else if((b->parent->right)==b&&(b->parent->left)!=NULL){	//���Һ��������Ӳ�Ϊ�� 
		if((b->value)>(b->parent->left->value)&&(b->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->value;
			b->value = temp;
			fin = false;
		}//���ӵ�swap 
		else if((b->value)<=(b->parent->left->value)&&(b->parent->left->value)>(b->parent->value)){
				temp = b->parent->value;
				b->parent->value = b->parent->left->value;
				b->parent->left->value = temp;
				fin = false;
		}//�Һ��ӵ�swap
	}
	else if((b->parent->left)==NULL||(b->parent->right)==NULL){
		if((b->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->value;
			b->value = temp;
			fin = false;
		}//���ӵ�swap
	}
	if(b->right!=NULL)
		Big_Heap(b->right);
	if(fin==false){
		fin = true;
		Big_Heap(bt);
	}
}

void Exchange(int length) {
	Big_Heap(bt);
	
	int temp = length;
	vector<int> mov; 
	while(temp>1){
		mov.push_back(temp%2);
		temp/=2;
	}
	
	//seek: 0 to left 
	BTree *pos;	pos = bt;
	int signal;						//��ʾ���һ���ڵ����丸�ڵ������or�Һ��� 
	for(int j=mov.size()-1;j>=0;j--){
		if(j==0)
			signal = mov[j];		//��¼���һ��ת�䷽�� 
		if(!mov[j])
			pos = pos->left;
		else
			pos = pos->right;
	}
	
	//exchange
	int swap = bt->value;
	bt->value = pos->value;
	pos->value = swap;
	
	//delete node&save the biggest
	pos = pos->parent;
	if(!signal)
		pos->left = NULL;
	else
		pos->right = NULL;
	a[length-1] = swap;				//δ�����ֵ���ĩβ������� 
	
	//next recurrence
	if(length>1){
		length--;
		Exchange(length);
	}
	else
		a[0] = bt->value;
}
