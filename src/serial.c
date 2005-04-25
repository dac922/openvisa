//serial port linux access
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;






void ASRLInitDefault(Instr* a,ViString name)
{
	//Visa Specs Apendix A: required attributes
	//general
	a->vi_attr_INTF_TYPE=VI_INTF_ASRL;
	a->vi_attr_INTF_INST_NAME=strdup(name);
	//specific
	a->vi_attr_ASRL_AVAIL_NUM=0;
	a->vi_attr_ASRL_BAUD=9600;
	a->vi_attr_ASRL_DATA_BITS=8;
	a->vi_attr_ASRL_PARITY=VI_ASRL_PAR_NONE;
	a->vi_attr_ASRL_END_IN=VI_ASRL_END_TERMCHAR;
	a->vi_attr_ASRL_END_OUT=VI_ASRL_END_NONE;
	a->vi_attr_ASRL_STOP_BITS=VI_ASRL_STOP_ONE;
	a->vi_attr_ASRL_FLOW_CNTRL=VI_ASRL_FLOW_NONE;
	a->vi_attr_ASRL_REPLACE_CHAR=0;
	a->vi_attr_ASRL_XON_CHAR=0x11;
	a->vi_attr_ASRL_XOFF_CHAR=0x13;
	
};

void SetSerialBaudRate(int fd,ViUInt32 BaudRate)
{
	struct termios T;
	tcgetattr(fd,&T);
	//baud rate
	switch (BaudRate)
	{
		case 0:
			cfsetispeed(&T,B0);
			cfsetospeed(&T,B0);
			break;
		case 50:
			cfsetispeed(&T,B50);
			cfsetospeed(&T,B50);
			break;
		case 75:
			cfsetispeed(&T,B75);
			cfsetospeed(&T,B75);
			break;
		case 110:
			cfsetispeed(&T,B110);
			cfsetospeed(&T,B110);
			break;
		case 134:
			cfsetispeed(&T,B134);
			cfsetospeed(&T,B134);
			break;
		case 150:
			cfsetispeed(&T,B150);
			cfsetospeed(&T,B150);
			break;
		case 200:
			cfsetispeed(&T,B200);
			cfsetospeed(&T,B200);
			break;
		case 300:
			cfsetispeed(&T,B300);
			cfsetospeed(&T,B300);
			break;
		case 600:
			cfsetispeed(&T,B600);
			cfsetospeed(&T,B600);
			break;
		case 1200:
			cfsetispeed(&T,B1200);
			cfsetospeed(&T,B1200);
			break;
		case 1800:
			cfsetispeed(&T,B1800);
			cfsetospeed(&T,B1800);
			break;
		case 2400:
			cfsetispeed(&T,B2400);
			cfsetospeed(&T,B2400);
			break;
		case 4800:
			cfsetispeed(&T,B4800);
			cfsetospeed(&T,B4800);
			break;
		case 9600:
			cfsetispeed(&T,B9600);
			cfsetospeed(&T,B9600);
			break;
		case 19200:
			cfsetispeed(&T,B19200);
			cfsetospeed(&T,B19200);
			break;
		case 38400:
			cfsetispeed(&T,B38400);
			cfsetospeed(&T,B38400);
			break;
		case 57600:
			cfsetispeed(&T,B57600);
			cfsetospeed(&T,B57600);
			break;
		//no definido en linux
		//case 76800:
		//	break;
		case 115200:
			cfsetispeed(&T,B115200);
			cfsetospeed(&T,B115200);
			break;
		default:
			cfsetispeed(&T,B9600);
			cfsetospeed(&T,B9600);
	}
	
	tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&T);
	
}




void SetSerialDataBits(int fd,ViUInt16 DataBits)
{
	struct termios T;
	tcgetattr(fd,&T);

	// size bits
	T.c_cflag &= ~CSIZE; /* Mask the character size bits */
    switch (DataBits)
	{
		case 5:
			T.c_cflag |= CS5;
			break;		
		case 6:
			T.c_cflag |= CS6; 
			break;
		case 7:
			T.c_cflag |= CS7; 
			break;
		case 8:
			T.c_cflag |= CS8; 
			break;
		default:
			T.c_cflag |= CS8; 
			break;
	}
	tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&T);
}

void SetSerialParity(int fd,ViUInt16 Parity)
{
	struct termios T;
	tcgetattr(fd,&T);

	// parity
	switch (Parity)
	{
		case VI_ASRL_PAR_NONE:
			T.c_cflag &= ~PARENB;
			break;
		case VI_ASRL_PAR_ODD:
			T.c_cflag |= PARENB;
			T.c_cflag |= PARODD;
			//activamos  control de paridad
			T.c_iflag |= (INPCK | ISTRIP);
			break;
		case VI_ASRL_PAR_EVEN:
			T.c_cflag |= PARENB;
			T.c_cflag &= ~PARODD;
			//activamos  control de paridad
			T.c_iflag |= (INPCK | ISTRIP);
			break;
		case VI_ASRL_PAR_MARK: //esto no se si se puede
			break;
		case VI_ASRL_PAR_SPACE: //esto pone q se puede emular
			break;
		default:
			T.c_cflag &= ~PARENB;
			break;
	}
	tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&T);
}


