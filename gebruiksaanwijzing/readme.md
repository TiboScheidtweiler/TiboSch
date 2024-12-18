# Gebruiksaanwijzing

### opladen / vervangen batterijen
verwijder het deksel van de batterijhouder en neem de batterijen eruit. Voorzie de oplader van voeding en steek de batterijen in de oplader. Het opladen is voltooid als het lichtje groen wordt. Blijf altijd in de buurt van de batterijen tijdens het opladen voor de veiligheid.

### draadloze communicatie
#### verbinding maken
Vul in de code de naam van het wifi netwerk en het wachtwoord in. als je het programma start en op de kalibratieknop drukt zal je in de seriële monitor het IP-adres van de microcontoller kunnen uitlezen. Als je dan via je smartphone of laptop naar dit IP-adres surft via een browser kom je op een webpagina waarmee je de auto kan besturen. Let wel op dat je smartphone/laptop met hetzelfde netwerk is verbonden.

#### commando's 
- start / zorgt dat de auto begint te rijden 
- stop  / zorgt dat de auto stopt met rijden
- set power [0..255]  / bepaalt de snelheid van de auto
- set Reverse factor [o..255] / bepaalt de achterwaartse snelheid van binnenste wiel in scherpe bochten
- set kp [0..] / bepaald de kp waarde van de pid regelaar
- set ki [0..] / bepaald de ki waarde van de pid regelaar
- set kd [0..] / bepaald de kd waarde van de pid regelaar
- calibrate / de sensoren worden gekalibreert op de zwarte en witte waarden.  

### kalibratie
Druk op de kalibratieknop (pin D12) of op de kalibratie knop op de webpagina. Nu zal er 10s gekalibreert worden, de ingebouwde led zal branden zolang de kalibratie loopt. In deze 10s moeten je de sensor zwart en wit laten zien zodat de uitgelezen worden hiermee vergeleken kunnen worden. Dit zorgt voor een goede werking van de sensor.  

### settings
De robot rijdt stabiel met volgende parameters:  Kp=1,05 , Ki=0 , Kd=0,3 , Base Speed=110 , Max Speed=250 , Reverse factor=85

### start/stop button
Start/stop knop is verbonden met pin D11, maar start/stop kan ook via de webpagina. De ingebouwde led zal knipperen als de auto in de 'run' mode staat en dus zal rijden.
