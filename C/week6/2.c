#include<stdio.h>
#define maxn 1005
#define maxsum 2000
int input[maxn], dp[maxn][maxsum], result[50], maksik;
vector<int> p;

void kombi(int i, int sumka, int temp[], int poz){
	if(i==0 && sumka!=0 && dp[0][sumka]) 
    {
        p.push_back(input[i]); 
        return; 
    } 
    if(i==0 && sumka==0){
    	if(poz>maksik){
    		maksik = poz;
    		for(int i=0; i<poz; i++)
    			result[i] = temp[i];
    	} 
        return; 
    } 
	if(dp[i-1][sumka]) 
    { 
    	int tab[50];
        kombi(i-1, sumka, tab, 0); 
    } 
    if(sumka >= input[i] && dp[i-1][sumka-input[i]]) 
    { 
        p.push_back(input[i]); 
        temp[poz]=input[i];
        kombi(i-1, sumka-input[i], temp, poz+1); 
    } 
}

int main(){
		int n;
		scanf("%d", &n);
		maksik = 0;
		for(int i=0; i<n; i++){
			scanf("%d", &input[i]);
			input[i]+=1000;
		}
}