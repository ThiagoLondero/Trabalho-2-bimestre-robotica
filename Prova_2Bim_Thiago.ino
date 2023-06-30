#include <LiquidCrystal.h>

const int echoPin = 26;  // PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO (RECEBE)
const int trigPin = 30;  // PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG (ENVIA)
const int pinoBuzzer = 40;  // PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // Inicializa o objeto LCD

int distancia;  // Cria uma variável chamada "distancia" do tipo inteiro

void setup() {
  pinMode(echoPin, INPUT);  // Define o pino como entrada (recebe)
  pinMode(trigPin, OUTPUT);  // Define o pino como saída (envia)
  pinMode(pinoBuzzer, OUTPUT);  // Declara o pino como sendo saída

  Serial.begin(9600);

  lcd.begin(16, 2);  // Seta a quantidade de colunas (16) e o número de linhas (2) do display LCD
  lcd.setCursor(0, 0);  // Seta a posição em que o cursor inicializa (linha 1)
}

void loop() {
  distancia = medirDistancia();  // Chama a função para medir a distância

  if (distancia <= 30) {  // Se a distância entre o objeto e o sensor ultrassônico for menor que 30cm
    tone(pinoBuzzer, 100);  // Aciona o buzzer
  } else {
    noTone(pinoBuzzer);  // Buzzer permanece desligado
  }

  // Limpa o LCD
  lcd.clear();

  // Exibe a distância no LCD
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
  lcd.setCursor(0, 1);
  lcd.print(distancia);

  delay(100);
}

// Função para medir a distância
int medirDistancia() {
  digitalWrite(trigPin, LOW);  // Seta o pino trigPin com um pulso baixo (LOW)
  delayMicroseconds(2);  // Delay de 2 microssegundos
  digitalWrite(trigPin, HIGH);  // Seta o pino trigPin com pulso alto (HIGH)
  delayMicroseconds(10);  // Delay de 10 microssegundos
  digitalWrite(trigPin, LOW);  // Seta o pino trigPin com pulso baixo (LOW) novamente

  // A função pulseIn() mede a duração do pulso recebido pelo pino echoPin em microssegundos
  // O valor retornado é proporcional à distância medida
  long duracaoPulso = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros usando a velocidade do som no ar (aproximadamente 343 metros por segundo)
  int distanciaEmCm = duracaoPulso * 0.0343 / 2;

  return distanciaEmCm;
}
