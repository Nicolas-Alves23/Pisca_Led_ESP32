// //UC_IOT_AULA2_Prática2 - Ligar Led com pulso no pino D15
// //Recursos KIT ESP32 / Resistor / Led
// //PROGRAMA 2 : PISCA PISCA
// const int PINO_LED = 15; // PINO D15
// void setup() {
//   pinMode(PINO_LED, OUTPUT); // Define o PINO do LED como saída
// }
// void loop() {
//   digitalWrite(PINO_LED, HIGH); // Liga o LED
//   delay(1000); // Espera 1 segundo. * Alterar o valor dessa variavel muda o tempo de duração em MILISEGUNDOS que o led permanece LIGADO.
//   digitalWrite(PINO_LED, LOW); // Desliga o LED
//   delay(1000); // Espera 1 segundo. * Alterar o valor dessa variavel muda o tempo de duração em MILISEGUNDOS que o led permanece DESLIGADO.
// }
// //const int -> declara uma variavel apenas uma vez e a partir daquele momento ela se torna fixa.
// //int -> por sua vez quando utilizar somente o "int" é declarada uma variavel inteira que a qualquer momento do código pode ser alterada.



// // Define o número do pino do LED
// const int ledPin = 15;  // O número 15 corresponde ao GPIO 15 do ESP32
 
// void setup() {
//   // Configura o pino do LED como saída
//   pinMode(ledPin, OUTPUT);  // Define o pino como saída para controle do LED
// }
 
// void loop(){
//   // Aumentar a intensidade do brilho do LED
//   for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
//     // A função analogWrite controla a intensidade do LED com PWM (modulação por largura de pulso)
//     // A variável dutyCycle vai de 0 a 255, que representa os níveis de intensidade
//     analogWrite(ledPin, dutyCycle);  // Aplica o valor do ciclo de trabalho ao pino do LED
//     delay(15);  // Pausa de 15 milissegundos entre os ajustes de brilho
//   }
 
//   // Diminuir a intensidade do brilho do LED
//   for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
//     // A função analogWrite controla a intensidade do LED com PWM
//     analogWrite(ledPin, dutyCycle);  // Aplica o valor do ciclo de trabalho ao pino do LED
//     delay(15);  // Pausa de 15 milissegundos entre os ajustes de brilho
//   }
// }


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SEU_WIFI";
const char* password = "SENHA_WIFI";
const char* scriptURL = "https://script.google.com/macros/s/SEU_SCRIPT_ID/exec";

const int botaoPin = D5; // pino do botão

void setup() {
  Serial.begin(115200);
  pinMode(botaoPin, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");
}

void loop() {
  if (digitalRead(botaoPin) == LOW) {
    enviarDados("Botao Pressionado");
    delay(500); // debounce simples
  }
}

void enviarDados(String mensagem) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(scriptURL) + "?botao=" + mensagem;
    http.begin(url);
    int httpCode = http.GET();
    http.end();
    Serial.println("Enviado: " + mensagem);
  }
}
