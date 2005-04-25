#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;


ViStatus viGetAttribute (ViObject vi, ViAttr attrName, void _VI_PTR attrValue)
{

ViInt16* Int16P;
ViString StringP;
ViUInt16* UInt16P;
ViUInt32* UInt32P;
ViUInt8* UInt8P;
ViBoolean* BooleanP;
ViVersion* VersionP;
ViAccessMode* AccessModeP;
ViSession* SessionP;
ResourceRecord* r=NULL;
	
	r=LookForResource(vi);
	if(r!=NULL)
	{
		printf("lo he encontrado!\n");
		switch (attrName) 
		{
				//Template Attributes
			case VI_ATTR_RSRC_IMPL_VERSION:// RO Global  0h to FFFFFFFFh 
			{
				VersionP=(ViVersion *) attrValue;
				*VersionP=r->i->vi_attr_RSRC_IMPL_VERSION;
				return VI_SUCCESS;						
			}
	    	case VI_ATTR_RSRC_LOCK_STATE:// RO Global  VI_NO_LOCK VI_EXCLUSIVE_LOCK VI_SHARED_LOCK 
			{
				AccessModeP=(ViVersion *) attrValue;
				*AccessModeP=r->i->vi_attr_RSRC_IMPL_VERSION;
				return VI_SUCCESS;						
			}
			case VI_ATTR_RSRC_MANF_ID:// RO Global  0h to 3FFFh 
			{
				UInt16P=(ViUInt16 *) attrValue;
				*UInt16P=r->i->vi_attr_RSRC_MANF_ID;
				return VI_SUCCESS;
			}	
			case VI_ATTR_RSRC_MANF_NAME:// RO Global  N/A 
			{
				//aqui hay q hacer un string copy
				//pa luego
			}
			case VI_ATTR_RSRC_NAME:// RO Global  N/A 
			{
				//aqui hay q hacer un string copy
				//pa luego
			}
			case VI_ATTR_RSRC_SPEC_VERSION:// RO Global  00200200h 
			{
				VersionP=(ViVersion *) attrValue;
				*VersionP=r->i->vi_attr_RSRC_SPEC_VERSION;
				return VI_SUCCESS;						
			}
			case VI_ATTR_RM_SESSION:// RO Local  N/A 
			{
				SessionP=(ViSession *) attrValue;
				*SessionP=r->i->vi_attr_RM_SESSION;
				return VI_SUCCESS;						
			}
			case VI_ATTR_MAX_QUEUE_LENGTH:// R/W* Local  1h to FFFFFFFFh 
			{
				UInt32P=(ViUInt32 *) attrValue;
				*UInt32P=r->i->vi_attr_MAX_QUEUE_LENGTH;
				return VI_SUCCESS;			
			}
			case VI_ATTR_RSRC_CLASS:// RO Global  N/A 
			{
				//aqui hay q hacer un string copy
				//pa luego
			}
			case VI_ATTR_USER_DATA:// R/W Local  **
			{
				//aqui hay q hacer un string copy
				//pa luego
			}
		
			//atributos generales
			case VI_ATTR_INTF_NUM://(RO)//0 to FFFFh
			{
				UInt16P=(ViUInt16 *) attrValue;
				*UInt16P=r->i->vi_attr_INTF_NUM;
				return VI_SUCCESS;
			}
			case VI_ATTR_INTF_TYPE://(RO)//VI_INTF_VXI VI_INTF_GPIB VI_INTF_GPIB_VXI VI_INTF_ASRL VI_INTF_TCPIP
			{
				UInt16P=(ViUInt16 *) attrValue;
				*UInt16P=r->i->vi_attr_INTF_TYPE;
				return VI_SUCCESS;
			}
			case VI_ATTR_INTF_INST_NAME://(RO)//N/A
			{
				StringP=(ViString) attrValue;
				strcpy(StringP,r->i->vi_attr_INTF_INST_NAME);
				return VI_SUCCESS;
			}
			case VI_ATTR_IO_PROT://(R/W) //VI_NORMAL VI_FDC VI_HS488 VI_PROT_4882_STRS
			{
				
				UInt16P=(ViUInt16 *) attrValue;
				*UInt16P=r->i->vi_attr_IO_PROT;
				return VI_SUCCESS;						
			}
			case VI_ATTR_RD_BUF_OPER_MODE://(R/W) //VI_FLUSH_ON_ACCESS VI_FLUSH_DISABLE
			{
				UInt16P=(ViUInt16 *) attrValue;
				*UInt16P=r->i->vi_attr_RD_BUF_OPER_MODE;
				return VI_SUCCESS;						
			}
			case VI_ATTR_SEND_END_EN://(R/W) //VI_TRUE VI_FALSE
			{
				BooleanP=(ViBoolean *) attrValue;
				*BooleanP=r->i->vi_attr_SEND_END_EN;
				return VI_SUCCESS;						
			}
			case VI_ATTR_SUPPRESS_END_EN://(R/W) //VI_TRUE VI_FALSE
			{
				BooleanP=(ViBoolean *) attrValue;
				*BooleanP=r->i->vi_attr_SUPPRESS_END_EN;
				return VI_SUCCESS;						
			}
			case VI_ATTR_TERMCHAR://(R/W) //0 to FFh
			{
				UInt8P=(ViUInt8 *) attrValue;
				*UInt8P=r->i->vi_attr_TERMCHAR;
				return(VI_SUCCESS);
			}
			case VI_ATTR_TERMCHAR_EN://(R/W) //VI_TRUE VI_FALSE
			{
				BooleanP=(ViBoolean *) attrValue;
				*BooleanP=r->i->vi_attr_TERMCHAR_EN;
				return VI_SUCCESS;						
			}
			case VI_ATTR_TMO_VALUE://(R/W) //VI_TMO_IMMEDIATE 1 to FFFFFFFEh VI_TMO_INFINITE
			{
				UInt32P=(ViUInt32 *) attrValue;
				*UInt32P=r->i->vi_attr_TMO_VALUE;
				return(VI_SUCCESS);
			}
			case VI_ATTR_TRIG_ID://(R/W*) //VI_TRIG_SW; VI_TRIG_TTL0 to VI_TRIG_TTL7; VI_TRIG_ECL0 to VI_TRIG_ECL1
			{
				Int16P=(ViInt16 *) attrValue;
				*Int16P=r->i->vi_attr_TRIG_ID;
				return VI_SUCCESS;
			}
			case VI_ATTR_WR_BUF_OPER_MODE://(R/W) //VI_FLUSH_ON_ACCESS VI_FLUSH_WHEN_FULL
			{
				UInt16P=(ViUInt16 *) attrValue;
				*UInt16P=r->i->vi_attr_WR_BUF_OPER_MODE;
				return VI_SUCCESS;						
			}
			case VI_ATTR_DMA_ALLOW_EN://(R/W) //VI_TRUE VI_FALSE
			{
				BooleanP=(ViBoolean *) attrValue;
				*BooleanP=r->i->vi_attr_DMA_ALLOW_EN;
				return VI_SUCCESS;						
			}
			case VI_ATTR_FILE_APPEND_EN://(R/W) //VI_TRUE VI_FALSE
			{
				BooleanP=(ViBoolean *) attrValue;
				*BooleanP=r->i->vi_attr_FILE_APPEND_EN;
				return VI_SUCCESS;						
			}
			
			//atributos para el puerto serie
			//ASRL Specific INSTR Resource Attributes
			case VI_ATTR_ASRL_AVAIL_NUM://(RO) //0 to FFFFFFFFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt32P=(ViUInt32 *) attrValue;
					*UInt32P=r->i->vi_attr_ASRL_AVAIL_NUM;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_BAUD://(R/W) //0 to FFFFFFFFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt32P=(ViUInt32 *) attrValue;
					*UInt32P=r->i->vi_attr_ASRL_BAUD;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_DATA_BITS:// (R/W) //5 to 8
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_ASRL_DATA_BITS;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_PARITY://(R/W) //VI_ASRL_PAR_NONE VI_ASRL_PAR_ODD VI_ASRL_PAR_EVEN VI_ASRL_PAR_MARK VI_ASRL_PAR_SPACE
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_ASRL_PARITY;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_STOP_BITS://(R/W) //VI_ASRL_STOP_ONE VI_ASRL_STOP_ONE5 VI_ASRL_STOP_TWO
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_ASRL_STOP_BITS;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_FLOW_CNTRL://(R/W) //VI_ASRL_FLOW_NONE VI_ASRL_FLOW_XON_XOFF VI_ASRL_FLOW_RTS_CTS VI_ASRL_FLOW_DTR_DSR
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_ASRL_FLOW_CNTRL;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_END_IN://(R/W) //VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_ASRL_END_IN;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
				case VI_ATTR_ASRL_END_OUT://(R/W) //VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR VI_ASRL_END_BREAK
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_ASRL_END_OUT;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_CTS_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=r->i->vi_attr_ASRL_CTS_STATE;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_DCD_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=r->i->vi_attr_ASRL_DCD_STATE;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_DSR_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=r->i->vi_attr_ASRL_DSR_STATE;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_DTR_STATE://(R/W) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=r->i->vi_attr_ASRL_DTR_STATE;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_RI_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=r->i->vi_attr_ASRL_RI_STATE;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_RTS_STATE://(R/W) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=r->i->vi_attr_ASRL_RTS_STATE;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_REPLACE_CHAR://(R/W) //0 to FFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt8P=(ViUInt8 *) attrValue;
					*UInt8P=r->i->vi_attr_ASRL_REPLACE_CHAR;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_XON_CHAR://(R/W) //0 to FFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt8P=(ViUInt8 *) attrValue;
					*UInt8P=r->i->vi_attr_ASRL_XON_CHAR;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_XOFF_CHAR://(R/W) //0 to FFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					UInt8P=(ViUInt8 *) attrValue;
					*UInt8P=r->i->vi_attr_ASRL_XOFF_CHAR;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			//GPIB and GPIB-VXI Specific INSTR Resource Attributes
			 
			case VI_ATTR_GPIB_PRIMARY_ADDR:// RO Global  0 to 30 
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_GPIB_PRIMARY_ADDR;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			case VI_ATTR_GPIB_SECONDARY_ADDR:// RO Global  0 to 31, VI_NO_SEC_ADDR 
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=r->i->vi_attr_GPIB_SECONDARY_ADDR;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			case VI_ATTR_GPIB_READDR_EN:// R/W Local  VI_TRUE VI_FALSE 
			{
				BooleanP=(ViBoolean *) attrValue;
				*BooleanP=r->i->vi_attr_GPIB_READDR_EN;
				return VI_SUCCESS;						
			}

			case VI_ATTR_GPIB_UNADDR_EN:// R/W Local  VI_TRUE VI_FALSE 
			{
				BooleanP=(ViBoolean *) attrValue;
				*BooleanP=r->i->vi_attr_GPIB_UNADDR_EN;
				return VI_SUCCESS;						
			}
			case VI_ATTR_GPIB_REN_STATE:// RO Global  VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=r->i->vi_attr_GPIB_REN_STATE;
					return VI_SUCCESS;						
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			
			
			
			default:
				return VI_ERROR_NSUP_ATTR;
		}
			
	}
	else
		return VI_ERROR_INV_SESSION;
}
