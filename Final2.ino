bool firstphase = true;
bool secondphase = false;
bool thirdphase = false;
bool valves = false;
bool pres[4];
void setup() {
  for (int i = 0; i < 13; i++) {
    if (i == 2) {
      pinMode(i, INPUT);
    } else {
      pinMode(i, OUTPUT);
    }
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), checkKeys, RISING );
  Serial.begin(9600);
}

void loop() {
  if (firstphase) {
    reset();
    openangle(0, 1.5);
    delay(500);
    openangle(0, 0);
    
    movesteper(140, 10, 5, 6, 0, 0);
    
    openangle(1, 1.5);
    valves = true;
    movesteper(112, 10, 5, 6, 1, 100000);
    
    valves = true;
    openangle(12, 1.5);
    movesteper(280, 10, 5, 6, 12, 200000);

    for (int i = 0; i < 3; i++) {
      valves = true;
      openangle(3, 1.5);
      movesteper(112, 5, 5, 6, 3, 100000);
    }
    
    firstphase = false;
    secondphase = true;
  }
  if (secondphase) {
    movesteper(28, 1, 7, 8, 0, 0);
    digitalWrite(9, HIGH);
    delay(1000);
    digitalWrite(9, LOW);
    movesteper(28, 1, 7, 8, 0, 0);
    delay(1000);
    secondphase = false;
    thirdphase = true;
  }
  if (thirdphase) {

    if (pres[0]) {

      openangle(4, 1);
      digitalWrite(10, HIGH);
      movesteper(28, 1, A0, A1, 0, 0);
      digitalWrite(10, LOW);

      openangle(4, 1.5);
      digitalWrite(11, HIGH);
      movesteper(28, 1, A0, A1, 0, 0);
      digitalWrite(11, LOW);

      openangle(4, 0);
      pres[0] = false;
      firstphase = true;
    }
    else if (pres[1]) {

      openangle(4, 1);
      for (int i = 0; i < 2; i++) {
        digitalWrite(10, LOW);
        movesteper(7, 1, A0, A1, 0, 0);
        digitalWrite(10, HIGH);
        movesteper(7, 1, A0, A1, 0, 0);
      }
      digitalWrite(10, LOW);

      openangle(4, 1.5);
      for (int i = 0; i < 2; i++) {
        digitalWrite(11, HIGH);
        movesteper(7, 1, A0, A1, 0, 0);
        digitalWrite(11, LOW);
        movesteper(7, 1, A0, A1, 0, 0);
      }

      openangle(4, 0);
      pres[1] = false;
      firstphase = true;

    }
    else if (pres[2]) {

      openangle(4, 0);
      digitalWrite(10, HIGH);
      delay(200);
      digitalWrite(10, LOW);
      delay(200);

      openangle(4, 1.5);
      int j = 0;
      for (int i = 0; i < 14; i++) {
        digitalWrite(11, HIGH);
        movemotoronerotation( A0, A1, j);
        j++;
        if (j == 4) {
          j = 0;
        }
        delay(200);
        digitalWrite(11, LOW);
        movemotoronerotation( A0, A1, j);
        j++;
        if (j == 4) {
          j = 0;
        }
        delay(200);
      }

      pres[2] = false;
      firstphase = true;
    }
    else if (pres[3]) {
      bool whichpreves = 0; //0 for red ,1 for yellow
      byte pin;

      openangle(4, 0);
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);

      for (float i = 0.5; i <= 1; i += 0.5) {
        openangle(4, i);
        digitalWrite(11, HIGH);
        movesteper(28, 1, A0, A1, 0, 0);
        digitalWrite(11, LOW);
        delay(300);
      }

      openangle(4, 1.5);
      int j = 0;
      for (int i = 0; i < 14; i++) {
        if (whichpreves) {
          pin = 11;
          whichpreves = 0;
        }
        else {
          pin = 10;
          whichpreves = 1;
        }
        digitalWrite(pin, HIGH);
        movemotoronerotation( A0, A1, j);
        j++;
        if (j == 4) {
          j = 0;
        }
        delay(200);
        digitalWrite(pin, LOW);
        movemotoronerotation( A0, A1, j);
        j++;
        if (j == 4) {
          j = 0;
        }
        delay(200);
      }

      pres[3] = false;
      firstphase = true;
    }
  }
}

void openangle(byte pin, float angle) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(angle * 1000);
  digitalWrite(pin, LOW);
  delayMicroseconds(20 * 1000 - angle * 1000);
  if (angle != 0) {
    delay(150);
  }
}

void reset() {
  openangle(0, 0);
  openangle(1, 0);
  openangle(12, 0);
  openangle(3, 0);
  openangle(4, 0);

}
void movemotoronerotation(byte pin1 , byte pin2, byte thisStep) {
  switch (thisStep) {
    case 0:  // 00
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);

      break;

    case 1:  // 10
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);

      break;

    case 2:  // 11
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);

      break;

    case 3:  // 01

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);

      break;

  }
}
void movesteper(int steps, byte needspeed, byte bin1, byte bin2, byte valvepin, unsigned long delaywanted) {
  int numberofsteps = steps;
  //28 is a  step per revlotion
  //140;
  //280;
  byte stepnumber = 0;
  unsigned long stepdelay;
  switch (needspeed) {
    case 1:
      stepdelay = 60L * 1000L * 1000L / 28 / 15;
      break;
    case 2:
      stepdelay = 60L * 1000L * 1000L / 28 / 1;
      break;
    case 5:
      stepdelay = 1000L * 1000L / 28 / 5;
      break;
    case 10:
      stepdelay = 1000L * 1000L / 28 / 10;
      break;
  }
  //(((60/15)/28)*1000*1000) for 15 rpm
  //((0.2/28)*1000*1000)=7142; for 5 rps
  //((0.1/28)*1000*1000)=3572; for 10 rps
  int stepsleft = numberofsteps;
  unsigned long laststeptime = 0;
  unsigned long openvanillatime = 0;
  if (valves) {
    openvanillatime = micros();
  }
  int i = 0;
  while (stepsleft > 0) {
    unsigned long now = micros();
    if (valves) {
      if (now - openvanillatime >= delaywanted) {
        openangle(valvepin, 0);
        valves = false;
      }
    }
    if (now - laststeptime >= stepdelay) {
      laststeptime = now;

      stepnumber++;
      if (stepnumber == numberofsteps) {
        stepnumber = 0;
      }

      stepsleft--;
      i++;
      Serial.println(i);
      movemotoronerotation(bin1, bin2, stepnumber % 4);
    }
  }
}
void checkKeys() {
  pres[0] = false;
  pres[1] = false;
  pres[2] = false;
  pres[3] = false;
  if (digitalRead(2)) {
    if (digitalRead(A5))
    {
      pres[0] = true;
    }
    else if (digitalRead(A4))
    {
      pres[1] = true;
    }
    else if (digitalRead(A3))
    {
      pres[2] = true;
    }
    else if (digitalRead(A2))
    {
      pres[3] = true;
    }
  }
}
