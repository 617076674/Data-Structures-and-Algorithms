#include<iostream>
#include<queue>

using namespace std;

struct node{
	int lchild, rchild;
};

node Node[10];
int index = 0;
vector<int> leaves;

void levelOrderTraversal(int head);

int main(){
	int N;
	scanf("%d", &N);
	char str[2];
	bool flag[N];
	fill(flag, flag + N, false);
	for(int i = 0; i < N; i++){
		scanf("%s", str);
		if(str[0] == '-'){
			Node[i].lchild = -1;
		}else{
			Node[i].lchild = str[0] - '0';
			flag[str[0] - '0'] = true;
		}
		scanf("%s", str);
		if(str[0] == '-'){
			Node[i].rchild = -1;
		}else{
			Node[i].rchild = str[0] - '0';
			flag[str[0] - '0'] = true;
		}
	}
	int head;
	for(int i = 0; i < N; i++){
		if(!flag[i]){
			head = i;
		}
	}
	levelOrderTraversal(head);
	for(int i = 0; i < leaves.size(); i++){
		printf("%d", leaves[i]);
		if(i != leaves.size() - 1){
			printf(" ");
		}else{
			printf("\n");
		}
	}
	return 0;
}

void levelOrderTraversal(int head){
	queue<int> q;
	q.push(head);
	while(!q.empty()){
		int now = q.front();
		if(Node[now].lchild == -1 && Node[now].rchild == -1){
			leaves.push_back(now);
		}
		q.pop();
		if(Node[now].lchild != -1){
			q.push(Node[now].lchild);
		}
		if(Node[now].rchild != -1){
			q.push(Node[now].rchild);
		}
	}
}
