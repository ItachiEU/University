#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node{
	char nazwa[257];
	struct Node* sons[257];
	int count;
	struct Node* parent;
};
struct Node* root;

void setNode(struct Node* node){
	node->count = 0;
	for(int i=0; i<=256; i++){
		node->sons[i] = NULL;
		node->nazwa[i] = 0;
	}
}

void mkdir(char word[],int len, struct Node* currNode){
	if(currNode->count>=256)
		return ;
	for(int i=0; i<currNode->count; i++){
		for(int j=0; j<(int)strlen(currNode->sons[i]->nazwa); j++){
			if(word[j] != currNode->sons[i]->nazwa[j])
				break;
			if(j==(int)strlen(currNode->sons[i]->nazwa)-1 && j==len-1)
				return ;
		}
	}
	currNode->count+=1;
	currNode->sons[currNode->count-1] = (struct Node*)malloc(sizeof(struct Node));
	setNode(currNode->sons[currNode->count-1]);
	currNode->sons[currNode->count-1]->parent = currNode;
	for(int i=0; i<len; i++)
		currNode->sons[currNode->count-1]->nazwa[i] = word[i];
}
void cd(char word[], int len, struct Node* currNode){
	for(int i=0; i<currNode->count; i++){
		for(int j=0; j<(int)strlen(currNode->sons[i]->nazwa); j++){
			if(word[j] != currNode->sons[i]->nazwa[j])
				break;
			if(j==(int)strlen(currNode->sons[i]->nazwa)-1 && j==len-1){
				root = currNode->sons[i];
				return ;
			}
		}
	}
}
void cd_back(struct Node* currNode){
		root = currNode->parent;
}
void pwd(struct Node* currNode, int ile){
	if(currNode->parent != currNode)
		pwd(currNode->parent, ile+1);
	for(int i=0; i<(int)strlen(currNode->nazwa); i++)
		printf("%c", currNode->nazwa[i]);
	if(ile==0 && currNode==root)
	printf("/");
	else
	if(currNode!=root)
	printf("/");
}
void ls(struct Node* currNode){
	for(int i=0; i<currNode->count; i++){
		for(int j=0; j<(int)strlen(currNode->sons[i]->nazwa); j++){
			printf("%c", currNode->sons[i]->nazwa[j]);
		}
		if(i == currNode->count-1)
			printf("\n");
		else
			printf(" ");
	}
}
int main(){
	char input[300],nazwa[300];
	root = (struct Node*)malloc((sizeof(struct Node)));
	setNode(root);
	root->parent = root;
	while(scanf("%s", input)!=EOF){
		if(input[0] == 'l'){
			ls(root);
		}
		else
		if(input[0] == 'p'){
			pwd(root, 0);
			printf("\n");
		}else
		if(input[0] == 'm'){
			scanf("%s", nazwa);
			mkdir(nazwa, strlen(nazwa), root);
		}else
		if(input[0] == 'c'){
			//cd back
			scanf("%s", nazwa);
			if(nazwa[0]=='.' && nazwa[1]=='.')
				cd_back(root);
			else			
				cd(nazwa, strlen(nazwa), root);
		}
	}
}