// Definição dos pinos
const int trigPin = 9;           // Pino do trigger do sensor ultrassônico
const int echoPin = 8;           // Pino do echo do sensor ultrassônico
const int buzzerPin = 10;        // Pino do buzzer
const int ledAmareloPin = 12;    // Pino do LED amarelo
const int ledVermelhoPin = 11;   // Pino do LED vermelho
const int pirSensorPin = 7;      // Pino do sensor PIR
const int ldrPin = A0;           // Pino do LDR

// Variáveis
long duration;                   // Duração do pulso do sensor ultrassônico
int distance;                    // Distância calculada pelo sensor ultrassônico
int ldrValue = 0;                // Valor lido do LDR
int limiarEscuro = 100;          // Limiar para considerar "escuro" (ajustável)
int pirState = LOW;              // Estado do sensor PIR (LOW = sem movimento, HIGH = movimento)

void setup() {
  // Configuração dos pinos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledAmareloPin, OUTPUT);
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(pirSensorPin, INPUT);
  
  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);
}

void loop() {
  // Leitura do sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Calcula a distância em cm

  // Exibe a distância no Monitor Serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Leitura do valor do LDR
  ldrValue = analogRead(ldrPin);

  // Exibe o valor do LDR no Monitor Serial
  Serial.print("Valor LDR: ");
  Serial.println(ldrValue);

  // Leitura do estado do sensor PIR
  pirState = digitalRead(pirSensorPin);

  // Exibe o estado do PIR no Monitor Serial (ativo ou não)
  Serial.print("Estado PIR: ");
  if (pirState == HIGH) {
    Serial.println("Movimento detectado");
  } else {
    Serial.println("Sem movimento");
  }

  // Controle do buzzer baseado no LDR
  // Se o valor do LDR for menor que o limiar, significa que está escuro
  if (ldrValue < limiarEscuro) {
    // Aciona o buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Desliga o buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Controle dos LEDs baseado no sensor ultrassônico
  // Se a distância for menor que 10 cm, aciona o LED vermelho
  if (distance < 10) {
    digitalWrite(ledVermelhoPin, HIGH);
    digitalWrite(ledAmareloPin, LOW);
  } 
  // Se a distância for maior ou igual a 10 cm, aciona o LED amarelo
  else {
    digitalWrite(ledAmareloPin, HIGH);
    digitalWrite(ledVermelhoPin, LOW);
  }

  delay(100);  // Pequeno atraso para evitar muitas leituras
}