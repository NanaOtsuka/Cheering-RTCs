/* Library code for Gainer and clones                                        */
/* This program is distributed under the license GNU GPL version 3 or later. */
/* Copyright (c) 2009 Noriaki Mitsunaga                                      */


#define WINDOWS

#ifdef WINDOWS
#include "gainer-lib.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#else
#include "gainer-lib.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#endif

/* Global variables */
void (*gm_button_pressed)(void) = NULL;
void (*gm_button_released)(void) = NULL;

static int configuration = 0;

/* Function declarations */
static int hex2int(int c);

/* ////////////////////////////////////////////////////////////////////////// */
/* Functions                                                                  */
/* ////////////////////////////////////////////////////////////////////////// */

#ifndef WINDOWS
////////////////////////////////////////////////////////////////////////////////////
// Functions for UNIX machines
ASY_HANDLE
asy_init(ASY_HANDLE fd, speed_t speed)
{
	struct termios	t;
	int modemline;

	/* 現在の設定を読む */
	tcgetattr(fd, &t);

	/* ボーレートのセット */
	cfsetspeed(&t, speed);

	/* raw モードのセット(パリティチェックなし) */
	cfmakeraw(&t);

	/* 入力モードの設定 */
	t.c_iflag = (IGNBRK | IGNPAR);

	/* 制御モードの設定 */
	t.c_cflag = (CS8 | CREAD | CLOCAL);

	/* 制御文字の設定, 0.1 秒が経過するか 1 文字受信するまでブロックする */
	t.c_cc[VTIME] = 1; /* 0.1 sec */
	t.c_cc[VMIN] = 1;  /* 1 char */

	/* Set attributes */
	tcsetattr(fd, TCSANOW, &t);

	/* Flush buffers */
	tcflush(fd, TCIOFLUSH);

	return 0;
}

ASY_HANDLE
asy_open(const char *dev)
{
  int asy;

  if((asy = open(dev, O_RDWR | O_NDELAY))<0) {
    fprintf(stderr, "Colud not open serial port.\n");
    exit(2);
  }
  return asy;
}

int
asy_read(ASY_HANDLE fd, char buf[], int len)
{
  char r;
  int i;

  for (i=0; i<(len-1); i ++) {
    if (read(fd, &r, 1) <= 0) {
      // fprintf(stderr, "Read timeout\n");
      return(-1);
    }
    buf[i] = r;
    if (r == '*') {
      buf[i+1] = '\0';
      if (i == 1 && buf[0] == 'N' && buf[1] == '*') {
	if (gm_button_pressed != NULL)
	  (*gm_button_pressed)();
	i = -1;
	continue;
      } else if (i == 1 && buf[0] == 'F' && buf[1] == '*') {
	if (gm_button_released != NULL)
	  (*gm_button_released)();
	i = -1;
	continue;
      }

      return i+1;
    }
  }
  return -1;
}
#else
////////////////////////////////////////////////////////////////////////////////////
// Functions for Windows (tested with VC++ 2008)
int
asy_init(ASY_HANDLE h, int speed)
{
  COMMTIMEOUTS cto;
  DCB dcb;

  GetCommState( h, &dcb ); // シリアルポートの状態を取得
  dcb.BaudRate = speed;
  SetCommState( h, &dcb ); // シリアルポートの状態を設定

  GetCommTimeouts( h, &cto ); // タイムアウトの設定状態を取得
  cto.ReadIntervalTimeout = 1000;
  cto.ReadTotalTimeoutMultiplier = 10;
  cto.ReadTotalTimeoutConstant = 1000;
  cto.WriteTotalTimeoutMultiplier = 10;
  cto.WriteTotalTimeoutConstant = 1000;
  SetCommTimeouts( h, &cto ); // タイムアウトの状態を設定

  return 0;
}

ASY_HANDLE
asy_open(const char *dev)
{
  HANDLE h;

  h = CreateFileA( dev, 
		  GENERIC_READ | GENERIC_WRITE,
		  0,
		  NULL,
		  OPEN_EXISTING,
		  0,
		  NULL ); 
  if (h == INVALID_HANDLE_VALUE) {
    fprintf(stderr, "Colud not open serial port %s.\n", dev);
	Sleep(10*1000);
    exit(2);
  }
  return h;
}


