//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GLOBAL PARAMETERS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//------------> Including external libraries:
#include <LiquidCrystal.h> // Library of liquid-crystal screen


//------------> Creating objects
LiquidCrystal lcd (A3, 7, 8, 11, 12, 13); // Liquid-crystal screen object: RS, E, D4, D5, D6, D7


//------------> Digital OUTPUTs of selectors for analog MUXes:
#define MUX_S0 2 // Selector S0
#define MUX_S1 3 // Selector S1
#define MUX_S2 4 // Selector S2


//------------> Digital OUTPUTs for LEDs
#define LED1 10 // Led 1 FX1 state
#define LED2 5 // Led 2 FX2 state
#define LED3 9 // Led 3 Rack1 state
#define LED4 6 // Led 4 Rack2 state


//------------> Analog INPUTs for pots:
#define POT_PIN1 A0 // MUX#1, 0-7
#define POT_PIN2 A1 // MUX#2, 8-15


//------------> Analog INPUTs for buttons: 
#define BUTT_PIN1 A2 // MUX#3, 16-23


//------------> Array for storing actual names of the effects:
const char* effects [28] = {"LFO", "LFD", "HAA", "FSH", "PSH", "EQL", "MRR", "SAT", "H/C", "OTO", "TUB", "FRM", "MSF",
"CMB", "FIL", "PHS", "FL1", "CHR", "FL2", "B/C", "AMP", "SH1", "SH2", "EVL", "DEL", "DIF", "GRN", "RVB"};

//------------> Array for storing names of all parameters of all effects (except for common):
const char* fxControls [124] = {
"Frm", "Temp", "Mod", "Shft", "Snc", "Frq", "Wdth", "Att", "Dec", "Sus", "Rel", "EnvOn", 
"Frq", "Temp", "Mod", "Shft", 
"DelL", 
"FSh+/-","Rng", 
"Shft", "Fin", "Rat", "MIDI", 
"Ptch", "Res", "Q", "Res", "Q", "Res", "Q",
"Min", "Max", 
"Sat", "GainC", 
"Ptch", "Amp", "Mod", 
"1", "2", 
"In", "Main", "Drv", "BasDrv", "Mode", "Fb", "HP", "Bass", "Bass", "Mode", 
"Horiz", "Vert", 
"Ptch", "Res", 
"Ptch", "Fb", "Mix", 
"Res", "Cut", "FltEnv", "Typ", "KeyTr", "Att", "Dec", "Sus", "Rel", "Invrt", 
"Cntr", "ModFr", "ModAmp", "Fb", 
"Frq1", "Amp1", "Frq2", "Amp2", 
"Frq", 
"Bits", "SmpRt", 
"Drv", "Asym", "Emphs", "Ton", 
"ModAmp", "ModPit", "Slp0+", "Slp0-", "Sl+Mod", "BrptUp", "BrptDn", "SlpUp", "SlpUpDn", "Sl-Mod", 
"Drv", 
"Push", "Evl", "Dist", "Drv", "Pop", 
"Del", "Fb", "Menu", 
"Del", "Dfs", "Fb", "Menu", 
"Ptch", "Dstn", "Temp", "Fb", "Dirctn", "PitShf", "LFOF", "LFOA", "GrnLen", "Del", "Att", "Dec", "Amp", "Frz", 
"DecTim", "HiDmp"};


//------------> Array for storing number of available for tweaking parameters for the corresponding effect (when alone):
const int availableParameters[28] = {4, 4, 1, 2, 3, 3, 2, 2, 3, 0, 4, 2, 2, 3, 4, 4, 4, 4, 1, 2, 4, 4, 1, 4, 3, 4, 4, 2};

//------------> Array for storing number of available for tweaking parameters for the corresponding effect (when both are the same effect):
const int availableParametersDual[28] = {6, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 1, 0, 0, 8, 0};

//------------> Array for storing number of available for tweaking buttons for the corresponding effect (when alone):
const bool availableButtons[28] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};

//------------> Array for storing number of available for tweaking buttons for the corresponding effect (when both are the same effect):
const bool availableButtonsDual[28] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};

//------------> Array for storing starting CC for effect:
const int firstCC[28] = {0, 12, 16, 17, 19, 23, 30, 32, 34, 37, 39, 49, 51, 53, 56, 66, 70, 74, 78, 79, 81, 85, 95, 96, 101, 104, 108, 122};


//------------> Array for storing last state of buttons (On/Off):
bool buttonsState[28] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//------------> Array for storing last state of buttons (On/Off):
bool buttonsState2[28] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


//------------> MIDI channel initial settings
int rack1Channel[2] = {1,2}; // Rack 1 is on the 1st and the 2nd channels
int rack2Channel[2] = {1,2}; // Rack 2 is on the 3rd and the 4th channels


//------------> MASTER Mode initial settings
bool masterMode = 1; //0 = FX1 and FX2 are different effect; 1 = FX1 and FX2 are the same effect


//------------> Both racks of effects ON/OFF initial settings
bool rackStatus [2] = {1,1}; // FX1 and FX2 effect racks are ON


//------------> Initial #'s of FX1 and FX2 that are in the focus
int focusFx1 = 0;
int focusFx2 = 0;


//------------> Effects that are ON by default
bool fx1States[28] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
bool fx2States[28] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


//------------> MISC variables
const int ledBrightnessBlue = 5; // Brightness of all leds
const int ledBrightnessRed = 10; // Brightness of all leds

const int debounceInterval = 275; // Next button press is registered only if this time has passed
const int pressedInterval = 1000; // Time to wait when button is pressed to enter the EDIT mode

int currentValue[16]; // Array for storing current reading of the pin
int currentAveragedValue[16]; // Array for storing current averaged value of the selected pot
int lastAveragedValue[16]; // Array for storing last averaged value of the selected pot

const int averageFactor = 3; // Averaging factot - the more it is, the more there is an inertion

bool buttonCurrentReading[8]; // Array for storing current reading of the selected button
bool buttonLastReading[8]; // Array for storing previous reading of the selected button
unsigned long lastPressedTime[8]; // Array for storing time stamps of the last press of the buttons

unsigned long lastDisplayChange = 0; // Var for storing time stamps of the last display change
const int displayHoldTime = 2000; // Time display holds it value before initializing

bool displayInitialised; //0 - no, 1 - yes

bool lastButton; // 0 - ordinary button, 1 - hold button

bool rows[] = {0,0}; //00 - all free, 10 - 1st taken, 01 - 2nd taken, 11 - both taken

