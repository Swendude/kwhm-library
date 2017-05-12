# Kunnen wij het Maken?!
<a href="www.setup.nl"><img alt="Setup logo" src=http://www.moocha.nl/wp-content/uploads/2010/04/setup_logo.jpg width="100"></a>     <a href="www.mindmingle.nl"><img alt="Mindmingle logo" src="http://i.imgur.com/NHPQaB8.png" width="100"></a>
## introductie

Welkom bij de officiele Kunnen wij het Maken?! repository! Een repository is een heel stoer woord voor "plek waar code woont". 
Op deze pagina vind je alle benodigdheden om je eigen dubieus apparaat te maken.  

Tijdens de masterclasses maak je gebruik van het [Arduino  platform](https://www.arduino.cc/). De bestanden in deze repo gaan je helpen de Arduino aan te sturen.

## Hoe te starten?

### Arduino IDE
Allereerst heb je de Arduino IDE (Integrated Development Envirnoment) nodig. Dit is de plek waarin je je code gaat onderhouden en output van de arduino kan lezen. De IDE kan je [hier](https://www.arduino.cc/en/main/software) downloaden. Zorg ervoor dat je de laatste versie voor je besturingssysteem download! We werken niet met de online versie.

### KWHM file
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

## Documentatie

Hieronder staat de uitleg voor alle beschikbare functies. Ze zijn ingedeeld per categorie. 

### Informatie tonen in de serial monitor

Arduino kan ons berichten sturen via een "seriele" poort. Die berichten kunnen we bekijken met een "seriele monitor". Gelukkig heeft de Arduino IDE al zo'n monitor voor ons klaargezet. Deze is te vinden onder ```Tools > Serial Monitor```. Door gebruik te maken van onderstaande functies. __Zorg ervoor dat je Seriele Monitor op '9600 baud' staat (rechtsonderin).__

---
#### toon_op_scherm(tekst)
Deze functie zal een bericht naar de seriele monitor sturen, gevolgd door een enter (nieuwe regel).

__Input__:

  _tekst_
  
  De waarde die je op het scherm wilt laten zien

__Output__:
  
  Geen

__Voorbeeld__:
```arduino
  void setup() {
    toon_op_scherm("Hallo, van Arduino!");
  }
  void loop() {
  }
```
---
#### voeg_toe_op_scherm(symbool)
Deze functie zal een bericht naar de seriele monitor sturen zonder een enter toe te voegen. Handig in combinatie met ```regel_op_scherm```. __Deze functie werk alleen met een ```char``` type, dat is een symbool omrings met enkele aanhalingstekens zoals ```'a'```

__Input__:

  _symbool_
  
het symbool die je op het scherm wilt toevoegen

__Output__:
  
  Geen

__Voorbeeld__:
```arduino
  void setup() {
  }
  void loop() {
  voeg_toe_op_scherm('a'); // Er zullen een heleboel a's verschijnen!
  }
```
