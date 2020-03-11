#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

int katalogi;

struct Node{
	int id[256];
	struct Node* sons[257];
	int count;
	struct Node* parent;
	int depth;
};
struct Node* root;

void setNode(struct Node* node){
	node->count = 0;
	for(int i=0; i<=256; i++){
		node->sons[i] = NULL;
		node->id[i] = -1;
	}
}

void mkdir(char word[],int len, struct Node* currNode){
	if(currNode->count>=256)
		return ;
	katalogi++;
	currNode->count+=1;
	currNode->sons[currNode->count-1] = (struct Node*)malloc(sizeof(struct Node));
	setNode(currNode->sons[currNode->count-1]);
	currNode->sons[currNode->count-1]->parent = currNode;
	currNode->sons[currNode->count-1]->depth = currNode->depth+1;
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
	katalogi = 0;
	root = (struct Node*)malloc((sizeof(struct Node)));
	setNode(root);
	root->parent = root;
	root->depth = 0;
}