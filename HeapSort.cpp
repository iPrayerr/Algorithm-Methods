/*
	heap sort:
	1. 对数组按照堆的定义建立完全二叉树
	2. 将二叉树作一次调整，变成大顶堆
	3. 将大顶堆的根和最后一个树叶交换，并剔除交换后的树叶
	4. 重复23，直至所有元素被剔除，则得到sorted array 
*/
//树的核心：recurrence 
//测试数据为n个无序伪随机数，n为人工设定
 
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
		BTree* pos;		pos = bt;	//寻找父节点 
		
		int temp = i;
		if(i>3){
			vector<int> mov;		//轨迹算法：对于堆构建的完全二叉树，可以用i不断模2得到逆序的查找轨迹
									//0：当前查找中为左孩子；1：当前查找中为右孩子 
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

bool fin = true;			//调整完成标志 
void Big_Heap(BTree* &b){	//大顶堆应该从下往上调 
							//左孩子NULL, 右孩子必定NULL 
	int temp;			//两数值交换的中间变量
	if((b->left)!=NULL)
		Big_Heap(b->left);
	//compare
	if((b->parent->left)==b&&(b->parent->right)!=NULL){		//是左孩子且右孩子不为空 
		if((b->value)>(b->parent->right->value)&&(b->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->value;
			b->value = temp;
			fin = false;
		}//左孩子的swap 
		else if((b->value)<=(b->parent->right->value)&&(b->parent->right->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->parent->right->value;
			b->parent->right->value = temp;
			fin = false;
		}//右孩子的swap
	}
	else if((b->parent->right)==b&&(b->parent->left)!=NULL){	//是右孩子且左孩子不为空 
		if((b->value)>(b->parent->left->value)&&(b->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->value;
			b->value = temp;
			fin = false;
		}//左孩子的swap 
		else if((b->value)<=(b->parent->left->value)&&(b->parent->left->value)>(b->parent->value)){
				temp = b->parent->value;
				b->parent->value = b->parent->left->value;
				b->parent->left->value = temp;
				fin = false;
		}//右孩子的swap
	}
	else if((b->parent->left)==NULL||(b->parent->right)==NULL){
		if((b->value)>(b->parent->value)){
			temp = b->parent->value;
			b->parent->value = b->value;
			b->value = temp;
			fin = false;
		}//孩子的swap
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
	int signal;						//表示最后一个节点是其父节点的左孩子or右孩子 
	for(int j=mov.size()-1;j>=0;j--){
		if(j==0)
			signal = mov[j];		//记录最后一次转弯方向 
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
	a[length-1] = swap;				//未处理部分的最末尾存最大数 
	
	//next recurrence
	if(length>1){
		length--;
		Exchange(length);
	}
	else
		a[0] = bt->value;
}
