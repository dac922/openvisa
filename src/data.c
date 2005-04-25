#include "visa.h"
#include "common.h"
//---------------------------------
//common variables for the library
//---------------------------------






InstrRecord *InstrList; //List of registered instruments 

int InstrsCount=0; //numer of instruments
int SessionsCount=0; //number of sessions
ViBoolean DefaultRMFirst=VI_TRUE; //first time the ressource manager is called?
