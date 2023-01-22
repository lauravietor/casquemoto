///////////////////////////////////////////////////////////Temperature
float reading;
float voltage;
float temperature = 0;   

#define sensorPin A0

///////////////////////////////////////////////////////////Accelerometer
#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;

///////////////////////////////////////////////////////////GPS
#include <SoftwareSerial.h>                                    //Librairie permettant d’émuler (simuler) un nouveau port série
SoftwareSerial GPS (7, 8 );                                    //GPS est la variable permettant de communiquer avec le GPS. Communication sur les pins 7(RX) et 8(TX)

char caractere;                                                //Définition d'une chaîne de caractère
String msg = String("");                                       //Tableau contenant des chaines de caractères
String coordonees;

void setup()
{
    Serial.begin(9600);  //Débit de communication à 9600 baud (nbr de symboles transmissibles / sec

    // Setup de l'accéléromètre
    Wire.begin();                      // Initialize comunication
    Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);        //end the transmission
    
    // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
    Wire.beginTransmission(MPU);
    Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
    Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
    Wire.endTransmission(true);

    // Configuration du GPS
    GPS.begin(9600);                                           //Débit de communication avec le GPS à 9600 baud
      GPRS.begin(19200);                // Vitesse de transmission. Ouverture du port série virtuel avec un débit de 19200 bauds.
      GPRS.println("AT+IPR=19200");     // Mise en mémoire du débit
      delay(1000);
      GPRS.println("AT+CMGF=1");        // SMS en mode texte et non binaire
      delay(1000);  
  }


String getGPS() {                                             //exemple de ce qu'envoie le GPS : $GPGGA,064036.289,4836.5375,N,00740.9373,E,1,04,3.2,200.2,M,,,,0000*0E
    caractere = GPS.read();
    while (caractere != 10) {
        caractere = GPS.read();
    }
    
    String lecture = "";
    while(lecture.length() < 70) {
        if (GPS.available()) {
            caractere = GPS.read();
            lecture += String(caractere);
        }
    }

    coordonees = msg.substring(18,42);
    return coordonees;
}


void loop() { 
  
    //Lecture des données de l'accéléromètre intégré
    Wire.beginTransmission(MPU);
    Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
    acceleration = AccX + AccY + AccZ // A adapter, mais l'idée est là
    
    if (acceleration < 400) {    
        while ( temperature < 28 ) {
            reading = analogRead(sensorPin);
            voltage = reading * (5.0 / 1024.O);
            temperature = voltage * 100; 
            Serial.print("La température en Celsius est de: ");
            Serial.println(temperature);
            delay(1000);
        }
        sensorValue = analogRead(A1);                                   //lire la valeur au port A1
        Serial.println(sensorValue);                                    // Imprimer la valeur dans la fenêtre
    }

    coordonees = getGPS();
    Serial.println(coordonees);    
}

//////////////////////////////////////////////////////////// Ancien code de getGPS ////////////////////////////////////////////////////////////////////////////////////////////////
// while(1) {
//             if (GPS.available()) {                                          // si un caractère est présent...      
//                 caractere = GPS.read();                                 // lire caractère
                
//                 if (caractere==10) {                                 // Dans la lecture du caractère : si le caractère est un saut de ligne...
//                     if (msg.startsWith("$GPGGA")) {                  // si la chaine de caractère commence par $GPGGA         
//                     Serial.println(msg.substring(18,42));           // Alors on va afficher les caractères du 18e jusqu'au 42e qui corespondent aux coordonnées GPS voulue
//                     msg="";                                         // effacer la chaine de caractère parce que je l'ai déjà traitée -> Pour laisser place aux lignes suivantes
//                     } 
//                 }
//                 else {                                                   //sinon... 
//                     msg += String(caractere);                           //ajouter le caractère lu à la chaine de caractère -> enregistrer le caractère qui vient d'arriver pour le traiter ensuite
//                 }
//             }  
//         }
