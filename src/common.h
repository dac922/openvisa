//---------------------------------
//common structures for the library
//---------------------------------

#include "visa.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//serial definitions
#define MODEMDEVICE1 "/dev/ttyS1"
#define FIRST_SERIAL '1'
#define LAST_SERIAL '4'

typedef struct
{
		//Template Attributes
	    ViVersion vi_attr_RSRC_IMPL_VERSION;// RO Global  0h to FFFFFFFFh 
		ViAccessMode vi_attr_RSRC_LOCK_STATE;// RO Global  VI_NO_LOCK VI_EXCLUSIVE_LOCK VI_SHARED_LOCK 
		ViUInt16 vi_attr_RSRC_MANF_ID;// RO Global  0h to 3FFFh 
		ViString vi_attr_RSRC_MANF_NAME;// RO Global  N/A 
		ViRsrc vi_attr_RSRC_NAME;// RO Global  N/A 
		ViVersion vi_attr_RSRC_SPEC_VERSION;// RO Global  00200200h 
		ViSession vi_attr_RM_SESSION;// RO Local  N/A 
		ViUInt32 vi_attr_MAX_QUEUE_LENGTH;// R/W* Local  1h to FFFFFFFFh 
		ViString vi_attr_RSRC_CLASS;// RO Global  N/A 
		ViAddr vi_attr_USER_DATA;// R/W Local  **
	
	
	
		//General attributes of INSTR Resource
		ViUInt16 vi_attr_INTF_NUM;//0 to FFFFh
		ViUInt16 vi_attr_INTF_TYPE;//VI_INTF_VXI VI_INTF_GPIB VI_INTF_GPIB_VXI VI_INTF_ASRL VI_INTF_TCPIP
		ViString vi_attr_INTF_INST_NAME;//N/A
		ViUInt16 vi_attr_IO_PROT;//VI_NORMAL VI_FDC VI_HS488 VI_PROT_4882_STRS
		ViUInt16 vi_attr_RD_BUF_OPER_MODE;//VI_FLUSH_ON_ACCESS VI_FLUSH_DISABLE
		ViBoolean vi_attr_SEND_END_EN;//VI_TRUE VI_FALSE
		ViBoolean vi_attr_SUPPRESS_END_EN;//VI_TRUE VI_FALSE
		ViUInt8 vi_attr_TERMCHAR;//0 to FFh
		ViBoolean vi_attr_TERMCHAR_EN;//VI_TRUE VI_FALSE
		ViUInt32 vi_attr_TMO_VALUE;//VI_TMO_IMMEDIATE 1 to FFFFFFFEh VI_TMO_INFINITE
		ViInt16 vi_attr_TRIG_ID;//VI_TRIG_SW; VI_TRIG_TTL0 to VI_TRIG_TTL7; VI_TRIG_ECL0 to VI_TRIG_ECL1
		ViUInt16 vi_attr_WR_BUF_OPER_MODE;//VI_FLUSH_ON_ACCESS VI_FLUSH_WHEN_FULL
		ViBoolean vi_attr_DMA_ALLOW_EN;//VI_TRUE VI_FALSE
		ViBoolean vi_attr_FILE_APPEND_EN;//VI_TRUE VI_FALSE
	
		//ASRL Specific INSTR Resource Attributes
		ViUInt32 vi_attr_ASRL_AVAIL_NUM;//0 to FFFFFFFFh
		ViUInt32 vi_attr_ASRL_BAUD;//0 to FFFFFFFFh
		ViUInt16 vi_attr_ASRL_DATA_BITS;//5 to 8
		ViUInt16 vi_attr_ASRL_PARITY;//VI_ASRL_PAR_NONE VI_ASRL_PAR_ODD VI_ASRL_PAR_EVEN VI_ASRL_PAR_MARK VI_ASRL_PAR_SPACE
		ViUInt16 vi_attr_ASRL_STOP_BITS;//VI_ASRL_STOP_ONE VI_ASRL_STOP_ONE5 VI_ASRL_STOP_TWO
		ViUInt16 vi_attr_ASRL_FLOW_CNTRL;//VI_ASRL_FLOW_NONE VI_ASRL_FLOW_XON_XOFF VI_ASRL_FLOW_RTS_CTS VI_ASRL_FLOW_DTR_DSR
		ViUInt16 vi_attr_ASRL_END_IN;//VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR
		ViUInt16 vi_attr_ASRL_END_OUT;//VI_ASRL_END_NONE VI_ASRL_END_LAST_BIT VI_ASRL_END_TERMCHAR VI_ASRL_END_BREAK
		ViInt16 vi_attr_ASRL_CTS_STATE;//VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
		ViInt16 vi_attr_ASRL_DCD_STATE;//VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
		ViInt16 vi_attr_ASRL_DSR_STATE;//VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
		ViInt16 vi_attr_ASRL_DTR_STATE;//VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
		ViInt16 vi_attr_ASRL_RI_STATE;//VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
		ViInt16 vi_attr_ASRL_RTS_STATE;//VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN
		ViUInt8 vi_attr_ASRL_REPLACE_CHAR;//0 to FFh
		ViUInt8 vi_attr_ASRL_XON_CHAR;//0 to FFh
		ViUInt8 vi_attr_ASRL_XOFF_CHAR;//0 to FFh
	
		//GPIB and GPIB-VXI Specific INSTR Resource Attributes
		ViUInt16 vi_attr_GPIB_PRIMARY_ADDR;// RO Global  0 to 30 
		ViUInt16 vi_attr_GPIB_SECONDARY_ADDR;// RO Global  0 to 31, VI_NO_SEC_ADDR 
		ViBoolean vi_attr_GPIB_READDR_EN;// R/W Local  VI_TRUE VI_FALSE 
		ViBoolean vi_attr_GPIB_UNADDR_EN;// R/W Local  VI_TRUE VI_FALSE 
		ViInt16 vi_attr_GPIB_REN_STATE;// RO Global  VI_STATE_ASSERTED VI_STATE_UNASSERTED VI_STATE_UNKNOWN



}Instr;



typedef struct Resource
{
	Instr *i;
	ViSession vi;
	int fd; //file descriptor of the instrument
	struct Resource* Next;
}ResourceRecord;
