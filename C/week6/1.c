#include <stdio.h> 
#define maxn 40
long long int input[maxn],result[11], maksik;
void kombi(long long int data[], int left, int right, int index, int k) 
{ 
    if (index == k){ 
        long long int temp = 0;
        for (int j=0; j<k; j++) 
            temp+=data[j];
        if(temp==0 && k>maksik){
            maksik = k;
            for(int i=0; i<k; i++)
                result[i]=data[i];
        }
        return; 
    } 
    for (int i=left; i<=right && right-i+1 >= k-index; i++){ 
        data[index] = input[i]; 
        kombi(data, i+1, right, index+1, k);
    } 
} 
int main() 
{ 
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%lld", &input[i]);
    for(int i=1; i<=10; i++){
        long long int data[11];
        kombi(data,0, n-1, 0, i); 
    }
    for(int i=0; i<maksik; i++)
        printf("%lld ", result[i]);
}