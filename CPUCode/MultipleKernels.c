#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
/*
 * This function demonstrates running 3 max files on the same DFE. There is the max files for addition, subtraction and multiplication. Every max file is loaded, then
 * actions are run, then max files are unloaded and DFE is deallocated.
 * */
int twoKernelsRun(void)
{
	int size=16;//Size of the arrays
	int *x=calloc(size, sizeof(int));// Array of the first operands
	int *y=calloc(size, sizeof(int));// Array of the second operands
	int *z=calloc(size, sizeof(int));// Array of the results
	for(int i=0;i<size;i++){
		x[i]=i;y[i]=i+1;//Operands initialization.
	}
	printf("x: ");
	for(int i=0;i<size;i++)printf("%d ",x[i]);
	printf("\n");
	printf("y: ");
	for(int i=0;i<size;i++)printf("%d ",y[i]);
	printf("\n");

	max_file_t* kernel1=Adder_init(); //Creates a handle to Adder max file.
	max_engine_t* engine1=max_load(kernel1,"*"); //Loads Adder max file to engine
	printf("addition\n");
	Adder_actions_t action;//Defines action to be run on engine
	action.instream_x=x;//Setting stream for the first operands
	action.instream_y=y;//Setting stream for the second operands
	action.outstream_s=z;//Setting stream for the results
	action.param_N=size;//Setting stream size
	printf("z: ");

	Adder_run(engine1,&action);//Run actions on the DFE
	for(int i=0;i<size;i++) printf("%d ",z[i]);
	max_unload(engine1);//Unloads Adder max file
	Adder_free();//Deallocate engine
	printf("\n");
	//Rest of the code is analog to Adder
	max_file_t* kernel2=Subtractor_init();
	engine1=max_load(kernel2,"*");
	printf("subtraction\n");
	Subtractor_actions_t action2;
	action2.instream_x=x;
	action2.instream_y=y;
	action2.outstream_s=z;
	action2.param_N=size;
	Subtractor_run(engine1,&action2);
	printf("z: ");
	for(int i=0;i<size;i++) printf("%d ",z[i]);
	max_unload(engine1);
	printf("\n");
	Subtractor_free();

	max_file_t* kernel3=Multiplier_init();
	engine1=max_load(kernel3,"*");
	printf("Multiplication\n");
	Multiplier_actions_t action3;
	action3.instream_x=x;
	action3.instream_y=y;
	action3.outstream_s=z;
	action3.param_N=size;
	Multiplier_run(engine1,&action3);
	printf("z: ");
	for(int i=0;i<size;i++) printf("%d ",z[i]);
	max_unload(engine1);
	printf("\n");
	Multiplier_free();

	return 0;
}
/*
 * This function demonstrates running a design with 3 Kernels and Manager routing blocks. On every run, we select which inputs of the multiplexers and outputs of the
 * demultiplexers are used. We use kernels for addition, subtraction and multiplication, and in every run, we choose on of these 3 operations.
 */

int chainedKernelsRun(){
	int32_t size=16;
	int32_t *x=calloc(size,size*sizeof(int32_t));//Array of the first operands
	int32_t *y=calloc(size, sizeof(int32_t));//Array of the second operands
	int32_t *z=calloc(size, sizeof(int32_t));//Array of the results.


	for(int i=0;i<size;i++){
		x[i]=i; //Initialization
		y[i]=i+1;
	}
	printf("x: ");
	for(int i=0;i<size;i++)printf("%d ",x[i]);
	printf("\n");
	printf("y: ");
	for(int i=0;i<size;i++)printf("%d ",y[i]);
	printf("\nAddition\n");

	//Running addition. With routing string, we route inputs to the addition kernel and route output from the addition kernel to the CPU.
	MultipleKernels(size,x,y,z,"x_add->demuxX,y_add->demuxY,res_add->muxRes");
	printf("z: ");
	for(int i=0;i<size;i++)printf("%d ",z[i]);
	printf("\nSubtraction\n");

	//Running addition. With routing string, we route inputs to the subtraction kernel and route output from the subtraction kernel to the CPU.
	MultipleKernels(size,x,y,z,"x_sub->demuxX,y_sub->demuxY,res_sub->muxRes");
	printf("z: ");
	for(int i=0;i<size;i++)printf("%d ",z[i]);
	printf("\nMultiplication\n");


	//Running addition. With routing string, we route inputs to the multiplication kernel and route output from the multiplication kernel to the CPU.
	MultipleKernels(size,x,y,z,"x_mul->demuxX,y_mul->demuxY,res_mul->muxRes");
	printf("z: ");
	for(int i=0;i<size;i++)printf("%d ",z[i]);
	printf("\n");

	return 0;
}
int main(){
	printf("===============RUN1==============\n");
	int ret = twoKernelsRun();
	if (ret != 0) return ret;
	printf("===============RUN2==============\n");
	return chainedKernelsRun();
}
