/* Gainer (GainerMini) のためのライブラリ       */
/* GNU GPL version 3 以降に従った配布を認めます */
/* This program is distributed under the license GNU GPL version 3 or later. */
/* Copyright (c) 2009 Noriaki Mitsunaga         */

#ifndef __GAINER_LIB_H__
#define __GAINER_LIB_H__

#define WINDOWS

#ifndef WINDOWS
// #include <termios.h>
#include <termios.h>
#define ASY_HANDLE int
#else
#include <windows.h>
#define ASY_HANDLE HANDLE
#define usleep(x) Sleep((x)/1000)
#endif

#ifndef WINDOWS
int  asy_init(ASY_HANDLE fd, speed_t speed);
#else
int  asy_init(ASY_HANDLE fd, int speed);
#endif
ASY_HANDLE  asy_open(const char *dev);
int  gm_ain(ASY_HANDLE asy, int *a, int n);
void gm_aout(ASY_HANDLE asy, int *a, int n);
void gm_aout1(ASY_HANDLE asy, int n, int a);
int  gm_configuration(ASY_HANDLE asy, int n);
unsigned long gm_din(ASY_HANDLE asy);
void gm_dH(ASY_HANDLE asy, int n);
void gm_dL(ASY_HANDLE asy, int n);
void gm_dout(ASY_HANDLE asy, int d);
void gm_led_on(ASY_HANDLE asy);
void gm_led_off(ASY_HANDLE asy);
void gm_mled(ASY_HANDLE asy, int n, int *row);
void gm_mled88(ASY_HANDLE asy, char *led);
ASY_HANDLE gm_open(const char *dev, int mode);
void gm_rc(ASY_HANDLE asy, int *a, int n);
void gm_rc1(ASY_HANDLE asy, int n, int a);
void gm_reset(ASY_HANDLE asy);
int  asy_read(ASY_HANDLE fd, char buf[], int len);
int  asy_write(ASY_HANDLE fd, const char buf[], int len);

extern void (*gm_button_pressed)(void);
extern void (*gm_button_released)(void);

#ifndef WINDOWS
#define asy_write(X, Y, Z) write((X), (Y), (Z))
#endif

#endif
