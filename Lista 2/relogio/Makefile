# MPLAB IDE generated this makefile for use with GNU make.
# Project: relogio.mcp
# Date: Tue Apr 04 12:14:51 2023

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

relogio.cof : q1.o
	$(LD) /p18F4520 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "q1.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"relogio.cof" /M"relogio.map" /W

q1.o : q1.c ../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4520.h
	$(CC) -p=18F4520 "q1.c" -fo="q1.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "q1.o" "relogio.cof" "relogio.hex"

