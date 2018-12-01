#include<iostream>
#include<set>

using namespace std;

int father[10001];

int findFather(int x);
void unionTwo(int a, int b);

int main(){
	int N;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++){
		father[i] = i;
	}
	char operation[2];
	int c1, c2;
	while(true){
		scanf("%s", operation);
		if(operation[0] == 'C'){
			scanf("%d %d", &c1, &c2);
			if(findFather(c1) == findFather(c2)){
				printf("yes\n");
			}else{
				printf("no\n");
			}
		}else if(operation[0] == 'I'){
			scanf("%d %d", &c1, &c2);
			unionTwo(c1, c2);
		}else{
			break;
		}
	}
	set<int> fatherSet;
	for(int i = 1; i <= N; i++){
		fatherSet.insert(findFather(i));
	}
	if(fatherSet.size() == 1){
		printf("The network is connected.\n");
	}else{
		printf("There are %d components.\n", fatherSet.size());
	}
	return 0;
}

int findFather(int x){
	int a = x;
	while(x != father[x]){
		x = father[x];
	}
	while(a != father[a]){
		int z = a;
		a = father[a];
		father[z] = x;
	}	
	return x;
}

void unionTwo(int a, int b){
	int a_father = findFather(a);
	int b_father = findFather(b);
	if(a_father != b_father){
		father[a_father] = b_father;
	}
}