int oldContr; // # of last touched controller (1st)
bool oldContrRow; //0 - 1st, 1 - 2nd
int newContr; // # of last touched controller (2nd)
bool newContrRow; //0 - 1st, 1 - 2nd


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SETUP FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() 
{
  //Starting serial object at speed 9600 baud:
  Serial.begin(9600);
  

  //Setting up pins for selectors of MUX's:
  pinMode(MUX_S0, OUTPUT); //Selector 1 of of MUX's
  pinMode(MUX_S1, OUTPUT); //Selector 2 of of MUX's
  pinMode(MUX_S2, OUTPUT); //Selector 3 of of MUX's
  pinMode(LED1, OUTPUT);
  analogWrite(LED1, fx1States[focusFx1] * ledBrightnessBlue); // Current FX1 state
  pinMode(LED2, OUTPUT);  
  pinMode(LED3, OUTPUT);
  analogWrite(LED3, rackStatus[0] * ledBrightnessRed); // Current Rack1 state
  pinMode(LED4, OUTPUT);

  
  //Setting up the LCD's number of columns and rows 
  lcd.begin(16, 2);

   
  //Starting display with proper out:
  initialDisplay();

  //Run Debug function with init setting (COMMENT WHEN DONE)
  //debug(42);
}








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LOOP FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void loop() 
{

  //Go through all pots 5 times and and make a proper action
  for (int t = 0; t < 5; t++)
  {
    for (int p = 0; p < 16; p++) potRead(p);  
  }
    
  //Go through all buttons once and and make a proper action
  for (int b = 0; b < 8; b++) buttonReadAndLeds(b);

  //Check if need to return display to default
  if (millis() - lastDisplayChange > displayHoldTime && displayInitialised == 0) initialDisplay(); 
 
}







//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~initialDisplay() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Setting up the LCD's initial out

void initialDisplay()
{
 
  lcd.clear(); // Let's clear display, btw

  if (masterMode == 1)
  {
    //First row
    lcd.setCursor(0, 0);
    lcd.print(F("<<<<DUALMODE>>>>"));
    lcd.setCursor(0, 1);
    lcd.print(F("FX:"));
    lcd.print(effects[focusFx1]);
    lcd.print(F("("));
    lcd.print(availableParameters[focusFx1] + availableButtons[focusFx1]);
    lcd.print(F("/"));
    lcd.print(availableParametersDual[focusFx1] + availableButtonsDual[focusFx1]);
    lcd.print(F(")"));
    lcd.print(F(","));
    lcd.print(F("("));
    lcd.print(focusFx1 + 1);
    lcd.print(F(")"));
  }


  else if (rack1Channel[0] == rack2Channel[0] && masterMode == 0)
  {
    //First row
    lcd.setCursor(0, 0);
    lcd.print(F("**"));
    lcd.print(F(","));
    lcd.print(effects[focusFx1]);
    lcd.print(F("("));
    lcd.print(availableParameters[focusFx1] + availableButtons[focusFx1]);
    lcd.print(F("/"));
    lcd.print(availableParametersDual[focusFx1] + availableButtonsDual[focusFx1]);
    lcd.print(F(")"));
    lcd.print(F(","));
    lcd.print(F("("));
    lcd.print(focusFx1 + 1);
    lcd.print(F(")"));
  
    
    //Second row  
    lcd.setCursor(0, 1);
    lcd.print(F("**"));
    lcd.print(F(","));
    lcd.print(effects[focusFx2]);
    lcd.print(F("("));
    lcd.print(availableParameters[focusFx2] + availableButtons[focusFx2]);
    lcd.print(F("/"));
    lcd.print(availableParametersDual[focusFx2] + availableButtonsDual[focusFx2]);
    lcd.print(F(")"));
    lcd.print(F(","));
    lcd.print(F("("));
    lcd.print(focusFx2 + 1);
    lcd.print(F(")"));
  }


  else {
    
  
  //First row
  lcd.setCursor(0, 0);
  lcd.print(F("L"));
  lcd.print(rack1Channel[0]);
  lcd.print(F(","));
  lcd.print(effects[focusFx1]);
  lcd.print(F("("));
  lcd.print(availableParameters[focusFx1] + availableButtons[focusFx1]);
  lcd.print(F("/"));
  lcd.print(availableParametersDual[focusFx1] + availableButtonsDual[focusFx1]);
  lcd.print(F(")"));
  lcd.print(F(","));
  lcd.print(F("("));
  lcd.print(focusFx1 + 1);
  lcd.print(F(")"));

  
  //Second row  
  lcd.setCursor(0, 1);
  lcd.print(F("R"));
  lcd.print(rack2Channel[0]);
  lcd.print(F(","));
  lcd.print(effects[focusFx2]);
  lcd.print(F("("));
  lcd.print(availableParameters[focusFx2] + availableButtons[focusFx2]);
  lcd.print(F("/"));
  lcd.print(availableParametersDual[focusFx2] + availableButtonsDual[focusFx2]);
  lcd.print(F(")"));
  lcd.print(F(","));
  lcd.print(F("("));
  lcd.print(focusFx2 + 1);
  lcd.print(F(")"));
  }

  displayInitialised = 1;

  //free up rows
  rows[0] = 0;
  rows[1] = 0;
  
  //free up rows
  oldContr = 42;
  newContr = 42;

/* NEEDED FOR DEBUG
  Serial.println();
  Serial.println();
  Serial.println(F("END"));
  Serial.println();
  Serial.println();
  */
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~updateDisplayButton() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Updating display considering changed pot control
void updateDisplayButton(int contr, bool value)
{

//-----> Controller 0 (FX1 FX-)
  if (contr == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("                "));
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("FX-"));
    lcd.print(F(":"));
    lcd.print(focusFx1 + 1);
    lcd.print(F("("));
    lcd.print(effects[focusFx1]);
    lcd.print(F(")"));
    if (masterMode == 1) lcd.print("+DU");
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    for (int b = 0; b < 28; b++)
    {
      if (fx1States[b] == 1)
      {
        lcd.print(b + 1);
        lcd.print(F(" "));
      }
    }
  }


//-----> Controller 1 (FX2 FX-)
  else if (contr == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("                "));
    lcd.setCursor(0, 0);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(F("FX-"));
    lcd.print(F(":"));
    lcd.print(focusFx2 + 1);
    lcd.print(F("("));
    lcd.print(effects[focusFx2]);
    lcd.print(F(")"));
    if (masterMode == 1) lcd.print(F("+DU"));
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    for (int b = 0; b < 28; b++)
    {
      if (fx1States[b] == 1)
      {
        lcd.print(b + 1);
        lcd.print(F(" "));
      }
    }
  }


//-----> Controller 2 (FX1 FX+)
  else if (contr == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("                "));
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("FX+"));
    lcd.print(F(":"));
    lcd.print(focusFx1 + 1);
    lcd.print(F("("));
    lcd.print(effects[focusFx1]);
    lcd.print(F(")"));
    if (masterMode == 1) lcd.print(F("+DU"));
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    for (int b = 0; b < 28; b++)
    {
      if (fx1States[b] == 1)
      {
        lcd.print(b+1);
        lcd.print(F(" "));
      }
    }
  }


//-----> Controller 3 (FX2 FX+)
  else if (contr == 3)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("                "));
    lcd.setCursor(0, 0);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(F("FX+"));
    lcd.print(F(":"));
    lcd.print(focusFx2 + 1);
    lcd.print(F("("));
    lcd.print(effects[focusFx2]);
    lcd.print(F(")"));
    if (masterMode == 1) lcd.print(F("+DU"));
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    for (int b = 0; b < 28; b++)
    {
      if (fx1States[b] == 1)
      {
        lcd.print(b + 1);
        lcd.print(F(" "));
      }
    }
  }


