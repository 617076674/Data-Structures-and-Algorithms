#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct edge {
	int u, v, cost;
	edge(int _u, int _v, int _cost) {
		u = _u;
		v = _v;
		cost = _cost;
	}
};

int N, M, City1, City2, Cost, Status, lost, INF = 1000000000;
vector<edge> edges;
int costs[501], father[501];

int kruskal();
int findFather(int x);
bool cmp(edge e1, edge e2);

int main() {
	scanf("%d %d", &N, &M);
	fill(costs + 1, costs + N + 1, 0);
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d %d", &City1, &City2, &Cost, &Status);
		if(Status == 1) {	//如果这条高速公路未损坏，则其费用为0
			Cost = 0;
		}
		edges.push_back(edge(City1, City2, Cost));
	}
	for(int i = 1; i <= N; i++) {
		lost = i;
		costs[i] = kruskal();
	}
	int maxIndex = 1;	//求出最大花费的下标
	for(int i = 2; i <= N; i++) {
		if(costs[i] > costs[maxIndex]) {
			maxIndex = i;
		}
	}
	if(costs[maxIndex] == 0) {	//如果最大花费为0，直接输出0并return 0
		printf("0\n");
		return 0;
	}
	vector<int> maxCosts;	//存储最大花费的丢失的城市的索引
	for(int i = 1; i <= N; i++) {
		if(costs[i] == costs[maxIndex]) {
			maxCosts.push_back(i);
		}
	}
	for(int i = 0; i < maxCosts.size(); i++) {
		printf("%d", maxCosts[i]);
		if(i != maxCosts.size() - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}
	return 0;
}

int kruskal() {
	int ans = 0, num_edge = 0;
	for(int i = 1; i <= N; i++) {	//并查集的初始化
		father[i] = i;
	}
	sort(edges.begin(), edges.end(), cmp);
	for(int i = 0; i < edges.size(); i++){
		int u = edges[i].u;
		int v = edges[i].v;
		if(u == lost || v == lost){
			continue;
		}
		int faU = findFather(u);
		int faV = findFather(v);
		if(faU != faV){
			father[faU] = faV;
			ans += edges[i].cost;
			num_edge++;
			if(num_edge == N - 2){
				break;
			}
		}
	}
	if(num_edge != N - 2){
		return INF;
	}
	return ans;
}

int findFather(int x) {
	int a = x;
	while(x != father[x]) {
		x = father[x];
	}
	while(a != father[a]) {
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}

bool cmp(edge e1, edge e2){
	return e1.cost < e2.cost;
}
