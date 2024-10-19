//pins
const byte switch_pin = 8;
const byte data_pin = A2;

//constants
const unsigned short hold = 300;
const unsigned short cooldown = 3000;
const unsigned int cycle_wait = 68;//~3 checks per millis
const byte samples = 110;
const unsigned short minimum_strength = 300;
const byte range = 25;
const byte minimum_acceptable = 100;

unsigned short value = 0;

byte index = 0;
unsigned short data[samples];

unsigned int total = 0;
unsigned short average = 0;
byte accepted = 0;

long t = millis();
int count = 0;

void setup() {
  pinMode(switch_pin, OUTPUT);
  pinMode(data_pin, INPUT);

  Serial.begin(115200);

  for (int i = 0; i < samples;i++) {
    data[i] = 0;
  }
}

void loop() {
  value = analogRead(data_pin);
  if (value <= 5) {
    value = 0;
  }
  data[index] = value;
  index++;
  if (index >= samples) {
    index = 0;
  }
  total = 0;
  for (int i = 0; i < samples; i++) {
    total += data[i];
  }
  average = (int)((double)total/(double)samples);
  if (average > minimum_strength) {
    accepted = 0;
    for (int i = 0; i < samples; i++) {
      if (data[i] > average-range && data[i] < average+range) {
        accepted++;
      }
    }
    if (accepted > minimum_acceptable) {
      digitalWrite(switch_pin, HIGH);
      delay(hold);
      digitalWrite(switch_pin, LOW);
      delay(cooldown);
    }
  }
  delayMicroseconds(cycle_wait);
  count++;
  if (millis() - t > 1000) {
    Serial.println(count);
    t = millis();
    count = 0;    
  }
}