//-----> Controller 4 (Custom)
  else if (contr == 4 && availableButtons[focusFx1] == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("                "));
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx1]);
    lcd.print(F(":"));
    lcd.print(fxControls[firstCC[focusFx1] + availableParameters[focusFx1]]);
    lcd.print(F(":"));
    if (value == 1) lcd.print(F("ON"));
    else lcd.print(F("OFF"));
 }


//-----> Controller 5 (Custom) (SINGLE)
  else if (contr == 5 && availableButtonsDual[focusFx2] == 1 && masterMode == 0) //Custom
  {
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx2]);
    lcd.print(F(":"));
    lcd.print(fxControls[firstCC[focusFx2] + availableParametersDual[focusFx2]]);
    lcd.print(F(":"));
    if (value == 1) lcd.print(F("ON"));
    else lcd.print(F("OFF"));
 }


//-----> Controller 5 (Custom) (DUAL)
  else if (contr == 5 && availableButtonsDual[focusFx2] == 1 && masterMode == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx2]);
    lcd.print(F(":"));
    lcd.print(fxControls[firstCC[focusFx2] + availableParameters[focusFx2] + availableParametersDual[focusFx2] + 1]);
    lcd.print(F(":"));
    if (value == 1) lcd.print(F("ON"));
    else lcd.print(F("OFF"));
 }


//-----> Controller 6 (FX1 ON)
  else if (contr == 6)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("                "));
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("FX1"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx1]);
    lcd.print(F(":"));
    if (value == 1) lcd.print(F("ON"));
    else lcd.print(F("OFF"));
  }


//-----> Controller 7 (FX2 ON)
  else if (contr == 7)
  {
    lcd.setCursor(0, 1);
    lcd.print(F("                "));
    lcd.setCursor(0, 1);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(F("FX2"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx2]);
    lcd.print(F(":"));
    if (value == 1) lcd.print(F("ON"));
    else lcd.print(F("OFF"));
  }


  displayInitialised = 0; //Display needs to be initialized
  lastDisplayChange = millis(); // Register last display update
  delay (2);

} 



  


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~updateDisplayButtonHold() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Updating display considering changed button control
void updateDisplayButtonHold(int contr, bool value)
{

  lcd.clear(); // Let's clear it

//-----> Controller 0 (FX1 CH-)
  if (contr == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("CH-"));
    lcd.print(F(":"));
    lcd.print(rack1Channel[0]);
    if (masterMode == 1) lcd.print(F(",DUAL"));
    else if (rack1Channel[0] == rack2Channel[0]) lcd.print(F(",1 RACK"));
  }


//-----> Controller 1 (FX2 CH-)
  else if (contr == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(F("CH-"));
    lcd.print(F(":"));
    lcd.print(rack2Channel[0]);
    if (masterMode == 1) lcd.print(F(",DUAL"));
    else if (rack1Channel[0] == rack2Channel[0]) lcd.print(F(",1 RACK"));
  }


//-----> Controller 2 (FX1 CH+)
  else if (contr == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("CH+"));
    lcd.print(F(":"));
    lcd.print(rack1Channel[0]);
    if (masterMode == 1) lcd.print(F(",DUAL"));
    else if (rack1Channel[0] == rack2Channel[0]) lcd.print(F(",1 RACK"));
  }


//-----> Controller 3 (FX2 CH+)
  else if (contr == 3)
  {
    lcd.setCursor(0, 1);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(F("CH+"));
    lcd.print(F(":"));
    lcd.print(rack2Channel[0]);
    if (masterMode == 1) lcd.print(F(",DUAL"));
    else if (rack1Channel[0] == rack2Channel[0]) lcd.print(F(",1 RACK"));
  }


//-----> Controller 4 (FX1 RND)
  else if (contr == 4)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("MASTER"));
    lcd.print(F(":"));
    lcd.print(F("RANDOM"));
  }


//-----> Controller 5 (FX2 RND) (SINGLE)
  else if (contr == 5 && masterMode == 0) //FX2 Random
  {
    lcd.setCursor(0, 1);
    lcd.print(F("R"));
    lcd.print(F(":"));
    lcd.print(F("MASTER"));
    lcd.print(F(":"));
    lcd.print(F("RANDOM"));
  }


//-----> Controller 5 (FX2 RND) (DUAL)
  else if (contr == 5 && masterMode == 1) //FX2 Random
  {
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("MASTER"));
    lcd.print(F(":"));
    lcd.print(F("RANDOM"));
  }


//-----> Controller 6 (FX1 ON/OFF)
  else if (contr == 6)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    if (value == 0) lcd.print(F("OFF"));
    else lcd.print(F("ON"));
  }


//-----> Controller 7 (FX2 ON/OFF) (SINGLE)
  else if (contr == 7 && masterMode == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("R"));
    lcd.print(F(":"));
    if (value == 0) lcd.print(F("OFF"));
    else lcd.print(F("ON"));
  }
  

//-----> Controller 7 (FX2 ON/OFF) (DUAL)
  else if (contr == 7 && masterMode == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("L"));
    lcd.print(F(":"));
    if (value == 0) lcd.print(F("OFF"));
    else lcd.print(F("ON"));
  }


  displayInitialised = 0;
  lastDisplayChange = millis(); // Register last display update
  delay (2);
}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~rowSelectAndClean() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Updating display considering changed pot control

