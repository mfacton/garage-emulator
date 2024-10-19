const byte data_pin = A2;
const byte switch_pin = 8;

long timePassed = micros();
long pulseTime = micros();
boolean lastRead = false;

int newSequence = 10000;
String pass = "";
boolean data;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(switch_pin, OUTPUT);
  digitalWrite(switch_pin, LOW);

  //init data lines
  pinMode(data_pin, INPUT);
  delay(100);
}

void loop() {
  if (analogRead(data_pin) < 10) {
    data = false;
  } else {
    data = true;
  }
  if (lastRead && !data) {
    if ((micros() - pulseTime) > 1000) {
      pass += "1";
    } else {
      pass += "0";
    }
    if (pass.indexOf("011011011110010111110111") > 0) {
      digitalWrite(switch_pin, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(300);
      digitalWrite(switch_pin, LOW);
      delay(3000);
      digitalWrite(LED_BUILTIN, LOW);
      pass = "";
    }
    timePassed = micros();
  }else if (!lastRead && data) {
    pulseTime = micros();
    if ((micros() - timePassed) > newSequence) {
      pass = "";
    }
  }
  lastRead = data;
}