int
asy_read(ASY_HANDLE fd, char buf[], int len)
{
  char r;
  int i;
  unsigned long n;

  for (i=0; i<(len-1); i ++) {
	DWORD dmy;

    ReadFile(fd, &r, 1, &n, NULL);
    if (n == 0) {
#if 0
	  SetCommMask(fd, EV_RXCHAR);
	  WaitCommEvent(fd, &dmy, NULL);
	  ReadFile(fd, &r, 1, &n, NULL);
#endif
	  if (n == 0)
		fprintf(stderr, "Read timeout\n");
      return(-1);
    }
    buf[i] = r;
    if (r == '*') {
      buf[i+1] = '\0';
      if (i == 1 && buf[0] == 'N' && buf[1] == '*') {
	if (gm_button_pressed != NULL)
	  (*gm_button_pressed)();
	i = -1;
	continue;
      } else if (i == 1 && buf[0] == 'F' && buf[1] == '*') {
	if (gm_button_released != NULL)
	  (*gm_button_released)();
	i = -1;
	continue;
      }

      return i+1;
    }
  }
  return -1;
}

int
asy_write(ASY_HANDLE fd, const char buf[], int len)
{
  unsigned long n;
  WriteFile(fd, buf, len, &n, NULL);
  return n;
}
#endif
////////////////////////////////////////////////////////////////////////////////////
// Functions common to all systems
int
gm_ain(ASY_HANDLE asy, int *a, int n)
{
  char buf[BUFSIZ];
  int i;
  unsigned long ret;

  asy_write(asy, "I*", 2);
  usleep(5*1000);
  if (asy_read(asy, buf, BUFSIZ-1)<0)
    return 0;

  // fprintf(stderr, "[%s]", buf);

  if (configuration == 1 || configuration == 3 || configuration == 8) {
    if (n>4)
      n = 4;
  } else if (configuration == 2 || configuration == 4) {
    if (n>8)
      n = 8;
  } else {
    n = 0;
  }

  for (i=0; i<n; i ++)
    a[i] = hex2int(buf[1+i*2])<<4 | hex2int(buf[1+i*2+1]);

  return n;
}

void
gm_aout(ASY_HANDLE asy, int *a, int n)
{
  char s[BUFSIZ], r[BUFSIZ];
  int i;

  if (n<0)
    return;
  if (!((configuration == 1 && n == 4) || (configuration == 2 && n == 4) ||
	(configuration == 3 && n == 8) || (configuration == 4 && n == 8)))
    return;

  for (i=0; i<n; i ++)
    if (a[i]<0)
      a[i]= 0;
    else if (a[i]>0xff)
      a[i] = 0xff;

  if (n == 4) {
#ifndef WINDOWS
    snprintf(s, BUFSIZ-1, "A%02X%02X%02X%02X*", a[0], a[1], a[2], a[3]);
#else
	_snprintf(s, BUFSIZ-1, "A%02X%02X%02X%02X*", a[0], a[1], a[2], a[3]);
#endif
  } else {
#ifndef WINDOWS
    snprintf(s, BUFSIZ-1, "A%02X%02X%02X%02X%02X%02X%02X%02X*", a[0], a[1], a[2], a[3],
	     a[4], a[5], a[6], a[7]);
#else
    _snprintf(s, BUFSIZ-1, "A%02X%02X%02X%02X%02X%02X%02X%02X*", a[0], a[1], a[2], a[3],
	     a[4], a[5], a[6], a[7]);
#endif
  }

  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      r[0] != 'A' || r[1] != '*')
    fprintf(stderr, "%s\n", r);
}

void
gm_aout1(ASY_HANDLE asy, int n, int a)
{
  char s[BUFSIZ], r[BUFSIZ];

  if (n<0)
    return;
  if (!((configuration == 1 && n<4) || (configuration == 2 && n<4) ||
	(configuration == 3 && n<8) || (configuration == 4 && n<8)))
    return;

  if (a<0)
    a = 0;
  else if (a>0xff)
    a = 0xff;

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "a%X%02X*", n, a);
#else
  _snprintf(s, BUFSIZ-1, "a%X%02X*", n, a);
#endif
  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 || 
      strcmp(s, r) != 0)
    fprintf(stderr, "%s\n", r);
}

/*
  KONFIGURATION_n	KONFIGURATION_n*	n: configuration (1~8)

  configuration	ain/din/aout/dout	comments
  0	 0/ 0/ 0/ 0	initial configuration just after rebooting
  1	 4/ 4/ 4/ 4	default configuration
  2	 8/ 0/ 4/ 4	
  3	 4/ 4/ 8/ 0	
  4	 8/ 0/ 8/ 0	
  5	 0/16/ 0/ 0	
  6	 0/ 0/ 0/16	
  7	 0/ 8/ 8/ 0	matrix LED control mode
  [Gainer]
  8	 0/ 8/ 0/ 8	capacitive sensing switch mode (first 4 ports only)
  [GainerMini]
  8	 4/ 0/ 0/ 4	4 ain, 4 dout, 8 R/C servo
*/
int
gm_configuration(ASY_HANDLE asy, int n)
{
  char s[BUFSIZ], r[BUFSIZ];
  int rn;

  if (n<0 || n>8)
    return -1;

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "KONFIGURATION_%d*", n);
#else
  _snprintf(s, BUFSIZ-1, "KONFIGURATION_%d*", n);
