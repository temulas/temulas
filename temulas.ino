
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

constexpr uint8_t RST_PIN = 26;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 53;     // Configurable, see typical pin layout above

int sensorPin=6;

byte uidArr[4];

float userbalance=0;

int balance=0;
int artis=25;

int okundu=0;

int bakiye=0;

String card1="1622196233";
String card2="199116196233";
String card3="212129196233";
String card4= "1721815589";
String card5="013156206233";

String barcode0="8690525060010";
String barcode1="8690565017838";
String barcode2="86921077";
String barcode3="90162602";
String barcode4="8690767160189";
String barcode5="8690767160189";


String uid;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];


void yazici(int balance){

       Serial2.write(0x1b);
        Serial2.write(0x61);
        Serial2.write(0x31);
        Serial2.write(29);
        Serial2.write(33);
        Serial2.write(8);
        Serial2.println("TEM-ULAS");
        Serial2.print("Kart1 Bakiye:");
         float para2;
                  para2=(float)balance/100;
        Serial2.println(para2);
        Serial2.println("Iyi yolculuklar dileriz."); 
       
        
        Serial2.write(29);
        Serial2.write(86);
        Serial2.write(66);
        Serial2.write(128);
       



  
}


void setup() { 
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  pinMode(sensorPin,INPUT);

  lcd.begin(16, 2);
  
  lcd.print("  Geri Donusum");

  lcd.setCursor(0, 1);
  lcd.print("     Otomati");
  
       

  
}
 
void loop() {

  String barcode;
  
   while(Serial1.available())
    { 
      char data=char(Serial1.read());  
       if(data!=13){
        barcode+=data;

       }
        okundu=1;
        delay(10);
     }
     
     if(okundu==1)
     { 
      
      
         Serial.println(barcode);
         //Serial.println(barcode0);
          okundu=0;

              if(barcode==barcode0)
              {
                balance=balance+artis;
              }else if(barcode==barcode1){
                balance=balance+artis;
              }else if(barcode==barcode2){
                balance=balance+artis;
              }else if(barcode==barcode3){
                balance=balance+artis;
              }else if(barcode==barcode4){
                balance=balance+artis;
              }else if(barcode==barcode5){
                balance=balance+artis;
              }else{
                lcd.clear();
                lcd.setCursor(0, 1);
                 lcd.print("Gecersiz Atik");
                 delay(2000);
              }
  
                  lcd.clear();
                  lcd.setCursor(0, 1);
                  lcd.print("Bakiye:");
                  float para;
                  para=(float)balance/100;
                  lcd.print(para);
            
 
      }


      
            

    
         
   

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

    


    for (byte i = 0; i < 4; i++) {
          uid+=(String) rfid.uid.uidByte[i];
    }
    
     if(uid=="1622196233")
     {
      Serial.println("birincikart");
        
        bakiye=EEPROM.read(0);
        bakiye=bakiye<<8;
        
        bakiye=bakiye+EEPROM.read(1);

        balance=bakiye+balance;
        
        EEPROM.write(0, (balance>>8)&0xff);
        EEPROM.write(1, (balance&0xff));

        balance=EEPROM.read(0);
        balance=balance<<8;
        
        balance=balance+EEPROM.read(1);

                  lcd.clear();
                  lcd.setCursor(0, 1);
                  lcd.print("Yeni Bak:");
                   float para3;
                  para3=(float)balance/100;
                   lcd.print(para3);
                  yazici(balance);
                  delay(2000);
        balance=0;
       
       
     }
     else if(uid=="199116196233"){
      Serial.println("ikinci kart");
         bakiye=EEPROM.read(2);
        bakiye=bakiye<<8;
        
        bakiye=bakiye+EEPROM.read(3);

        balance=bakiye+balance;
        
        EEPROM.write(2, (balance>>8)&0xff);
        EEPROM.write(3, (balance&0xff));

        balance=EEPROM.read(2);
        balance=balance<<8;
        
        balance=balance+EEPROM.read(3);

                  lcd.clear();
                  lcd.setCursor(0, 1);
                  lcd.print("Yeni Bak:");
                 float para3;
                   para3=(float)balance/100;
                   lcd.print(para3);
                  yazici(balance);
                  
                  delay(2000);
        balance=0;
         

      
     }
     else if(uid=="212129196233"){
      Serial.println("ucuncu kart");

          bakiye=EEPROM.read(4);
        bakiye=bakiye<<8;
        
        bakiye=bakiye+EEPROM.read(5);

        balance=bakiye+balance;
        
        EEPROM.write(4, (balance>>8)&0xff);
        EEPROM.write(5, (balance&0xff));

        balance=EEPROM.read(4);
        balance=balance<<8;
        
        balance=balance+EEPROM.read(5);

                  lcd.clear();
                  lcd.setCursor(0, 1);
                  lcd.print("Yeni Bak:");
                  float para3;
                  para3=(float)balance/100;
                   lcd.print(para3);
                  yazici(balance);
                  
                  delay(2000);
        balance=0;

      
     }
     else if(uid=="1721815589"){
      Serial.println("dorduncu kart");

          bakiye=EEPROM.read(6);
        bakiye=bakiye<<8;
        
        bakiye=bakiye+EEPROM.read(7);

        balance=bakiye+balance;
        
        EEPROM.write(6, (balance>>8)&0xff);
        EEPROM.write(7, (balance&0xff));

        balance=EEPROM.read(6);
        balance=balance<<8;
        
        balance=balance+EEPROM.read(7);

                  lcd.clear();
                  lcd.setCursor(0, 1);
                  lcd.print("Yeni Bak:");
                  lcd.print(balance);
                  yazici(balance);
                  delay(2000);
        balance=0;
         

      
     }
     else if(uid=="13156206233"){
      Serial.println("besinci kart");
           bakiye=EEPROM.read(8);
        bakiye=bakiye<<8;
        
        bakiye=bakiye+EEPROM.read(9);

        balance=bakiye+balance;
        
        EEPROM.write(8, (balance>>8)&0xff);
        EEPROM.write(9, (balance&0xff));

        balance=EEPROM.read(8);
        balance=balance<<8;
        
        balance=balance+EEPROM.read(9);

                  lcd.clear();
                  lcd.setCursor(0, 1);
                  lcd.print("Yeni Bak:");
                   float para1;
                  para1=(float)balance/100;
                  lcd.print(para1);
                  yazici(balance);
                  delay(2000);
        balance=0;
      
     }
     
  uid="";
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

  rfid.PCD_Init(); // Init MFRC522 
}











