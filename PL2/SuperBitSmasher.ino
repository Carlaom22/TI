int pinAND = 4, pinOR = 3, pinXOR = 2; //Botões XOR,OR e AND
int led1 = 8, led2 = 9, led3 = 10, led4 = 11; //4 leds

unsigned long tempoJogo = 10000; //Duração do jogo, em milisegundos
String a = ""; //variável para armazenar a string da porta série
int intValue = -1; //variável para armazenar a string convertida 

void setup() {
  Serial.begin(9600); //inicializar a porta série
  pinMode(pinAND, INPUT_PULLUP); 
  pinMode(pinOR, INPUT_PULLUP);
  pinMode(pinXOR, INPUT_PULLUP);

  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  int enDig = random(0, 4); //gerar um numero random de 0 a 3(inclusive)
  int enAND = bitRead(enDig, 1); //extrair o bit 1 do número random, para ativar o botão AND
  int enXOR = bitRead(enDig, 0); //extrair o bit 0 do número random, para ativar o botão XOR

  Serial.print("Opções disponiveis: "); //mostrar as operações disponiveis no serial monitor
  if (enAND == 1) Serial.print("AND, "); // 
  if (enXOR == 1) Serial.print("XOR, "); // 
  Serial.println("OR"); //

  int inicio = random(0, 225); //gerar um número aleatório para começar
  Serial.print("Ponto inicial: ");  Serial.println(inicio, BIN); //mostrar esse número no serial monitor e em binário

  int objetivo = random(inicio, 256); //gerar um número random para atingir
  Serial.print("Objetivo: "); Serial.println(objetivo, BIN); //mostrar esse número no serial monitor e em binário

  Serial.println("Insira um número decimal:"); //inserir um número em decimal
  unsigned long tempodeinicio = millis(); //registar o tempo de início

  //Loop do jogo//
  while ((millis() - tempodeinicio <= tempoJogo) && (objetivo != intValue)) { //the loop runs until runtime< game time
    mostrartempo(tempoJogo - (millis() - tempodeinicio) ); //call the function for displaying game time on LEDs

    
    if (Serial.available() > 0) {
      a = Serial.readStringUntil('\n'); //ler o input 
      intValue = a.toInt(); //converter a string input para int
      Serial.print("Valor inserido: "); Serial.println(intValue, BIN); //mostrar esse número no serial monitor em binário
    }

    if (digitalRead(pinOR) == 0) { //lêr o botão OR
      inicio =  intValue | inicio; 
      Serial.print("Valor de momento:");
      Serial.println(inicio, BIN); 
      delay(200); //delay do debounce
    }
    else if ((digitalRead(pinAND) == 0) && (enAND == 1)) { //lêr o botão AND
      inicio =  intValue & inicio; //
      Serial.print("Valor de momento:");
      Serial.println(inicio, BIN); //
      delay(200); 
    }
    else if ((digitalRead(pinXOR) == 0) && (enXOR == 1)) { //Lêr o botão XOR
      inicio =  intValue ^ inicio; //Realizar a operação XOR bit a bit entre o valor atual e o valor inserido
      Serial.println(inicio, BIN); //mostrar o novo valor no serial monitor
      delay(200); 
    }
  }

  
  if (objetivo == inicio) { //se atingiu o valor dado como objetivo
    Serial.println("Objetivo atingido!!"); 
  }
  else { //se não atingiu o valor dado como objetivo
    Serial.println("Acabou o tempo, o jogo irá recomeçar!!"); //display the timeout message
  }
  delay(500);
  Serial.println(); 
}


void mostrartempo(unsigned long tempofalta) {
  int quarterTime = tempoJogo / 4; //calcular um quarto do tempo de jogo
  int ledStates[4]; //4 leds num array

  if (tempofalta > (quarterTime * 3)) { //maior que 0.75, ligar 4 leds
    ledStates[0] = 1; ledStates[1] = 1; ledStates[2] = 1; ledStates[3] = 1;
  }
  else if (tempofalta > (quarterTime * 2)) { //maior que 0.5, ligar 3 leds
    ledStates[0] = 1; ledStates[1] = 1; ledStates[2] = 1; ledStates[3] = 0;
  }
  else if (tempofalta > quarterTime) { //maior que 0.25, ligar 2 leds
    ledStates[0] = 1; ledStates[1] = 1; ledStates[2] = 0; ledStates[3] = 0;
  }
  else if (tempofalta > 0) { //menor que 0.25, ligar 1 led
    ledStates[0] = 1; ledStates[1] = 0; ledStates[2] = 0; ledStates[3] = 0;
  }
  else { //se acabou o tempo, desligar os leds todos
    ledStates[0] = 0; ledStates[1] = 0; ledStates[2] = 0; ledStates[3] = 0;
  }

  for (int pin = 8; pin <= 11; pin++) {
    digitalWrite(pin, ledStates[pin - 8]); //
  }
}
