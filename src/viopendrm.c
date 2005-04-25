#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;



ViStatus viOpenDefaultRM(ViPSession vi)
{
	int i=0;
	ResourceRecord* r;
	//only this for the momment
	if (vi!=VI_NULL) 
	{
		
		if (DefaultRMFirst==VI_TRUE) 
		{
			*vi=0;
			r=NewResource(*vi);
			RecordNewResource(r);
			SessionsCount=1;
			DefaultRMFirst=VI_FALSE;
		}
		else
		{
			*vi=SessionsCount;
			r=NewResource(*vi);
			RecordNewResource(r);
			SessionsCount++;
		}
		return VI_SUCCESS;
	}
	else
		return VI_ERROR_SYSTEM_ERROR;
}
