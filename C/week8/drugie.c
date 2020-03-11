#include<stdio.h>
#include<stdlib.h>

int main(){
	long long int l = 0, r = ((long long int)1<<50);
	printf("%lld\n", r);
	size_t mid;
	while(l<r){
		mid = l + (r-l)/2;
		void* pointer = malloc(mid);
		if(pointer == NULL)
			r = mid - 1;
		else{
			l = mid + 1;
			free(pointer);
		}
	}
	printf("%zu\n", mid);
}