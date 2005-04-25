//serial port linux access
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#include "common.h"

extern ResourceRecord *ResourceList;;
extern int SessionsCount;
extern ViBoolean DefaultRMFirst;




void AsrlInit(Instr* a,ViString name)
{
	
	//general
	a->vi_attr_INTF_TYPE=VI_INTF_ASRL;
	a->vi_attr_INTF_INST_NAME=(char* )malloc(sizeof(char)*strlen(name));
	strcpy(a->vi_attr_INTF_INST_NAME,name);
	//specific
	//vi_attr_ASRL_AVAIL_NUM;???
	a->vi_attr_ASRL_BAUD=9600;
	a->vi_attr_ASRL_DATA_BITS=8;
	a->vi_attr_ASRL_PARITY=VI_ASRL_PAR_NONE;
	a->vi_attr_ASRL_STOP_BITS=VI_ASRL_STOP_ONE;
	a->vi_attr_ASRL_FLOW_CNTRL=VI_ASRL_FLOW_NONE;
	
};






ViStatus OpenSerialPort(ViString SerialPort,ViSession vi)
{
int fd;
struct termios oldtio,newtio;
ResourceRecord *r;
/* 
Open modem device for reading and writing and not as controlling tty
because we don't want to get killed if linenoise sends CTRL-C.
*/
	fd = open(SerialPort, O_RDWR | O_NOCTTY ); 
    if (fd <0) {perror(SerialPort);return 1;}
    //falta comprobar error de no encontrar r
	r=LookForRessource(vi);
	r->fd=fd;    
    tcgetattr(fd,&oldtio); /* save current serial port settings */
    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */
        
    //newtio.c_cflag = CRTSCTS | CS8 | CLOCAL | CREAD;
    //estas opciones son comunes para todos
	newtio.c_cflag = CLOCAL | CREAD;
	
	
	//baud rate
	switch (r->i->vi_attr_ASRL_BAUD)
	{
		case 0:
			cfsetispeed(&newtio,B0);
			cfsetospeed(&newtio,B0);
			break;
		case 50:
			cfsetispeed(&newtio,B50);
			cfsetospeed(&newtio,B50);
			break;
		case 75:
			cfsetispeed(&newtio,B75);
			cfsetospeed(&newtio,B75);
			break;
		case 110:
			cfsetispeed(&newtio,B110);
			cfsetospeed(&newtio,B110);
			break;
		case 134:
			cfsetispeed(&newtio,B134);
			cfsetospeed(&newtio,B134);
			break;
		case 150:
			cfsetispeed(&newtio,B150);
			cfsetospeed(&newtio,B150);
			break;
		case 200:
			cfsetispeed(&newtio,B200);
			cfsetospeed(&newtio,B200);
			break;
		case 300:
			cfsetispeed(&newtio,B300);
			cfsetospeed(&newtio,B300);
			break;
		case 600:
			cfsetispeed(&newtio,B600);
			cfsetospeed(&newtio,B600);
			break;
		case 1200:
			cfsetispeed(&newtio,B1200);
			cfsetospeed(&newtio,B1200);
			break;
		case 1800:
			cfsetispeed(&newtio,B1800);
			cfsetospeed(&newtio,B1800);
			break;
		case 2400:
			cfsetispeed(&newtio,B2400);
			cfsetospeed(&newtio,B2400);
			break;
		case 4800:
			cfsetispeed(&newtio,B4800);
			cfsetospeed(&newtio,B4800);
			break;
		case 9600:
			cfsetispeed(&newtio,B9600);
			cfsetospeed(&newtio,B9600);
			break;
		case 19200:
			cfsetispeed(&newtio,B19200);
			cfsetospeed(&newtio,B19200);
			break;
		case 38400:
			cfsetispeed(&newtio,B38400);
			cfsetospeed(&newtio,B38400);
			break;
		case 57600:
			cfsetispeed(&newtio,B57600);
			cfsetospeed(&newtio,B57600);
			break;
		//no definido en linux
		//case 76800:
		//	break;
		case 115200:
			cfsetispeed(&newtio,B115200);
			cfsetospeed(&newtio,B115200);
			break;
		default:
			cfsetispeed(&newtio,B9600);
			cfsetospeed(&newtio,B9600);
	}
		
    
	
	
	// size bits
	newtio.c_cflag &= ~CSIZE; /* Mask the character size bits */
    switch (r->i->vi_attr_ASRL_DATA_BITS)
	{
		case 5:
			newtio.c_cflag |= CS5;
			break;		
		case 6:
			newtio.c_cflag |= CS6; 
			break;
		case 7:
			newtio.c_cflag |= CS7; 
			break;
		case 8:
			newtio.c_cflag |= CS8; 
			break;
		default:
			newtio.c_cflag |= CS8; 
			break;
	}
				
	// parity
	switch (r->i->vi_attr_ASRL_PARITY)
	{
		case VI_ASRL_PAR_NONE:
			newtio.c_cflag &= ~PARENB;
			break;
		case VI_ASRL_PAR_ODD:
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			//activamos  control de paridad
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case VI_ASRL_PAR_EVEN:
			newtio.c_cflag |= PARENB;
			newtio.c_cflag &= ~PARODD;
			//activamos  control de paridad
			newtio.c_iflag |= (INPCK | ISTRIP);
			break;
		case VI_ASRL_PAR_MARK: //esto no se si se puede
			break;
		case VI_ASRL_PAR_SPACE: //esto pone q se puede emular
			break;
		default:
			newtio.c_cflag &= ~PARENB;
			break;
	}
	
	// stop bits 
	switch (r->i->vi_attr_ASRL_STOP_BITS)
	{
		case VI_ASRL_STOP_ONE:
			newtio.c_cflag &= ~CSTOPB;
			break;
		case VI_ASRL_STOP_ONE5://no se puede?
			break;
		case VI_ASRL_STOP_TWO:
			newtio.c_cflag |= CSTOPB;
			break;
		default:
			break;
	}
	
	//flow control
	//desactivar control hardware
	newtio.c_cflag &= ~CRTSCTS;
	//desactivar control software
	newtio.c_iflag &= ~(IXON | IXOFF | IXANY);
	switch (r->i->vi_attr_ASRL_FLOW_CNTRL)
	{
		case VI_ASRL_FLOW_NONE:
			break; //en este caso no hacemos nada , lo hemos hecho arriba
		case VI_ASRL_FLOW_XON_XOFF:
			//activamos control software
			newtio.c_iflag |= (IXON | IXOFF | IXANY);
			break;
		case VI_ASRL_FLOW_RTS_CTS:
			//activamos ontrol hardware
			newtio.c_cflag |= CRTSCTS;
			break;
		case VI_ASRL_FLOW_DTR_DSR:
			//not defined in linux: kernel patch avaible
			break;
		default:
			break;
	}
	
	
	
	
	//vi_attr_asrl_xon_char
	//vi_attr_asrl_xoff_char
	newtio.c_cc[VSTART]   = r->i->vi_attr_ASRL_XON_CHAR;     /* por defecto  Ctrl-q */ 
    newtio.c_cc[VSTOP]    = r->i->vi_attr_ASRL_XOFF_CHAR;;     /* por defecto Ctrl-s */
	
	
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