bool rowSelectAndClean(int contr)
{

//------> CONTROLLERS HAVE NOT CHANGED
//---> This is oldContr
  if (contr == oldContr) // Controller hasn't changed
  {
    lcd.setCursor(0, oldContrRow);
    lcd.print(F("                "));//Clean it
    if (newContr != 42) // Current contr becomes last touched (if newContr is already in use)
    {
      int tempContr = newContr; // Save current id of current newContr
      bool tempContrRow = newContrRow; // Save current row of current newContr
      newContr = oldContr; // newContr becomes last touched (it was oldContr)
      newContrRow = oldContrRow; // newContrRow becomes row of last touched (it was oldContr)
      oldContr = tempContr; // Previous newContr is getting older
      oldContrRow = tempContrRow; // Previous newContrRow is getting older
      //debugPot(contr, 0);
      return newContrRow; // Use updated row
    }
    //debugPot(contr, 1);
    return oldContrRow;
  }
  
//---> This is newContr
  else if (contr == newContr) // Controller hasn't changed
  {
    lcd.setCursor(0, newContrRow);
    lcd.print(F("                "));//Clean it
    //debugPot(contr, 2);
    return newContrRow;
  }

  

//-----> ASSIGNING OLD- AND NEW CONTR PROCEDURE
//---> Assigning oldContr
  if (oldContr == 42) 
  {
    oldContr = contr; // First contr is empty
    //debugPot(contr, 3);
  }

//---> Assigning newContr
  else if (contr != oldContr && newContr == 42) 
  {
    newContr = contr; //Second contr is empty
    //debugPot(contr, 4);
  }

//---> Reassigning controls
  else if (contr != oldContr && contr != newContr) //New contr appeared
  {
    oldContr = newContr; // Growing older
    oldContrRow = newContrRow; // Growing older
    newContr = contr;
    //debugPot(contr, 5);
  }




//-----> SETTING THE ROW
//---> First row is free (Assign only left)
  if (rows[0] == 0)
  {
//-> Contr is left and it is old    
    if (oldContr < 8)
    {
      rows[0] = 1;
      oldContrRow = 0;
      lcd.setCursor(0, oldContrRow);
      lcd.print(F("                "));
      //debugPot(contr, 6);
      return oldContrRow;
    }

//-> Contr is left and it is new
    else if (newContr < 8)
    {
      rows[0] = 1;
      newContrRow = 0;
      lcd.setCursor(0, newContrRow);
      lcd.print(F("                "));
      //debugPot(contr, 7);
      return newContrRow;
    }
  }

  
//---> Second row is free (Assign right (old/new) or left (new))
  if (rows[1] == 0)
  
  {
//-> Left (new)    
    if (newContr < 8)
    {
      rows[1] = 1;
      newContrRow = 1;
      lcd.setCursor(0, newContrRow);
      lcd.print(F("                "));
      //debugPot(contr, 8);
      return newContrRow;
    }

//-> Right (old)     
    else if (oldContr > 7 && oldContr < 16)
    {
      rows[1] = 1;
      oldContrRow = 1;
      lcd.setCursor(0, oldContrRow);
      lcd.print(F("                "));
      //debugPot(contr, 9);
      return oldContrRow;
    }

//-> Right (new)    
    else if (newContr > 7 && newContr < 16)
    {
      rows[1] = 1;
      newContrRow = 1;
      lcd.setCursor(0, newContrRow);
      lcd.print(F("                "));
      //debugPot(contr, 10);
      return newContrRow;
    }
  }


//---> Both rows are occupied
  if (rows[0] == 1 && rows[1] == 1)
  {
    newContrRow = !oldContrRow;
    lcd.setCursor(0, newContrRow);
    lcd.print(F("                "));
    //debugPot(contr, 11);
    return newContrRow;
  } 

}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~updateDisplayPot() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Updating display considering changed pot control

void updateDisplayPot(int contr, int CC, int value)
{

  
////-----------------------------------------------------> FX1 (STATIC)

//-----> contr = 0 (FX1 VOL)
  if (contr == 0) 
  {
    lcd.setCursor(0, rowSelectAndClean(contr));
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx1]);
    lcd.print(F(":"));
    lcd.print(F("Volume"));
    lcd.print(F(":"));
    lcd.print(map(value, 0, 125, 0, 99));
    lcd.print(F("%"));
  }


//-----> contr = 1 (FX1 D/W)
  else if (contr == 1) 
  {
    lcd.setCursor(0, rowSelectAndClean(contr));
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx1]);
    lcd.print(F(":"));
    lcd.print(F("DryWet"));
    lcd.print(F(":"));
    lcd.print(map(value, 0, 125, 0, 99));
    lcd.print(F("%"));
  }


////-----> contr = 2-5 (FX1 Par1-4)
  else if (contr > 1 && contr < 6) 
  {
    lcd.setCursor(0, rowSelectAndClean(contr));
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(effects[focusFx1]);
    lcd.print(F(":"));
    lcd.print(fxControls[CC]);
    lcd.print(F(":"));
    lcd.print(map(value, 0, 125, 0, 99));
    lcd.print(F("%"));
  }


////-----> contr = 6 (FX1 MASTER VOLUME)
  else if (contr == 6)
  {
    lcd.setCursor(0, rowSelectAndClean(contr));
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("MASTER"));
    lcd.print(F(":"));
    lcd.print(F("VOL"));
    lcd.print(F(":"));
    lcd.print(map(value, 0, 125, 0, 99));
    lcd.print(F("%"));
  }


////-----> contr == 7 (FX1 MASTER D/W)
  else if (contr == 7)
  {
    lcd.setCursor(0, rowSelectAndClean(contr));
    lcd.print(F("L"));
    lcd.print(F(":"));
    lcd.print(F("MASTER"));
    lcd.print(F(":"));
    lcd.print(F("D/W"));
    lcd.print(F(":"));
    lcd.print(map(value, 0, 125, 0, 99));
    lcd.print(F("%"));
  }
  

////-----------------------------------------------------> FX2 (SINGLE)
////-----> contr = 8 (FX1 VOL)
      else if (contr == 8 && masterMode == 0) 
      {
        lcd.setCursor(0, rowSelectAndClean(contr));
        lcd.print(F("R"));
        lcd.print(F(":"));
        lcd.print(effects[focusFx2]);
        lcd.print(F(":"));
        lcd.print(F("Volume"));
        lcd.print(F(":"));
        lcd.print(map(value, 0, 125, 0, 99));
        lcd.print(F("%"));
      }
    
////-----> contr = 9 (FX1 D/W)
        else if (contr == 9 && masterMode == 0)
      {
        lcd.setCursor(0, rowSelectAndClean(contr));
        lcd.print(F("R"));
        lcd.print(F(":"));
        lcd.print(effects[focusFx2]);
        lcd.print(F(":"));
        lcd.print(F("DryWet"));
        lcd.print(F(":"));
        lcd.print(map(value, 0, 125, 0, 99));
        lcd.print(F("%"));
      }

////-----> contr = 10-13 (FX2 Par1-4)     
      else if (contr > 9 && contr < 14 && masterMode == 0)
      {
        lcd.setCursor(0, rowSelectAndClean(contr));
        lcd.print(F("R"));
        lcd.print(F(":"));
        lcd.print(effects[focusFx2]);
        lcd.print(F(":"));
        lcd.print(fxControls[CC]);
        lcd.print(F(":"));
        lcd.print(map(value, 0, 125, 0, 99));
        lcd.print(F("%"));
      }

////-----> contr = 14 (FX1 MASTER VOLUME)
    else if (contr == 14 && masterMode == 0)
    {
      lcd.setCursor(0, rowSelectAndClean(contr));
      lcd.print(F("R"));
      lcd.print(F(":"));
      lcd.print(F("MASTER"));
      lcd.print(F(":"));
      lcd.print(F("VOL"));
      lcd.print(F(":"));
      lcd.print(map(value, 0, 125, 0, 99));
      lcd.print(F("%"));
    }
  
////-----> contr = 15 (FX1 MASTER D/W)
      else if (contr == 15 && masterMode == 0)
    {
      lcd.setCursor(0, rowSelectAndClean(contr));
      lcd.print(F("R"));
      lcd.print(F(":"));
      lcd.print(F("MASTER"));
      lcd.print(F(":"));
      lcd.print(F("D/W"));
      lcd.print(F(":"));
      lcd.print(map(value, 0, 125, 0, 99));
      lcd.print(F("%"));
    }

 
