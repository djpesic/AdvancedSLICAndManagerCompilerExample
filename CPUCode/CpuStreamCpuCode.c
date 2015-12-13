#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"

//int twoKernelsRun(void)
//{
//	int size=16;
//	int *x=calloc(size, sizeof(int));
//	int *y=calloc(size, sizeof(int));
//	int *z=calloc(size, sizeof(int));
//	for(int i=0;i<size;i++){
//		x[i]=i;y[i]=i+1;
//	}
//	for(int i=0;i<size;i++)printf("%d ",x[i]);
//	printf("\n");
//	for(int i=0;i<size;i++)printf("%d ",y[i]);
//	printf("\n");
//	max_file_t* kernel1=CpuStream_init();
//	max_engine_t* engine1=max_load(kernel1,"*");
//	printf("addition\n");
//	CpuStream_actions_t action;
//	action.instream_x=x;
//	action.instream_y=y;
//	action.outstream_s=z;
//	action.param_N=size;
//	CpuStream_run(engine1,&action);
//	for(int i=0;i<size;i++) printf("%d ",z[i]);
//	max_unload(engine1);
//	printf("\n");
//
//	max_file_t* kernel2=CpuStream1_init();
//	engine1=max_load(kernel2,"*");
//	printf("subtraction\n");
//	CpuStream1_actions_t action2;
//	action2.instream_x=x;
//	action2.instream_y=y;
//	action2.outstream_s=z;
//	action2.param_N=size;
//	CpuStream1_run(engine1,&action2);
//	for(int i=0;i<size;i++) printf("%d ",z[i]);
//	max_unload(engine1);
//	printf("\n");
//	CpuStream_free();
//	CpuStream1_free();
//
//	return 0;
//}


int chainedKernelsRun(){
	int32_t size=16;
	int32_t *x=calloc(size,size*sizeof(int32_t));
	int32_t *y=calloc(size, sizeof(int32_t));
	int32_t *z=calloc(size, sizeof(int32_t));


	for(int i=0;i<size;i++){
		x[i]=i;
		y[i]=i+1;
	}
	printf("x: ");
	for(int i=0;i<size;i++)printf("%d ",x[i]);
	printf("\n");
	printf("y: ");
	for(int i=0;i<size;i++)printf("%d ",y[i]);
	printf("\n");

	ProbaCustom(size,x,y,z);

	for(int i=0;i<size;i++)printf("%d ",z[i]);
	printf("\n");

	return 0;
}
int main(){
	return chainedKernelsRun();
}
