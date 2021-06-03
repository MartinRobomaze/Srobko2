//************ Ovladanie robota Arduino-Raspberry-Kinect **************
//****** radio RF24 ******************
#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"
#include "printf.h"
#include <Servo.h>
RF24 radio(41, 42);
uint8_t data[25];
const uint64_t adresa = (0xF0F0F0F0E1LL);
int kontrolne_cislo = 159;
#define INTERRUPT_PIN 2
#include "tony.h"
int ton[] = {C4, G4, G4, A4, G4, B4, C5, C5, B4, G4, A4, G4, G4, C4};
int doba[] = {4, 8, 8, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 4};

Servo servorob1;
Servo servorob2;
Servo servorob3;
Servo servorob4;
Servo servorob5;
Servo servorob6;
Servo servorob7;
Servo servorob8;
Servo servorob9;
Servo servorob10;
Servo servorob11;
Servo servorob12;
Servo servorob13;
Servo servorob14;
Servo servorob15;
Servo servorob16;
Servo servorob17;
Servo servorob18;
Servo servorob19;
Servo servorob20;
Servo servorob21;
Servo servorob22;
Servo servorob23;
Servo servorob24;
Servo servorob25;

int uholserva[25];
int uholmin[25];
int uholmax[25];
int i, x, vzd;
void setup()
{
  //****** Pre RF24 *************
  printf_begin();
  Serial.begin(115200);
  pinMode(INTERRUPT_PIN, INPUT);
  radio.begin();
  delay(1000);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(adresa); //doplnene
  radio.openReadingPipe(1, adresa);

  radio.setChannel(0x66);
  radio.printDetails();
  radio.enableDynamicPayloads(); //toto som doplnil pre ovl. z raspberry
  radio.startListening();
  //*******************************
  for (i = 0; i < 13; i++)
  {
    int dlzka = 1000 / doba[i];
    tone(46, ton[i], dlzka);
    int cakanie = dlzka * 1.30;
    delay(cakanie);
    noTone(46);
  }

  uholserva[1] = 0;    // Rameno prave hore
  uholserva[2] = 180;  // Rameno lave hore
  uholserva[3] = 150;  // Rameno prave od tela
  uholserva[4] = 20;   // Rameno lave od tela
  uholserva[5] = 90;   // Rameno prave vytocit
  uholserva[6] = 90;   // Rameno lave vytocit
  uholserva[7] = 95;   // Laket pravy
  uholserva[8] = 60;   // Laket lavy
  uholserva[9] = 90;   // Hlava hore-dole
  uholserva[10] = 40;  // Hlava vľavo-vpravo
  uholserva[11] = 0;   // Zápästie pravé
  uholserva[12] = 140; // Zápästie ľavé 140
  uholserva[13] = 10;  // P dlaň
  uholserva[14] = 160; // L dlaň
  uholserva[15] = 95;  // Pravé chodidlo Ľ/P
  uholserva[16] = 100; // Ľavé chodidlo Ľ/P
  uholserva[17] = 60;  // Pravé chodidlo H/D
  uholserva[18] = 90;  // Ľavé chodidlo H/D
  uholserva[19] = 60;  // Pravé koleno 0-110 60
  uholserva[20] = 50;  // Ľavé koleno 0-110 50
  uholserva[21] = 175; // Pravá noha H/D 30-55-180
  uholserva[22] = 155; // Ľavá noha H/D 10-35-160
  uholserva[23] = 160; // Pravá noha nabok
  uholserva[24] = 5;   // Ľavá noha nabok
  uholserva[25] = 110; // Nohy vytočiť 70-90-110

  servorob1.attach(9); // Rameno prave hore
  servorob1.write(uholserva[1]);
  uholmin[1] = 0;
  uholmax[1] = 180;
  servorob2.attach(17); // Rameno lave hore
  servorob2.write(uholserva[2]);
  uholmin[2] = 180;
  uholmax[2] = 0;
  servorob3.attach(12); // Rameno prave od tela
  servorob3.write(uholserva[3]);
  uholmin[3] = 170;
  uholmax[3] = 80;
  servorob4.attach(20); // Rameno lave od tela
  servorob4.write(uholserva[4]);
  uholmin[4] = 0;
  uholmax[4] = 90;
  servorob5.attach(13); // Rameno prave vytocit
  servorob5.write(uholserva[5]);
  uholmin[5] = 0;
  uholmax[5] = 180;
  servorob6.attach(21); // Rameno lave vytocit
  servorob6.write(uholserva[6]);
  uholmin[6] = 180;
  uholmax[6] = 0;
  servorob7.attach(10); // Laket pravy
  servorob7.write(uholserva[7]);
  uholmin[7] = 5;
  uholmax[7] = 110;
  servorob8.attach(18); // Laket lavy
  servorob8.write(uholserva[8]);
  uholmin[8] = 160;
  uholmax[8] = 50;

  servorob9.attach(31); // Hlava hore-dole
  servorob9.write(uholserva[9]);
  uholmin[9] = 110;
  uholmax[9] = 60;
  servorob10.attach(30); // Hlava vlavo-vpravo
  servorob10.write(uholserva[10]);
  uholmin[10] = 0;
  uholmax[10] = 90;

  servorob11.attach(11); // Zápästie pravé
  servorob11.write(uholserva[11]);
  uholmin[11] = 0;
  uholmax[11] = 140;
  servorob12.attach(45); // Zápästie ľavé bolo na 19
  servorob12.write(uholserva[12]);
  uholmin[12] = 140;
  uholmax[12] = 0;

  servorob13.attach(8); // dlaň pravá
  servorob13.write(uholserva[13]);
  uholmin[13] = 10;
  uholmax[13] = 60;
  servorob14.attach(16); // dlaň ľavá
  servorob14.write(uholserva[14]);
  uholmin[14] = 160;
  uholmax[14] = 100;

  servorob15.attach(4); // Pravé chodidlo Ľ/P
  servorob15.write(uholserva[15]);
  uholmin[15] = 145;
  uholmax[15] = 0;
  servorob16.attach(3); // Ľavé chodidlo Ľ/P
  servorob16.write(uholserva[16]);
  uholmin[16] = 145;
  uholmax[16] = 0;
  servorob17.attach(33); // Pravé chodidlo H/D
  servorob17.write(uholserva[17]);
  uholmin[17] = 40;
  uholmax[17] = 110;
  servorob18.attach(32); // Ľavé chodidlo H/D
  servorob18.write(uholserva[18]);
  uholmin[18] = 70;
  uholmax[18] = 115;
  servorob19.attach(5); // Pravé koleno
  servorob19.write(uholserva[19]);
  uholmin[19] = 0;
  uholmax[19] = 110;
  servorob20.attach(2); // Ľavé koleno
  servorob20.write(uholserva[20]);
  uholmin[20] = 0;
  uholmax[20] = 110;
  servorob21.attach(7); // Pravá noha dopredu
  servorob21.write(uholserva[21]);
  uholmin[21] = 30;
  uholmax[21] = 180;
  servorob22.attach(15); // Ľavá noha dopredu
  servorob22.write(uholserva[22]);
  uholmin[22] = 10;
  uholmax[22] = 160;
  servorob23.attach(6); // Pravá noha nabok
  servorob23.write(uholserva[23]);
  uholmin[23] = 160;
  uholmax[23] = 130;
  servorob24.attach(14); // Ľavá noha nabok
  servorob24.write(uholserva[24]);
  uholmin[24] = 5;
  uholmax[24] = 60;
  servorob25.attach(34); // Nohy vytočiť
  servorob25.write(uholserva[25]);
  uholmin[25] = 70;
  uholmax[25] = 110;

  // Definovanie portov pre tlačidlá
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
}
//***** Hlavny cyklus programu ****
void loop()
{
  int tl, t2, t3, t4, t5, t6;
  
  //***** RF24 **************************
  if (radio.available())
  {
    radio.read(data, sizeof(data));
    if (data[0] == kontrolne_cislo)
    {
      Serial.print("KC: ");
      Serial.print(int(data[0]));
      Serial.print(" U11: ");
      Serial.println(int(data[11]));
      Serial.print(" U12: ");
      Serial.println(int(data[12]));
      Serial.print(" U24: ");
      Serial.println(int(data[24]));

      uholserva[1] = data[1];
      uholserva[2] = data[2];
      uholserva[3] = data[3];
      uholserva[4] = data[4];
      uholserva[5] = data[5];
      uholserva[6] = data[6];
      uholserva[7] = data[7];
      uholserva[8] = data[8];
      uholserva[9] = data[9];
      uholserva[10] = data[10];
      uholserva[11] = data[11];
      uholserva[12] = data[12];
      uholserva[13] = data[13];
      uholserva[14] = data[14];
      NastavServa();
      delay(10);
    }
  }
  //***** Načítanie hodnôt tlačidiel t1-t6, 0...stlačené

  tl = digitalRead(40);
  t2 = digitalRead(39);
  t3 = digitalRead(38);
  t4 = digitalRead(37);
  t5 = digitalRead(36);
  t6 = digitalRead(35);
  //Serial.print("Stlacene tlacidla 1-6:");
  //Serial.print(tl);Serial.print(t2);Serial.print(t3);
  //Serial.print(t4);Serial.print(t5);Serial.println(t6);
  //***** Volanie funkcie tlacidlo1-6()
  if (tl == 0)
    tlacidlo1();
  if (t2 == 0)
    tlacidlo2();
  if (t3 == 0)
    tlacidlo3();
  if (t4 == 0)
    tlacidlo4();
  if (t5 == 0)
    tlacidlo5();
  if (t6 == 0)
    tlacidlo6();
  //***** Načítanie uhlov od kinektu zo sériového portu
  if (Serial.available() > 12)
  {
    char val = Serial.read();
    // Ak je startovaci znak 'S' cita hodnoty uhlov pre serva z Kinectu
    if (val == 'S')
    {
      for (i = 1; i < 12; i++)
      {
        uholserva[i] = Serial.read();
      }
    }
    //***** Transformovanie uhlov do ineho intervalu
    uholserva[1] = (int)map(uholserva[1], 50, 160, 0, 180);   //ruka prava H/D
    uholserva[2] = (int)map(uholserva[2], 50, 150, 180, 0);   //ruka lava H/D
    uholserva[3] = (int)map(uholserva[3], 80, 150, 170, 80);  //ruka prava od tela
    uholserva[4] = (int)map(uholserva[4], 80, 150, 0, 90);    //ruka lava od tela
    uholserva[5] = (int)map(uholserva[5], 0, 255, 0, 180);    //ruka prava vytocit
    uholserva[6] = (int)map(uholserva[6], 0, 255, 180, 0);    //ruka lava vytocit
    uholserva[7] = (int)map(uholserva[7], 0, 160, 5, 110);    //ruka prava laket ohyb
    uholserva[8] = (int)map(uholserva[8], 0, 160, 160, 50);   //ruka lava laket ohyb
    uholserva[9] = (int)map(uholserva[9], 50, 150, 110, 60);  //hlava hore dole
    uholserva[10] = (int)map(uholserva[10], 100, 255, 0, 90); //hlava vlavo vpravo
    //uholserva[11]=(int)map(uholserva[11],110,150,70,95); //trup vpravo vlavo nepoužité

    //***** Kontrola prekrocenia max a min hodnoty pre uhol serva
    for (i = 1; i <= 25; i++)
    {
      if (uholserva[i] > uholmax[i])
      {
        uholserva[i] = uholmax[i];
      }
      if (uholserva[i] < uholmin[i])
      {
        uholserva[i] = uholmin[i];
      }
    }
    NastavServa();
    delay(10);
  }
}

