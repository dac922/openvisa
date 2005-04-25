#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;

ViStatus viClose(ViObject vi)
{
	ResourceRecord* r;
	//ViObject=ViSession or ViEvent or ViFindList
	//for now only visession
	r=LookForResource(vi);
	if (r!=NULL)
	{
		if(CompareString(r->i->vi_attr_INTF_INST_NAME,"DRM")==VI_TRUE)
		{
			FreeInstrument(vi);
			printf("es un drm, deberiamos cerrar todo lo relacionado\n");
			return VI_SUCCESS;
		}
		else
		{
			FreeInstrument(vi);
			printf("no es un drm, solo cerramos el instrumento\n");
			return VI_SUCCESS;
		}
	}
	else
		return VI_ERROR_INV_SESSION;
}
