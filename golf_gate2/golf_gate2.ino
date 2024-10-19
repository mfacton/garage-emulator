const byte g_r = 5;
const byte v_r = 2;
const byte d_r = 3;

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

String password = "011011011110010111110111";

int count = 0;

void setup() {
  //set ground pin
  pinMode(g_r, OUTPUT);
  digitalWrite(g_r, LOW);

  //set 5 volt pin
  pinMode(v_r, OUTPUT);
  digitalWrite(v_r, HIGH);

  //init data line
  pinMode(d_r, INPUT);

  pinMode(steerIn1, OUTPUT);
  pinMode(steerIn2, OUTPUT);
  pinMode(steerEn, OUTPUT);

  digitalWrite(steerIn1, LOW);
  digitalWrite(steerIn2, HIGH);
  digitalWrite(steerEn, LOW);
    
  Serial.begin(250000);
  delay(500);
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
      Serial.print("Password?: ");
      Serial.println(count);
      Serial.println(pass);
      if (pass == password) {
        buttonPress();
      }
      count = 0;
      pass = "";
    }
  }
  lastRead = data;
}
void buttonPress() {
  
}
