#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;


ViStatus viRead(ViSession vi,ViPBuf buf,ViUInt32 cnt,ViPUInt32 retcnt)
{
	ssize_t numbytes;
	int i=0;
	ResourceRecord *r;
	
	if(r=LookForResource(vi)!=VI_NULL)
	{
		if (r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
		{
			numbytes= read(r->fd,buf,cnt);			
			*retcnt=numbytes;
			if (numbytes==cnt) return VI_SUCCESS;
			return VI_ERROR_BERR;	
		}
		return VI_ERROR_NSUP_OPER;
 	}
	else
		return VI_ERROR_INV_SESSION;
}
