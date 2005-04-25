#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;


ViStatus viSetAttribute (ViObject vi, ViAttr attrName, ViAttrState attrValue) //(attrstate is uint 32)
{

	ResourceRecord *r=NULL;
	
	r=LookForResource(vi);
	if(r!=NULL)
	{
		switch (attrName) 
		{
			//Template Attributes
			case VI_ATTR_RSRC_IMPL_VERSION:// RO Global  0h to FFFFFFFFh 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
	    	case VI_ATTR_RSRC_LOCK_STATE:// RO Global  VI_NO_LOCK VI_EXCLUSIVE_LOCK VI_SHARED_LOCK 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_RSRC_MANF_ID:// RO Global  0h to 3FFFh 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_RSRC_MANF_NAME:// RO Global  N/A 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_RSRC_NAME:// RO Global  N/A 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_RSRC_SPEC_VERSION:// RO Global  00200200h 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_RM_SESSION:// RO Local  N/A 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_MAX_QUEUE_LENGTH:// R/W* Local  1h to FFFFFFFFh 
			{
				//read only for the moment:will have to change
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_RSRC_CLASS:// RO Global  N/A 
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_USER_DATA:// R/W Local  **
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			
			//atributos generales INSTR
			case VI_ATTR_INTF_NUM://(RO)//0 to FFFFh
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_INTF_TYPE://(RO)//VI_INTF_VXI VI_INTF_GPIB VI_INTF_GPIB_VXI VI_INTF_ASRL VI_INTF_TCPIP
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_INTF_INST_NAME://(RO)//N/A
			{
				return VI_ERROR_ATTR_READONLY;
				break;
			}
			case VI_ATTR_IO_PROT://(R/W) //VI_NORMAL VI_FDC VI_HS488 VI_PROT_4882_STRS
			{
				if ((attrValue!=VI_NORMAL)&&(attrValue!=VI_FDC)&&(attrValue!=VI_HS488)&&(attrValue!=VI_PROT_4882_STRS))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			case VI_ATTR_RD_BUF_OPER_MODE://(R/W) //VI_FLUSH_ON_ACCESS VI_FLUSH_DISABLE
			{
				if ((attrValue!=VI_FLUSH_ON_ACCESS)&&(attrValue!=VI_FLUSH_DISABLE))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			case VI_ATTR_SEND_END_EN://(R/W) //VI_TRUE VI_FALSE
			{
				if ((attrValue!=VI_TRUE)&&(attrValue!=VI_FALSE))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			case VI_ATTR_SUPPRESS_END_EN://(R/W) //VI_TRUE VI_FALSE
			{
				if ((attrValue!=VI_TRUE)&&(attrValue!=VI_FALSE))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			case VI_ATTR_TERMCHAR://(R/W) //0 to FFh
			{
				if ((attrValue<0) || (attrValue>0xFF))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return(VI_SUCCESS);
				break;
			}
			case VI_ATTR_TERMCHAR_EN://(R/W) //VI_TRUE VI_FALSE
			{
				if ((attrValue!=VI_TRUE)&&(attrValue!=VI_FALSE))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			case VI_ATTR_TMO_VALUE://(R/W) //VI_TMO_IMMEDIATE 1 to FFFFFFFEh VI_TMO_INFINITE
			{
				if ((attrValue<1) && (attrValue>0xFFFFFFFE) && (attrValue!=VI_TMO_IMMEDIATE) &&(attrValue!=VI_TMO_INFINITE))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return(VI_SUCCESS);
				break;
			}
			case VI_ATTR_TRIG_ID://(R/W*) //VI_TRIG_SW; VI_TRIG_TTL0 to VI_TRIG_TTL7; VI_TRIG_ECL0 to VI_TRIG_ECL1
			{
				return VI_ERROR_NSUP_ATTR;
				break;
			}
			case VI_ATTR_WR_BUF_OPER_MODE://(R/W) //VI_FLUSH_ON_ACCESS VI_FLUSH_WHEN_FULL
			{
				if ((attrValue!=VI_FLUSH_ON_ACCESS)&&(attrValue!=VI_FLUSH_WHEN_FULL))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			case VI_ATTR_DMA_ALLOW_EN://(R/W) //VI_TRUE VI_FALSE
			{
				if ((attrValue!=VI_TRUE)&&(attrValue!=VI_FALSE))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			case VI_ATTR_FILE_APPEND_EN://(R/W) //VI_TRUE VI_FALSE
			{
				if ((attrValue!=VI_TRUE)&&(attrValue!=VI_FALSE))
					return VI_ERROR_NSUP_ATTR_STATE;
				else
					return VI_SUCCESS;						
				break;
			}
			
			//atributos para el puerto serie
			//ASRL Specific INSTR Resource Attributes
			case VI_ATTR_ASRL_AVAIL_NUM://(RO) //0 to FFFFFFFFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					return VI_ERROR_ATTR_READONLY;	
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_BAUD://(R/W) //0 to FFFFFFFFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					r->i->vi_attr_ASRL_BAUD=(ViUInt32) attrValue;
					SetSerialBaudRate(r->fd,r->i->vi_attr_ASRL_BAUD);
					return(VI_SUCCESS);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_DATA_BITS:// (R/W) //5 to 8
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue>=5)&&(attrValue<=8))
					{
						r->i->vi_attr_ASRL_DATA_BITS=(ViUInt16) attrValue;
						SetSerialDataBits(r->fd,r->i->vi_attr_ASRL_DATA_BITS);
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_PARITY://(R/W) //VI_ASRL_PAR_NONE VI_ASRL_PAR_ODD VI_ASRL_PAR_EVEN VI_ASRL_PAR_MARK VI_ASRL_PAR_SPACE
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue==VI_ASRL_PAR_NONE)||(attrValue==VI_ASRL_PAR_ODD)||(attrValue==VI_ASRL_PAR_EVEN)||(attrValue==VI_ASRL_PAR_MARK)||(attrValue==VI_ASRL_PAR_SPACE))
					{
						r->i->vi_attr_ASRL_PARITY=(ViUInt16) attrValue;
						SetSerialParity(r->fd,r->i->vi_attr_ASRL_PARITY);
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_STOP_BITS://(R/W) //VI_ASRL_STOP_ONE VI_ASRL_STOP_ONE5 VI_ASRL_STOP_TWO
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue==VI_ASRL_STOP_ONE)||(attrValue==VI_ASRL_STOP_ONE5)||(attrValue== VI_ASRL_STOP_TWO))
					{
						r->i->vi_attr_ASRL_STOP_BITS=(ViUInt16) attrValue;
						SetSerialStopBits(r->fd,r->i->vi_attr_ASRL_STOP_BITS);
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_FLOW_CNTRL://(R/W) //VI_ASRL_FLOW_NONE VI_ASRL_FLOW_XON_XOFF VI_ASRL_FLOW_RTS_CTS VI_ASRL_FLOW_DTR_DSR
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue==VI_ASRL_FLOW_NONE)||(attrValue==VI_ASRL_FLOW_XON_XOFF)||(attrValue==VI_ASRL_FLOW_RTS_CTS)||(attrValue==VI_ASRL_FLOW_DTR_DSR))
					{
						r->i->vi_attr_ASRL_FLOW_CNTRL=(ViUInt16) attrValue;
						SetSerialFlowControl(r->fd,r->i->vi_attr_ASRL_FLOW_CNTRL);
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_END_IN://(R/W) //VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue==VI_ASRL_END_NONE)||(attrValue==VI_ASRL_END_LAST_BIT)||(attrValue==VI_ASRL_END_TERMCHAR))
					{
						r->i->vi_attr_ASRL_END_IN=(ViUInt16) attrValue;						
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_END_OUT://(R/W) //VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR VI_ASRL_END_BREAK
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue==VI_ASRL_END_NONE)||(attrValue==VI_ASRL_END_LAST_BIT)||(attrValue==VI_ASRL_END_TERMCHAR)||(attrValue== VI_ASRL_END_BREAK))
					{
						r->i->vi_attr_ASRL_END_OUT=(ViUInt16) attrValue;
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_CTS_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					return VI_ERROR_ATTR_READONLY;	
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_DCD_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					return VI_ERROR_ATTR_READONLY;	
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_DSR_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					return VI_ERROR_ATTR_READONLY;	
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_DTR_STATE://(R/W) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue==VI_STATE_ASSERTED)||(attrValue== VI_STATE_UNASSERTED)||(attrValue== VI_STATE_UNKNOWN))
					{
						r->i->vi_attr_ASRL_DTR_STATE=(ViInt16) attrValue;
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_RI_STATE://(RO) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
					return VI_ERROR_ATTR_READONLY;	
				else
					return VI_ERROR_NSUP_ATTR;
			}
			case VI_ATTR_ASRL_RTS_STATE://(R/W) //VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue==VI_STATE_ASSERTED)||(attrValue==VI_STATE_UNASSERTED)||(attrValue== VI_STATE_UNKNOWN))
					{
						r->i->vi_attr_ASRL_RTS_STATE=(ViInt16) attrValue;					
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_REPLACE_CHAR://(R/W) //0 to FFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue>=0)&&(attrValue<=0xFF))
					{
						r->i->vi_attr_ASRL_REPLACE_CHAR=(ViUInt8) attrValue;
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_XON_CHAR://(R/W) //0 to FFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue>=0)&&(attrValue<=0xFF))
					{
						r->i->vi_attr_ASRL_XON_CHAR=(ViUInt8) attrValue;
						SetSerialXonChar(r->fd,r->i->vi_attr_ASRL_XON_CHAR);
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("no vale\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			case VI_ATTR_ASRL_XOFF_CHAR://(R/W) //0 to FFh
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_ASRL)
				{
					if ((attrValue>=0)&&(attrValue<=0xFF))
					{
						r->i->vi_attr_ASRL_XOFF_CHAR=(ViUInt8) attrValue;
						SetSerialXoffChar(r->fd,r->i->vi_attr_ASRL_XOFF_CHAR);
						return(VI_SUCCESS);
					}
					else 
						return(VI_ERROR_NSUP_ATTR_STATE);
				}
				else
				{
					printf("non valid\n");
					return VI_ERROR_NSUP_ATTR;
				}
			}
			//GPIB and GPIB-VXI Specific INSTR Resource Attributes
					
			case VI_ATTR_GPIB_PRIMARY_ADDR:// RO Global  0 to 30
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
					return VI_ERROR_ATTR_READONLY;	
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			case VI_ATTR_GPIB_SECONDARY_ADDR:// RO Global  0 to 31, VI_NO_SEC_ADDR
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
					return VI_ERROR_ATTR_READONLY;	
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			
			case VI_ATTR_GPIB_READDR_EN:// R/W Local  VI_TRUE VI_FALSE
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
				{
					if ((attrValue!=VI_TRUE)&&(attrValue!=VI_FALSE))
						return VI_ERROR_NSUP_ATTR_STATE;
					else
					{
						r->i->vi_attr_GPIB_READDR_EN=(ViBoolean) attrValue;
						return VI_SUCCESS;						
					}
					break;
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			case VI_ATTR_GPIB_UNADDR_EN:// R/W Local  VI_TRUE VI_FALSE 
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
				{
					if ((attrValue!=VI_TRUE)&&(attrValue!=VI_FALSE))
						return VI_ERROR_NSUP_ATTR_STATE;
					else
					{
						r->i->vi_attr_GPIB_UNADDR_EN=(ViBoolean) attrValue;
						return VI_SUCCESS;						
					}
					break;
				}
				else
					return VI_ERROR_NSUP_ATTR;
			}
			
			
			case VI_ATTR_GPIB_REN_STATE:// RO Global  VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
			{
				if(r->i->vi_attr_INTF_TYPE==VI_INTF_GPIB)
					return VI_ERROR_ATTR_READONLY;	
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
