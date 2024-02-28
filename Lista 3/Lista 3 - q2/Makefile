# MPLAB IDE generated this makefile for use with GNU make.
# Project: q2.mcp
# Date: Sat May 06 11:49:16 2023

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

q2.cof : q2.o
	$(LD) /p18F4520 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "q2.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"q2.cof" /M"q2.map" /W

q2.o : q2.c ../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4520.h
	$(CC) -p=18F4520 "q2.c" -fo="q2.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "q2.o" "q2.cof" "q2.hex"

