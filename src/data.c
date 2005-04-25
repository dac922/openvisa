#include "visa.h"
#include "common.h"
//---------------------------------
//common variables for the library
//---------------------------------






ResourceRecord *ResourceList=NULL; //List of registered instruments 
int SessionsCount=0; //number of sessions
ViBoolean DefaultRMFirst=VI_TRUE; //first time the ressource manager is called?

//creates new resource
ResourceRecord* NewResource(ViSession vi)
{
	ResourceRecord* aux;
	
	aux=ResourceList;
	while (aux!=NULL)
	{
		aux=aux->Next;
	}
	//here we have a valid pointer in the list
	aux=(ResourceRecord *) malloc(sizeof(ResourceRecord));
	memset(aux,0,sizeof(ResourceRecord));
	aux->Next=NULL;
	aux->i=NULL;
	aux->vi=vi;
	return aux;
	
}

ResourceRecord* LookForRessource(ViSession vi)
{
	ResourceRecord* r=NULL;
	
	r=ResourceList;
	while(r!=NULL)
	{
		if(r->vi==vi)
			return r;
		else
			r=r->Next;
	}
	return r;
}

Instr* NewInstrument()
{
	Instr* i;
	i=(Instr *)malloc(sizeof(Instr));
	memset(i,0,sizeof(Instr));
	return i;
	
}

void RecordNewResource(ResourceRecord* r)
{
	ResourceRecord* aux=NULL;
	ResourceRecord* ant=NULL;
	aux=ResourceList;
	
	if (ResourceList==NULL)
	{
		ResourceList=r;
	}
	else
	{
		while(aux!=NULL)
		{	
			ant=aux;
			aux=aux->Next;
		}
		ant->Next=r;
	}	
}
