#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;

ViStatus viOpen(ViSession sesn,ViRsrc name, ViAccessMode mode,ViUInt32 timeout,ViPSession vi)
{
	ResourceRecord *r;
	int i=0;
	//check session
	if (sesn!=0) return VI_ERROR_INV_SESSION;
	//check access mode: missing implementation
	if (mode!=VI_LOAD_CONFIG) return VI_ERROR_INV_ACC_MODE;
	//timeout
	
	
	//check name of the instrument
	if (CompareString(name,"ASRL")!=VI_TRUE)
	{
		printf("invalid device\n");
		return VI_ERROR_INV_RSRC_NAME;
	}
	else
	{
		printf("We want to open serial\n");
		if ((name[4]>='1') && (name[4]<='4'))
		{
			
			*vi=SessionsCount; 
			r=NewResource(*vi);
			r->i=NewInstrument();
			AsrlInit(r->i,name);
			RecordNewResource(r);
			SessionsCount++;
			//try to open serial port
			return OpenSerialPort(MODEMDEVICE1,i);
		
		} 
		else
			return VI_ERROR_INV_RSRC_NAME;	
		
	}
		
	
	
	
}
