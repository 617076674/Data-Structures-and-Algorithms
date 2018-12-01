#include<iostream>
#include<map>
#include<cstring>

using namespace std;

int N;
char Command[2];
long long QQ_No;
map<long long, char[17]> accounts;	//注意字符串的存储方式 

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		char Password[17];
		scanf("%s %lld %s", Command, &QQ_No, Password);
		if(Command[0] == 'R'){
			if(accounts.find(QQ_No) != accounts.end()){
				printf("ERROR: Account Number Already Exists\n");
			}else{
				printf("Register Successful\n");
				strcpy(accounts[QQ_No], Password);	//将Password复制一份进accounts[QQ_No] 
			}
		}else if(Command[0] == 'L'){
			if(accounts.find(QQ_No) != accounts.end()){
				if(strcmp(accounts[QQ_No], Password) == 0){
					printf("Log in Successful\n");
				}else{
					printf("ERROR: Wrong Password\n");
				}
			}else{
				printf("ERROR: Account Not Exist\n");
			}
		}
	}
	return 0;
}
