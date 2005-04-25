//---------------------------------
// auxiliar functions
//---------------------------------


#include "visa.h"
#include "common.h"

ViBoolean CompareString (char * stringtocompare, char* string)
{
	if (strncasecmp(stringtocompare,string,strlen(string))==0) return VI_TRUE;
	return VI_FALSE;
}