////-----------------------------------------------------> FX2 (DUAL)
////-----> contr = 8-15 (FX1 additional params)
    else if (contr > 7 && masterMode == 1)
    {
        lcd.setCursor(0, rowSelectAndClean(contr));
        lcd.print(F("R"));
        lcd.print(F(":"));
        lcd.print(effects[focusFx2]);
        lcd.print(F(":"));
        lcd.print(fxControls[CC]);
        lcd.print(F(":"));
        lcd.print(map(value, 0, 125, 0, 99));
        lcd.print(F("%"));
    }

  displayInitialised = 0; //Need to update display
  lastDisplayChange = millis(); // Register last display update
  delay (2);
   
} 
  








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~buttonReadAndLeds() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void buttonReadAndLeds(int contr)
{
  pinSet(contr); // Make appropriate MUX pin to spit out controller's voltage
    
  
  //-----> Read real current button state and put it into buttonCurrentReading[] array
  buttonCurrentReading[contr] = digitalRead(BUTT_PIN1); // These are on MUX @ ANALOG input A2
    

  //-----> If the button has been just pressed and debounce time has passed
  if (buttonCurrentReading[contr] == HIGH && buttonLastReading[contr] == LOW && millis() - lastPressedTime[contr] > debounceInterval)
  {
    buttonPressed(contr);

    lastButton = 0; // last pressed button is ordinary button
  }   
    





  //-----> If the button had been already pressed and still is pressed more than 1000 ms
  if (buttonCurrentReading[contr] == HIGH && buttonLastReading[contr] == HIGH && millis() - lastPressedTime[contr] > pressedInterval)
    {

      
      //---> If CH- is pressed for rack 1
      if (contr == 0)
      {
        if (lastButton == 0) buttonPressed(2);//Undo button pressed effect     
        
        if (rack1Channel[0] == 1)
        {
          rack1Channel[0] = 15;
          rack1Channel[1] = 16;
        }
        else
        {
          rack1Channel[0] -= 2;
          rack1Channel[1] -= 2;
        }
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;
        else masterMode = 0;
        updateDisplayButtonHold(contr, 0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
        //debug(contr);
      }
      
      
      
      
      
      //---> If CH- is pressed for rack 2
      if (contr == 1)
      {

        if (lastButton == 0) buttonPressed(3);//Undo button pressed effect
        
        if (rack2Channel[0] == 1)
        {
          rack2Channel[0] = 15;
          rack2Channel[1] = 16;
        }
        else
        {
          rack2Channel[0] -= 2;
          rack2Channel[1] -= 2;
        }
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;
        else masterMode = 0;
        updateDisplayButtonHold(contr, 0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button

        //debug(contr);
      }



      
      
      //---> If CH+ is pressed for rack 1
      if (contr == 2)
      {

        if (lastButton == 0) buttonPressed(0);//Undo button pressed effect
        
        if (rack1Channel[0] == 15)
        {
          rack1Channel[0] = 1;
          rack1Channel[1] = 2;
        }
        else
        {
          rack1Channel[0] += 2;
          rack1Channel[1] += 2;
        }
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;
        else masterMode = 0;
        updateDisplayButtonHold(contr, 0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button

        //debug(contr);
      }




      
      
      //---> If CH+ is pressed for rack 1
      if (contr == 3)
      {

        if (lastButton == 0) buttonPressed(1);//Undo button pressed effect
        
        if (rack2Channel[0] == 15)
        {
          rack2Channel[0] = 1;
          rack2Channel[1] = 2;
        }
        else
        {
          rack2Channel[0] += 2;
          rack2Channel[1] += 2;
        }
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;
        else masterMode = 0;
        updateDisplayButtonHold(contr, 0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button

        //debug(contr);
      }




      //---> If RND is pressed for rack 1
      if (contr == 4)
      {

        if (lastButton == 0) buttonPressed(4);//Undo button pressed effect
        
        MIDImessage(rack1Channel[0], 29, 127);
        updateDisplayButtonHold(contr, 1);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }



      //---> If RND is pressed for rack 2
      if (contr == 5)
      {

        if (lastButton == 0) buttonPressed(5);//Undo button pressed effect
        
        MIDImessage(rack2Channel[0], 29, 127);
        updateDisplayButtonHold(contr, 1);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }




      //---> If ON is pressed for rack 1
      if (contr == 6)
      {

        if (lastButton == 0) buttonPressed(6);//Undo button pressed effect
        
        rackStatus[0] = !rackStatus[0];
        MIDImessage(rack1Channel[0], 28, rackStatus[0] * 127);
        updateDisplayButtonHold(contr, rackStatus[0]);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button

        //debug(contr);
      }



      //---> If ON is pressed for rack 2
      if (contr == 7 && rack1Channel[0] != rack2Channel[0])
      {
        
        if (lastButton == 0) buttonPressed(6); //Undo button pressed effect
        
        rackStatus[1] = !rackStatus[1];
        updateDisplayButtonHold(contr, rackStatus[1]);
        MIDImessage(rack2Channel[0], 28, rackStatus[1] * 127);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button

        //debug(contr);
      }

      lastButton = 1; // last pressed button was hold
      
    }

    
///-----> LEDS
    analogWrite(LED1, fx1States[focusFx1] * ledBrightnessBlue); // Current FX1 state
    analogWrite(LED3, rackStatus[0] * ledBrightnessRed); // Current Rack1 state
    
    if (rack1Channel[0] != rack2Channel[0]) //Different channels
    {
      analogWrite(LED2, fx2States[focusFx2] * ledBrightnessBlue); // Current FX2 state
      analogWrite(LED4, rackStatus[1] * ledBrightnessRed); // Current Rack1 state 
    }
    
    else // Same channels
    {
      analogWrite(LED4,0);
      
      if (masterMode == 1)//masterMode  = 1
      {
        analogWrite(LED2,0);  
      }
      else analogWrite(LED2, fx1States[focusFx2] * ledBrightnessBlue); // Current FX1 state
    }

    
    buttonLastReading[contr] = buttonCurrentReading[contr]; // End of cycle: update last buttonLastReading[] value with buttonCurrentReading[] value
  }







//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~calcMIDIPot() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Updating display considering changed button control

void calcMIDIPot(int contr, int value)
{ 
  if (contr == 4) contr = 0;
  if (contr == 12) contr = 8;

  
  
////-----------------------------------------------------> FX1 (STATIC) <---------------------------------------------------------\\\\
      
////-----> contr == 0 (VOL)
      if (contr == 0)
      {
        MIDImessage(rack1Channel[0],focusFx1 + 32, value);
        updateDisplayPot(contr, focusFx1 + 32, value);
      }

  
 
////-----> contr == 1 (D/W)
      else if (contr == 1)
      {
        MIDImessage(rack1Channel[0], focusFx1 + 60, value);
        updateDisplayPot(contr, focusFx1 + 60, value);
      }
  

////-----> contr == 2 (Par 1)
      else if (contr == 2 && availableParameters[focusFx1] > 0) // Check if there are assignable parameters
      {
        MIDImessage(rack1Channel[1], firstCC[focusFx1], value);
        updateDisplayPot(contr, firstCC[focusFx1], value);
      }


////-----> contr == 3 (Par 2)
      else if (contr == 3 && availableParameters[focusFx1] > 1) // Check if there are assignable parameters
      {
        MIDImessage(rack1Channel[1], firstCC[focusFx1] + 1, value);
        updateDisplayPot(contr, firstCC[focusFx1] + 1, value);
      }


////-----> contr == 4 (Par 3)
      else if (contr == 4 && availableParameters[focusFx1] > 2) // Check if there are assignable parameters
      {
        MIDImessage(rack1Channel[1], firstCC[focusFx1] + 2, value);
        updateDisplayPot(contr, firstCC[focusFx1] + 2, value);
      }


////-----> contr == 5 (Par 4)
      else if (contr == 5 && availableParameters[focusFx1] > 3) // Check if there are assignable parameters
      {
        MIDImessage(rack1Channel[1], firstCC[focusFx1] + 3, value);
        updateDisplayPot(contr, firstCC[focusFx1] + 3, value);
      }
  

////-----> contr == 6 (MASTER VOl)  
      else if (contr == 6) 
      {
        MIDImessage(rack1Channel[0], 30, value);
        updateDisplayPot(contr, 30, value);
      }
  
  
////-----> contr == 7 (MASTER D/W)
      else if (contr == 7)
      {
        MIDImessage(rack1Channel[0], 31, value);
        updateDisplayPot(contr, 31, value);
      }




/////////////////////--------------------------------> FX2 (DIFFERENT) <-----------------------------------------\\\\\\\\\\\\\\\
 
     
////-----> contr == 8 (VOL)   
    else if (contr == 8 && masterMode == 0)
    {
      MIDImessage(rack2Channel[0],focusFx2 + 32, value);
      updateDisplayPot(contr, focusFx2 + 32, value);
    }
      
  
////-----> contr == 9 (D/W) 
    else if (contr == 9 && masterMode == 0)
    {
      MIDImessage(rack2Channel[0],focusFx2 + 60, value);
      updateDisplayPot(contr, focusFx2 + 60, value);
    }


////-----> contr == 10 (Par 1)
    else if (contr == 10  && masterMode == 0 && availableParameters[focusFx2] > 0) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2], value);
      updateDisplayPot(contr, firstCC[focusFx2], value);
    }


////-----> contr == 11 (Par 2)
    else if (contr == 11  && masterMode == 0 && availableParameters[focusFx2] > 1) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + 1, value);
      updateDisplayPot(contr, firstCC[focusFx2] + 1, value);
    }