//***** Natocenie serv podla hodnôt uhlov ****
void NastavServa()
{
  servorob1.write(uholserva[1]);   //Prava ruka hore*
  servorob2.write(uholserva[2]);   //Lava ruka hore*
  servorob3.write(uholserva[3]);   //Prava ruka od tela*
  servorob4.write(uholserva[4]);   //Lava ruka od tela*
  servorob5.write(uholserva[5]);   //Prava ruka vytocit*
  servorob6.write(uholserva[6]);   //Lava ruka vytocit*
  servorob7.write(uholserva[7]);   //Prava ruka laket ohyb*
  servorob8.write(uholserva[8]);   //Lava ruka laket ohyb*
  servorob9.write(uholserva[9]);   //Hlava hore-dole*
  servorob10.write(uholserva[10]); //Hlava vpravo-vlavo*
  servorob11.write(uholserva[11]); //Zápästie pravé vytočiť*
  servorob12.write(uholserva[12]); //Zápästie ľavé vytočiť*
  servorob13.write(uholserva[13]); //Pravá dlaň*
  servorob14.write(uholserva[14]); //Ľavá dlaň*
  //servorob15.write(uholserva[15]); //Pravé chodidlo Ľ/P*
  //servorob16.write(uholserva[16]); //Ľavé chodidlo Ľ/P*
  //servorob17.write(uholserva[17]); //Pravé chodidlo H/D*
  //servorob18.write(uholserva[18]); //Ľavé chodidlo H/D*
  //servorob19.write(uholserva[19]); //Pravé koleno*
  //servorob20.write(uholserva[20]); //Ľavé koleno*
  //servorob21.write(uholserva[21]); //Pravá noha dopredu*
  //servorob22.write(uholserva[22]); //Ľavá noha dopredu*
  //servorob23.write(uholserva[23]); //Pravá noha nabok*
  //servorob24.write(uholserva[24]); //Ľavá noha nabok*
  //servorob25.write(uholserva[25]); //Nohy vytočiť*
}
//***** Funkcie s programom po stlačení tlačidiel 1-6
void tlacidlo1()
{
  pohyb(servorob2, 180, 40, 20);
  servorob8.write(120); //uholmin[8]=160,50;
  delay(1000);
  servorob12.write(40);
  uholmin[12] = 140, 0;
  delay(1000);
  servorob6.write(150); //uholmin[6]=180,90,0;
  servorob6.write(30);
  delay(1000);
  servorob6.write(150);
  delay(1000);
  servorob6.write(30);
  delay(1000);
  servorob6.write(150);
  delay(1000);
  servorob6.write(30);
  delay(1000);
  servorob6.write(150);
  delay(1000);
  servorob6.write(30);
  delay(1000);
  servorob6.write(120);
  delay(1000);
  servorob12.write(140);
  delay(1000);
  servorob8.write(60);
  delay(1000);
  pohyb(servorob2, 40, 180, 20);
}
void tlacidlo2() //**** stojí *********************
{
  uholserva[15] = 95;              // Pravé chodidlo Ľ/P
  uholserva[16] = 100;             // Ľavé chodidlo Ľ/P
  uholserva[17] = 70;              // Pravé chodidlo H/D
  uholserva[18] = 100;             // Ľavé chodidlo H/D
  uholserva[19] = 0;               // Pravé koleno 0-110 60
  uholserva[20] = 0;               // Ľavé koleno 0-110 50
  uholserva[21] = 55;              // Pravá noha H/D 30-55-180
  uholserva[22] = 35;              // Ľavá noha H/D 10-35-160
  uholserva[23] = 160;             // Pravá noha nabok
  uholserva[24] = 5;               // Ľavá noha nabok
  uholserva[25] = 90;              // Nohy vytočiť 70-90-110
  servorob15.write(uholserva[15]); //Pravé chodidlo Ľ/P*
  servorob16.write(uholserva[16]); //Ľavé chodidlo Ľ/P*
  servorob17.write(uholserva[17]); //Pravé chodidlo H/D*
  servorob18.write(uholserva[18]); //Ľavé chodidlo H/D*
  servorob19.write(uholserva[19]); //Pravé koleno*
  servorob20.write(uholserva[20]); //Ľavé koleno*
  servorob21.write(uholserva[21]); //Pravá noha dopredu*
  servorob22.write(uholserva[22]); //Ľavá noha dopredu*
  servorob23.write(uholserva[23]); //Pravá noha nabok*
  servorob24.write(uholserva[24]); //Ľavá noha nabok*
  servorob25.write(uholserva[25]); //Nohy vytočiť*
}
void tlacidlo3() //**** sedí ***********************
{
  uholserva[15] = 95;              // Pravé chodidlo Ľ/P
  uholserva[16] = 100;             // Ľavé chodidlo Ľ/P
  uholserva[17] = 60;              // Pravé chodidlo H/D
  uholserva[18] = 90;              // Ľavé chodidlo H/D
  uholserva[19] = 60;              // Pravé koleno 0-110 60
  uholserva[20] = 50;              // Ľavé koleno 0-110 50
  uholserva[21] = 175;             // Pravá noha H/D 30-55-180
  uholserva[22] = 155;             // Ľavá noha H/D 10-35-160
  uholserva[23] = 160;             // Pravá noha nabok
  uholserva[24] = 5;               // Ľavá noha nabok
  uholserva[25] = 110;             // Nohy vytočiť 70-90-110
  servorob15.write(uholserva[15]); //Pravé chodidlo Ľ/P*
  servorob16.write(uholserva[16]); //Ľavé chodidlo Ľ/P*
  servorob17.write(uholserva[17]); //Pravé chodidlo H/D*
  servorob18.write(uholserva[18]); //Ľavé chodidlo H/D*
  servorob19.write(uholserva[19]); //Pravé koleno*
  servorob20.write(uholserva[20]); //Ľavé koleno*
  servorob21.write(uholserva[21]); //Pravá noha dopredu*
  servorob22.write(uholserva[22]); //Ľavá noha dopredu*
  servorob23.write(uholserva[23]); //Pravá noha nabok*
  servorob24.write(uholserva[24]); //Ľavá noha nabok*
  servorob25.write(uholserva[25]); //Nohy vytočiť*
}
void tlacidlo4()
{
}
void tlacidlo5()
{
}
void tlacidlo6()
{
  radio.stopListening();
  uholserva[0] = 1;
  radio.write(uholserva, sizeof(uholserva));
  radio.startListening();
}

//***** Funkcia pre regulovaný pohyb serva *************

void pohyb(Servo s, int od, int po, int r)
{

  if (od < po)
  {
    x = po - od;
    for (i = 1; i <= x; i++)
    {
      s.write(od + i);
      delay(r);
    }
  }
  else
  {
    x = od - po;
    for (i = 1; i <= x; i++)
    {
      s.write(od - i);
      delay(r);
    }
  }
}

//***** Funkcia pre zvučku *****
void zvucka()
{
  for (i = 0; i < 8; i++)
  {
    int dlzka = 1000 / doba[i];
    tone(46, ton[i], dlzka);
    int cakanie = dlzka * 1.30;
    delay(cakanie);
    noTone(46);
  }
}
