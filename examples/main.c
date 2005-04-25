#include <stdio.h>
#include "visa.h"

int main()
{
	ViSession v;
	ViStatus status;
	ViSession a;

	//little tests	
	status=viOpenDefaultRM(&v);
	printf("%dsesion abierta:%d\n",status,v);
	
	status=viOpen(v,"ASRL1",VI_LOAD_CONFIG,VI_NULL,&a);
	printf("%dsesion abierta:%d\n",status,a);
	
	status=viOpen(v,"ASRL2",VI_LOAD_CONFIG,VI_NULL,&a);
	printf("%dsesion abierta:%d\n",status,a);
	status=viOpen(v,"ASRL1",VI_LOAD_CONFIG,VI_NULL,&a);
	printf("%dsesion abierta:%d\n",status,a);
	
	
	status=viSetAttribute(1,VI_ATTR_ASRL_PARITY,VI_ASRL_PAR_NONE);
	printf("resultado:%d\n",status);
	
	status=viSetAttribute(2,VI_ATTR_ASRL_PARITY,VI_ASRL_PAR_NONE);
	printf("resultado:%d\n",status);
	
	status=viSetAttribute(3,VI_ATTR_ASRL_PARITY,VI_ASRL_PAR_NONE);
	printf("resultado:%d\n",status);
	
		
	
	char nombre[20];
	status=viGetAttribute(3,VI_ATTR_INTF_INST_NAME,nombre);
	printf("%d: nombre:%s\n",status,nombre);
	
	
	return (0);}
