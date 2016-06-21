/*

  Chess.pde
  
  Little Rook Chess

  Modified for the Arduboy, 2016. ross@arduboy.com.
  
  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/
  
  Copyright (c) 2012, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  

*/

#include "U8glib.h"

U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(15, 16, 12, 4, 6);

uint8_t uiKeyPrev = A2;
uint8_t uiKeyNext = A1;
uint8_t uiKeySelect = 7;
uint8_t uiKeyBack = 8;

uint8_t uiKeyCodeFirst = CHESS_KEY_NONE;
uint8_t uiKeyCodeSecond = CHESS_KEY_NONE;
uint8_t uiKeyCode = CHESS_KEY_NONE;


void uiSetup(void) {
  // configure input keys 
#if defined(ARDUINO)
  pinMode(uiKeyPrev, INPUT_PULLUP);           // set pin to input
  pinMode(uiKeyNext, INPUT_PULLUP);           // set pin to input
  pinMode(uiKeySelect, INPUT_PULLUP);           // set pin to input
  pinMode(uiKeyBack, INPUT_PULLUP);           // set pin to input
#endif
}

void uiStep(void)
{
  uiKeyCodeSecond = uiKeyCodeFirst;
#if defined(ARDUINO)
  if ( digitalRead(uiKeyPrev) == LOW )
    uiKeyCodeFirst = CHESS_KEY_PREV;
  else if ( digitalRead(uiKeyNext) == LOW )
    uiKeyCodeFirst = CHESS_KEY_NEXT;
  else if ( digitalRead(uiKeySelect) == LOW )
    uiKeyCodeFirst = CHESS_KEY_SELECT;
  else if ( digitalRead(uiKeyBack) == LOW )
    uiKeyCodeFirst = CHESS_KEY_BACK;
  else
#endif
    uiKeyCodeFirst = CHESS_KEY_NONE;

  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = CHESS_KEY_NONE;
}

void setup() {
  // rotate screen, if required
  //u8g.setRot180();
  
  uiSetup();
  chess_Init(u8g.getU8g(), 0);
}

void loop() {  
  uint8_t keyCode = CHESS_KEY_NONE;
  
  u8g.firstPage();
  do {
    chess_Draw();
    uiStep();
    if ( uiKeyCode != CHESS_KEY_NONE )
      keyCode = uiKeyCode;
  } while( u8g.nextPage() );
  
  u8g_Delay(10);
  chess_Step(keyCode);
  uiStep();
  keyCode = uiKeyCode;
}
