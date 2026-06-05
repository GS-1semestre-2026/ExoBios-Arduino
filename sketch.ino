#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Keypad.h>

#define DHTPIN 2
#define DHTTYPE DHT22

// LEDs :)
const int ledAzul = 8;       // Resfriamento
const int ledVerde = 9;      // Irrigação
const int ledVermelho = 10;  // Aquecimento
const int ledLuz = 11;       // Iluminação

// Sensores :)
const int ldrPin = A1;

// Buzzer :)
const int buzzer = A2;

// LCD :)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT :)
DHT dht(DHTPIN, DHTTYPE);

// :) * :) * :) * :) * :) * 
// KEYPAD :)
// :) * :) * :) * :) * :) * 

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {3,4,5,6};
byte colPins[COLS] = {7,12,13,A0};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// :) * :) * :) * :) * :) * 
// PLANTAS :)
// :) * :) * :) * :) * :) * 

String plantas[] = {
  "ALFACE",
  "TOMATE",
  "CENOURA",
  "ERVILHA",
  "BATATA DOCE",
  "GRAO BICO",
  "ORA PRO NOBIS"
};

int indicePlanta = 0;
bool plantaConfirmada = false;

String plantaAtual = "ALFACE";

float tempMin;
float tempMax;

float umidMin;
float umidMax;

int luzMin;
int luzMax;

// :) * :) * :) * :) * :) * 
// CONFIGURAR PLANTA :)
// :) * :) * :) * :) * :) * 

void configurarPlanta(int indice){

  switch(indice){

    case 0:
      plantaAtual = "ALFACE";
      tempMin = 18;
      tempMax = 24;
      umidMin = 60;
      umidMax = 80;
      luzMin = 400;
      luzMax = 800;
      break;

    case 1:
      plantaAtual = "TOMATE";
      tempMin = 20;
      tempMax = 30;
      umidMin = 60;
      umidMax = 75;
      luzMin = 600;
      luzMax = 1000;
      break;

    case 2:
      plantaAtual = "CENOURA";
      tempMin = 16;
      tempMax = 24;
      umidMin = 55;
      umidMax = 70;
      luzMin = 500;
      luzMax = 900;
      break;

    case 3:
      plantaAtual = "ERVILHA";
      tempMin = 13;
      tempMax = 22;
      umidMin = 60;
      umidMax = 80;
      luzMin = 400;
      luzMax = 850;
      break;

    case 4:
      plantaAtual = "BATATA DOCE";
      tempMin = 21;
      tempMax = 30;
      umidMin = 50;
      umidMax = 70;
      luzMin = 600;
      luzMax = 1000;
      break;

    case 5:
      plantaAtual = "GRAO BICO";
      tempMin = 18;
      tempMax = 30;
      umidMin = 40;
      umidMax = 60;
      luzMin = 650;
      luzMax = 1000;
      break;

    case 6:
      plantaAtual = "ORA PRO NOBIS";
      tempMin = 20;
      tempMax = 35;
      umidMin = 30;
      umidMax = 60;
      luzMin = 700;
      luzMax = 1023;
      break;
  }
}

// :) * :) * :) * :) * :) * 
// MENU :)
// :) * :) * :) * :) * :) * 

void mostrarMenu(){

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(">");
  lcd.print(plantas[indicePlanta]);

  lcd.setCursor(0,1);
  lcd.print("A+ B- #OK");
}

// :) * :) * :) * :) * :) * 
// SETUP :)
// :) * :) * :) * :) * :) * 

void setup(){

  Serial.begin(9600);

  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledLuz, OUTPUT);

  pinMode(buzzer, OUTPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("EXOBIOS");

  lcd.setCursor(0,1);
  lcd.print("INICIANDO");

  delay(2000);

  mostrarMenu();
}

// :) * :) * :) * :) * :) * 
// LOOP :)
// :) * :) * :) * :) * :) * 

void loop(){

  char tecla = keypad.getKey();

  // Voltar ao menu :)

  if(tecla == 'D'){

    plantaConfirmada = false;
    indicePlanta = 0;

    mostrarMenu();

    return;
  }

  // Menu de seleção :)

  if(!plantaConfirmada){

    if(tecla == 'A'){

      indicePlanta++;

      if(indicePlanta > 6){
        indicePlanta = 0;
      }

      mostrarMenu();
    }

    if(tecla == 'B'){

      indicePlanta--;

      if(indicePlanta < 0){
        indicePlanta = 6;
      }

      mostrarMenu();
    }

    if(tecla == '#'){

      configurarPlanta(indicePlanta);

      plantaConfirmada = true;

      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print(plantaAtual);

      lcd.setCursor(0,1);
      lcd.print("SELECIONADA");

      delay(2000);
    }

    return;
  }

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  int luminosidade = analogRead(ldrPin);

  if(isnan(temperatura) || isnan(umidade)){
    return;
  }

  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledLuz, LOW);

  noTone(buzzer);

  String status = "";

  bool alerta = false;

  // :) * :) * :) * :) * :) * 
  // TEMPERATURA :)
  // :) * :) * :) * :) * :) * 

  if(temperatura < tempMin){

    digitalWrite(ledVermelho, HIGH);

    status += "AQ ";

    alerta = true;
  }

  else if(temperatura > tempMax){

    digitalWrite(ledAzul, HIGH);

    status += "RF ";

    alerta = true;
  }

// :) * :) * :) * :) * :) * 
// UMIDADE :)
// :) * :) * :) * :) * :) * 

if(umidade < umidMin){

    digitalWrite(ledVerde, HIGH);

    status += "UM- ";

    alerta = true;
}

else if(umidade > umidMax){

    digitalWrite(ledVerde, HIGH);

    status += "UM+ ";

    alerta = true;
}

// :) * :) * :) * :) * :) * 
// LUZ :)
// :) * :) * :) * :) * :) * 

if(luminosidade < luzMin){

    digitalWrite(ledLuz, HIGH);

    status += "LUZ+ ";

    alerta = true;
}

else if(luminosidade > luzMax){

    digitalWrite(ledLuz, HIGH);

    status += "LUZ- ";

    alerta = true;
}

  // :) * :) * :) * :) * :) * 
  // BUZZER :)
  // :) * :) * :) * :) * :) * 

  if(alerta){

    tone(buzzer, 1200);

  }else{

    noTone(buzzer);
  }

  if(status == ""){

    status = "AMBIENTE OK";
  }

  // :) * :) * :) * :) * :) * 
  // LCD :)
  // :) * :) * :) * :) * :) * 

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(plantaAtual);

  lcd.setCursor(0,1);
  lcd.print(status);

  // :) * :) * :) * :) * :) * 
  // SERIAL :)
  // :) * :) * :) * :) * :) * 

  Serial.print("Planta: ");
  Serial.print(plantaAtual);

  Serial.print(" | Temp: ");
  Serial.print(temperatura);

  Serial.print(" | Umidade: ");
  Serial.print(umidade);

  Serial.print(" | Luz: ");
  Serial.print(luminosidade);

  Serial.print(" | Status: ");
  Serial.println(status);

  delay(1000);
}
