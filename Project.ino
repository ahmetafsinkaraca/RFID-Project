
#include <Wire.h>
#include <LiquidCrystal_I2C_AvrI2C.h>

#include <DS1302RTC.h>
#include <TimeLib.h>
#include <SD.h> // hafıza kartı kütüphanesi
#include <SPI.h>
#include <RFID.h>

#define RFID_RST_PIN 9
#define RFID_SS_PIN 10
int say = 0;
RFID rfid(RFID_SS_PIN, RFID_RST_PIN);
#define CSpin 4 // hafıza kartı seçim pini
File dosya; // dosya
LiquidCrystal_I2C_AvrI2C lcd(0x27 , 16 , 2);  // avr kutuphanesi 
DS1302RTC RTC(5, 6, 7);
byte kisi = 0;
byte saat = 0;
byte dakika = 0;
byte saniye = 0;
byte yil = 0;
byte ay = 0;
byte gun = 0;
byte bir[5] = {51, 60, 145, 12, 146};
byte iki[5] = {208, 4, 220, 37, 45};
byte uc[5] = {208, 39, 253, 37, 47};
byte serNum[5];
byte data[5];





void setup() {
  Serial.begin(9600);
  pinMode(RFID_RST_PIN, OUTPUT);
  pinMode(RFID_SS_PIN, OUTPUT);
  pinMode(CSpin, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
  SPI.begin();
  rfid.init();
  lcd.begin();
  lcd.backlight();
  if (!SD.begin(CSpin)) { // SD kart başlangıç

    lcd.clear();
    lcd.setCursor (0, 0);
    lcd.println(" SD KART TAKILI ");
    lcd.setCursor (0, 1);
    lcd.println(" !!!  DEGIL !!! ");
    delay(2000);
    lcd.clear();
    lcd.setCursor (0, 0);
    lcd.println("   SAAT AYARI   ");
    lcd.setCursor (0, 1);
    lcd.println("!! YAPILAMADI !!");
    delay(2000);
    Serial.println("SD KART YOK");
    return;
  }
  Serial.print("RTC ETKIN ");

  delay(500);
  if (RTC.haltRTC())
    Serial.print("SAAT DURDU!");


  else
    Serial.print("SAAT AKTIF ");
  if (RTC.writeEN())
    Serial.print("YAZMAYA IZIN VER ");
  else
    Serial.print("YAZMA KORUMALI");
  Serial.print("RTC AYARLARI");
  setSyncProvider(RTC.get); // the function to get the time from the RTC
  if (timeStatus() == timeSet)
    Serial.print(" TAMAM!");
  else
    Serial.print(" HATALI!");

  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.println(" KATILIM TAKIP  ");
  lcd.setCursor (0, 1);
  lcd.println("    SISTEMI     ");

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(8, HIGH);
  delay(1000);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(8, LOW);
}

void loop() {

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  kisi = 0;
  digitalWrite(8, LOW);
  saniye = second();
  saat = hour();
  dakika = minute();
  gun = day();
  ay = month();
  yil = year();




  lcd.setCursor (0, 0);
  lcd.println("TAKIP SISTEMI   ");
  lcd.setCursor (0, 1);
  if (ay < 10) {
    lcd.print("0");
    lcd.print(ay);
    lcd.print(".");
  }
  if (ay > 9) {
    lcd.print(ay);
    lcd.print(".");
  }
  if (gun < 10) {
    lcd.print("0");
    lcd.print(gun);
    lcd.print(" / ");
  }
  if (gun > 9) {
    lcd.print(gun);
    lcd.print(" / ");
  }
  if (saat < 10) {
    lcd.print("0");
    lcd.print(saat);
    lcd.print(":");
  }
  if (saat > 9) {
    lcd.print(saat);
    lcd.print(":");
  }
  if (dakika < 10) {
    lcd.print("0");
    lcd.print(dakika);
    lcd.print(":");
  }
  if (dakika > 9) {
    lcd.print(dakika);
    lcd.print(":");
  }
  if (saniye < 10) {
    lcd.print("0");
    lcd.print(saniye);
    lcd.print("....");
  }
  if (saniye > 9) {
    lcd.print(saniye);
    lcd.print("...");
  }

  digitalWrite(RFID_SS_PIN, LOW); //aktif RFID
  digitalWrite(CSpin, HIGH); //aktif
  if (rfid.isCard())
  {
    if (rfid.readCardSerial())
    {
      //      Serial.print("Kart bulundu ID: ");
      //      Serial.print(rfid.serNum[0]);
      //      Serial.print(",");
      //      Serial.print(rfid.serNum[1]);
      //      Serial.print(",");
      //      Serial.print(rfid.serNum[2]);
      //      Serial.print(",");
      //      Serial.print(rfid.serNum[3]);
      //      Serial.print(",");
      //      Serial.println(rfid.serNum[4]);
    }

    if (rfid.serNum[0] == bir[0]) {
      if (rfid.serNum[1] == bir[1]) {
        if (rfid.serNum[2] == bir[2]) {
          if (rfid.serNum[3] == bir[3]) {
            if (rfid.serNum[4] == bir[4]) {
              Serial.println("KAYITLI KULLANICI");
              lcd.clear();
              lcd.setCursor (0, 0);
              lcd.println(" Kemal Murat    ");
              lcd.setCursor (0, 1);
              lcd.println(" 170201803      ");

              digitalWrite(8, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              delay(500);
              kisi = 1;  kayit();

            }
          }
        }
      }
    }

    if (rfid.serNum[0] == iki[0]) {
      if (rfid.serNum[1] == iki[1]) {
        if (rfid.serNum[2] == iki[2]) {
          if (rfid.serNum[3] == iki[3]) {
            if (rfid.serNum[4] == iki[4]) {
              Serial.println("KAYITLI KULLANICI");

              digitalWrite(8, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              lcd.clear();
              lcd.setCursor (0, 0);
              lcd.println("");
              lcd.setCursor (0, 1);
              lcd.println("");
              delay(500);
              kisi = 2; kayit();

            }
          }
        }
      }
    }


    if (rfid.serNum[0] == uc[0]) {
      if (rfid.serNum[1] == uc[1]) {
        if (rfid.serNum[2] == uc[2]) {
          if (rfid.serNum[3] == uc[3]) {
            if (rfid.serNum[4] == uc[4]) {
              Serial.println("KAYITLI KULLANICI");

              digitalWrite(8, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              lcd.clear();
              lcd.setCursor (0, 0);
              lcd.println(" ");
              lcd.setCursor (0, 1);
              lcd.println(" ");
              delay(500);
              kisi = 3;  kayit();

            }
          }
        }
      }
    }

              digitalWrite(8, HIGH);
              digitalWrite(3, LOW);
              digitalWrite(2, HIGH);
 


kayit();


    rfid.halt();
  }
}



void kayit()
{

  digitalWrite(8, LOW);

  digitalWrite(RFID_SS_PIN, HIGH); // RFID pasif
  digitalWrite(CSpin, LOW); //aktif

  dosya = SD.open("DOSYAM.txt", FILE_WRITE); //dosya oluşturuldu
  if (SD.exists("DOSYAM.txt")) { //
    Serial.println("KAYIT YAPILDI");

    lcd.setCursor (15, 1);
    lcd.println("+");
    dosya.print("KAYIT :");
    if (ay < 10) {
      dosya.print("0");
      dosya.print(ay);
      dosya.print(".");
    }
    if (ay > 9) {
      dosya.print(ay);
      dosya.print(".");
    }
    if (gun < 10) {
      dosya.print("0");
      dosya.print(gun);
      dosya.print(" / ");
    }
    if (gun > 9) {
      dosya.print(gun);
      dosya.print(" / ");
    }
    if (saat < 10) {
      dosya.print("0");
      dosya.print(saat);
      dosya.print(":");
    }
    if (saat > 9) {
      dosya.print(saat);
      dosya.print(":");
    }
    if (dakika < 10) {
      dosya.print("0");
      dosya.print(dakika);
      dosya.print(":");
    }
    if (dakika > 9) {
      dosya.print(dakika);
      dosya.print(":");
    }
    if (saniye < 10) {
      dosya.print("0");
      dosya.print(saniye);
      dosya.print("....");
    }
    if (saniye > 9) {
      dosya.print(saniye);
      dosya.print("....");
    }


    if (kisi == 1)
    {
      dosya.print(" Kemal Murat numara 170201803    ");

    }


    if (kisi == 2)
    {
      dosya.print(" ");

    }

    if (kisi == 3)
    {
      dosya.print(" ");

    }

    if (kisi == 0)
    {
      dosya.print(" Kayıt Dısı Kart Okutuldu !!!  ");

      kisi = 0;
    }
    dosya.print("Kart ID: ");
    dosya.print(rfid.serNum[0]);
    dosya.print(",");
    dosya.print(rfid.serNum[1]);
    dosya.print(",");
    dosya.print(rfid.serNum[2]);
    dosya.print(",");
    dosya.print(rfid.serNum[3]);
    dosya.print(",");
    dosya.println(rfid.serNum[4]);

    dosya.close();  // dosya kapandı
  }

    else {
    }

  delay(1000);
}
