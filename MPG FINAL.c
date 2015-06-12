/*----------------------------------------------||
||                                              ||
|| @file: MilesPerGallonVer8_0.pde              ||
|| @version 9.0                                 ||
|| @author: Junaid Malik                        ||
|| @date 29/Apr/2014                            ||
||                                              ||
|| @description: program asks for user to choose||
|| either KPG or KPL and then asks for input of ||
|| lires or gallons and or miles or k/m, it then||
|| displays the output result in MPG and KPL    ||
|| 9th itteration of a menu system              ||
*/
// we include the following libraries to included in our code
#include <Keypad.h>
#include <LiquidCrystal.h>

// keypad has 4 rows and 3 columns resulting in 12 keys
const byte ROWS = 4; // Four rows
const byte COLS = 3; // columns

// Our keymap is a multi-dimensional array consistening of type char value
// This matrix holds the digital pin numbers we have our keypad connected to
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'.','0','#'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//Our global variables are accesible by any function which invokes it////
void FuelSelect(); // this shows our menu to lcd
double getgallons(); // this obatins gallons from the user input
double getlitres(); // this obatins liters from the user input
double convertToMPG(double); // converting to MPG
double convertToKPL(double); // converting to KPL
double gallons; // this is the number of gallons
double Miles; // this is Miles we travelled
double litres; // this is the number of litres
double Kilometers; // this is kilometers we travelled

void setup(){
  Serial.begin(9600); //sets data rate in bits per second for serial data transmission
  keypad.setHoldTime(500);// Default is 1000mS
  lcd.begin(16,2); // set up the LCD's number of columns and rows: 
  lcd.clear(); // clears lcd screen and sets cursor to top right
}

//~~~~~~~~~~~~~~~~~~~~~~~START OF MAIN LOOP~~~~~~~~~~~~~~~~~~~~~~~//
void loop()
{
  // I used double precision floating point number to store values
  // 
  double gallons; // this is the number we convert to litres or gallons
  double mpg; //
  double kpl;
  char key = keypad.getKey(); // returns the key that is pressed
  
      FuelSelect();               // display the menu
      char waitForKey();          // this will forever until key is pressed
      if (key != NO_KEY)          // only do stuff if choice is not invalid
      {
         if (key == '1') // this if condition only executes if statment is true
         {
           gallons = getgallons(); // we call function getGallons and it has one input(gallons) and assigns returned to gallons          
           Miles =  getMiles(); // we call function getMiles and it has one input(miles) and assigns returned to miles           
           mpg = convertToMPG(gallons,Miles); // we call function convertToMPG and it takes in two inputs
                                              // and assigns the returned result to mpg
         }
         else if (key == '2')// this if condition only executes if statment is true
         {
           litres = getlitres();// we call function getLiters and it has one input(liters) and assigns returned to liters 
           Kilometers =  getKilometers();// we call function getKilometers and it has one input(kilometers) and assigns returned to Kilometers            
           kpl = convertToKPL(litres,Kilometers);// we call function convertToKPL and it takes in two inputs
                                                // and assigns the returned result to kpl
         }
      }
} 
//~~~~~~~~~~~~~~~~~~~END OF MAIN LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~//
////////////// FuelSelect Menu is called everytime ////////////// 
void FuelSelect()
{
  lcd.print("1.MPG");
  lcd.setCursor(0,1);
  lcd.print("2.KPL           ");
}

///////////// START OF MPG FUNCTIONS //////////////////
double getgallons(void)
{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter Gallons");   
   lcd.setCursor(0,1);
   int gallons = 0;

   char key = keypad.getKey();
   while (key != '#'){ // Do nothing if # key is not pressed.
   switch (key) // switch case is stuck in while loop until it is broken
   {            // switch compres key press to compare to valued specifies in case statments
     case NO_KEY:
      break;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':

      lcd.print(key);
      gallons = gallons * 10 + (key - '0');
      break;

    case '#': // this is the enter key
        delay(100); // Removes possiblilty of debounce
        return gallons;  
        break;
   }
  key = keypad.getKey();
}
return gallons; // return statement causes the value to be returned to the calling program
}
////// end of getgallons function ////

/// start of milesTravelled
void Milestravelled()
{
  lcd.clear();
  lcd.print("Enter Miles");
  getMiles(); 
}
/// start of getMiles 
double getMiles(void)
{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter Miles");
   lcd.setCursor(0,1);
   int Miles = 0;
   char key = keypad.getKey();
   while (key != '#'){ // Do nothing if # key is not pressed.
   switch (key)
   {
     case NO_KEY:
      break;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
    
      lcd.print(key);
      Miles = Miles * 10 + (key - '0');
      break;

    case '#':
        delay(100); // Removes possiblilty of debounce
        return Miles;  
        break;    
 }
  key = keypad.getKey();
}
return Miles;
}
// convertToMPG function passes in gallons and Miles from previous functions
double convertToMPG(double gallons,double Miles)
{ 
  double mpg;
  double kplconv;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("In mpg ="); 
  mpg = Miles / gallons;
  lcd.print(mpg);
  delay(4000);
  lcd.clear();
  lcd.print("Result in KPL");
  lcd.setCursor(0,1);
  lcd.print("=");
  kplconv = mpg * 0.219969;
  lcd.print(kplconv);
  delay(4000);
  lcd.clear();
}

///////////// END OF MPG PROGRAMME/////////////////////
///////////// START OF KPL FUNCTIONS //////////////////

double getlitres(void)
{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter Litres");   
   lcd.setCursor(0,1);
   int litres = 0;

   char key = keypad.getKey();
   while (key != '#'){ // Do nothing if # key is not pressed.
   switch (key)
   {
     case NO_KEY:
      break;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':

      lcd.print(key);
      litres = litres * 10 + (key - '0');
      break;

    case '#':
        delay(100); // Removes possiblilty of debounce
        return litres;  
        break;   
 }
  key = keypad.getKey();
}
return litres;
}

void Kilometerstravelled()
{
  lcd.clear();
  lcd.print("Enter Kilometers");
  getKilometers(); 
}

double getKilometers(void)
{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Enter Kilometers");
   lcd.setCursor(0,1);
   int Kilometers = 0;
   char key = keypad.getKey();
   while (key != '#'){ // Do nothing if # key is not pressed.
   switch (key)
   {
     case NO_KEY:
      break;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
    
      lcd.print(key);
      Kilometers = Kilometers * 10 + (key - '0');
      break;

    case '#':
        delay(100); // Removes possiblilty of debounce
        return Kilometers;  
        break;     
 }
  key = keypad.getKey();
}
return Kilometers;
}
// convertToKPL function passes in litres and Kilometers from previous functions
double convertToKPL(double litres,double Kilometers)
{ 
  double kpl;
  double mpgconv;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("In kpl ="); 
  kpl = Kilometers / litres;
  lcd.print(kpl);
  delay(4000);
  lcd.clear();
  lcd.print("Result in MPG");
  lcd.setCursor(0,1);
  lcd.print("=");
  mpgconv = kpl * 4.54609;
  lcd.print(mpgconv);
  delay(4000);
  lcd.clear();
}
/////////////////////// END OF KPL FUNCTIONS//////////////////////////