void SetSerialStopBits(int fd,ViUInt16 StopBits)
{
	struct termios T;
	tcgetattr(fd,&T);

	// stop bits 
	switch (StopBits)
	{
		case VI_ASRL_STOP_ONE:
			T.c_cflag &= ~CSTOPB;
			break;
		case VI_ASRL_STOP_ONE5://no se puede?
			break;
		case VI_ASRL_STOP_TWO:
			T.c_cflag |= CSTOPB;
			break;
		default:
			break;
	}
	tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&T);
}
void SetSerialFlowControl(int fd,ViUInt16 FlowControl)
{
	struct termios T;
	tcgetattr(fd,&T);

	//flow control
	//desactivar control hardware
	T.c_cflag &= ~CRTSCTS;
	//desactivar control software
	T.c_iflag &= ~(IXON | IXOFF | IXANY);
	switch (FlowControl)
	{
		case VI_ASRL_FLOW_NONE:
			break; //en este caso no hacemos nada , lo hemos hecho arriba
		case VI_ASRL_FLOW_XON_XOFF:
			//activamos control software
			T.c_iflag |= (IXON | IXOFF | IXANY);
			break;
		case VI_ASRL_FLOW_RTS_CTS:
			//activamos ontrol hardware
			T.c_cflag |= CRTSCTS;
			break;
		case VI_ASRL_FLOW_DTR_DSR:
			//not defined in linux: kernel patch avaible
			break;
		default:
			break;
	}
	tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&T);
	
}


void SetSerialXonChar(int fd,ViUInt8 XonChar)
{
	struct termios T;
	tcgetattr(fd,&T);

	T.c_cc[VSTART]   = XonChar;     /* por defecto  Ctrl-q */ 
	tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&T);
}
void SetSerialXoffChar(int fd,ViUInt8 XoffChar)
{
	struct termios T;
	tcgetattr(fd,&T);

    T.c_cc[VSTOP]    = XoffChar;     /* por defecto Ctrl-s */
	tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&T);
}


ViStatus OpenSerialPort(ViString SerialPort,ResourceRecord* r)
{
int fd;
struct termios oldtio,newtio;
/* 
Open modem device for reading and writing and not as controlling tty
because we don't want to get killed if linenoise sends CTRL-C.
*/
	fd = open(SerialPort, O_RDWR | O_NOCTTY ); 
    if (fd <0) {perror(SerialPort);return VI_ERROR_RSRC_BUSY;}
    //falta comprobar error de no encontrar r
	r->fd=fd;    
    tcgetattr(fd,&oldtio); /* save current serial port settings */
    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */
        
    //newtio.c_cflag = CRTSCTS | CS8 | CLOCAL | CREAD;
    //estas opciones son comunes para todos
	newtio.c_cflag = CLOCAL | CREAD;
	
	/*SetSerialBaudRate(&newtio,r->i->vi_attr_ASRL_BAUD);
	SetSerialDataBits(&newtio,r->i->vi_attr_ASRL_DATA_BITS);
	SetSerialParity(&newtio,r->i->vi_attr_ASRL_PARITY);
	SetSerialStopBits(&newtio,r->i->vi_attr_ASRL_STOP_BITS);
	SetSerialFlowControl(&newtio,r->i->vi_attr_ASRL_FLOW_CNTRL);
	SetSerialXonChar(&newtio,r->i->vi_attr_ASRL_XON_CHAR);
	SetSerialXoffChar(&newtio,r->i->vi_attr_ASRL_XOFF_CHAR);
	*/
	//Missing code for:
	//vi_attr_asrl_end_in
	//vi_attr_asrl_end_out
	//2 de los  estados de las lineas DTR y RTS
	//vi_attr_asrl_replace_char
	
	// this is all common 
    //      IGNPAR  : ignore bytes with parity errors
    //      ICRNL   : map CR to NL (otherwise a CR input on the other computer
    //                will not terminate input)
    //      otherwise make device raw (no other input processing)
    newtio.c_iflag = IGNPAR | ICRNL;
    //Raw output.
    newtio.c_oflag = 0;
    //  ICANON  : enable canonical input
    //  disable all echo functionality, and don't send signals to calling program
    newtio.c_lflag = ICANON;
    //initialize all control characters 
    //default values can be found in /usr/include/termios.h, and are given
    //in the comments, but we don't need them here
    newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */ 
    newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    newtio.c_cc[VERASE]   = 0;     /* del */
    newtio.c_cc[VKILL]    = 0;     /* @ */
    newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
    newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
    newtio.c_cc[VSWTC]    = 0;     /* '\0' */
    
    newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
    newtio.c_cc[VEOL]     = 0;     /* '\0' */
    newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
    newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
    newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
    newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
    newtio.c_cc[VEOL2]    = 0;     /* '\0' */
        
    

	//end of setting attributes------------------------------------------------------
    //now clean the modem line and activate the settings for the port
    
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSADRAIN,&newtio); //there are different options for updating the structure
        
    //no errors checked yet
	return VI_SUCCESS;
}
