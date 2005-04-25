#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;

ViStatus viOpen(ViSession sesn,ViRsrc name, ViAccessMode mode,ViUInt32 timeout,ViPSession vi)
{
	ViStatus status;
	ResourceRecord *r;
	
	//check session
	r=LookForResource(sesn);
	if (r==NULL) return VI_ERROR_INV_SESSION;
	if (CompareString(r->i->vi_attr_INTF_INST_NAME,"DRM")==VI_FALSE) return VI_ERROR_INV_SESSION;
		
	//check access mode: missing implementation
	if (mode!=VI_LOAD_CONFIG) return VI_ERROR_INV_ACC_MODE;
	//timeout... missings
	
	
	//check name of the instrument
	if (CompareString(name,"ASRL")==VI_TRUE)
	{
		printf("We want to open serial\n");
		if ((name[4]>=FIRST_SERIAL) && (name[4]<=LAST_SERIAL))
		{
			SessionsCount++;
			*vi=SessionsCount; 
			r=NewResource(*vi);
			r->i=NewInstrument();
			ASRLInitDefault(r->i,name);
			r->i->vi_attr_RM_SESSION=sesn;
			//try to open serial port
			status=VI_SUCCESS;//OpenSerialPort(MODEMDEVICE1,r);
			if(status!=VI_SUCCESS)
			{
				free(r);
				*vi=-1;
				return status;
			}
			RecordNewResource(r);
			
			return VI_SUCCESS;
		
		} 
		else
			return VI_ERROR_INV_RSRC_NAME;	
		
	}
		
	if (CompareString(name,"GPIB")==VI_TRUE)
	{
		printf("We want to open GPIB\n");
		
		SessionsCount++;
		*vi=SessionsCount; 
		r=NewResource(*vi);
		r->i=NewInstrument();
		GPIBInitDefault(r->i,name);
		r->i->vi_attr_RM_SESSION=sesn;
		//try to open gpib
		status=VI_SUCCESS;
		if(status!=VI_SUCCESS)
		{
			free(r);
			*vi=-1;
			return status;
		}
		RecordNewResource(r);
		
		return VI_SUCCESS;
		
	}
	
	
	
	return VI_ERROR_INV_RSRC_NAME;
	
	
}
