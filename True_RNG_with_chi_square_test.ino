// Generator for true Random Numbers with integrated Chi Square Test 
// Michael Klein | DL1MKP 7-2025 | art-of-electronics.blog

#include <MD_cmdProcessor.h> // Commandprozessor for the user interface
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

int loops = 200; // how many random numbers should be generated? ; default
unsigned int zufall; // analog value at A0
unsigned int bin = 20; // number of bins for statistical analysis; default
bool Go_noGo = false; // if true: chi-square test positive
bool statswitch = false; // if true: output to plotter

// Array to store RNs
int array[300]; // limited to 300 values, otherwise memory overflow and faulty output

void handlerHelp(char* param); // Help-function 

void handlerGR(char* param) { // Generate a single random number
  zufall = analogRead(14);
  Serial.print("\nRandom number: "); Serial.println(zufall);

}

void handlerGA(char* param) { // Generate array of random numbers
  Serial.println("\n"); Serial.print(loops);Serial.print(" Random numbers are being generated.\n");
  werterfassung(); // Data capture
  Serial.println("Process finished.");
}

void handlerGI(char* param) { // Generate RNs and check if they are uniformly distributed
  Serial.println("\n"); Serial.print(loops);Serial.print(" Array of random numbers is being generated and chi-square checked. \n");
  Go_noGo = false; // flag for checking if chi square test fails
  int i=1; // counter
  while ((Go_noGo != true) && (i <11)) {
    werterfassung(); // Data capture
    chi_quadrat();
    Serial.print("Round # "); Serial.println(i);
    i++;
    delay(100);
  }
  Serial.println("\nProcess finished.");
  Go_noGo = false; // Reset flag.
}

void handlerAR(char* param) // Set amount of RNs
{
  loops = strtod(param, nullptr);
  Serial.print(F("\nAmount of RNs set to: ")); Serial.println(loops); 
}

void handlerBE(char* param) // Set number of boxes
{
  bin = strtod(param, nullptr);
  if ((loops % bin)!= 0 ) {
    Serial.print("\nPlease choose a number of boxes that is a multiple of > "); Serial.println(bin);
    bin = 200; // Zurück auf default-Wert 200
    }
  else {
    Serial.print(F("\nYour # of boxes is: ")); Serial.println(bin); 
  }
}

void handlerTA(char* param) // list output of RNs
{
  zufallszahlen();
}

void handlerCS(char* param) // CSV-output of RNs
{
  csv_Daten();
}

void handlerST(char* param) // statistics: how many numbers are in each box?
{
  statistik();
}

void handlerSP(char* param) // statistics ST as plot
{
  statswitch = true; // activate plot
  statistik();
}

void handlerCH(char* param) // perform chi-square test
{
  chi_quadrat();
}

void handlerAB(char* param) // setting opAmp control voltage
{
  Serial.println("\nsetting opAmp control voltage - 15 sec");
  for (int i=0; i<10; i++) {
    float volt_sigl = 0; 
    float volt = 0;
    for (int j=0; j<100; j++) {
      volt_sigl =  volt_sigl + analogRead(15)*0.032;
    }
    volt = volt_sigl/100; 
    Serial.print("\nYour offset voltage is [V]: "); Serial.println(volt, 2);
    delay(1500);
  }
  Serial.println("\nSetting finished - you may start");
}

const MD_cmdProcessor::cmdItem_t PROGMEM cmdTable[] =
{
  { "?",  handlerHelp,  "",    "Help", 0 },
  { "h",  handlerHelp,  "",    "Help", 0 },
  { "gr", handlerGR,    "",    "Generate single RN", 0 },
  { "ga", handlerGA,    "",    "Generate array of RNs", 0 },
  { "gi", handlerGI,    "",    "Generate array of RNs and loop until perfect", 0 },
  { "ar", handlerAR,    "a",   "Set amount of RNs f.e.: aw 200", 0 },
  { "be", handlerBE,    "",    "Set amount of bins f.e.: be 20", 0 },
  { "ta", handlerTA,    "",    "Result as table", 1 },
  { "cs", handlerCS,    "",    "Result as CSV", 1 },
  { "st", handlerST,    "",    "Statistical result shows bins", 1 },
  { "sp", handlerSP,    "",    "Statistical result as plot", 1 },
  { "ch", handlerCH,    "",    "Perform chi-square Test", 1 },
  { "ab", handlerAB,    "",    "Set control voltage of OpAmp", 2 },
};

MD_cmdProcessor CP(Serial, cmdTable, ARRAY_SIZE(cmdTable));

void handlerHelp(char* param)
{
  Serial.println("Please set line end only to **new line**.");
  CP.help();
  Serial.print(F("\n"));
}

void setup() {
  Serial.begin(9600);
  CP.begin();
  CP.help();
}

void loop() {
  CP.run();
}m
