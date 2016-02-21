//connection à une page internet avec accusé de réception
#include <SoftwareSerial.h> // inclusions de bibliothèque
#include <String.h>

SoftwareSerial mySerial(7, 8); // définition de la liaison série "mySerial" sur las pattes 7 et 8
 
void setup()
{
  mySerial.begin(19200); // définition de la vitesse de communication
  Serial.begin(19200); // définition de la vitesse de communication
  delay(3000); // attente de 3000 ms
  Serial.println("setup"); // écriture de "setup" sur la liaison arudino-PC
  // demande au shield :
  mySerial.println("AT+CPIN?"); // état de la carte : dévérouillée
  delay(100); ShowSerialData(); // attente de 100 ms et appelle de la fonction ShowSerialData
  mySerial.println("AT+CPIN=\"1234\""); // insertion du code PIN
  delay(100); ShowSerialData();
  mySerial.println("AT+CSQ");  // qualité du signal
  delay(200); ShowSerialData();
  mySerial.println("AT+CGATT=?"); // état de connection au réseau
  delay(100); ShowSerialData();
}
 
void loop()
{
  Serial.println("loop"); // écriture de "loop" sur la liaison arduino-PC
  delay(5000); // attente de 3000 ms
  
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); // paramétrage de SAPBR, en connection de type GPRS
  delay(1000); ShowSerialData();
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"CMNET\""); // paramétrage de APN
  delay(4000); ShowSerialData();
  mySerial.println("AT+SAPBR=1,1"); // paramétrage de SAPBR
  delay(2000); ShowSerialData();
 
  mySerial.println("AT+HTTPINIT"); // initialisation de la requête HTTP
  delay(2000); ShowSerialData();
  mySerial.println("AT+HTTPPARA=\"URL\",\"www.google.fr\""); // paramétrage de l'HTTP et le lien internet
  delay(1000); ShowSerialData();
 
  mySerial.println("AT+HTTPACTION=0"); // envoi d'une requête 
  delay(10000); ShowSerialData();
  mySerial.println("AT+HTTPREAD"); // lecture des données envoyées par le site
  delay(300); ShowSerialData();
  mySerial.println("");delay(100);
  
}
 
void ShowSerialData()
{
  while(mySerial.available()!=0) // tant que la liaison série n'est pas vide
    Serial.write(mySerial.read()); // écriture de ce que l'arduino reçoit du shield vers le PC
}
