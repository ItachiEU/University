#include<stdio.h>
#include<stdlib.h>

int min(int a, int b){
	if(a < b)
		return a;
	return b;
}

typedef struct Array2D {
	unsigned int width, height;
	int *t;
} Array2D;
void print(Array2D *array) {
	for (unsigned int y = 0; y < array->height; y++) {
		for (unsigned int x = 0; x < array->width; x++)
			printf(" %i", array->t[y*array->width+x]);
		printf("\n");
	}
}

void resize(Array2D *array, unsigned int width, unsigned int height){
	if(width ==0 || height == 0){
		array->width = 0;
		array->height = 0;
		array->t = NULL;
		return ;
	}
	int oldW = array->width, oldH = array->height;
	//printf("%d %d\n", min(height-1, oldH-1),min(width-1, oldW-1) );
	if(oldH<=height && oldW>width){
		for(int i=height-1; i>=0; i--)
			for(int j=width-1; j>=0; j--){
				if(i<oldH && j<width)
					array->t[i*width+j] = array->t[i*oldW+j];
			}
		for(int i=height-1; i>=0; i--)
			for(int j=width-1; j>=0; j--){
				if(i>=oldH || j>=width)
					array->t[i*width+j] = 0;
			}
	}
	else
	if(oldW<=width && oldH>height){
		for(int i=height-1; i>=0; i--)
			for(int j=width-1; j>=0; j--){
				if(i<height && j<oldW)
					array->t[i*width+j] = array->t[i*oldW+j];
			}
		for(int i=height-1; i>=0; i--)
			for(int j=width-1; j>=0; j--){
				if(i>=height || j>=oldW)
					array->t[i*width+j] = 0;
			}
	}
	else
	if(oldW>width && oldH>height){
		for(int i=height-1; i>=0; i--)
			for(int j=width-1; j>=0; j--){
				if(i<height && j<width)
					array->t[i*width+j] = array->t[i*oldW+j];
			}
	}
	array->t = (int*)realloc(array->t, width*height*sizeof(int));
	array->height = height;
	array->width = width;
	if(oldW <= width && oldH <= height){
		for(int i=height-1; i>=0; i--)
			for(int j=width-1; j>=0; j--){
				if(i<oldH && j<oldW)
					array->t[i*width+j] = array->t[i*oldW+j];
			}
		for(int i=height-1; i>=0; i--)
			for(int j=width-1; j>=0; j--){
				if(i>=oldH || j>=oldW)
					array->t[i*width+j] = 0;
			}
	}
}

int main(){
	Array2D a = {3,3,(int*)malloc(9*sizeof(int))};
	for (int i = 0; i < 9; i++) a.t[i] = i+1;

	print(&a);
	// 1 2 3
	// 4 5 6
	// 7 8 9
	resize(&a,4,3); print(&a);
	// 1 2 3 0
	// 4 5 6 0
	// 7 8 9 0
	resize(&a,5,2); print(&a);
	// 1 2 3 0 0
	// 4 5 6 0 0
	resize(&a,2,3); print(&a);
	// 1 2
	// 4 5
	// 0 0
	resize(&a,1,2); print(&a);
	resize(&a,4,5); print(&a);
	// 1 2 0 0
	// 4 5 0 0
	// 4 5 0 0
	// 0 0 0 0
	// 0 0 0 0
	resize(&a,4,0);
	resize(&a,4,1); print(&a);
	// 0 0 0 0
	free(a.t);
}