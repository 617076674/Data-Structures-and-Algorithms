#include<iostream>
#include<vector>

using namespace std;

struct node {
	int data;
	node* lchild;
	node* rchild;
};

int N, L;

node* newNode(int num);
void insert(node* &head, int num);
node* create(int* nums);
void preOrderTraversal(node* head, vector<int> &preOrder);

int main() {
	while(true) {
		scanf("%d", &N);
		if(N == 0) {
			break;
		}
		scanf("%d", &L);
		int nums[N];
		for(int j = 0; j < N; j++) {
			scanf("%d", &nums[j]);
		}
		node* head = create(nums);
		vector<int> preOrder;
		preOrderTraversal(head, preOrder);
		for(int i = 0; i < L; i++) {
			int nums[N];
			for(int j = 0; j < N; j++) {
				scanf("%d", &nums[j]);
			}
			node* head = create(nums);
			vector<int> tempPreOrder;
			preOrderTraversal(head, tempPreOrder);
			if(tempPreOrder == preOrder){
				printf("Yes\n");
			}else{
				printf("No\n");
			}
		}
	}
	return 0;
}

node* newNode(int num) {
	node* head = new node();
	head->data = num;
	head->lchild = head->rchild = NULL;
	return head;
}

void insert(node* &head, int num) {
	if(head == NULL) {
		head = newNode(num);
		return;
	}
	if(head->data < num) {
		insert(head->rchild, num);
	} else {
		insert(head->lchild, num);
	}
}

node* create(int* nums) {
	node* head = NULL;
	for(int i = 0; i < N; i++) {
		insert(head, nums[i]);
	}
	return head;
}

void preOrderTraversal(node* head, vector<int> &preOrder){
	if(head == NULL){
		return;
	}
	preOrder.push_back(head->data);
	preOrderTraversal(head->lchild, preOrder);
	preOrderTraversal(head->rchild, preOrder);
}
