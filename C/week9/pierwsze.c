#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

struct Node { 
	struct Node *letters[26];
	int count;
};
struct Node* root;
void setNewNode(struct Node* node) { 
	for(int i = 0; i < 26; i++) 
		node->letters[i] = NULL;
	node->count = 0;
} 
int AddIter(struct Node* currNode, char s[], int i) { 
	if(i == strlen(s)){
		currNode->count++;
		return	currNode->count-1;
	}
	if(currNode->letters[s[i]-'a'] == NULL) { 
		currNode->letters[s[i]-'a'] = (struct Node* )malloc(sizeof(struct Node));
		setNewNode(currNode->letters[s[i]-'a']);
	}
	currNode->count++;	
	AddIter(currNode->letters[s[i]-'a'],s, i+1);
}
int Add(char s[]){ 
	return AddIter(root, s, 0);		
}
int main(){
	root = (struct Node* )malloc(sizeof(struct Node));
	setNewNode(root);
	char tekst[1000005];
	while(scanf("%s", tekst)!=EOF)
		printf("%d\n", Add(tekst));
	return 0;
}