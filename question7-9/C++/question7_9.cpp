#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

bool isPre(char* str1, char* str2);	//判断str1是否是str2的前缀或str2是否是str1的前缀 

int main() {
	int N;
	scanf("%d", &N);
	int frequency[63];
	fill(frequency, frequency + 63, 0);
	char str[2];
	int count;
	priority_queue<int, vector<int>, greater<int> > q;
	for(int i = 0; i < N; i++) {
		scanf("%s %d", str, &count);
		if(str[0] >= '0' && str[0] <= '9') {
			frequency[str[0] - '0'] = count;
		} else if(str[0] >= 'a' && str[0] <= 'z') {
			frequency[str[0] - 'a' + 10] = count;
		} else if(str[0] >= 'A' && str[0] <= 'Z') {
			frequency[str[0] - 'A' + 36] = count;
		} else if(str[0] == '_') {
			frequency[62] = count;
		}
		q.push(count);
	}
	int x, y, minLen = 0;
	while(q.size() > 1) {
		x = q.top();
		q.pop();
		y = q.top();
		q.pop();
		q.push(x + y);
		minLen += x + y;
	}
	int M, len, num;
	scanf("%d", &M);
	char code[N][64];
	for(int i = 0; i < M; i++) {
		len = 0;
		for(int j = 0; j < N; j++) {
			scanf("%s %s", str, code[j]);
			if(str[0] >= '0' && str[0] <= '9') {
				len += frequency[str[0] - '0'] * strlen(code[j]);
			} else if(str[0] >= 'a' && str[0] <= 'z') {
				len += frequency[str[0] - 'a' + 10] * strlen(code[j]);
			} else if(str[0] >= 'A' && str[0] <= 'Z') {
				len += frequency[str[0] - 'A' + 36] * strlen(code[j]);
			} else if(str[0] == '_') {
				len += frequency[62] * strlen(code[j]);
			}
		}
		bool flag = true;
		for(int j = 0; j < N; j++){
			for(int k = j + 1; k < N; k++){
				if(isPre(code[j], code[k])){
					flag = false;
					break;
				}
			}
			if(!flag){
				break;
			}
		} 
		if(len == minLen && flag) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}

bool isPre(char* str1, char* str2) {
	int commonLen = min(strlen(str1), strlen(str2));
	for(int t = 0; t < commonLen; t++) {
		if(str1[t] != str2[t]) {
			return false;
		}
	}
	return true;
}
