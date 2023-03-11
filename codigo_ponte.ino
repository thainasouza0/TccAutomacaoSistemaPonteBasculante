#include <Servo.h> //Inclusão da biblioteca do servomotor

// Declaração das variáveis dos servos
Servo ponte1, ponte2, cancela1, cancela2; 
// Declaração de variáveis e definição das portas do arduino
int verde1=22, verde2=23, amarelo1=26, amarelo2=27, vermelho1=30, vermelho2=31, infra1=41, infra2=38, buzzer=52;
// Declaração de variáveis e atribuição de valor
int pos=0, pos2=100, Dir=0;

void sobecan(){ // Função que faz subir as cancelas
  for(pos2=5; pos2<=100; pos2++){ // pos2 inicia no ângulo 5 devido a posição física do servo
    cancela1.write(pos2);
    cancela2.write(pos2+3); // pos2 +3 para ajuste mecânico do tabuleiro
    delay(25); // Tempo de subida das cancelas de 25 milisegundos
  }
}

void descecan(){ // Função que faz descer as cancelas
  for(pos2=100; pos2>=5; pos2--){
    cancela1.write(pos2);
    cancela2.write(pos2+3);
    delay(25);
  }
}

void sobeponte(){ // Função que faz subir os tabuleiros da ponte
  for(pos=0; pos<=60; pos++){
    ponte1.write(pos);
    ponte2.write(pos);
    delay(75);
  }
}

void desceponte(){ // Função que faz descer os tabuleiros da ponte
  for(pos=60; pos>=0; pos--){
    ponte1.write(pos);
    ponte2.write(pos);
    delay(75);
  }
}

void setup() {
  // Inicializando os componentes e definindo se serão do tipo saída (output) ou entrada (input)
  pinMode(verde1,   OUTPUT);
  pinMode(verde2,   OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(amarelo2, OUTPUT);
  pinMode(vermelho1,OUTPUT);
  pinMode(vermelho2,OUTPUT);
  pinMode(buzzer,  OUTPUT);
  pinMode(infra1,   INPUT);
  pinMode(infra2,   INPUT);
  // Definindo e inicializando as portas do arduino em que os servos estão conectados
  ponte1.attach(12);
  cancela1.attach(10);
  cancela2.attach(8);
  ponte2.attach(6);

}

void loop() {
  if(Dir==0){ // Rotina principal
    if(digitalRead(infra1)==1 && digitalRead(infra2)==1){ // Verifica se os sensores estão desacionados
      digitalWrite(verde1, 1); // Acende led verde
      digitalWrite(verde2, 1);
      ponte1.write(0); // Tabuleiros baixados
      ponte2.write(0);
      cancela1.write(100); // Cancelas levantadas
      cancela2.write(100);
    }
    else{
      if(digitalRead(infra1)==0){ // Se sensor 1 acionado executa rotina abaixo
        Dir=2; // Atribui valor 2 a variável Dir
        digitalWrite(verde1, 0); // Apaga led verde
        digitalWrite(verde2, 0);
        digitalWrite(amarelo1, 1); // Acende led amarelo
        digitalWrite(amarelo2, 1);
        delay(1500); // Led amarelo permanece aceso por 1.5 segundos
        digitalWrite(amarelo1, 0); // Apaga led amarelo
        digitalWrite(amarelo2, 0);
        digitalWrite(vermelho1, 1); // Acende led vermelho
        digitalWrite(vermelho2, 1);
        descecan(); // Executa a função para descer as cancelas
        digitalWrite(buzzer, 1); // Liga o buzzer
        delay(1000); // Buzzer permanece ligado por 1 segundo
        digitalWrite(buzzer, 0); // Desliga o buzzer
        sobeponte(); // Executa a função para subir a ponte
      }
      else{ // Senão executa rotina abaixo
        Dir=1;
        digitalWrite(verde1, 0);
        digitalWrite(verde2, 0);
        digitalWrite(amarelo1, 1);
        digitalWrite(amarelo2, 1);
        delay(1500);
        digitalWrite(amarelo1, 0);
        digitalWrite(amarelo2, 0);
        digitalWrite(vermelho1, 1);
        digitalWrite(vermelho2, 1);
        descecan();
        digitalWrite(buzzer, 1);
        delay(1000);
        digitalWrite(buzzer, 0);
        sobeponte();
      }
    }
  }
  if((Dir==2) || (Dir==1)){ // Verifica qual rotina está em execução
    if(digitalRead(infra1)==1 && digitalRead(infra2)==1){ // Verifica se os dois sensores estão desacionados
      Dir=0;
      desceponte();
      sobecan();
      digitalWrite(vermelho1, 0);
      digitalWrite(vermelho2, 0);
    }
  }
}
