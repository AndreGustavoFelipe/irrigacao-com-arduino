#include <Adafruit_LiquidCrystal.h>

int verifica = 0;
int Recebe = A1;
int ledIndicadorA = 8;
int ledIndicadorB = 9;
int ledIndicadorC = 10;
int ledIndicadorD = 11;
int ledIndicadorE = 12;
int ledIndicadorF = 13;
int velocidade = 255;
int bomba = A2;
int pulso = A0;
int seconds = 0;
int sensorPin = A1; 

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.setBacklight(1);
  
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(pulso, OUTPUT);
  pinMode(Recebe,INPUT);
  pinMode(6,INPUT_PULLUP);
  pinMode(ledIndicadorA,OUTPUT);
  pinMode(ledIndicadorB,OUTPUT);
  pinMode(ledIndicadorC,OUTPUT);
  pinMode(ledIndicadorD,OUTPUT);
  pinMode(ledIndicadorE,OUTPUT);
  pinMode(ledIndicadorF,OUTPUT);
}

void loop()
{
  int botaoManual = digitalRead(6);
  teste();
  
  int valor_mapeado = map(verifica, 0, 1023, 0, 118);
  
  lcd_1.setCursor(0,0);
  lcd_1.print("Umidade do solo:");
  lcd_1.setCursor(0,1);
  lcd_1.print(valor_mapeado);  
  lcd_1.print("%");
  lcd_1.setCursor(0, 1);

  if(verifica == 0){
    digitalWrite(ledIndicadorA, LOW);
    digitalWrite(ledIndicadorB, LOW);
    digitalWrite(ledIndicadorC, LOW);
    digitalWrite(ledIndicadorD, LOW);
    digitalWrite(ledIndicadorE, LOW);
    digitalWrite(ledIndicadorF, LOW);
    analogWrite(bomba,255);
    piscarTela();
    avisoPiezo();
  }
  else if((verifica>0)&&(verifica<145)){
    digitalWrite(ledIndicadorA,HIGH);
    digitalWrite(ledIndicadorB,LOW);
    digitalWrite(ledIndicadorC,LOW);
    digitalWrite(ledIndicadorD,LOW);
    digitalWrite(ledIndicadorE,LOW);
    digitalWrite(ledIndicadorF,LOW);
    analogWrite(bomba,255);
    piscarTela();
    avisoPiezo();  
  }
  else if((verifica>146)&&(verifica<291)){
    digitalWrite(ledIndicadorB,HIGH);
    digitalWrite(ledIndicadorC,LOW);
    digitalWrite(ledIndicadorD,LOW);
    digitalWrite(ledIndicadorE,LOW);
    digitalWrite(ledIndicadorF,LOW);
    if(botaoManual == 1){ //Sem isso a lâmpada esquerda ficava piscando
      analogWrite(bomba,0);
    }
    lcd_1.setBacklight(1);
    noTone(7);

  }
  else if((verifica>292)&&(verifica<438)){
    digitalWrite(ledIndicadorC,HIGH);
    digitalWrite(ledIndicadorD,LOW);
    digitalWrite(ledIndicadorE,LOW);
    digitalWrite(ledIndicadorF,LOW);
    if(botaoManual == 1){
      analogWrite(bomba,0);
    }
    lcd_1.setBacklight(1);
    noTone(7);

  }
  else if((verifica>439)&&(verifica<580)){
    digitalWrite(ledIndicadorD,HIGH);
    digitalWrite(ledIndicadorE,LOW);
    digitalWrite(ledIndicadorF,LOW);
    if(botaoManual == 1){
      analogWrite(bomba,0);
    }
    lcd_1.setBacklight(1);
    noTone(7);
  }
  else if((verifica>581)&&(verifica<727)){
    digitalWrite(ledIndicadorE,HIGH);
    digitalWrite(ledIndicadorF,LOW);
    if(botaoManual == 1){
      analogWrite(bomba,0);
    }
    lcd_1.setBacklight(1);
    noTone(7);
  }
  else if((verifica>728)&&(verifica<900)){
    digitalWrite(ledIndicadorF,HIGH);
    if(botaoManual == 1){
      analogWrite(bomba,0);
    }
    lcd_1.setBacklight(1);
    noTone(7);
  }
 
  if(botaoManual != 1){
    analogWrite(bomba,255);
  }
  
  delay(100);
}

void avisoPiezo(){
  tone(7,4000);
  delay(100);
}

void piscarTela(){
  lcd_1.setBacklight(1);
  delay(200); 
  lcd_1.setBacklight(0);
  delay(200);  
}

void teste(){
  digitalWrite(pulso,HIGH);
  delay(10);
  verifica = analogRead(Recebe);
  digitalWrite(pulso,LOW);
}
