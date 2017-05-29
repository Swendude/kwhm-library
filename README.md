# Kunnen wij het Maken?!
![](http://i.imgur.com/VvGWHDa.png)


<a href="www.setup.nl"><img alt="Setup logo" src=http://www.moocha.nl/wp-content/uploads/2010/04/setup_logo.jpg width="100"></a>     <a href="www.mindmingle.nl"><img alt="Mindmingle logo" src="http://i.imgur.com/NHPQaB8.png" width="100"></a>

## Inhoudsopgave
+ [Introductie](#introductie)
+ [Hoe te starten?](#hoe-te-starten)
  + [Arduino IDE](#arduino-ide)
  + [KWHM File](#kwhm-file)
+ Voorbeeld
  + [Elon Musk: houdt je kamer op de temperatuur onder je dekens](#bored-elon-musk-voorbeeld)
+ [Documentatie](#documentatie)
  + Input
    + Sensoren
      + [Analoge sensoren](#analoge-sensoren)
      + [Afstandsensor](#afstandsensor)
      + [Vochtsensor](#bodemvochtigheid)
      + [Temperatuursensor](#temperatuursensor)
    + andere input
      + [Input via een keypad](#input-via-een-keypad)
      + [Potmeters](#potmeters)
      + [knop](#knoppen)
  + Data
    + [SD Kaartlezer](#sd-kaartlezer)
  + Output
    + [Informatie tonen in de serial monitor](#informatie-tonen-in-de-serial-monitor)
    + [Aansturen van LED](#aansturen-van-led)
    + [Servo motoren](#servo-motoren)
    + [Geluid maken](#geluid-maken)
    + [DC motoren en Waterpomp](#dc-motoren-en-waterpomp)
  + Extra
    + [Controle functies](#controle-functies)

## Introductie

Welkom bij de officiele Kunnen wij het Maken?! repository! Een repository is een heel stoer woord voor "plek waar code woont". 
Op deze pagina vind je alle benodigdheden om je eigen dubieus apparaat te maken.  

Tijdens de masterclasses maak je gebruik van het [Arduino  platform](https://www.arduino.cc/). De bestanden in deze repo gaan je helpen de Arduino aan te sturen.

## Hoe te starten?

### Arduino IDE
Allereerst heb je de Arduino IDE (Integrated Development Envirnoment) nodig. Dit is de plek waarin je je code gaat onderhouden en output van de arduino kan lezen. De IDE kan je [hier](https://www.arduino.cc/en/main/software) downloaden. Zorg ervoor dat je de laatste versie voor je besturingssysteem download! We werken niet met de online versie.

### KWHM File
Om het werken met arduino makkelijker te maken hebben wij alvast een hele hoop code voor je geschreven die je zomeer mag gebruiken. Om deze code te gebruiken moet je de volgende stappen ondernemen:

* Download de repo zipfile: Rechtboven "Clone or download > Download ZIP"
* Plaats de zipfile ergens op je systeem
* Unzip de zipfile
* Open de file "kwhm-code.ino"

Als het goed is opent de Arduino IDE vanzelf, op het scherm zie je veel regels (misschien wel willekeurige) tekst staan. Regels waarvoor een ```//``` staat zijn zogenaamde comments, deze worden niet gelezen door arduino en hebben dus geen effect op je code. Wel ghandig om te laten weten wat je code doet aan andere programmeurs natuurlijk. Voel je vrij om je eigen code van comments te voorzien.

De KWHM file bestaat uit twee hoofddelen:

1. ```Kunnen wij het Maken?! code```
2. ```Eigen code```

Deze twee delen zijn te herkennen door de volgende soort regels:
```arduino
////// Begin Kunnen wij het Maken?! code ////////
...
/////// Einde Kunnen wij het Maken?! code ////////
/////// Begin eigen code ////////
void setup() {...}
void loop() {...}
/////// Einde eigen code ////////
```

Deel 1 is door ons geschreven en mag je negeren. Het voorziet de rest van je code met handige helper-methodes zodat je je apparaat kan bouwen. In het ```eigen code``` blok gaan we (verassend genoeg) onze eigen code typen. Tijdens de masterclass zal uitgelegd worden hoe je precies moet coderen met deze file. Hieronder volgt de documentatie (uitleg) van alles functies die je kan gebruiken.

## Bored Elon Musk Voobeeld
![](https://pbs.twimg.com/profile_images/378800000305778238/852d2f76797dbe1da82095f988d38fbe_400x400.png =200x)

_Thermostat that sets your entire house to be the same temperate as under your blanket as you wake up and get out of bed._

Dit voorbeeld laat zien hoe je met een temperatuursensor en een servo het bovenstaande voorbeeld kunt uitwerken.

Benodigdheden:
  + Arduino
  + usb kabel voor de arduino
  + temperatuursensor (aangesloten op analoge pin 0)
  + Servo motor (aangesloten op digitale pin 9)
  
__Voorbeeld__:
```arduino
void setup() {
  Serial.begin(9600);
}

void loop() {
   // lees de temperatuur
  int temperatuur = lees_temperatuur(sensorpin = 0);
  // bereken de hoek voor de servo motor
  int hoek = map(temperatuur, 15, 50, 15, 170);
  // bereken de bijbehorende stand van de verwarming. Mijn verwarming
  // heeft thuis 9 standen. Daarom wil ik graag dat hij deze ook 
  // op het scherm kan tonen zodat ik zie wat mijn programma doet.
  int stand_verwarming = map(hoek, 15, 170, 1, 9);

  // zet de servo motor (180* motor) in de juiste hoek
  positioneer_servo(hoek, pinnummer = 9);

  // toon de waarden in de seriele monitor
  toon_op_scherm("temperatuur: " + String(temperatuur));
  toon_op_scherm("stand verwarming: " + String(stand_verwarming));
  slaap(5);
}
```
---
## Documentatie

Hieronder staat de uitleg voor alle beschikbare functies. Ze zijn ingedeeld per categorie. 

### Informatie tonen in de serial monitor

Arduino kan ons berichten sturen via een "seriele" poort. Die berichten kunnen we bekijken met een "seriele monitor". Gelukkig heeft de Arduino IDE al zo'n monitor voor ons klaargezet. Deze is te vinden onder ```Tools > Serial Monitor```. Door gebruik te maken van onderstaande functies. __Zorg ervoor dat je Seriele Monitor op '9600 baud' staat (rechtsonderin). Daarnaast moet je de seriele verbinding 'starten' door als eerste ```Serial.begin(9600);``` in je setup te plaatsen (zie voorbeelden)__

---
#### `toon_op_scherm(String tekst)`
Deze functie zal een bericht naar de seriele monitor sturen, gevolgd door een enter (nieuwe regel).

__Input__:

  _tekst_
  
  De waarde die je op het scherm wilt laten zien

__Output__:
  
  Geen

__Voorbeeld__:
```arduino
  void setup() {
    Serial.begin(9600);
    toon_op_scherm("Hallo, van Arduino!");
  }
  void loop() {
  }
```
---
#### `voeg_toe_op_scherm(char symbool)`
Deze functie zal een bericht naar de seriele monitor sturen zonder een enter toe te voegen. Handig in combinatie met ```regel_op_scherm```. __Deze functie werk alleen met een ```char``` type, dat is een symbool omrings met enkele aanhalingstekens zoals ```'a'```

__Input__:

  _symbool_
  
het symbool die je op het scherm wilt toevoegen

__Output__:
  
  Geen

__Voorbeeld__:
```arduino
  void setup() {
  Serial.begin(9600);
  }
  void loop() {
  voeg_toe_op_scherm('a'); // Er zullen een heleboel a's verschijnen!
  }
```
---
#### `regel_op_scherm(char symbool)`
Deze functie zal een regeleinde naar de monitor sturen. Handig in combinatie met ```voeg_toe_op_scherm(symbool)```.

__Input__:

  Geen

__Output__:
  
  Geen

__Voorbeeld__:
```arduino
  void setup() {
  Serial.begin(9600);
  }
  void loop() {
  voeg_toe_op_scherm('a'); 
  regel_op_scherm(); // Er zullen een heleboel a's verschijnen, maar nu onder elkaar!
  }
```
---

### Input via een keypad
Het toetsenbord dat wij gebruiken heet officeel een keypad. Je ziet ze vaak in liften. Handig om de Arduino te voorzien van input.

#### `toetsenbord_getal(int minimum, int maximum, String *vraag, char *bevestigtoets)`
Deze functie vraagt de gebruiker om een getal tussen minimum en maximum. Laat de invoerwaarde zien op de seriele monitor.

__Input__:

  _`int minimum`_
  
  De minimumwaarde van het getal
  
  _`int maximum`_
  
  De maximumwaarde van het getal
  
  _'String vraag' (optioneel)_
  
  De vraag die gesteld moet worden. Dit argument hoeft niet gegeven te worden. Standaard: ```Getal tussen``` _minimum_ ```en``` _maximum_.
 
   _'char bevestigtoets' (optioneel)_
  
  De toets die gebruikt kan worden om te bevestigen, keuze uit 'A', 'B', 'C', 'D', '#', '*'. 
  Standaard: 'D'

__Output__:
  
  _'int waarde'_
  de waarde die is ingevoerd.

__Voorbeeld__:
```arduino
  void setup() {
  Serial.begin(9600);
  }
  void loop() {
  int getal = toetsenbord_getal(0, 100);
  toon_op_scherm(getal); 
  }
```

```arduino
  void setup() {
  Serial.begin(9600);
  }
  void loop() {
  int getal = toetsenbord_getal(0, 100, "Hoe graag wil je het maken?!");
  toon_op_scherm(String(getal) + '%'); 
  }
```
---
### Aansturen van LED
LED's zijn hippe, natuurvriendelijke en duurzame lampjes die erg makkelijk aan te sturen zijn. __Vergeet je resistor niet!__.

---
#### `zet_led_aan(int pin)`
Zet een LED aan op _pin_.

__Input__:

  _`int pin`_
  
  Het pinnummer waarop de LED is aangesloten

__Output__:
  
  Geen

__Voorbeeld__:
```arduino
  void setup() {
    zet_led_aan(13); // Als je een LED op pin 13 zet gaat die aan
  }
  void loop() {
  }
```

---
#### `zet_led_uit(int pin)`
Zet een LED uit op _pin_.

__Input__:

  _`int pin`_
  
  Het pinnummer waarop de LED is aangesloten

__Output__:
  
  Geen

__Voorbeeld__:
```arduino
  void setup() {
    zet_led_uit(13); // Als je een LED op pin 13 zet gaat die uit, of hij blijft uit.
  }
  void loop() {
  }
```
---
### Potmeters
Een potentiometer kan je gebruiken als draaiknop om een waarde uit te lezen. De waarde loopt van 0 tot 100 (dicht tot helemaal open).

---
#### `lees_potmeter(int pin)`
Lees de waarde van een potmeter op analoge _pin_.

__Input__:

  _`int pin`_
  
  Het analoge pinnummer waarop de potmeter is aangesloten

__Output__:
  
  _`int waarde`_
  
  De waarde van de potmeter, tussen de 0 en 100.

__Voorbeeld__:
```arduino
  void setup() {
    Serial.begin(9600);
    int potmeterwaarde = lees_potmeter(2);
    toon_op_scherm(potmeterwaarde);
  }
  void loop() {
  }
```
---
### Knoppen
Een drukknop kan wachten totdat deze ingedrukt wordt. Dat kan met de volgende functie.

#### `wacht_op_knop(int *pinummer)`
Wacht net zolang tot de knop is ingedrukt

__Input__:
  
  _`int pinummer` (optioneel)_
   
 Het pinnummer van de knop.
 _Standaard: 2_

---
### Servo motoren
Servo motoren aansturen doe je met de volgende functies. Let op met het opgeven van hoeken, de meeste servo's vinden hoeken onder de 20 en boven de 170 graden moeilijk. Ze gaan dan 'jitteren'.

#### `positioneer_servo(int hoek, int *pinummer)`
Zet de servo in een bepaalde hoek.

__Input__:

  _`int hoek`_
  
  de hoek waarin je de servo wilt positioneren
  
   _`int pinummer` (optioneel)_
  
  Het pinnummer van de servo. 
  _Standaard: 9_

__Output__:
  
  Geen
  
__Voorbeeld__:
```arduino
  void setup() {
    positioneer_servo(15);
    slaap(1);
    positioneer_servo(170);
  }
  void loop() {
    
  }
```
---
### Geluid maken
Als je een speaker aansluit kan je tonen (en dus muziek) maken met de volgende functie:

#### `void speel_toon(int toon, float seconde, int *pinummer)`
Speel een toon op de speaker.

__Input__:

  _`int toon`_
  
  De toon die je wilt spelen. Kijk naar de file "Pitches.h" om tonen te vinden.
  
  _`float seconde`_
  
  Aantal seconde dat toon speelt.

   _`int pinummer` (optioneel)_
  
  Het pinnumer van de speaker. 
  _Standaard: 11_
  
__Output__:
  
  Geen
  
__Voorbeeld__:
```arduino
  void setup() {
    speel_toon(NOTE_G1, 10); // NOTE_G1 komt uit pitches.h
  }
  void loop() {
    
  }
```
---

### DC motoren en Waterpomp
Dc motoren stuur je aan via een transistor (= een aan/uit knop). Een waterpomp stuur je op dezelfde manier aan als een dc motor.

#### `dcmotor_seconde(float seconde, int *pinummer)`
Laat een DC motor draaien.

__Input__:

  _`float seconde`_
  
  Aantal seconde dat de motor gaat draaien.
  
   _`int pinummer` (optioneel)_
  
  Het pinnumer van de transistor. 
  _Standaard: 13_

__Output__:
  
  Geen
  
__Voorbeeld__:
```arduino
  void setup() {
    dcmotor_seconde(15);
  }
  void loop() {
    
  }
```
---
### Analoge sensoren
Veel sensoren die we gebruiken zijn analoog. Om deze sensoren uit te lezen gebruik je de volgende functie

#### `lees_sensor(int *sensorpin)`
Lees de waarde van de sensor.

__Input__:

  _`int sensorpin` (optioneel)_
  
  De (analoge) pin waarop de sensor is aangesloten. Default: 0

__Output__:
  
  _`int waarde`_
  
  De waarde van de sensor, tussen de 0 en 100. Per sensor verschilt de betekenis van de waarde, probeer het vooral!
  
__Voorbeeld__:
```arduino
  void setup() {
    Serial.begin(9600);
  }
  void loop() {
    Serial.println(lees_sensor());
  }
```

### Afstandsensor
#### `cm_afstand(int *trigpin, int *echopin)`
Lees de waarde van de afstandssensor. Om deze functie te gebruiken is het belangrijk de "Ultrasonic" library te installeren. Ga hiervoor in de Arduino IDE naar `Sketch > Include Library > Manage libraries...` en zoek dan op `Ultrasonic` en installeer de Ultrasonic library van `Eric Simões`.

__Input__:

  _`int trigpin` (optioneel)_
  
  De pin waarop de aansluiting 'trig' zit. Standaard: 11
 
  _`int echopin` (optioneel)_
  
  De pin waarop de aansluiting 'echo' zit. Standaard: 12

__Output__:
  
  _`int waarde`_
  
  De waarde van de sensor. 0 = 0cm afstand, 100 = >50cm afstand.
  
__Voorbeeld__:
```arduino
  void setup() {
    Serial.begin(9600);
  }
  void loop() {
    Serial.println(cm_afstand());
  }
```
---

### Temperatuursensor
De temperatuursensor is een analoge sensor die de temperatuur teruggeeft in graden celcius.
#### `lees_temperatuur(int *sensorpin)`
Lees de waarde van de sensor.

__Input__:

  _`int sensorpin` (optioneel)_
  
  De (analoge) pin waarop de sensor is aangesloten. Default: 0

__Output__:
  
  _`int temperatuur`_
  
  De waarde van de temperatuursensor, in graden celcius. Hij geeft de temperatuur in graden zonder decimalen. 
  
__Voorbeeld__:
```arduino
  void setup() {
    Serial.begin(9600);
  }
  void loop() {
    int temperatuur = lees_temperatuur();
    toon_op_scherm(temperatuur);
    slaap(1)
  }
```

### Bodemvochtigheid
Met een bodevochtigheidsmeter kan je verassend genoeg de vochtigheid van de bodem bepalen. Op de sensor zit een draaiknop (daarvoor heb je een kruiskop schroevendraaiertje nodig). Deze draaiknop bepaalt de gevoeligheid van de sensor. De sensor zal laten weten wanneer het vochtigheids niveau de drempelwaarde overschrijft.

#### `wacht_op_vochtigheid(int* pinummer)`
Wacht tot de gewenste vochtigheid bereikt is. 

__Input__:
  
  _`int pinummer` (optioneel)_
  Het pinnummer van de sensor (digitale pin). Standaard: 13
  
__Output__:

  Geen
  
__Voorbeeld__:
```arduino
  void setup(){
    Serial.begin(9600);
  }
  
  void loop(){
    wacht_op_vochtigheid(); // De code blijft hier wachten tot de vochtigheidswaarde overschreden is.
    toon_op_scherm("Het is hier nat!");
  }
```
Het afstellen van de sensor met de draaiknop kan je het beste even testen om de ideale positie te vinden!
  

---
### SD Kaartlezer
Om je apparaat van data te voorzien heb je natuurlijk een database nodig. Wij gebruiken hiervoor een .csv bestand.

#### `lees_numerieke_waarde(int waarde, int *pinummer)`
Lees de waarde van de input op de sd kaart.

__Input__:

  _`int waarde`_
  De 'sleutel' waarvan de waarde opgezocht moet worden
  
  _`int pinummer` (optioneel)_
  Het pinnummer (ss) van de SD kaartlezer.

__Output__:
  
  _`int waarde`_
  
  De waarde die bij de 'sleutel' hoort

__Voorbeeld__:

Arduino code:

```arduino
void setup(){
  Serial.begin(9600);
  int postcode = toetsenbord_getal(1000, 10000, "Voer een postcode in");
  int postcode_waarde = lees_numerieke_waarde(postcode);
  toon_op_scherm("de waarde van postcode " + String(postcode) + " is " + String(postcode_waarde));
}
  
void loop(){
}
```
voorbeeld van hoe je data-bestand eruit kan zien op je SD kaart als we naar postcodes kijken:
_data.csv_
```csv
...
3510,67
3511,45
3512,12
...
```

#### `lees_keuze_waardes(String waardes[], int lengtewaardes, int *pinummer)`
Laat de gebruiker een keuze maken uit een lijst en geef de waarde op die plek terug.

__Input__:

  _`String waardes[]`_
  De lijst met waardes om uit te kiezen
  
  _`int lengtewaardes`_
  De lengte van de lijst hierboven.
  
  _`int pinummer` (optioneel)_
  Het pinummer (ss) van de SD kaartlezer.

__Output__:
  
  _`int waarde`_
  
  De waarde die bij de 'sleutel' hoort

__Voorbeeld__:

Arduino code:

```arduino
void setup(){
  Serial.begin(9600);
  String keuzes[] = {"Foutloos Nederlands spreken", "Rechtvaardigheid", "Samen", "Geld", "Wat de buren van mij denken", "Een mooie auto", "Werk", "Vrijheid", "Kunnen Wij Het Maken?!"}; // Op deze manier maak je een lijst
  int waarde = lees_keuze_waardes(keuzes, 9); // Laat de gebruiker een keuze maken uit de lijst. Bijvoorbeeld "Boos". Dan print dit "64"
  toon_op_scherm(waarde);
}
  
  void loop(){
}
```
voorbeeld van hoe je data-bestand eruit kan zien op je SD kaart.  

data.csv:
```csv
...
Foutloos Nederlands spreken,67
Rechtvaardigheid,64
Samen,12
Geld,14
...
```

---
### Controle functies
De volgende functies interacteren niet met onderdelen maar stellen je in staat je programma te controleren.

#### `slaap(float seconde)`
Laat je Arduino lekker rusten af en toe.

__Input__:

  _`float seconde`_
  
  Het aantal seconde, decimale getallen mogen ook!

__Output__:
  
  Geen
  
  
__Voorbeeld__:
```arduino
  void setup() {
  }
  void loop() {
    zet_led_aan(13);
    slaap(2);
    zet_led_uit(13);
    slaap(2);
  }
```
