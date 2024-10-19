const int g_t = 12;
const int v_t = 11;
const int d_t = 10;

const int g_r = 5;
const int v_r = 2;
const int d_r = 3;

const int openPin = 8;

long timePassed = micros();
long pulseTime = micros();
boolean lastRead = false;

int newSequence = 10000;
String pass = "";

//my garage
//750 short pulse length = 0
//1500 long pulse length = 1
//> 10000 = next sequence
//3775 time between pulse starts
//password 011011011110010111110111

//brooks garage
//password 011101111100000101000000

//send variables
byte password[24] = { 0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0};
int pulseStartGap = 3775;
int longPulse = 1500;
int shortPulse = 750;

int count = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(openPin, OUTPUT);
  digitalWrite(openPin, LOW);
  //set ground pins
  pinMode(g_t, OUTPUT);
  pinMode(g_r, OUTPUT);
  digitalWrite(g_t, LOW);
  digitalWrite(g_r, LOW);

  //set 5 volt pins
  pinMode(v_t, OUTPUT);
  pinMode(v_r, OUTPUT);
  digitalWrite(v_t, HIGH);
  digitalWrite(v_r, HIGH);

  //init data lines
  pinMode(d_t, OUTPUT);
  pinMode(d_r, INPUT);
  pinMode(A0, INPUT);
  Serial.begin(250000);
  digitalWrite(d_t, LOW);
  delay(500);
  //openGarage();
}

void openGarage() {
  for (int t = 0; t != 3; t++) {
    for (int i = 0; i != sizeof(password); i++) {
      if (password[i] == 0) {
        sendPulse(shortPulse);
        delayMicroseconds(pulseStartGap - shortPulse);
      }
      if (password[i] == 1) {
        sendPulse(longPulse);
        delayMicroseconds(pulseStartGap - longPulse);
      }
    }
    delay(10);
  }
}

void loop() {
  boolean data;
  if (digitalRead(d_r) == 0) {
    data = false;
  } else {
    data = true;
  }
  if (lastRead && !data) {
    count++;
    if ((micros() - pulseTime) > 1000) {
      pass += "1";
    } else {
      pass += "0";
    }
    timePassed = micros();
  }
  if (!lastRead && data) {
    count++;
    pulseTime = micros();
    if ((micros() - timePassed) > newSequence) {
      if (pass == "011011011110010111110111") {
        digitalWrite(openPin, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(2000);
        digitalWrite(openPin, LOW);
        delay(2000);
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("OPEN SESAME");
      }
      Serial.print("Password?: ");
      Serial.println(count);
      Serial.println(pass);
      count = 0;
      pass = "";
    }
  }
  lastRead = data;
}

void sendPulse(int microSeconds) {
  digitalWrite(d_t, HIGH);
  delayMicroseconds(microSeconds);
  digitalWrite(d_t, LOW);
}
