// Definição dos pinos
const int trigPin = 9;
const int echoPin = 8;
const int buzzerPin = 10;
const int ledAmareloPin = 12;
const int ledVermelhoPin = 11;
const int pirSensorPin = 7;  // Pino do sensor de presença

// Variáveis
long duration;
int distance;

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
  distance = duration * 0.034 / 2;

  // Exibe a distância no Monitor Serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Aciona o buzzer se a distância for menor que 20 cm
  if (distance < 20) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Leitura do sensor de presença
  int movimentoDetectado = digitalRead(pirSensorPin);

  // Se movimento for detectado e a mão estiver a menos de 10 cm, aciona o LED vermelho
  if (movimentoDetectado == HIGH && distance < 10) {
    digitalWrite(ledVermelhoPin, HIGH);
    digitalWrite(ledAmareloPin, LOW);
  } 
  // Se movimento for detectado mas a mão estiver a mais de 10 cm, aciona o LED amarelo
  else if (movimentoDetectado == HIGH && distance >= 10) {
    digitalWrite(ledAmareloPin, HIGH);
    digitalWrite(ledVermelhoPin, LOW);
  } 
  // Se não houver movimento, mantém o LED amarelo aceso
  else {
    digitalWrite(ledAmareloPin, HIGH);
    digitalWrite(ledVermelhoPin, LOW);
  }

  delay(100);  // Pequeno atraso para estabilizar as leituras
}