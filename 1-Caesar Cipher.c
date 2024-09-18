#include<stdio.h>
#include<string.h>
int main(){
	char plain[100];
	char cipher[100];
	int k,i;
	char c;
	printf("Enter plain text: ");
	scanf("%s",plain);
	printf("Enter key: ");
	scanf("%d",&k);
	int l=strlen(plain);
	//encryption
	for(i=0;i<=l;i++){
		c=plain[i];
		if(c>='A'&&c<='Z'){
			cipher[i]=(c-'A'+k)%26+'A';
		}
		else if(c>='a'&&c<='z'){
			cipher[i]=(c-'a'+k)%26+'a';
		}
	}
	printf("Enctrpted text: %s\n",cipher);
	//decryption
	for(i=0;i<=l;i++){
		c=cipher[i];
		if(c>='A'&&c<='Z'){
			plain[i]=(c-'A'-k+26)%26+'A';
		}
		else if(c>='a'&&c<='z'){
			plain[i]=(c-'a'-k+26)%26+'a';
		}
	}
	printf("Decrypted text after encryption: %s",plain);
	return 0;
}
