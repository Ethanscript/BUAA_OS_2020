#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	int num=n;
	int rev=0;
	while(num>0){
		rev=rev*10+num%10;
		num/=10;
	}
	if(rev==n){
		printf("Y");
	}else{
		printf("N");
	}
	return 0;
}
