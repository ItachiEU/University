#include<stdio.h>

void copy_bit(__uint32_t x, __uint32_t i, __uint32_t k){
	int bit = (x & 1 << i);
	x = ()
}

int main(){
	__uint32_t x, i, k;
	scanf("%d%d%d", &x, &i, &k);
	printf("%d%d%d\n", x, i, k);
	copy_bit(x, i, k);
}