#endif
  asy_write(asy, s, strlen(s));
#ifndef WINDOWS
  usleep(100*1000);
#else
  Sleep(1000);
#endif
  rn = asy_read(asy, r, BUFSIZ-1);
  if (rn<=0 || strcmp(s, r) != 0) {
	  fprintf(stderr, "ERR: %s != %s\n", s, r);
    return -1;
  }

  configuration = n;
  return 0;
}

unsigned long
gm_din(ASY_HANDLE asy)
{
  char buf[BUFSIZ];
  int i;
  unsigned long ret;

  asy_write(asy, "R*", 2);
  usleep(5*1000);
  if (asy_read(asy, buf, BUFSIZ-1)<0)
    return 0;
  fprintf(stderr, "[%s]", buf);
  if (buf[0] != 'R' || buf[5] != '*')
    return 0;
  if (configuration == 1 || configuration == 3)
    ret = hex2int(buf[4]);

  if (configuration == 5)
    ret = (hex2int(buf[3])<<4) | (hex2int(buf[4]));

  return ret;
}

void
gm_dH(ASY_HANDLE asy, int n)
{
  char s[BUFSIZ], r[BUFSIZ];

  if (n<0)
    return;
  if (!((configuration == 1 && n < 4) || (configuration == 2 && n < 4) ||
	(configuration == 6 && n < 0x10) || (configuration == 8 && n < 4)))
    return;

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "H%X*", n);
#else
  _snprintf(s, BUFSIZ-1, "H%X*", n);
#endif
  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      strcmp(s, r) != 0)
    fprintf(stderr, "%s\n", r);
}

void
gm_dL(ASY_HANDLE asy, int n)
{
  char s[BUFSIZ], r[BUFSIZ];

  if (n<0 || n>=0x10)
    return;

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "L%X*", n);
#else
  _snprintf(s, BUFSIZ-1, "L%X*", n);
#endif
  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      strcmp(s, r) != 0)
    fprintf(stderr, "%s\n", r);
}

void
gm_dout(ASY_HANDLE asy, int d)
{
  char s[BUFSIZ], r[BUFSIZ];

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "D%04X*", d);
#else
  _snprintf(s, BUFSIZ-1, "D%04X*", d);
#endif
  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 || 
      strcmp(s, r) != 0)
    fprintf(stderr, "%s\n", r);
}

void
gm_led_on(ASY_HANDLE asy)
{
  char r[BUFSIZ];

  asy_write(asy, "h*", 2);
  usleep(50*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      strcmp(r, "h*") != 0)
    fprintf(stderr, "Sent %s. Got %s.\n", "h*", r);
  return;
}

void
gm_led_off(ASY_HANDLE asy)
{
  char r[BUFSIZ];

  asy_write(asy, "l*", 2);
  usleep(50*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      strcmp(r, "l*") != 0)
     fprintf(stderr, "Sent %s. Got %s.\n", "l*", r);
  return;
}

void
gm_mled(ASY_HANDLE asy, int n, int *row)
{
  char s[BUFSIZ], r[BUFSIZ];
  int i;

  if (n<0 || n>=8 || configuration != 7)
    return;

  for (i=0; i<n; i ++)
    if (row[i]<0)
      row[i]= 0;
    else if (row[i]>0xf)
      row[i] = 0xf;

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "a%X%X%X%X%X%X%X%X%X*", n, 
	   row[0], row[1], row[2], row[3],
	   row[4], row[5], row[6], row[7]);
#else
  _snprintf(s, BUFSIZ-1, "a%X%X%X%X%X%X%X%X%X*", n, 
	   row[0], row[1], row[2], row[3],
	   row[4], row[5], row[6], row[7]);
#endif

  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      r[0] != 'a' || r[1] != '*')
    fprintf(stderr, "%s\n", r);
}

