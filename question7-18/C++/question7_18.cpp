#include<iostream>
#include<vector>
#include<queue> 

using namespace std;

int N; 
int nums[1000], inDegree[1000];
vector<int> graph[1000];
vector<int> result;

struct cmp{
	bool operator() (int a, int b){	//重载int型的比较方法 
		return nums[a] > nums[b];
	}
};

int main(){
	fill(inDegree, inDegree + N, 0);	//所有节点的入度初始化为0
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
		if(nums[i] < 0){
			inDegree[i] = -1;	//不存在的点标记其入度为-1 
		}
	}
	for(int i = 0; i < N; i++){
		int key = nums[i] % N;	//key位置是nums[i]应该原本应该插入的位置 
		if(key == i || nums[i] < 0){
			continue;
		}
		for(int j = 0; j < N; j++){	//从key位置递增，依次寻找节点i的所有前驱节点 
			if(nums[(key + j) % N] == nums[i]){	 
				break;
			}
			graph[(key + j) % N].push_back(i);
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < graph[i].size(); j++){	//对每个点计算其入度值 
			inDegree[graph[i][j]]++;
		}
	}
	priority_queue<int, vector<int>, cmp> q; //优先队列，采用自定义cmp函数 
	for(int i = 0; i < N; i++){	//将入度为0的点入队 
		if(inDegree[i] == 0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u = q.top();
		result.push_back(nums[u]);
		q.pop();
		for(int i = 0; i < graph[u].size(); i++){
			int v = graph[u][i];
			inDegree[v]--;
			if(inDegree[v] == 0){
				q.push(v);
			}
		}
	}
	for(int i = 0; i < result.size(); i++){
		printf("%d", result[i]);
		if(i != result.size() - 1){
			printf(" ");
		}else{
			printf("\n");
		}
	}
	return 0;
}
