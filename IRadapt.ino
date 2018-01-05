#include <RCSwitch.h>
#include <IRremote.h>
//#include <IRremoteInt.h>
#include "Beomote.h"
#include "codes.h"

#define DEBUG

//IR 38Khz transmitter - pin D3

#define BOTxPin 10      //B&O IR receive  - pin D10
#define RECV_PIN 11     //38KHz IR receiver  - pin D11

IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irtx;

RCSwitch rxSwitch = RCSwitch();
RCSwitch txSwitch = RCSwitch();

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
  Beo.initialize(BOTxPin);
  txSwitch.enableTransmit(9);   //pin D9

  #ifdef DEBUG
  //38 KHz IR receiver
  irrecv.enableIRIn();
  //433MHz receiver
  rxSwitch.enableReceive(0);    //pin D2
  #endif
}

BeoCommand LastCmd;
unsigned char OutLetSwitch[2];
  
void loop()
{
  BeoCommand cmd;

  #ifdef DEBUG
  //show received rf 433MHz command
  if(rxSwitch.available())
  {
    output( rxSwitch.getReceivedValue(),
            rxSwitch.getReceivedBitlength(),
            rxSwitch.getReceivedDelay(),
            rxSwitch.getReceivedRawdata(),
            rxSwitch.getReceivedProtocol() );
    rxSwitch.resetAvailable();
  }

  //show 38KHz IR code
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
  #endif
  
  if(Beo.receive(cmd))
  {
    switch(cmd.address)
    {
      case 160:
      case SOURCE_VIDEO:
        if(cmd.command == BR1_BTN_REPEAT)
        {
          //delay(60);    //the beoremote one repeat faster than the tv can receive
          cmd.command = LastCmd.command;
        }
        
        //save last command, in case we get repeat
        LastCmd.command = cmd.command;
        
        switch(cmd.command)
        {
          case BR1_PAUSE:     irtx.sendSAMSUNG(SAMSUNG_STOP, 32); break;
          case BR1_PLAY:      irtx.sendSAMSUNG(SAMSUNG_PLAY, 32); break;
          case BR1_GO:        irtx.sendSAMSUNG(SAMSUNG_ENTER, 32); break;
          case BR1_BACK:      irtx.sendSAMSUNG(SAMSUNG_EXIT, 32); break;
          case BR1_UP:        irtx.sendSAMSUNG(SAMSUNG_UP, 32); break;
          case BR1_DOWN:      irtx.sendSAMSUNG(SAMSUNG_DOWN, 32); break;
          case BR1_LEFT:      irtx.sendSAMSUNG(SAMSUNG_LEFT, 32); break;
          case BR1_RIGHT:     irtx.sendSAMSUNG(SAMSUNG_RIGHT, 32); break;
          case BR1_FAST_BACK: irtx.sendSAMSUNG(SAMSUNG_FAST_BACK, 32); break;
          case BR1_FAST_FOR:  irtx.sendSAMSUNG(SAMSUNG_FAST_FOR, 32); break;
          case BR1_P_UP:      irtx.sendSAMSUNG(SAMSUNG_P_UP, 32); break;
          case BR1_P_DOWN:    irtx.sendSAMSUNG(SAMSUNG_P_DOWN, 32); break;
          case BR1_INFO:      irtx.sendSAMSUNG(SAMSUNG_RETURN, 32); break;    //context menu
          case STANDBY:       irtx.sendSAMSUNG(SAMSUNG_POWER, 32); break;
          case VOLUME_UP:     irtx.sendSAMSUNG(SAMSUNG_VOLUME_UP, 32); break;
          case VOLUME_DOWN:   irtx.sendSAMSUNG(SAMSUNG_VOLUME_DOWN, 32); break;
          case MENU:          irtx.sendSAMSUNG(SAMSUNG_MENU, 32); break;
          case MUTE:          irtx.sendSAMSUNG(SAMSUNG_MUTE, 32); break;
          /*case NUMBER_0:      irtx.sendSAMSUNG(SAMSUNG_0, 32); break;
          case NUMBER_1:      irtx.sendSAMSUNG(SAMSUNG_1, 32); break;
          case NUMBER_2:      irtx.sendSAMSUNG(SAMSUNG_2, 32); break;
          case NUMBER_3:      irtx.sendSAMSUNG(SAMSUNG_3, 32); break;
          case NUMBER_4:      irtx.sendSAMSUNG(SAMSUNG_4, 32); break;
          case NUMBER_5:      irtx.sendSAMSUNG(SAMSUNG_5, 32); break;
          case NUMBER_6:      irtx.sendSAMSUNG(SAMSUNG_6, 32); break;
          case NUMBER_7:      irtx.sendSAMSUNG(SAMSUNG_7, 32); break;
          case NUMBER_8:      irtx.sendSAMSUNG(SAMSUNG_8, 32); break;
          case NUMBER_9:      irtx.sendSAMSUNG(SAMSUNG_9, 32); break;*/
          case YELLOW:        irtx.sendSAMSUNG(SAMSUNG_YELLOW, 32); break;
          case GREEN:         irtx.sendSAMSUNG(SAMSUNG_GREEN, 32); break;
          case BLUE:          irtx.sendSAMSUNG(SAMSUNG_BLUE, 32); break;
          case RED:           irtx.sendSAMSUNG(SAMSUNG_RED, 32); break;
          
          //BR1_GUIDE: not used
        }
      break;
      case 161:
      case SOURCE_AUDIO:

        switch(cmd.command)
        {
          case STANDBY:   txSwitch.send(CH1_OFF, 24); break;
          case RADIO:     txSwitch.send(CH1_ON, 24);  break;
        }      
      break;
      case SOURCE_CONTROL:

        switch(cmd.command)
        {
          case NUMBER_1:
            OutLetSwitch[0] = !OutLetSwitch[0];
            if(OutLetSwitch[0])
              txSwitch.send(CH2_OFF, 24);
            else
              txSwitch.send(CH2_ON, 24);

            break;
          case NUMBER_2:
            OutLetSwitch[1] = !OutLetSwitch[1];
            if(OutLetSwitch[1])
              txSwitch.send(CH3_OFF, 24);
            else
              txSwitch.send(CH3_ON, 24);
            break;        
        }
      break;     
      case SOURCE_LIGHT:
        switch(cmd.command)
        {
          case BR1_GO:
            txSwitch.send(LED_POWER, 24);
          break;
          case LEFT:
            txSwitch.send(LED_COLOR_DOWN, 24);
          break;
          case RIGHT:
            txSwitch.send(LED_COLOR_UP, 24);
          break;
          case UP:
            txSwitch.send(LED_BRIGHT_UP, 24);
          break;
          case DOWN:
            txSwitch.send(LED_BRIGHT_DOWN, 24);
          break;
        }
      break;
    }

    #ifdef DEBUG
    //show B&O receied code

    //printf("B&O, link: %d, addr: %d, cmd: %x\n", cmd.link, cmd.address, cmd.command);
    

    Serial.print("addr: ");
    Serial.println(cmd.address);
    Serial.print("cmd: ");
    Serial.println(cmd.command, HEX);
    #endif
  }
}


