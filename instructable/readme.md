# Instructable

Een instructable is een stappenplan - zonder verdere uitleg - hoe je vertrekkend van de bill of materials en gebruik makend van de technische tekeningen de robot kan nabouwen. Ook de nodige stappen om de microcontroller te compileren en te uploaden staan beschreven.  

### stap 1
bestel alle componenten uit de bill of materials  
### Stap 2:  chasis montage
Lijm de motoren vast vanachter aan het chasis met de motorklemmen. Soldeer de aansluitdraden aan de motoren en steek door de gleuf achteraan. 
Bevestig de sensor vooraan het frame doormiddel van 2 M3 bouten en moeren. Om de sensor op de juiste hoogte te hangen kan je door hetzelfde gat nog een bout steken met langs beide kanten een moer zodat de kop van de bout verder uitsteekt dan de sensoren. Verbind met M/F kabels om naar het breadbord te gaan.
Lijm de batterijhouder vast boven de wielen. Zorg dat je het deksel nog kan verwijderen.
Lijm het breadbord vast in het middenste vak. Op het breadbord steek je de microcontoller en de H-brug. Zorg ook voor een kalibratie knop en een start/stop knop. 
Monteer de wielen op de motorassen
### Stap 3: elektrische aansluitingen
Soldeer de positieve kant van de batterij-aansluiting aan de powerswitch. En sluit de batterij aan de H-brug en de Vin pin van de microcontroller. Zorg dat alle ground pinnen met elkaar verbonden staan.
Sluit de motoren aan op de H-brug.
Volg voor de andere aansluitingen het elektrisch schema.
### Stap 4: Software instaleren
 Installeer Arduino IDE.
ESP32 configureren in Arduino IDE:
Open de Arduino IDE.
Ga naar Tools > Board > Board Manager en installeer de ESP32-bibliotheek.
Installeer ook de QTR 8A bibliotheek en de wifi bibliotheek.
### Stap 5: Code uploaden
Om de code te uploaden moet je de microcontroller in upload mode brengen. Dit doe je door dubbel te klikken op de reset knop, als de RGB led alle kleuren afgaat, druk je nog eens. Nu zou de led groen moeten knipperen. Dan kan je de juiste COM poort aanduiden in de programmeer omgeving en uploaden. 
Na het uploaden klik je nog eens op de reset knop en trek je de microcontroller uit en steek je hem terug in. Als de Arduino is opgestart klik je nog eens reset. Dan zou het programma moeten draaien.
### Stap 6: wireless communication
Door in de seriële monitor te kijken kan je het IP-adres zien
Surf naar dit IP-adres.
### Stap 7: Functionele Test
Sluit de batterij aan op de batterijhouders.
Plaats de robot op het zwarte vlak en calibreer, plaat de robot na 5sop wit.
Plaats de robot op het parcour en druk start.
Controleer of de robot de lijn correct volgt.

Je linefollower robot is nu klaar!
