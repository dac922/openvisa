#include <stdio.h>
#include "visa.h"

int main()
{
	ViSession v;
	ViStatus status;
	ViSession a;
	char desc[50]="k2k2k2k2";

	//little tests	
	status=viOpenDefaultRM(&v);
	viStatusDesc(0,status,desc);
	printf("%s-sesion abierta:%d\n",desc,v);
	ShowSessions();
	
	status=viClose(v);
	viStatusDesc(0,status,desc);
	printf("%s-sesion cerrada?:%d\n",desc,v);
	ShowSessions();
	
	status=viOpenDefaultRM(&v);
	viStatusDesc(0,status,desc);
	printf("%s-sesion abierta:%d\n",desc,v);
	ShowSessions();
	
	
	status=viOpen(v,"ASRL1",VI_LOAD_CONFIG,VI_NULL,&a);
	viStatusDesc(0,status,desc);
	printf("%s-sesion abierta:%d\n",desc,a);
	ShowSessions();
	
	status=viClose(a);
	viStatusDesc(0,status,desc);
	printf("%s-sesion cerrada?:%d\n",desc,a);
	ShowSessions();
	
	status=viOpen(v,"ASRL2",VI_LOAD_CONFIG,VI_NULL,&a);
	viStatusDesc(0,status,desc);
	printf("%s-sesion abierta:%d\n",desc,a);
	ShowSessions();
	
	status=viOpen(v,"ASRL1",VI_LOAD_CONFIG,VI_NULL,&a);
	viStatusDesc(0,status,desc);
	printf("%s-sesion abierta:%d\n",desc,a);
	ShowSessions();
	
	status=viSetAttribute(1,VI_ATTR_ASRL_PARITY,VI_ASRL_PAR_NONE);
	viStatusDesc(0,status,desc);
	printf("%s-resultado:%d\n",desc,status);
	
	status=viSetAttribute(2,VI_ATTR_ASRL_PARITY,VI_ASRL_PAR_NONE);
	viStatusDesc(0,status,desc);
	printf("%s-resultado:%d\n",desc,status);
	
	status=viSetAttribute(3,VI_ATTR_ASRL_PARITY,VI_ASRL_PAR_NONE);
	viStatusDesc(0,status,desc);
	printf("%s-resultado:%d\n",desc,status);
	
		
	
	char nombre[20];
	status=viGetAttribute(5,VI_ATTR_INTF_INST_NAME,nombre);
	viStatusDesc(0,status,desc);
	printf("%s: nombre:%s\n",desc,nombre);
	
	
	return (0);
}