#ifdef DEBUG
void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  }
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  }
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address,HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
     Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
     Serial.print("Decoded JVC: ");

  }
  else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
  }
  else if (results->decode_type == WHYNTER) {
     Serial.print("Decoded Whynter: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.print((int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(",");
  }
  Serial.println("");
}

void output(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {

  if (decimal == 0) {
    Serial.print("Unknown encoding.");
  } else {
    char* b = dec2binWzerofill(decimal, length);
    Serial.print("Decimal: ");
    Serial.print(decimal);
    Serial.print(" (");
    Serial.print( length );
    Serial.print("Bit) Binary: ");
    Serial.print( b );
    Serial.print(" Tri-State: ");
    Serial.print( bin2tristate( b) );
    Serial.print(" PulseLength: ");
    Serial.print(delay);
    Serial.print(" microseconds");
    Serial.print(" Protocol: ");
    Serial.println(protocol);
  }
  
  Serial.print("Raw data: ");
  for (int i=0; i<= length*2; i++) {
    Serial.print(raw[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.println();
}


static char* bin2tristate(char* bin) {
  char returnValue[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos]!='\0' && bin[pos+1]!='\0') {
    if (bin[pos]=='0' && bin[pos+1]=='0') {
      returnValue[pos2] = '0';
    } else if (bin[pos]=='1' && bin[pos+1]=='1') {
      returnValue[pos2] = '1';
    } else if (bin[pos]=='0' && bin[pos+1]=='1') {
      returnValue[pos2] = 'F';
    } else {
      return "not applicable";
    }
    pos = pos+2;
    pos2++;
  }
  returnValue[pos2] = '\0';
  return returnValue;
}

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength){
  static char bin[64]; 
  unsigned int i=0;

  while (Dec > 0) {
    bin[32+i++] = (Dec & 1 > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j< bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    }else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';
  
  return bin;
}
#endif


