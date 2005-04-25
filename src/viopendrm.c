#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;



ViStatus viOpenDefaultRM(ViPSession vi)
{
	int i=0;
	ResourceRecord* r;
	char DRM_Name[50];
	//only this for the momment
	if (vi!=VI_NULL) 
	{
		SessionsCount++;
		*vi=SessionsCount;
		r=NewResource(*vi);
		r->i=NewInstrument();
		
		if (DefaultRMFirst==VI_TRUE) 
		{
			strcpy(DRM_Name,"DRM:0");
			DefaultRMFirst=VI_FALSE;			
		}
		else
		{
			sprintf(DRM_Name,"DRM:%d",*vi);
		}
		r->i->vi_attr_INTF_INST_NAME=(char *) malloc(sizeof(char)*(strlen(DRM_Name)+1));
		strcpy(r->i->vi_attr_INTF_INST_NAME,DRM_Name);
		r->i->vi_attr_RM_SESSION=0;
		RecordNewResource(r);
		return VI_SUCCESS;
	}
	else
		return VI_ERROR_SYSTEM_ERROR;
}
