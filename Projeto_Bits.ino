#include <Keypad.h> //INCLUSÃO DE BIBLIOTECA
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 3; //QUANTIDADE DE COLUNAS DO TECLADO
 
//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_keys[qtdLinhas][qtdColunas] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte PinosqtdLinhas[qtdLinhas] = {4, 5, 6, 7}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {8, 9, 10}; //PINOS UTILIZADOS PELAS COLUNAS
 
//INICIALIZAÇÃO DO TECLADO
Keypad teclado = Keypad( makeKeymap(matriz_keys), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas); 

// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,20, 4);

//Variavel que irá guardar o valor da matricula
char matricula[15];
int i = 0;
 
void setup(){
  lcd.init();
  lcd.backlight();
  lcd.print("Matricula: ");
  lcd.setCursor(0, 1);
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial.println("Aperte uma tecla..."); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.println(); //QUEBRA UMA LINHA NO MONITOR SERIAL
}
  
void loop(){
  char tecla = teclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA

  if((i > 0) && tecla == '*'){
    i--;
  }
  
  if (tecla && i < 15){
    
    if(tecla == '*'){
      
      matricula[i] = ' ';
      lcd.setCursor(i, 1);
      lcd.print(" ");
      lcd.setCursor(i, 1); 
    }else if(tecla == '#'){
      //Script para enviar pro banco de dados ou pro serial
      Serial.println(matricula);
    }else{
      matricula[i] = tecla;
      lcd.print(tecla);
      i++;
    }
    
  }
}
