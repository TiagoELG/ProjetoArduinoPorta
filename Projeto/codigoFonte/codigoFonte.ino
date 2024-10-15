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
int movimentoDetectado;

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

  // Leitura do sensor de presença
  movimentoDetectado = digitalRead(pirSensorPin);

  // Exibe a distância e o status do sensor de presença no Monitor Serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.print(" cm | Sensor de Presenca: ");
  if (movimentoDetectado == HIGH) {
    Serial.println("Detectado");
  } else {
    Serial.println("Nao Detectado");
  }

  // Aciona o buzzer SOMENTE se o sensor de presença detectar movimento
  if (movimentoDetectado == HIGH) {
    digitalWrite(buzzerPin, HIGH);  // Buzzer liga quando presença é detectada
  } else {
    digitalWrite(buzzerPin, LOW);   // Buzzer desliga quando não há presença
  }

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