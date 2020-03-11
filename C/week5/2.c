#include<stdio.h>
#include<math.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) > (y)) ? (y) : (x))

#define radius 20
int hour_x[radius], hour_y[radius], minute_x[radius], minute_y[radius];

int check_hour(int x, int y){
	int x_tak=0, y_tak=0;
	for(int i=0; i<radius/2+1; i++){
		if(hour_x[i]==x && hour_y[i]==y)
			return 1;
	}
	return 0;
}
int check_minute(int x, int y){
	int x_tak=0, y_tak=0;
	for(int i=0; i<radius/2+6; i++){
		if(minute_x[i]==x && minute_y[i]==y)
			return 1;
	}
	return 0;
}
int main(){
	int a, b;
	scanf("%d", &a);getchar();
	scanf("%d", &b);
	if(a>12)
		a-=12;
	
	double angle_hour=(a*2*3.14)/12, angle_minute=(b*2*3.14)/60;
	for(int i=1; i<radius; i++){
		hour_x[i] = radius + i*sin(angle_hour)+1, hour_y[i]=radius - i*cos(angle_hour);
		minute_x[i] = radius + i*sin(angle_minute), minute_y[i]=radius - i*cos(angle_minute);
	}
	//printf("%d %d\n", hour_x[1], hour_y[1]);
	for(int i=1; i<=2*radius; i++){
		for(int j=0; j<=2*radius; j++){
			if(check_hour(j, i)==1){
				printf("H");
				continue;
			}
			if(check_minute(j, i)==1){
				printf("M");
				continue;
			}
			if((radius-i)*(radius-i)+(radius-j)*(radius-j)>(radius*radius)+1)
				printf(" ");
			else
				printf(".");
		}
		printf("\n");
	}
}	