/*  USB<->CAN Interface for the Arduino
 *  Copyright (c) 2013 Phil Birkelbach
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __CAN_H
#define __CAN_H 0x01

#include "Arduino.h"
#include <SPI.h>

#define CMD_RESET    0xC0
#define CMD_READ     0x03
#define CMD_WRITE    0x02
#define CMD_RXSTATUS 0xB0
#define CMD_READRXB  0x90
#define CMD_WRITETXB 0x40
#define CMD_RTS      0x80
#define CMD_RTS0     0x81
#define CMD_RTS1     0x82
#define CMD_RTS2     0x84

#define REG_CANCTRL   0x0F
#define REG_CANSTAT   0x0E
#define REG_CNF3      0x28
#define REG_CNF2      0x29
#define REG_CNF1      0x2A
#define REG_CANINTE   0x2B
#define REG_CANINTF   0x2C
#define REG_EFLG      0x2D
#define REG_TXB0CTRL  0x30
#define REG_TXB1CTRL  0x40
#define REG_TXB2CTRL  0x50
#define REG_RXB0CTRL  0x60
#define REG_RXB1CTRL  0x70
#define REG_TEC       0x1C
#define REG_REC       0x1D
#define REG_RXF0SIDH  0x00
#define REG_RXF1SIDH  0x04
#define REG_RXF2SIDH  0x08
#define REG_RXF3SIDH  0x10
#define REG_RXF4SIDH  0x14
#define REG_RXF5SIDH  0x18
#define REG_RXM0SIDH  0x20
#define REG_RXM1SIDH  0x24

#define RXB0CTRL_BUKT 0x04

#define EFLG_EWARN    0x01
#define EFLG_RXWAR    0x02
#define EFLG_TXWAR    0x04
#define EFLG_RXEP     0x08
#define EFLG_TXEP     0x10
#define EFLG_TXBO     0x20
#define EFLG_RX0OVR   0x40
#define EFLG_RX1OVR   0x80

//Bits
#define TXREQ         0x08

#ifndef CAN_MHZ
#define CAN_MHZ 16
#endif

#if CAN_MHZ == 20

#define CNF1_125 0x03
#define CNF2_125 0xB6
#define CNF3_125 0x04

#define CNF1_250 0x01
#define CNF2_250 0xB6
#define CNF3_250 0x04

#define CNF1_500 0x00
#define CNF2_500 0xB6
#define CNF3_500 0x04

#define CNF1_1000 0x00
#define CNF2_1000 0x92
#define CNF3_1000 0x02

#else

#define CNF1_125 0x03
#define CNF2_125 0xB8
#define CNF3_125 0x05

#define CNF1_250 0x01
#define CNF2_250 0xB8
#define CNF3_250 0x05

#define CNF1_500 0x00
#define CNF2_500 0xB8
#define CNF3_500 0x05

#define CNF1_1000 0x80
#define CNF2_1000 0x90
#define CNF3_1000 0x02

#endif

#define MODE_NORMAL 0x00
#define MODE_CONFIG 0x80

#define CAN_SETTINGS SPISettings(8000000, MSBFIRST, SPI_MODE0)

typedef struct {
  unsigned long id;
  byte eid;
  byte length;
  byte data[8];
} CanFrame;


class CAN
{
private:
  byte mode;
  byte ss_pin;
  void write(byte reg, byte *buff, byte count);
  void read(byte reg, byte *buff, byte count);
  CanFrame reg2frame(byte *regs);
  void frame2reg(CanFrame, byte *regs);
public:
  CAN(byte pin);
  void sendCommand(byte command);
  void setBitRate(int bitrate);
  void setMode(byte mode);
  byte getMode(void);
  byte getRxStatus(void);
  CanFrame readFrame(byte rxb);
  byte writeFrame(CanFrame frame);
  int writeFilter(CanFrame frame, byte filter);
  int writeMask(CanFrame frame, byte mask);
};

#endif /* __CAN_H */
