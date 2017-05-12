#include <Key.h>
#include <Keypad.h>
#include <ctype.h>

/////// Begin Kunnen wij het Maken?! code ////////

/// Begininstellingen componenten ///
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[4] = {2, 3, 4, 5};
byte colPins[4] = {6, 7, 8, 9};
Keypad toetsenbord = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4);

/// Einde instellingen componenten ///

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

void zet_led_aan(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void zet_led_uit(int pin) {
  digitalWrite(pin, LOW);
}

int lees_potmeter(int pin) {
  return map(analogRead(pin), 0, 1023, 0, 100);
}

void slaap(float seconde) {
  delay(1000 * seconde);
}
/////// Einde Kunnen wij het Maken?! code ////////






/////// Begin eigen code ////////
void setup() {
  // Plaats hier de code die je een maal aan het begin wilt uitvoeren:
  Serial.begin(9600);
}

void loop() {
  // Plaats hier de code die je steeds opnieuw wilt uitvoeren:
//  int waarde = toetsenbord_getal(0, 100, "Hoe graag wil je de led aan?");
//  if (waarde > 50) {
//    zet_led_aan(13);
//  }
//  else {
//    zet_led_uit(13);
//  }
  toon_op_scherm(lees_potmeter(2));
  slaap(1);
}
