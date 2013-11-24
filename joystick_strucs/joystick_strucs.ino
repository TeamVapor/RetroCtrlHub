
/*
  SNES Controller interface
  Based on NES Controller by Sebastian Tomczak
 
  Pinouts, clock times, communication protocol, etc...:
  http://www.gamefaqs.com/snes/916396-snes/faqs/5395
*/
 
// Controller buttons
// (based on button-to-clock pulse assignment)
#define SNES_B        32768  // 1000000000000000
#define SNES_Y        16384  // 0100000000000000
#define SNES_SELECT   8192   // 0010000000000000
#define SNES_START    4096   // 0001000000000000
#define SNES_UP       2048   // 0000100000000000
#define SNES_DOWN     1024   // 0000010000000000
#define SNES_LEFT      512   // 0000001000000000
#define SNES_RIGHT     256   // 0000000100000000
#define SNES_A         128   // 0000000010000000
#define SNES_X          64   // 0000000001000000
#define SNES_L          32   // 0000000000100000
#define SNES_R          16   // 0000000000010000
 
// Arduino pins vs. SNES controller pins
// (default is latch 2, clock 3, data 4)
int LatchPin  = 2; // Latch
int ClockPin  = 3; // Clock
int DataPin   = 4; // Serial Data
 
// Current controller data
unsigned int ControllerData = 0;
 
struct ControllerState{
byte b;
byte y;
byte SELECT;
byte START;
byte up;
byte down;
byte left;
byte right;
byte a;
byte x; 
byte l;
byte r;
};
 
// Setup the controller and serial output
void setup() 
{
  pinMode(LatchPin,OUTPUT);
  pinMode(ClockPin,OUTPUT);
  pinMode(DataPin,INPUT);
 
  digitalWrite(LatchPin,HIGH);
  digitalWrite(ClockPin,HIGH);
}
 
// Read controller
void controllerRead() 
{
  // Reset controller states and data
  ControllerData = 0;
  digitalWrite(LatchPin,LOW);
  digitalWrite(ClockPin,HIGH);
 
  // Controller needs to latch the state of all buttons
  digitalWrite(LatchPin,HIGH);
  delayMicroseconds(12);
  digitalWrite(LatchPin,LOW);
  delayMicroseconds(6);
 
  // Read controller data (initial reading)
  ControllerData = digitalRead(DataPin);
 
  // Send 16 clock pulses, one for each button. 
  for (int i = 0; i < 16; i ++) 
  {
    digitalWrite(ClockPin,LOW);
    delayMicroseconds(6);
    ControllerData = ControllerData << 1;
    ControllerData = ControllerData + digitalRead(DataPin) ;
    delayMicroseconds(6);
    digitalWrite(ClockPin,HIGH);
  }
 
  // Do a NOT, so '1' will be pressed buttons and '0' to the rest
  ControllerData = ~ControllerData;
}
 
// Program code
void loop() 
{
  ControllerState state1 = {0,0,0,0,0,0,0,0,0,0,0,0};
  // Read controller data
  controllerRead();
 
  if (ControllerData != 0) 
  {
    if (ControllerData & SNES_B) 
    {
      state1.b = 1;
    }
    if (ControllerData & SNES_Y) 
    {
      state1.y = 1;
    }
    if (ControllerData & SNES_SELECT) 
    {
      state1.SELECT = 1;
    }
    if (ControllerData & SNES_START) 
    {
      state1.START = 1;
    }
    if (ControllerData & SNES_UP) 
    {
      state1.up = 1;
    }
    if (ControllerData & SNES_DOWN) 
    {
      state1.down = 1;
    }
    if (ControllerData & SNES_LEFT) 
    {
      state1.left = 1;
    }
    if (ControllerData & SNES_RIGHT) 
    {
      state1.right = 1;
    }
    if (ControllerData & SNES_A) 
    {
      state1.a = 1;
    }
    if (ControllerData & SNES_X) 
    {
      state1.x = 1;
    }
    if (ControllerData & SNES_L) 
    {
      state1.l = 1;
    }
    if (ControllerData & SNES_R) 
    {
      state1.r = 1;
    }
  }
  
  delay(50);
  
  ControllerState state2 = {0,0,0,0,0,0,0,0,0,0,0,0};
  // Read controller data
  controllerRead();
 
  if (ControllerData != 0) 
  {
    if (ControllerData & SNES_B) 
    {
      state2.b = 1;
    }
    if (ControllerData & SNES_Y) 
    {
      state2.y = 1;
    }
    if (ControllerData & SNES_SELECT) 
    {
      state2.SELECT = 1;
    }
    if (ControllerData & SNES_START) 
    {
      state2.START = 1;
    }
    if (ControllerData & SNES_UP) 
    {
      state2.up = 1;
    }
    if (ControllerData & SNES_DOWN) 
    {
      state2.down = 1;
    }
    if (ControllerData & SNES_LEFT) 
    {
      state2.left = 1;
    }
    if (ControllerData & SNES_RIGHT) 
    {
      state2.right = 1;
    }
    if (ControllerData & SNES_A) 
    {
      state2.a = 1;
    }
    if (ControllerData & SNES_X) 
    {
      state2.x = 1;
    }
    if (ControllerData & SNES_L) 
    {
      state2.l = 1;
    }
    if (ControllerData & SNES_R) 
    {
      state2.r = 1;
    }
  }
  
  if (state1.b != state2.b)
  {
    if(state2.b)
      Joystick.button(1, 1);
    else
      Joystick.button(1, 0);
  }
  if (state1.y != state2.y)
  {
    if(state2.y)
      Joystick.button(2,1);
    else
      Joystick.button(2,0);
  }
  if (state1.SELECT != state2.SELECT)
  {
    if(state2.SELECT)
      Joystick.button(3,1);
    else
      Joystick.button(3,0);
  }
  if (state1.START != state2.START)
  {
    if(state2.START)
    {
      if(state2.SELECT)
        Joystick.button(31,1);
      else
      {
        Joystick.button(4,1);
        Joystick.button(31,0);
      }
    }
    else
    {
      Joystick.button(4,0);
      Joystick.button(31,0);
    }
  }
  if (state1.up != state2.up)
  {
    if(state2.up)
      Joystick.button(5,1);
    else
      Joystick.button(5,0);
  }
  if (state1.down != state2.down)
  {
    if(state2.down)
      Joystick.button(6,1);
    else
      Joystick.button(6,0);
  }
  if (state1.left != state2.left)
  {
    if(state2.left)
      Joystick.button(7,1);
    else
      Joystick.button(7,0);
  }
  if (state1.right != state2.right)
  {
    if(state2.right)
      Joystick.button(8,1);
    else
      Joystick.button(8,0);
  }
  if (state1.a != state2.a)
  {
    if(state2.a)
      Joystick.button(9,1);
    else
      Joystick.button(9,0);
  }
  if (state1.x != state2.x)
  {
    if(state2.x)
      Joystick.button(10,1);
    else
      Joystick.button(10,0);
  }
  if (state1.l != state2.l)
  {
    if(state2.l)
      Joystick.button(11,1);
    else
      Joystick.button(11,0);
  }
  if (state1.r != state2.r)
  {
    if(state2.r)
      Joystick.button(12,1);
    else
      Joystick.button(12,0);
  }
}
