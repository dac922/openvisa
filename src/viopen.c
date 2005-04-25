#include "visa.h"
#include "common.h"

extern InstrRecord *InstrList;

extern int InstrsCount;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;


ViStatus viOpen(ViSession sesn,ViRsrc name, ViAccessMode mode,ViUInt32 timeout,ViPSession vi)
{
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
		printf("Want to open serial\n");
		if ((name[4]>='1') && (name[4]<='4'))
		{
			SessionsCount++;
			*vi=SessionsCount; 
			for(i=0;i<MAX_INSTRUMENTS;i++) //looking for a register for us
				if ((InstrList[i].i==VI_NULL)&&(InstrList[i].vi==-1))
					{
						InstrList[i].vi=*vi;
						InstrList[i].i=(Instr *)malloc(sizeof(Instr));
						AsrlInit(InstrList[i].i,name);
						InstrsCount++;
			
						//try to open serial port
						return OpenSerialPort(MODEMDEVICE1,i);
		
					}
			return 24;//look for this error 
				
				
			
		}		
		else
			return VI_ERROR_INV_RSRC_NAME;	
		
	}
		
	
	
	
}
