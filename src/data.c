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

ResourceRecord* LookForResource(ViSession vi)
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

ViBoolean ExistsInstrument(ViString name)
{
	ResourceRecord* r=NULL;
	
	r=ResourceList;
	while(r!=NULL)
	{
		if(CompareString(r->i->vi_attr_INTF_INST_NAME,name))
			return VI_TRUE;
		else
			r=r->Next;
	}
	if (r==NULL) return VI_FALSE;
}

void FreeInstrument(ViStatus vi)
{
	ResourceRecord* r=NULL;
	ResourceRecord** ant=NULL;
	r=ResourceList;
	ant=&ResourceList;

	while(r!=NULL)
	{
		if(r->vi==vi)
		{
			//hacemos un salto en la lista
			*ant=r->Next;
			//aqui hay q hacer un free
			free(r);
			
			break;
		}
		else
		{
			ant=&(r->Next);
			r=r->Next;
		}
	}
}

void FreeDefaultResourceManager(ViStatus vi)
{
	ResourceRecord* r=NULL;
	ResourceRecord** ant=NULL;
	r=ResourceList;
	ant=&ResourceList;

	while(r!=NULL)
	{
		if(r->i->vi_attr_INTF_NUM==vi)
		{
			//hacemos un salto en la lista
			*ant=r->Next;
			//aqui hay q hacer un free
			free(r);
			
			break;
		}
		else
		{
			ant=&r;
			r=r->Next;
		}
	}
	
}

void ShowSessions()
{
	ResourceRecord* r=NULL;
	
	r=ResourceList;
	printf("Session\tDRM\n");
	while(r!=NULL)
	{
		printf("%d\t%d\n",r->vi,r->i->vi_attr_RM_SESSION);
		r=r->Next;
	}
	
}


void InitDefault(Instr* a)
{
	//Visa Specs Apendix A: required attributes
	//Resource template attributes
	a->vi_attr_RSRC_SPEC_VERSION=0x00200200;
	a->vi_attr_MAX_QUEUE_LENGTH=50;
	a->vi_attr_RSRC_LOCK_STATE=VI_NO_LOCK;
};


void INSTRInitDefault(Instr* a)
{
	//INSTR Resource Attributes (Generic)
	a->vi_attr_IO_PROT=VI_NORMAL;
	a->vi_attr_SEND_END_EN=VI_TRUE;
	a->vi_attr_SUPPRESS_END_EN=VI_FALSE;
	a->vi_attr_TERMCHAR=0x0A; //(linefeed)
	a->vi_attr_TERMCHAR_EN=VI_FALSE;
	a->vi_attr_TMO_VALUE=2000;
	a->vi_attr_INTF_NUM=0;
	a->vi_attr_TRIG_ID=VI_TRIG_SW;
	a->vi_attr_RD_BUF_OPER_MODE=VI_FLUSH_DISABLE;
	a->vi_attr_WR_BUF_OPER_MODE=VI_FLUSH_WHEN_FULL;
	a->vi_attr_FILE_APPEND_EN=VI_FALSE;
};
