#include<stdio.h>
#include<math.h>

int main(){
	int z, ile=1;
	scanf("%d", &z);
	double res = 0, res_prev = 0;
	while(1){
		res = res_prev + pow((double)(1.0/ile), z);
		//printf("%.10lf %lf\n", res, pow((double)(1.0/ile),z));
		if(res <= res_prev)
			break;
		ile++;
		res_prev = res;
	}
	printf("%.6lf %d", res, ile);
}