#include "visa.h"
#include "common.h"

extern InstrRecord *InstrList;

extern int InstrsCount;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;


ViStatus viGetAttribute (ViObject vi, ViAttr attrName, void _VI_PTR attrValue)
{

ViInt16* Int16P;
ViString StringP;
ViUInt16* UInt16P;
ViUInt32* UInt32P;
ViUInt8* UInt8P;
ViBoolean* ViBoolP;
int i=0;	

	for (i=0;i<SessionsCount;i++)
	{
		if (InstrList[i].vi==vi)
		{
			printf("lo he encontrado!\n");
			switch (attrName) 
			{
				
				//atributos generales
				case VI_ATTR_INTF_NUM://(RO)//0 to FFFFh
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=InstrList[i].i->vi_attr_INTF_NUM;
					return VI_SUCCESS;
				}
				case VI_ATTR_INTF_TYPE://(RO)//VI_INTF_VXI VI_INTF_GPIB VI_INTF_GPIB_VXI VI_INTF_ASRL VI_INTF_TCPIP
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=InstrList[i].i->vi_attr_INTF_TYPE;
					return VI_SUCCESS;
				}
				case VI_ATTR_INTF_INST_NAME://(RO)//N/A
				{
					StringP=(ViString) attrValue;
					strcpy(StringP,InstrList[i].i->vi_attr_INTF_INST_NAME);
					return VI_SUCCESS;
				}
				case VI_ATTR_IO_PROT://(R/W) //VI_NORMAL VI_FDC VI_HS488 VI_PROT_4882_STRS
				{
					
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=InstrList[i].i->vi_attr_IO_PROT;
					return VI_SUCCESS;						
				}
				case VI_ATTR_RD_BUF_OPER_MODE://(R/W) //VI_FLUSH_ON_ACCESS VI_FLUSH_DISABLE
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=InstrList[i].i->vi_attr_RD_BUF_OPER_MODE;
					return VI_SUCCESS;						
				}
				case VI_ATTR_SEND_END_EN://(R/W) //VI_TRUE VI_FALSE
				{
					ViBoolP=(ViBoolean *) attrValue;
					*ViBoolP=InstrList[i].i->vi_attr_SEND_END_EN;
					return VI_SUCCESS;						
				}
				case VI_ATTR_SUPPRESS_END_EN://(R/W) //VI_TRUE VI_FALSE
				{
					ViBoolP=(ViBoolean *) attrValue;
					*ViBoolP=InstrList[i].i->vi_attr_SUPPRESS_END_EN;
					return VI_SUCCESS;						
				}
				case VI_ATTR_TERMCHAR://(R/W) //0 to FFh
				{
					UInt8P=(ViUInt8 *) attrValue;
					*UInt8P=InstrList[i].i->vi_attr_TERMCHAR;
					return(VI_SUCCESS);
				}
				case VI_ATTR_TERMCHAR_EN://(R/W) //VI_TRUE VI_FALSE
				{
					ViBoolP=(ViBoolean *) attrValue;
					*ViBoolP=InstrList[i].i->vi_attr_TERMCHAR_EN;
					return VI_SUCCESS;						
				}
				case VI_ATTR_TMO_VALUE://(R/W) //VI_TMO_IMMEDIATE 1 to FFFFFFFEh VI_TMO_INFINITE
				{
					UInt32P=(ViUInt32 *) attrValue;
					*UInt32P=InstrList[i].i->vi_attr_TMO_VALUE;
					return(VI_SUCCESS);
				}
				case VI_ATTR_TRIG_ID://(R/W*) //VI_TRIG_SW; VI_TRIG_TTL0 to VI_TRIG_TTL7; VI_TRIG_ECL0 to VI_TRIG_ECL1
				{
					Int16P=(ViInt16 *) attrValue;
					*Int16P=InstrList[i].i->vi_attr_TRIG_ID;
					return VI_SUCCESS;
				}
				case VI_ATTR_WR_BUF_OPER_MODE://(R/W) //VI_FLUSH_ON_ACCESS VI_FLUSH_WHEN_FULL
				{
					UInt16P=(ViUInt16 *) attrValue;
					*UInt16P=InstrList[i].i->vi_attr_WR_BUF_OPER_MODE;
					return VI_SUCCESS;						
				}
				case VI_ATTR_DMA_ALLOW_EN://(R/W) //VI_TRUE VI_FALSE
				{
					ViBoolP=(ViBoolean *) attrValue;
					*ViBoolP=InstrList[i].i->vi_attr_DMA_ALLOW_EN;
					return VI_SUCCESS;						
				}
				case VI_ATTR_FILE_APPEND_EN://(R/W) //VI_TRUE VI_FALSE
				{
					ViBoolP=(ViBoolean *) attrValue;
					*ViBoolP=InstrList[i].i->vi_attr_FILE_APPEND_EN;
					return VI_SUCCESS;						
				}
				
				//atributos para el puerto serie
				//ASRL Specific INSTR Resource Attributes
				case VI_ATTR_ASRL_AVAIL_NUM://(RO) //0 to FFFFFFFFh
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt32P=(ViUInt32 *) attrValue;
						*UInt32P=InstrList[i].i->vi_attr_ASRL_AVAIL_NUM;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_BAUD://(R/W) //0 to FFFFFFFFh
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt32P=(ViUInt32 *) attrValue;
						*UInt32P=InstrList[i].i->vi_attr_ASRL_BAUD;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_DATA_BITS:// (R/W) //5 to 8
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt16P=(ViUInt16 *) attrValue;
						*UInt16P=InstrList[i].i->vi_attr_ASRL_DATA_BITS;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_PARITY://(R/W) //VI_ASRL_PAR_NONE VI_ASRL_PAR_ODD VI_ASRL_PAR_EVEN VI_ASRL_PAR_MARK VI_ASRL_PAR_SPACE
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt16P=(ViUInt16 *) attrValue;
						*UInt16P=InstrList[i].i->vi_attr_ASRL_PARITY;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_STOP_BITS://(R/W) //VI_ASRL_STOP_ONE VI_ASRL_STOP_ONE5 VI_ASRL_STOP_TWO
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt16P=(ViUInt16 *) attrValue;
						*UInt16P=InstrList[i].i->vi_attr_ASRL_STOP_BITS;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_FLOW_CNTRL://(R/W) //VI_ASRL_FLOW_NONE VI_ASRL_FLOW_XON_XOFF VI_ASRL_FLOW_RTS_CTS VI_ASRL_FLOW_DTR_DSR
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt16P=(ViUInt16 *) attrValue;
						*UInt16P=InstrList[i].i->vi_attr_ASRL_FLOW_CNTRL;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_END_IN://(R/W) //VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt16P=(ViUInt16 *) attrValue;
						*UInt16P=InstrList[i].i->vi_attr_ASRL_END_IN;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}

				case VI_ATTR_ASRL_END_OUT://(R/W) //VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR VI_ASRL_END_BREAK
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt16P=(ViUInt16 *) attrValue;
						*UInt16P=InstrList[i].i->vi_attr_ASRL_END_OUT;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_CTS_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						Int16P=(ViInt16 *) attrValue;
						*Int16P=InstrList[i].i->vi_attr_ASRL_CTS_STATE;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_DCD_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						Int16P=(ViInt16 *) attrValue;
						*Int16P=InstrList[i].i->vi_attr_ASRL_DCD_STATE;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_DSR_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						Int16P=(ViInt16 *) attrValue;
						*Int16P=InstrList[i].i->vi_attr_ASRL_DSR_STATE;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_DTR_STATE://(R/W) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						Int16P=(ViInt16 *) attrValue;
						*Int16P=InstrList[i].i->vi_attr_ASRL_DTR_STATE;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_RI_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						Int16P=(ViInt16 *) attrValue;
						*Int16P=InstrList[i].i->vi_attr_ASRL_RI_STATE;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_RTS_STATE://(R/W) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						Int16P=(ViInt16 *) attrValue;
						*Int16P=InstrList[i].i->vi_attr_ASRL_RTS_STATE;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_REPLACE_CHAR://(R/W) //0 to FFh
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt8P=(ViUInt8 *) attrValue;
						*UInt8P=InstrList[i].i->vi_attr_ASRL_REPLACE_CHAR;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_XON_CHAR://(R/W) //0 to FFh
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt8P=(ViUInt8 *) attrValue;
						*UInt8P=InstrList[i].i->vi_attr_ASRL_XON_CHAR;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				case VI_ATTR_ASRL_XOFF_CHAR://(R/W) //0 to FFh
				{
					if(InstrList[i].i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					{
						UInt8P=(ViUInt8 *) attrValue;
						*UInt8P=InstrList[i].i->vi_attr_ASRL_XOFF_CHAR;
						return VI_SUCCESS;						
					}
					else
						return VI_ERROR_NSUP_ATTR;
				}
				default:
					return VI_ERROR_NSUP_ATTR;
			}
				
		}
			
	}
	return VI_ERROR_INV_SESSION;
}
