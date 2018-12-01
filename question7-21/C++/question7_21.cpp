#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	vector<int> children;
};

int N, M, ID, K, child;

void bfs(node* Node, vector<int> &levelLeaves);

int main() {
	while(true) {
		scanf("%d %d", &N, &M);
		if(N == 0) {
			break;
		}
		node Node[N + 1];
		for(int i = 0; i < M; i++) {
			scanf("%d %d", &ID, &K);
			for(int j = 0; j < K; j++) {
				scanf("%d", &child);
				Node[ID].children.push_back(child);
			}
		}
		vector<int> levelLeaves;
		bfs(Node, levelLeaves);
		for(int i = 0; i < levelLeaves.size(); i++){
			printf("%d", levelLeaves[i]);
			if(i != levelLeaves.size() - 1){
				printf(" ");
			}else{
				printf("\n");
			}
		}
	}
	return 0;
}

void bfs(node* Node, vector<int> &levelLeaves) {
	queue<int> q;
	q.push(1);
	while(!q.empty()) {
		int qSize = q.size();
		int count = 0;
		for(int i = 0; i < qSize; i++) {
			int u = q.front();
			q.pop();
			if(Node[u].children.size() == 0){
				count++;
			}
			for(int j = 0; j < Node[u].children.size(); j++){
				q.push(Node[u].children[j]);
			}
		}
		levelLeaves.push_back(count);
	}
}
