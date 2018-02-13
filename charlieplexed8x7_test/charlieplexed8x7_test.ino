int d1[] = {7, 8};
int d2[] = {8, 7};
int d3[] = {6, 8};
int d4[] = {8, 6};
int d5[] = {2, 8};
int d6[] = {8, 2};
int d7[] = {4, 8};
int d8[] = {8, 4};
int d9[] = {6, 7};
int d10[] = {7, 6};
int d11[] = {5, 7};
int d12[] = {7, 5};
int d13[] = {5, 8};
int d14[] = {8, 5};
int d15[] = {3, 7};
int d16[] = {7, 3};
int d17[] = {5, 6};
int d18[] = {6, 5};
int d19[] = {4, 6};
int d20[] = {6, 4};
int d21[] = {4, 7};
int d22[] = {7, 4};
int d23[] = {3, 8};
int d24[] = {8, 3};
int d25[] = {4, 5};
int d26[] = {5, 4};
int d27[] = {1, 8};
int d28[] = {8, 1};
int d29[] = {3, 6};
int d30[] = {6, 3};
int d31[] = {2, 7};
int d32[] = {7, 2};
int d33[] = {3, 4};
int d34[] = {4, 3};
int d35[] = {3, 5};
int d36[] = {5, 3};
int d37[] = {2, 5};
int d38[] = {5, 2};
int d39[] = {1, 6};
int d40[] = {6, 1};
int d41[] = {2, 3};
int d42[] = {3, 2};
int d43[] = {2, 4};
int d44[] = {4, 2};
int d45[] = {1, 4};
int d46[] = {4, 1}; 
int d47[] = {2, 6};
int d48[] = {6, 2};
int d49[] = {1, 2};
int d50[] = {2, 1};
int d51[] = {1, 3};
int d52[] = {3, 1};
int d53[] = {1, 7};
int d54[] = {7, 1};
int d55[] = {1, 5};
int d56[] = {5, 1};

const int smDim = 8; // small dimension of the sield
const int LEDs = 56; //number of leds in shield
int LED;
int target = 1;
unsigned long t = 0;
const int startingPinOffset = 1;//used to convert the dx values to the correct pins

void setup() {
  target = 1;
  ledSelect(target);
  //delay(5000);
  t=millis()+500;
}

void loop() {
  if (millis() > t) {
    nextLED();
    t = millis() + 500;
  }

  ledSelect(target);
}

void nextLED() {
  target++;
  if (target > LEDs + 1) {
    target = 1;
  }
}

int ledSelect (int d) {
  if (d == 1) ledOn (d1);
  if (d == 2) ledOn (d2);
  if (d == 3) ledOn (d3);
  if (d == 4) ledOn (d4);
  if (d == 5) ledOn (d5);
  if (d == 6) ledOn (d6);
  if (d == 7) ledOn (d7);
  if (d == 8) ledOn (d8);
  if (d == 9) ledOn (d9);
  if (d == 10) ledOn (d10);
  if (d == 11) ledOn (d11);
  if (d == 12) ledOn (d12);
  if (d == 13) ledOn (d13);
  if (d == 14) ledOn (d14);
  if (d == 15) ledOn (d15);
  if (d == 16) ledOn (d16);
  if (d == 17) ledOn (d17);
  if (d == 18) ledOn (d18);
  if (d == 19) ledOn (d19);
  if (d == 20) ledOn (d20);
  if (d == 21) ledOn (d21);
  if (d == 22) ledOn (d22);
  if (d == 23) ledOn (d23);
  if (d == 24) ledOn (d24);
  if (d == 25) ledOn (d25);
  if (d == 26) ledOn (d26);
  if (d == 27) ledOn (d27);
  if (d == 28) ledOn (d28);
  if (d == 29) ledOn (d29);
  if (d == 30) ledOn (d30);
  if (d == 31) ledOn (d31);
  if (d == 32) ledOn (d32);
  if (d == 33) ledOn (d33);
  if (d == 34) ledOn (d34);
  if (d == 35) ledOn (d35);
  if (d == 36) ledOn (d36);
  if (d == 37) ledOn (d37);
  if (d == 38) ledOn (d38);
  if (d == 39) ledOn (d39);
  if (d == 40) ledOn (d40);
  if (d == 41) ledOn (d41);
  if (d == 42) ledOn (d42);
  if (d == 43) ledOn (d43);
  if (d == 44) ledOn (d44);
  if (d == 45) ledOn (d45);
  if (d == 46) ledOn (d46);
  if (d == 47) ledOn (d47);
  if (d == 48) ledOn (d48);
  if (d == 49) ledOn (d49);
  if (d == 50) ledOn (d50);
  if (d == 51) ledOn (d51);
  if (d == 52) ledOn (d52);
  if (d == 53) ledOn (d53);
  if (d == 54) ledOn (d54);
  if (d == 55) ledOn (d55);
  if (d == 56) ledOn (d56);
}

int ledOn (int *LED) {
  pinMode(LED[1] + startingPinOffset, OUTPUT);
  digitalWrite(LED[1] + startingPinOffset, HIGH);
  pinMode(LED[0] + startingPinOffset, OUTPUT);
  digitalWrite(LED[1] + startingPinOffset, LOW);
  pinMode(LED[1] + startingPinOffset, INPUT);
  pinMode(LED[0] + startingPinOffset, INPUT);
}


