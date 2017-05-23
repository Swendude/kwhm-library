#include <Ultrasonic.h>
#include <Key.h>
#include <Keypad.h>
#include <ctype.h>
#include <Servo.h>
#include <SD.h>
#include "pitches.h"

/////// Begin Kunnen wij het Maken?! code ////////

/// Begininstellingen componenten ///
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[4] = {9, 8, 7, 6};
byte colPins[4] = {5, 4, 3, 2};

byte servopin = 0;
byte transistorpin = 3;
byte speakerpin = 11;
byte sensorpin = 0;
byte trigpin = 12;
byte echopin = 13;
byte knoppin = 10;
byte sdpin = 10;

File datafile;

Keypad toetsenbord = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4);
Servo mijnservo;

/// Einde instellingen componenten ///

int lees_tekst_waarde(String waarde, int sdpin = sdpin){
  bool hasSD = SD.begin(sdpin);
  datafile = SD.open("data.csv", FILE_READ);
  if (!hasSD) {
    Serial.println("SD kaart lezer niet herkend");
    return - 1;
  };
  if (!datafile) {
    Serial.println("Datafile kan niet gelezen worden");
    return - 1;
  };
  while(datafile.available() != 0) {
    String eerstedeel = datafile.readStringUntil(',');
    String tweededeel = datafile.readStringUntil('\n');
    int tweedeint = tweededeel.toInt();
    if (waarde == eerstedeel) {
      return tweedeint; 
      };
    };
    Serial.println("Inputwaarde niet gevonden");
    return -1;
  }
 
int lees_numerieke_waarde(int waarde, int sdpin = sdpin){
  bool hasSD = SD.begin(sdpin);
  datafile = SD.open("data.csv", FILE_READ);
  if (!hasSD) {
    Serial.println("SD kaart lezer niet herkend");
    return - 1;
  };
  if (!datafile) {
    Serial.println("Datafile kan niet gelezen worden");
    return - 1;
  };
  while(datafile.available() != 0) {
    String eerstedeel = datafile.readStringUntil(',');
    String tweededeel = datafile.readStringUntil('\n');
    int eersteint = eerstedeel.toInt();
    int tweedeint = tweededeel.toInt();
    if (waarde == eersteint) {
      return tweedeint; 
      };
    };
    Serial.println("Inputwaarde niet gevonden");
    return -1;
  }

int toetsenbord_getal(int minimum, int maximum, String vraag = "", char bevestigtoets = 'D') {
  String input = "";
  bool submitted = false;
  if (vraag == "") {
    vraag = "Getal tussen " + String(minimum) + " en " + String(maximum);
  }
  toon_op_scherm(vraag);

  while (not submitted) {
    char inputchar = toetsenbord.waitForKey();
    if (isDigit(inputchar)) {
      if ((input + inputchar).toInt() <= maximum) {
        input += inputchar;
        voeg_toe_op_scherm(inputchar);
      }
    }
    if (inputchar == bevestigtoets) {
      regel_op_scherm();
      submitted = true;
    }
  }
  return input.toInt();
}
 
int lees_keuze_waardes(String waardes[], int lengtewaardes, int sdpin = sdpin){
  regel_op_scherm();
  for (int i = 0; i < lengtewaardes; i++) {
    String keuze = String(i + 1) + " : " + waardes[i];
    Serial.println(keuze);
  }
  int keuze = toetsenbord_getal(0, lengtewaardes, "Maak een keuze:");
  String keuzewoord = waardes[keuze - 1];
  return lees_tekst_waarde(keuzewoord, sdpin);
}

void wacht_op_knop(int pinnummer = knoppin) {
    pinMode(pinnummer, INPUT);
    while (true) {
    int buttonState = digitalRead(pinnummer);
    if (buttonState == HIGH) {
      slaap(0.3);
      return;
    }
    slaap(0.1);
  }
}


int cm_afstand(int trigpin = trigpin, int echopin = echopin) {
  Ultrasonic uss = Ultrasonic(trigpin, echopin);
  bool distancefound = false;
  int distance = 0;
  while (not distancefound) {
    int distance1 = uss.distanceRead();
    slaap(0.1);
    int distance2 = uss.distanceRead();

    if (abs(distance1 - distance2) < 5) {
      distance = ((distance1 + distance2) / 2);
      distancefound = true;
    }
  }
  if (distance > 50) {
    return 100;
  }
  else {
    return map(uss.distanceRead(), 0, 50, 0, 100);
  }
}

int lees_sensor(int sensorpin = sensorpin) {
  return map(analogRead(sensorpin), 0, 1024, 0 , 100);
}

void speel_toon(int toon, float seconde, int pinummer = speakerpin) {
  tone(pinummer, toon);
  slaap(seconde);
  noTone(pinummer);
}

void dcmotor_seconde(float seconde, int pinnummer = transistorpin) {
  pinMode(pinnummer, OUTPUT);
  digitalWrite(pinnummer, HIGH);
  slaap(seconde);
  digitalWrite(pinnummer, LOW);
}


void positioneer_servo(int hoek, int pinnummer = servopin) {
  mijnservo.attach(pinnummer);
  mijnservo.write(hoek);
  delay(30);
  //  mijnservo.detach();
}

void toon_op_scherm(String tekst) {
  Serial.println(tekst);
}

void toon_op_scherm(int getal) {
  Serial.println(String(getal));
}

void voeg_toe_op_scherm(char symbool) {
  Serial.print(symbool);
}

void regel_op_scherm() {
  Serial.println();
}

void zet_led_aan(int pinnummer) {
  pinMode(pinnummer, OUTPUT);
  digitalWrite(pinnummer, HIGH);
}

void zet_led_uit(int pinnummer) {
  digitalWrite(pinnummer, LOW);
}

int lees_potmeter(int pinnummer) {
  return map(analogRead(pinnummer), 0, 1023, 0, 100);
}

void slaap(float seconde) {
  delay(1000 * seconde);
}
/////// Einde Kunnen wij het Maken?! code ////////






/////// Begin eigen code ////////
void setup() {
  Serial.begin(9600);
}

void loop() {
  
}
/////// Einde eigen code ////////
