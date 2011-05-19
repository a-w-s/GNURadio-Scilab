
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <slab_sbhs_scilab.h>
#include <gr_io_signature.h>
#include "stack-c.h"
#include "call_scilab.h"
#include "api_scilab.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

slab_sbhs_scilab_sptr 
slab_make_sbhs_scilab (char* filename,int fan_speed,int heater_temperature)
{
  return slab_sbhs_scilab_sptr (new slab_sbhs_scilab (filename,fan_speed,heater_temperature));  
}

void slab_sbhs_scilab::set_fan_speed(int fan_speed)
{
	char buffer[100];
	d_fan_speed=fan_speed;
	SendScilabJob("writeserial(handl,ascii(253));");
	sprintf(buffer,"FAN=%d",d_fan_speed);
	SendScilabJob(buffer);
	SendScilabJob("writeserial(handl,ascii(FAN));");
}

void slab_sbhs_scilab::set_heater_temperature(int heater_temperature)
{
	char buffer[100];
	d_heater_temperature=heater_temperature;

	SendScilabJob("writeserial(handl,ascii(254));");
	sprintf(buffer,"HEATER=%d",d_heater_temperature);
	SendScilabJob(buffer);
	SendScilabJob("writeserial(handl,ascii(HEATER));");
}



float slab_sbhs_scilab::get_scilab(char *var)
{
	int rowA_ = 0,colA_ = 0,lp = 0;
	int i = 0, j = 0;
	double *matrixOfDouble = NULL;
	float ret;

	char *variableToBeRetrieved=var;
	SciErr sciErr;

	/* First, retrieve the size of the matrix */
	sciErr = readNamedMatrixOfDouble(pvApiCtx, variableToBeRetrieved, &rowA_, &colA_, NULL);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
	}

	/* Alloc the memory */
	matrixOfDouble=(double*)malloc((rowA_*colA_)*sizeof(double));

	/* Load the matrix */
	sciErr = readNamedMatrixOfDouble(pvApiCtx, variableToBeRetrieved, &rowA_, &colA_, matrixOfDouble);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
	}
	
	ret=(float)matrixOfDouble[0];		
	
	if (matrixOfDouble) 
	{
		free(matrixOfDouble);
		matrixOfDouble=NULL;
	}
	return ret;
}

void slab_sbhs_scilab::python_sleep()
{	
	FILE *fp=fopen("sleeper.py","w");
	fprintf(fp,"%s","#/usr/bin/env python\n");
	fprintf(fp,"%s","import time \n");
	fprintf(fp,"%s","time.sleep(0.05) \n");
	fclose(fp);

	system("python sleeper.py");
}


static const int MIN_IN = 0;	// mininum number of input streams
static const int MAX_IN = 0;	// maximum number of input streams
static const int MIN_OUT = 1;	// minimum number of output streams
static const int MAX_OUT = 1;	// maximum number of output streams

slab_sbhs_scilab::slab_sbhs_scilab (char* filename,int fan_speed,int heater_temperature)
  : gr_block ("sbhs_scilab",
		   gr_make_io_signature (MIN_IN, MAX_IN, 0),
		   gr_make_io_signature (MIN_OUT, MAX_OUT, sizeof(float)))
{
	strcpy(d_filename,filename);
	if ( StartScilab(getenv("SCI"),NULL,NULL) == FALSE )
	{
		printf("Error while calling StartScilab\n");
		exit(0);
	}
	else
	{
		printf("Scilab Started\n");
	}

	char cd[100],path[100];	
	char file[100];
	int i;

	strcpy(cd,"cd ");

	char *str=strrchr(d_filename,'/');
		
	for(i=0;i<str-d_filename;i++)
	{
		path[i]=d_filename[i];
	}
	path[i]='\0';

	strcat(cd,path);

	SendScilabJob(cd);

	SendScilabJob("exec ser_init.sce");
	set_fan_speed(fan_speed);
	set_heater_temperature(heater_temperature);
	
	
}

slab_sbhs_scilab::~slab_sbhs_scilab ()
{
  if ( TerminateScilab(NULL) == FALSE ) 
	{
  	printf("Error while calling TerminateScilab\n");
  	}	
	else
	{
		printf("Scilab Connection Terminated\n");
	}
}

int 
slab_sbhs_scilab::general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items)
{
	float *out = (float *) output_items[0];
	int DONE=1;
	float temp1,temp2,temp;

	python_sleep();
	
	while(DONE)
	{	
		
		SendScilabJob("writeserial(handl,ascii(255));");
		SendScilabJob("TEMP = ascii(readserial(handl));");
		SendScilabJob("TEMP1=TEMP(1)");
		SendScilabJob("TEMP2=TEMP(2)");			
					
		temp1=get_scilab("TEMP1");
		temp2=get_scilab("TEMP2");
	
		if(temp1>9 && temp2<10)
		{		
			temp=temp1+0.1*temp2;
			printf("Value from Scilab [%.1f]\n",temp);	
			out[0]=(float)temp;
			DONE=0;			
		}
	}
	consume_each(1);
	return 1;
}

