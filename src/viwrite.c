#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;
extern ResourceRecord* LookForRessource(ViSession );


ViStatus viWrite(ViSession vi,ViBuf buf,ViUInt32 cnt,ViPUInt32 retCnt)
{
	ssize_t numbytes;
	ResourceRecord *r;
	
	if(r=LookForResource(vi)!=VI_NULL)
	{
		if (r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
		{
			numbytes= write(r->fd,buf,cnt);			
			*retCnt=numbytes;
			if (numbytes==cnt) return VI_SUCCESS;
			return VI_ERROR_BERR;	
		}
		return VI_ERROR_NSUP_OPER;
				
	}
	else
		return VI_ERROR_INV_SESSION;
	
}