void
gm_mled88(ASY_HANDLE asy, char *led)
{
  char s[BUFSIZ], r[BUFSIZ];
  int i, j;

  if (configuration != 7)
    return;

  for (i=0; i<8; i ++) {
    for (j=0; j<8; j ++)
      if (led[i*8 + j]<0)
	led[i*8 + j]= 0;
      else if (led[i*8 + j]>0xf)
	led[i*8 + j] = 0xf;

#ifndef WINDOWS
	snprintf(s, BUFSIZ-1, "a%X%X%X%X%X%X%X%X%X*", i, 
	     led[i*8 + 0], led[i*8 + 1], led[i*8 + 2], led[i*8 + 3],
	     led[i*8 + 4], led[i*8 + 5], led[i*8 + 6], led[i*8 + 7]);
#else
	_snprintf(s, BUFSIZ-1, "a%X%X%X%X%X%X%X%X%X*", i, 
	     led[i*8 + 0], led[i*8 + 1], led[i*8 + 2], led[i*8 + 3],
	     led[i*8 + 4], led[i*8 + 5], led[i*8 + 6], led[i*8 + 7]);
#endif
	asy_write(asy, s, strlen(s));
    usleep(5*1000); // * を送った後、すぐに次のコマンドを送ってはいけない(?!)
  }
  usleep(5*1000);
  for (i=0; i<8; i ++) {
    if (asy_read(asy, r, BUFSIZ-1)<0 ||
	r[0] != 'a' || r[1] != '*')
      fprintf(stderr, "%s\n", r);
  }
}

ASY_HANDLE
gm_open(const char *dev, int mode)
{
  ASY_HANDLE asy;

  asy = asy_open(dev);
  /*
    speed: 38400bps, stop bit 1, no parity, no flow control
    all values are in hex and should be in upper case (e.g. 0A, F8...)
  */
#ifndef WINDOWS
  asy_init(asy, B38400);
#else
  asy_init(asy, 38400);
#endif

  gm_reset(asy);
  gm_configuration(asy, mode);

  return asy;
}

void
gm_rc(ASY_HANDLE asy, int *a, int n)
{
  char s[BUFSIZ], r[BUFSIZ];
  int i;

  if (n<0)
    return;
  if (!(configuration == 8 && n == 8))
    return;

  for (i=0; i<n; i ++)
    if (a[i]<0)
      a[i]= 0;
    else if (a[i]>0xff)
      a[i] = 0xff;

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "P%02X%02X%02X%02X%02X%02X%02X%02X*", a[0], a[1], a[2], a[3],
	   a[4], a[5], a[6], a[7]);
#else
  _snprintf(s, BUFSIZ-1, "P%02X%02X%02X%02X%02X%02X%02X%02X*", a[0], a[1], a[2], a[3],
	   a[4], a[5], a[6], a[7]);
#endif

  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      r[0] != 'P' || r[1] != '*')
    fprintf(stderr, "%s\n", r);
}

void
gm_rc1(ASY_HANDLE asy, int n, int a)
{
  char s[BUFSIZ], r[BUFSIZ];

  if (n<0)
    return;
  if (!(configuration == 8 && n < 8))
    return;

  if (a<0)
    a = 0;
  else if (a>0xff)
    a = 0xff;

#ifndef WINDOWS
  snprintf(s, BUFSIZ-1, "p%X%02X*", n, a);
#else
  _snprintf(s, BUFSIZ-1, "p%X%02X*", n, a);
#endif
  asy_write(asy, s, strlen(s));
  usleep(5*1000);
  if (asy_read(asy, r, BUFSIZ-1)<0 ||
      strcmp(s, r) != 0)
    fprintf(stderr, "%s\n", r);
}

void
gm_reset(ASY_HANDLE asy)
{
  const char reset[] = "Q*";
  char buf[BUFSIZ];

  asy_write(asy, reset, 2);
  asy_write(asy, reset, 2);
  usleep(100*1000);
#ifndef WINDOWS
  tcflush(asy, TCIFLUSH); /* ignore anything recieved */
#else
  // Discard input buffer
  usleep(200*1000);
  asy_read(asy, buf, BUFSIZ - 1);
#endif
  usleep(200*1000);

  asy_write(asy, reset, 2);
  usleep(200*1000);
  if (asy_read(asy, buf, BUFSIZ - 1) < 0 ||
      strcmp(buf, reset) != 0) {
    fprintf(stderr, "Reset command (%s) failed\n", reset);
    exit(1);
  }
}


int hex2int(int c)
{
  if (c>='0' && c<='9')
    return c - '0';

  return c - 'A' + 0xa;
}

/*
  Below, I put my memorandoms. 

  Programable Gain (Note: meaning is different for Gainer mini. 
                    See Gainer mini's source code)
  Gxy	Gxy*	set PGA gain and PGA reference, x: gain, y: reference

  Misc.		
  Vx	Vx*	verbose mode, x: mode (0: disabled, 1: enabled)
  ?	?1.0.0.xx*	version number, xx: build number
*/