////-----> contr == 12 (Par 3)
    else if (contr == 12 && masterMode == 0 && availableParameters[focusFx2] > 2) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + 2, value);
      updateDisplayPot(contr, firstCC[focusFx2] + 2, value);
    }


////-----> contr == 13 (Par 4)
    else if (contr == 13 && masterMode == 0 && availableParameters[focusFx2] > 3) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + 3, value);
      updateDisplayPot(contr, firstCC[focusFx2] + 3, value);
    }
       
  
////-----> contr == 14 (MASTER VOl)
    else if (contr == 14 && masterMode == 0) 
    {
      MIDImessage(rack2Channel[0], 30, value);
      updateDisplayPot(contr, 30, value);
    }
  
  
////-----> contr == 15 (MASTER D/W)
    else if (contr == 15 && masterMode == 0)
    {
      MIDImessage(rack2Channel[0], 31, value);
      updateDisplayPot(contr, 31, value);
    }
    


/////////////////////--------------------------------> FX2 (SAME) <-----------------------------------------\\\\\\\\\\\\\\\
    

////-----> contr == 8 (Par 5)   
    else if (contr == 8 && masterMode == 1 && availableParametersDual[focusFx2] > 0) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2], value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2], value);
    }


////-----> contr == 9 (Par 6)   
    else if (contr == 9 && masterMode == 1 && availableParametersDual[focusFx2] > 1) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[2], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 1, value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 1, value);
    }


////-----> contr == 10 (Par 7)   
    else if (contr == 10 && masterMode == 1 && availableParametersDual[focusFx2] > 2) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[2], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 2, value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 2, value);
    }   


////-----> contr == 11 (Par 8)   
    else if (contr == 11 && masterMode == 1 && availableParametersDual[focusFx2] > 3) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[2], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 3, value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 3, value);
    }


////-----> contr == 12 (Par 9)   
    else if (contr == 12 && masterMode == 1 && availableParametersDual[focusFx2] > 4) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 4, value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 4, value);
    }


////-----> contr == 13 (Par 10)   
    else if (contr == 13 && masterMode == 1 && availableParametersDual[focusFx2] > 5) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 5, value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 5, value);
    }


////-----> contr == 14 (Par 11)   
    else if (contr == 14 && masterMode == 1 && availableParametersDual[focusFx2] > 6) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 6, value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 6, value);
    }


////-----> contr == 15 (Par 12)   
    else if (contr == 15 && masterMode == 1 && availableParametersDual[focusFx2] > 7) // Check if there are assignable parameters
    {
      MIDImessage(rack2Channel[1], firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 7, value);
      updateDisplayPot(contr, firstCC[focusFx2] + availableParameters[focusFx2] + availableButtons[focusFx2] + 7, value);
    } 
  
 


}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~potRead() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void potRead(int contr)
{
  pinSet(contr); // Make appropriate MUX pin to spit out controller's voltage

  if (contr < 8) // These are on MUX @ ANALOG input A0
  {
    currentValue[contr] = map(analogRead(POT_PIN1), 0, 1023, 0, 127); // Log reading @ ANALOG input A0 to currentValue[] array and map it between 0 and 127
    
    currentAveragedValue[contr] = (currentAveragedValue[contr] * (averageFactor - 1) + currentValue[contr]) / averageFactor; // Get the averaged value
    
    if (currentAveragedValue[contr] != lastAveragedValue[contr]) // If current averaged value differs from last value
    {
      calcMIDIPot(contr, currentAveragedValue[contr]); // Calculate and send a (MIDI) message
      
    }         
    lastAveragedValue[contr] = currentAveragedValue[contr]; // Update last value with new current value
  }


  else if (contr > 7 && contr < 16) // These are on MUX @ ANALOG input A1
  {
    currentValue[contr] = map(analogRead(POT_PIN2), 0, 1023, 0, 127); // Log reading @ ANALOG input A1 to currentValue[] array and map it between 0 and 127
    
    currentAveragedValue[contr] = (currentAveragedValue[contr] * (averageFactor - 1) + currentValue[contr]) / averageFactor; // Get the averaged value
    
    if (currentAveragedValue[contr] != lastAveragedValue[contr]) // If current averaged value differs from last value
    {
      calcMIDIPot(contr, currentAveragedValue[contr]); // Calculate and send a (MIDI) message
    }         
    lastAveragedValue[contr] = currentAveragedValue[contr]; // Update last value with new current value
  }
 
}









