#include "visa.h"
#include "common.h"

extern InstrRecord *InstrList;

extern int InstrsCount;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;



ViStatus viOpenDefaultRM(ViPSession vi)
{
	int i=0;
	//only this for the momment
	if (vi!=VI_NULL) 
	{
		*vi=0;
		if (DefaultRMFirst==VI_TRUE) 
		{
			InstrList=(InstrRecord *) malloc(sizeof(InstrRecord)*MAX_INSTRUMENTS);
			memset(InstrList,0,sizeof(InstrRecord)*MAX_INSTRUMENTS);
			for (i=0;i<MAX_INSTRUMENTS;i++)
			{
				InstrList[i].vi=-1;
				InstrList[i].i=VI_NULL;
			}
			InstrsCount=0;
			SessionsCount=0;
			DefaultRMFirst=VI_FALSE;
		}	
		return VI_SUCCESS;
	}
	else
		return VI_ERROR_SYSTEM_ERROR;
}
