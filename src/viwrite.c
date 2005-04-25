#include "visa.h"
#include "common.h"

extern InstrRecord *InstrList;

extern int InstrsCount;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;


ViStatus viWrite(ViSession vi,ViBuf buf,ViUInt32 cnt,ViPUInt32 retCnt)
{
	ssize_t numbytes;
	int i=0;
	for(i=0;i<InstrsCount;i++) 
	{
		if (InstrList[i].vi==vi)
		{
			if (InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
			{
				numbytes= write(InstrList[i].fd,buf,cnt);			
				*retCnt=numbytes;
				if (numbytes==cnt) return VI_SUCCESS;
				return VI_ERROR_BERR;	
			}
			return VI_ERROR_NSUP_OPER;
		}
		
	}
	return VI_ERROR_INV_SESSION;
	
}