//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~calcMidiButton() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Updating display considering changed button control
void calcMidiButton(int contr, int value)
{
  
  
  
  //!!!FIX FOR 7 PAGES
  if (contr == 0) // FX1 FX-
  {
    if (focusFx1 == 4) MIDImessage(rack1Channel[0], 88, 125); // Page 1
    else if (focusFx1 == 5) MIDImessage(rack1Channel[0], 88, 80); // Page 2
    else if (focusFx1 == 10) MIDImessage(rack1Channel[0], 88, 55); // Page 3
    else if (focusFx1 == 14) MIDImessage(rack1Channel[0], 88, 35); // Page 4
    else if (focusFx1 == 18) MIDImessage(rack1Channel[0], 88, 15); // Page 5
    else if (focusFx1 == 23) MIDImessage(rack1Channel[0], 88, 5); // Page 6
    else if (focusFx1 == 27) MIDImessage(rack1Channel[0], 88, 0); // Page 7
  }


  //!!!FIX FOR 7 PAGES
  else if (contr == 1) // FX2 FX-
  {
    if (focusFx2 == 4) MIDImessage(rack1Channel[0], 88, 125); // Page 1
    else if (focusFx2 == 5) MIDImessage(rack2Channel[0], 88, 80); // Page 2
    else if (focusFx2 == 10) MIDImessage(rack2Channel[0], 88, 55); // Page 3
    else if (focusFx2 == 14) MIDImessage(rack2Channel[0], 88, 35); // Page 4
    else if (focusFx2 == 18) MIDImessage(rack2Channel[0], 88, 15); // Page 5
    else if (focusFx2 == 23) MIDImessage(rack2Channel[0], 88, 5); // Page 6
    else if (focusFx2 == 27) MIDImessage(rack2Channel[0], 88, 0); // Page 7
  }


    //!!!FIX FOR 7 PAGES
  else if (contr == 2) // FX1 FX+
  {
    if (focusFx1 == 0) MIDImessage(rack1Channel[0], 88, 125); // Page 1
    else if (focusFx1 == 5) MIDImessage(rack1Channel[0], 88, 80); // Page 2
    else if (focusFx1 == 6) MIDImessage(rack1Channel[0], 88, 55); // Page 3
    else if (focusFx1 == 11) MIDImessage(rack1Channel[0], 88, 35); // Page 4
    else if (focusFx1 == 15) MIDImessage(rack1Channel[0], 88, 15); // Page 5
    else if (focusFx1 == 19) MIDImessage(rack1Channel[0], 88, 5); // Page 6
    else if (focusFx1 == 24) MIDImessage(rack1Channel[0], 88, 0); // Page 7
  }


  //!!!FIX FOR 7 PAGES
  else if (contr == 3) // FX2 FX+
  {
    if (focusFx2 == 0) MIDImessage(rack1Channel[0], 88, 125); // Page 1
    else if (focusFx2 == 5) MIDImessage(rack2Channel[0], 88, 80); // Page 2
    else if (focusFx2 == 6) MIDImessage(rack2Channel[0], 88, 55); // Page 3
    else if (focusFx2 == 11) MIDImessage(rack2Channel[0], 88, 35); // Page 4
    else if (focusFx2 == 15) MIDImessage(rack2Channel[0], 88, 15); // Page 5
    else if (focusFx2 == 19) MIDImessage(rack2Channel[0], 88, 5); // Page 6
    else if (focusFx2 == 24) MIDImessage(rack2Channel[0], 88, 0); // Page 7
  }

  
  
  else if (contr == 4 && availableButtons[focusFx1] == 1) 
  {
    MIDImessage(rack1Channel[1], firstCC[focusFx1] + availableParameters[focusFx1], value);
  }


 
  else if (contr == 5 && availableButtonsDual[focusFx2] == 1 && masterMode == 0) 
  {
    MIDImessage(rack2Channel[1], firstCC[focusFx2] + availableParametersDual[focusFx2], value);
  }



  else if (contr == 5 && availableButtonsDual[focusFx2] == 1 && masterMode == 1) 
  {
    MIDImessage(rack2Channel[1], firstCC[focusFx2] + availableParameters[focusFx2] + availableParametersDual[focusFx2] + 1, value);
  }



   else if (contr == 6) 
  {
    MIDImessage(rack1Channel[0], focusFx1, value);
  }


   
  else if (contr == 7) 
  {
    MIDImessage(rack2Channel[0], focusFx2, value);
  }
  
}








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MIDImessage() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function that sends appropriate messages via serial protocol

void MIDImessage(byte command, byte data1, byte data2)
{

  Serial.write(command + 175); //Channel: (176 = CC command (channel 1 pot change)
  Serial.write(data1); // Contrl Change ID: (0 - 127)
  Serial.write(data2); // Control Change value: (0 - 127)

}







//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~pinSet() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This f-n sets the appropriate pin on all MUXes

