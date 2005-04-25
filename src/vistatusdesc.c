#include "visa.h"
#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;

ViStatus viStatusDesc (ViObject vi, ViStatus status, ViChar desc[])
{
	switch (status)
	{
	case VI_SUCCESS: strcpy(desc,"VI_SUCCESS");break;
	case VI_SUCCESS_EVENT_EN: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_SUCCESS_EVENT_DIS: strcpy(desc,"VI_SUCCESS_EVENT_DIS");break;
	case VI_SUCCESS_QUEUE_EMPTY: strcpy(desc,"VI_SUCCESS_QUEUE_EMPTY");break;
	case VI_SUCCESS_TERM_CHAR: strcpy(desc,"VI_SUCCESS_TERM_CHAR");break;
	case VI_SUCCESS_MAX_CNT: strcpy(desc,"VI_SUCCESS_MAX_CNT");break;
	case VI_SUCCESS_DEV_NPRESENT: strcpy(desc,"VI_SUCCESS_DEV_NPRESENT");break;
	case VI_SUCCESS_TRIG_MAPPED: strcpy(desc,"VI_SUCCESS_TRIG_MAPPED");break;
	case VI_SUCCESS_QUEUE_NEMPTY: strcpy(desc,"VI_SUCCESS_QUEUE_NEMPTY");break;
	case VI_SUCCESS_NCHAIN: strcpy(desc,"VI_SUCCESS_NCHAIN");break;
	case VI_SUCCESS_NESTED_SHARED: strcpy(desc,"VI_SUCCESS_NESTED_SHARED");break;
	case VI_SUCCESS_NESTED_EXCLUSIVE: strcpy(desc,"VI_SUCCESS_NESTED_EXCLUSIVE");break;
	case VI_SUCCESS_SYNC: strcpy(desc,"VI_SUCCESS_SYNC");break;
	case VI_WARN_CONFIG_NLOADED: strcpy(desc,"VI_WARN_CONFIG_NLOADED");break;
	case VI_WARN_NULL_OBJECT: strcpy(desc,"VI_WARN_NULL_OBJECT");break;
	case VI_WARN_NSUP_ATTR_STATE: strcpy(desc,"VI_WARN_NSUP_ATTR_STATE");break;
	case VI_WARN_UNKNOWN_STATUS: strcpy(desc,"VI_WARN_UNKNOWN_STATUS");break;
	case VI_WARN_NSUP_BUF: strcpy(desc,"VI_WARN_NSUP_BUF");break;
	case VI_ERROR_SYSTEM_ERROR: strcpy(desc,"VI_ERROR_SYSTEM_ERROR");break;
	case VI_ERROR_INV_OBJECT: strcpy(desc,"VI_ERROR_INV_OBJECT");break;
	case VI_ERROR_RSRC_LOCKED: strcpy(desc,"VI_ERROR_RSRC_LOCKED");break;
	case VI_ERROR_INV_EXPR: strcpy(desc,"VI_ERROR_INV_EXPR");break;
	case VI_ERROR_RSRC_NFOUND: strcpy(desc,"VI_ERROR_RSRC_NFOUND");break;
	case VI_ERROR_INV_RSRC_NAME: strcpy(desc,"VI_ERROR_INV_RSRC_NAME");break;
	case VI_ERROR_INV_ACC_MODE: strcpy(desc,"VI_ERROR_INV_ACC_MODE");break;
	case VI_ERROR_TMO: strcpy(desc,"VI_ERROR_TMO");break;
	case VI_ERROR_CLOSING_FAILED: strcpy(desc,"VI_ERROR_CLOSING_FAILED");break;
	case VI_ERROR_INV_DEGREE: strcpy(desc,"VI_ERROR_INV_DEGREE");break;
	case VI_ERROR_INV_JOB_ID: strcpy(desc,"VI_ERROR_INV_JOB_ID");break;
	case VI_ERROR_NSUP_ATTR: strcpy(desc,"VI_ERROR_NSUP_ATTR");break;
	case VI_ERROR_NSUP_ATTR_STATE: strcpy(desc,"VI_ERROR_NSUP_ATTR_STATE");break;
	case VI_ERROR_ATTR_READONLY: strcpy(desc,"VI_ERROR_ATTR_READONLY");break;
	case VI_ERROR_INV_LOCK_TYPE: strcpy(desc,"VI_ERROR_INV_LOCK_TYPE");break;
	case VI_ERROR_INV_ACCESS_KEY: strcpy(desc,"VI_ERROR_INV_ACCESS_KEY");break;
	case VI_ERROR_INV_EVENT: strcpy(desc,"VI_ERROR_INV_EVENT");break;
	case VI_ERROR_INV_MECH: strcpy(desc,"VI_ERROR_INV_MECH");break;
	case VI_ERROR_HNDLR_NINSTALLED: strcpy(desc,"VI_ERROR_HNDLR_NINSTALLED");break;
	case VI_ERROR_INV_HNDLR_REF: strcpy(desc,"VI_ERROR_INV_HNDLR_REF");break;
	case VI_ERROR_INV_CONTEXT: strcpy(desc,"VI_ERROR_INV_CONTEXT");break;
	case VI_ERROR_NENABLED: strcpy(desc,"VI_ERROR_NENABLED");break;
	case VI_ERROR_ABORT: strcpy(desc,"VI_ERROR_ABORT");break;
	case VI_ERROR_RAW_WR_PROT_VIOL: strcpy(desc,"VI_ERROR_RAW_WR_PROT_VIOL");break;
	case VI_ERROR_RAW_RD_PROT_VIOL: strcpy(desc,"VI_ERROR_RAW_RD_PROT_VIOL");break;
	case VI_ERROR_OUTP_PROT_VIOL: strcpy(desc,"VI_ERROR_OUTP_PROT_VIOL");break;
	case VI_ERROR_INP_PROT_VIOL: strcpy(desc,"VI_ERROR_INP_PROT_VIOL");break;
	case VI_ERROR_BERR: strcpy(desc,"VI_ERROR_BERR");break;
	case VI_ERROR_INV_SETUP: strcpy(desc,"VI_ERROR_INV_SETUP");break;
	case VI_ERROR_QUEUE_ERROR: strcpy(desc,"VI_ERROR_QUEUE_ERROR");break;
	case VI_ERROR_ALLOC: strcpy(desc,"VI_ERROR_ALLOC");break;
	case VI_ERROR_INV_MASK: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_IO: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_INV_FMT: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_NSUP_FMT: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_LINE_IN_USE: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_NSUP_MODE: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_SRQ_NOCCURRED: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_INV_SPACE: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	case VI_ERROR_INV_OFFSET: strcpy(desc,"VI_SUCCESS_EVENT_EN");break;
	
	case VI_ERROR_INV_WIDTH: strcpy(desc,"VI_ERROR_INV_WIDTH");break;
	case VI_ERROR_NSUP_OFFSET: strcpy(desc,"VI_ERROR_NSUP_OFFSET");break;
	case VI_ERROR_NSUP_VAR_WIDTH: strcpy(desc,"VI_ERROR_NSUP_VAR_WIDTH");break;
	case VI_ERROR_WINDOW_NMAPPED: strcpy(desc,"VI_ERROR_WINDOW_NMAPPED");break;
	case VI_ERROR_RESP_PENDING: strcpy(desc,"VI_ERROR_RESP_PENDING");break;
	case VI_ERROR_NLISTENERS: strcpy(desc,"VI_ERROR_NLISTENERS");break;
	case VI_ERROR_NCIC: strcpy(desc,"VI_ERROR_NCIC");break;
	case VI_ERROR_NSYS_CNTLR: strcpy(desc,"VI_ERROR_NSYS_CNTLR");break;
	case VI_ERROR_NSUP_OPER: strcpy(desc,"VI_ERROR_NSUP_OPER");break;
	case VI_ERROR_INTR_PENDING: strcpy(desc,"VI_ERROR_INTR_PENDING");break;
	case VI_ERROR_ASRL_PARITY: strcpy(desc,"VI_ERROR_ASRL_PARITY");break;
	case VI_ERROR_ASRL_FRAMING: strcpy(desc,"VI_ERROR_ASRL_FRAMING");break;
	case VI_ERROR_ASRL_OVERRUN: strcpy(desc,"VI_ERROR_ASRL_OVERRUN");break;
	case VI_ERROR_TRIG_NMAPPED: strcpy(desc,"VI_ERROR_TRIG_NMAPPED");break;
	case VI_ERROR_NSUP_ALIGN_OFFSET: strcpy(desc,"VI_ERROR_NSUP_ALIGN_OFFSET");break;
	case VI_ERROR_USER_BUF: strcpy(desc,"VI_ERROR_USER_BUF");break;
	case VI_ERROR_RSRC_BUSY: strcpy(desc,"VI_ERROR_RSRC_BUSY");break;
	case VI_ERROR_NSUP_WIDTH: strcpy(desc,"VI_ERROR_NSUP_WIDTH");break;
	case VI_ERROR_INV_PARAMETER: strcpy(desc,"VI_ERROR_INV_PARAMETER");break;
	case VI_ERROR_INV_PROT: strcpy(desc,"VI_ERROR_INV_PROT");break;
	case VI_ERROR_INV_SIZE: strcpy(desc,"VI_ERROR_INV_SIZE");break;
	case VI_ERROR_WINDOW_MAPPED: strcpy(desc,"VI_ERROR_WINDOW_MAPPED");break;
	case VI_ERROR_NIMPL_OPER: strcpy(desc,"VI_ERROR_NIMPL_OPER");break;
	case VI_ERROR_INV_LENGTH: strcpy(desc,"VI_ERROR_INV_LENGTH");break;
	case VI_ERROR_INV_MODE: strcpy(desc,"VI_ERROR_INV_MODE");break;
	case VI_ERROR_SESN_NLOCKED: strcpy(desc,"VI_ERROR_SESN_NLOCKED");break;
	case VI_ERROR_MEM_NSHARED: strcpy(desc,"VI_ERROR_MEM_NSHARED");break;
	case VI_ERROR_LIBRARY_NFOUND: strcpy(desc,"VI_ERROR_LIBRARY_NFOUND");break;
	case VI_ERROR_NSUP_INTR: strcpy(desc,"VI_ERROR_NSUP_INTR");break;
	case VI_ERROR_INV_LINE: strcpy(desc,"VI_ERROR_INV_LINE");break;
	case VI_ERROR_FILE_ACCESS: strcpy(desc,"VI_ERROR_FILE_ACCESS");break;
	case VI_ERROR_FILE_IO: strcpy(desc,"VI_ERROR_FILE_IO");break;
	case VI_ERROR_NSUP_LINE: strcpy(desc,"VI_ERROR_NSUP_LINE");break;
	case VI_ERROR_NSUP_MECH: strcpy(desc,"VI_ERROR_NSUP_MECH");break;
	case VI_ERROR_INTF_NUM_NCONFIG: strcpy(desc,"VI_ERROR_INTF_NUM_NCONFIG");break;
	case VI_ERROR_CONN_LOST: strcpy(desc,"VI_ERROR_CONN_LOST");break; 
	default: strcpy(desc,"VI_WARN_UNKNOWN_STATUS");return VI_WARN_UNKNOWN_STATUS;
		
	}
	return VI_SUCCESS;
}
