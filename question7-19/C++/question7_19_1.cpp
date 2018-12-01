#include<iostream>
#include<vector>

using namespace std;

struct node {
	int v, cost;
	node(int _v, int _cost) {
		v = _v;
		cost = _cost;
	}
};

int N, M, City1, City2, Cost, Status, lost, INF = 1000000000;
vector<node> graph[501];
int costs[501], d[501];
bool visited[501];

int prim();

int main() {
	scanf("%d %d", &N, &M);
	fill(costs + 1, costs + N + 1, 0);
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d %d", &City1, &City2, &Cost, &Status);
		if(Status == 1) {	//����������ٹ�·δ�𻵣��������Ϊ0
			Cost = 0;
		}
		graph[City1].push_back(node(City2, Cost));
		graph[City2].push_back(node(City1, Cost));
	}
	for(int i = 1; i <= N; i++) {
		lost = i;
		costs[i] = prim();
	}
	int maxIndex = 1;	//�����󻨷ѵ��±�
	for(int i = 2; i <= N; i++) {
		if(costs[i] > costs[maxIndex]) {
			maxIndex = i;
		}
	}
	if(costs[maxIndex] == 0) {	//�����󻨷�Ϊ0��ֱ�����0��return 0
		printf("0\n");
		return 0;
	}
	vector<int> maxCosts;	//�洢��󻨷ѵĶ�ʧ�ĳ��е�����
	for(int i = 1; i <= N; i++) {
		if(costs[i] == costs[maxIndex]) {
			maxCosts.push_back(i);
		}
	}
	for(int i = 0; i < maxCosts.size(); i++) {	//������
		printf("%d", maxCosts[i]);
		if(i != maxCosts.size() - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}
	return 0;
}

int prim() {
	fill(visited + 1, visited + 501, false);	//���е㶼δ�����ʹ�
	fill(d + 1, d + 501, INF);
	if(lost == 1) {
		d[2] = 0;
	} else {
		d[1] = 0;
	}
	int ans = 0;
	for(int i = 0; i < N - 1; i++) {
		int u = -1, min = INF;
		for(int j = 1; j <= N; j++) {
			if(!visited[j] && d[j] < min && j != lost) {
				u = j;
				min = d[j];
			}
		}
		if(u == -1) {
			return INF;	//����Ҳ���С��INF��d[u]����ʣ�µĶ���ͼ���S����ͨ����ʱ�Ļ�������ߵ� 
		}
		visited[u] = true;
		ans += d[u];
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int len = graph[u][j].cost;
			if(!visited[v] && v != lost && len < d[v]) {
				d[v] = len;
			}
		}
	}
	return ans;
}