void pinSet(int pin)
{
  // If controller's # is 0, 8 send an appropriate command to make all MUXes to spit out what is on their 0th pin
  if (pin == 0 || pin == 8 || pin == 16)
  {
    digitalWrite(MUX_S0, LOW);
    digitalWrite(MUX_S1, LOW);
    digitalWrite(MUX_S2, LOW);
  }

  // If controller's # is 1, 9, 17 or 25, send an appropriate command to make all MUXes to spit out what is on their 1st pin
  else if (pin == 1 || pin == 9 || pin == 17)
  {
    digitalWrite(MUX_S0, HIGH);
    digitalWrite(MUX_S1, LOW);
    digitalWrite(MUX_S2, LOW);
  }

  // If controller's # is 2, 10, 18 or 26, send an appropriate command to make all MUXes to spit out what is on their 2nd pin
  else if (pin == 2 || pin == 10 || pin == 18)
  {
    digitalWrite(MUX_S0, LOW);
    digitalWrite(MUX_S1, HIGH);
    digitalWrite(MUX_S2, LOW);
  }

  // If controller's # is 3, 11, 19 or 27, send an appropriate command to make all MUXes to spit out what is on their 3rd pin
  else if (pin == 3 || pin == 11 || pin == 19)
  {
    digitalWrite(MUX_S0, HIGH);
    digitalWrite(MUX_S1, HIGH);
    digitalWrite(MUX_S2, LOW);
  }

  // If controller's # is 4, 12, 20 or 28, send an appropriate command to make all MUXes to spit out what is on their 4th pin
  else if (pin == 4 || pin == 12 || pin == 20)
  {
    digitalWrite(MUX_S0, LOW);
    digitalWrite(MUX_S1, LOW);
    digitalWrite(MUX_S2, HIGH);
  }
  
  // If controller's # is 5, 13, 21 or 29, send an appropriate command to make all MUXes to spit out what is on their 5th pin
  else if (pin == 5 || pin == 13 || pin == 21)
  {
    digitalWrite(MUX_S0, HIGH);
    digitalWrite(MUX_S1, LOW);
    digitalWrite(MUX_S2, HIGH);
  }

  // If controller's # is 0, 8, 22 or 30, send an appropriate command to make all MUXes to spit out what is on their 6th pin
  else if (pin == 6 || pin == 14 || pin == 22)
  {
    digitalWrite(MUX_S0, LOW);
    digitalWrite(MUX_S1, HIGH);
    digitalWrite(MUX_S2, HIGH);
  }

  // If controller's # is 7, 15, 23 or 31, send an appropriate command to make all MUXes to spit out what is on their 7th pin
  else if (pin == 7 || pin == 15 || pin == 23)
  {
    digitalWrite(MUX_S0, HIGH);
    digitalWrite(MUX_S1, HIGH);
    digitalWrite(MUX_S2, HIGH);
  }
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~buttonPressed() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void buttonPressed(int contr)
{
  //---> If button pressed is FX- for Rack 1
    if (contr == 0) 
    {
    
    //-> FX must be > 0  
      if (focusFx1 > 0)
      {
        focusFx1 = focusFx1 - 1; // lower current focused fx
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;// Switch to proper masterMode if needed
        else masterMode = 0;   
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }

      else
      {
        focusFx1 = 27; //Setting proper FX #
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;// Switch to proper masterMode if needed
        else masterMode = 0;
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }
      
      //debug(contr);
    }







    //---> If button pressed is FX- for Rack 2
    if (contr == 1) 
    {
    
    //-> FX must be > 0  
      if (focusFx2 > 0)
      {
        focusFx2 = focusFx2 - 1; // lower current focused fx
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1; // Switch to proper masterMode if needed
        else masterMode = 0;
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }

      else
      {
        focusFx2 = 27; //Setting proper FX #
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1; // Switch to proper masterMode if needed
        else masterMode = 0;
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }

      //debug(contr);
      
    }








    //---> If button pressed is FX+ for Rack 1
    if (contr == 2) 
    {
    
    //-> FX must be < 27  
      if (focusFx1 < 27)
      {
        focusFx1 = focusFx1 + 1; // lower current focused fx
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;// Switch to proper masterMode if needed
        else masterMode = 0;
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }

      else
      {
        focusFx1 = 0; //Setting proper FX #
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1;// Switch to proper masterMode if needed
        else masterMode = 0;
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }

      //debug(contr);
    }






    

    //---> If button pressed is FX+ for Rack 2
    if (contr == 3) 
    {
    
    //-> FX must be < 27  
      if (focusFx2 < 27)
      {
        focusFx2 = focusFx2 + 1; // lower current focused fx
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1; // Switch to proper masterMode if needed
        else masterMode = 0;
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }

      else
      {
        focusFx2 = 0; //Setting proper FX #
        if (rack1Channel[0] == rack2Channel[0] && focusFx1 == focusFx2) masterMode = 1; // Switch to proper masterMode if needed
        else masterMode = 0;
        calcMidiButton(contr, 0);
        updateDisplayButton(contr,0);
        lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      }

      //debug(contr);
    }







   

    //---> If button pressed is CUST for Rack 1
    else if (contr == 4) 
    {
      buttonsState[focusFx1] = !buttonsState[focusFx1];//changing current button state
      calcMidiButton(contr, buttonsState[focusFx1] * 127);
      updateDisplayButton(contr, buttonsState[focusFx1]);
      lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
    }






    

    //---> If button pressed is CUST for Rack 2
    else if (contr == 5 && masterMode == 0) 
    {
      buttonsState[focusFx2] = !buttonsState[focusFx2];//changing current button state
      calcMidiButton(contr, buttonsState[focusFx1] * 127);
      updateDisplayButton(contr, buttonsState[focusFx2]);
      lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
    }




    //---> If button pressed is CUST for Rack 2 (DUAL)
    else if (contr == 5 && masterMode == 1) 
    {
      buttonsState2[focusFx2] = !buttonsState2[focusFx2]; //changing current button state
      calcMidiButton(contr, buttonsState2[focusFx2] * 127);
      updateDisplayButton(contr, buttonsState2[focusFx2]);
      lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
    }




    //---> If button pressed is ON for Rack 1
    else if (contr == 6) 
    {
      fx1States[focusFx1] = !fx1States[focusFx1]; //Switch current state
      calcMidiButton(contr, fx1States[focusFx1] * 127);
      updateDisplayButton(contr, fx1States[focusFx1]);
      lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
      
      //debug(contr);
    }




    //---> If button pressed is ON for Rack 2
    else if (contr == 7 && masterMode == 0) 
    {
      if (rack1Channel[0] == rack2Channel[0]) //Check if we are on same channel
      {
        fx1States[focusFx2] = !fx1States[focusFx2];
        updateDisplayButton(contr, fx1States[focusFx2]);
      }
      else 
      {
        fx2States[focusFx2] = !fx2States[focusFx2]; //Switch current state
        updateDisplayButton(contr, fx2States[focusFx2]);
      }
      calcMidiButton(contr, fx2States[focusFx2] * 127);
      lastPressedTime[contr] = millis(); // Register last time press of the button  of the button
           
      //debug(contr);
    }
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~pinSet() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DISABLE ME WHEN DONE
/*

void debug(int contr)
{
 
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.print(F("BUTTON: "));
      Serial.println(contr);
      Serial.print(F("focusFx1: "));
      Serial.println(focusFx1);
      Serial.print(F("focusFx2: "));
      Serial.println(focusFx2);
      Serial.print(F("rackStatus 1: "));
      Serial.println(rackStatus[0]);
      Serial.print(F("rackStatus 2: "));
      Serial.println(rackStatus[1]);
      Serial.print(F("rack1Channel 1: "));
      Serial.println(rack1Channel[0]);
      Serial.print(F("rack1Channel 2: "));
      Serial.println(rack1Channel[1]);
      Serial.print(F("rack2Channel 1: "));
      Serial.println(rack2Channel[0]);
      Serial.print(F("rack2Channel 2: "));
      Serial.println(rack2Channel[1]);
      Serial.print(F("masterMode: "));
      Serial.println(masterMode);
      Serial.print(F("lastButton: "));
      Serial.println(lastButton);
      
      Serial.println(F("fx1States: "));
      for (int i = 0; i<28; i++)
      {
        Serial.print(fx1States[i]);
      }
      
      Serial.println();
      
      Serial.println(F("fx2States: "));
      for (int i = 0; i<28; i++)
      {
        Serial.print(fx2States[i]);
      }
      
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~pinSet() FUNCTION~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DISABLE ME WHEN DONE


void debugPot(int contr, int caseid)
{
  
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.print(F("case: "));
      Serial.println(caseid);
      Serial.print(F("contr: "));
      Serial.println(contr);
      Serial.print(F("oldContr: "));
      Serial.println(oldContr);
      Serial.print(F("oldContrRow: "));
      Serial.println(oldContrRow);
      Serial.print(F("newContr: "));
      Serial.println(newContr);
      Serial.print(F("newContrRow: "));
      Serial.println(newContrRow);
      Serial.print(F("rows1: "));
      Serial.println(rows[0]);
      Serial.print(F("rows2: "));
      Serial.println(rows[1]); 
      Serial.println();
      Serial.println();
      Serial.println();
      Serial.println();
      
}
*/
