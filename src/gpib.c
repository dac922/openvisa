//serial port linux access
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;


void GPIBInitDefault(Instr* a,ViString name)
{
	//Visa Specs Apendix A: required attributes
	//general
	a->vi_attr_INTF_TYPE=VI_INTF_GPIB;
	a->vi_attr_INTF_INST_NAME=strdup(name);
	//INSTR Resource Attributes (GPIB and GPIB-VXI Specific)
	a->vi_attr_GPIB_READDR_EN=VI_TRUE;
	a->vi_attr_GPIB_UNADDR_EN=VI_FALSE;
	
	
}
