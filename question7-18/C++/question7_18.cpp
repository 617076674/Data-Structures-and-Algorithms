#include<iostream>
#include<vector>
#include<queue> 

using namespace std;

int N; 
int nums[1000], inDegree[1000];
vector<int> graph[1000];
vector<int> result;

struct cmp{
	bool operator() (int a, int b){	//����int�͵ıȽϷ��� 
		return nums[a] > nums[b];
	}
};

int main(){
	fill(inDegree, inDegree + N, 0);	//���нڵ����ȳ�ʼ��Ϊ0
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
		if(nums[i] < 0){
			inDegree[i] = -1;	//�����ڵĵ��������Ϊ-1 
		}
	}
	for(int i = 0; i < N; i++){
		int key = nums[i] % N;	//keyλ����nums[i]Ӧ��ԭ��Ӧ�ò����λ�� 
		if(key == i || nums[i] < 0){
			continue;
		}
		for(int j = 0; j < N; j++){	//��keyλ�õ���������Ѱ�ҽڵ�i������ǰ���ڵ� 
			if(nums[(key + j) % N] == nums[i]){	 
				break;
			}
			graph[(key + j) % N].push_back(i);
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < graph[i].size(); j++){	//��ÿ������������ֵ 
			inDegree[graph[i][j]]++;
		}
	}
	priority_queue<int, vector<int>, cmp> q; //���ȶ��У������Զ���cmp���� 
	for(int i = 0; i < N; i++){	//�����Ϊ0�ĵ���� 
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
