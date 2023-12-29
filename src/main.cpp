#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "MATHEUS ";
const char* password = "12213490";
const char* mqtt_username = "admin";
const char* mqtt_password = "1221";
const char* mqtt_broker_address = "ec2-13-58-196-72.us-east-2.compute.amazonaws.com";
const char* topic = "esp32/atenuador";
const int ledPin = 2; // GPIO onde o LED está conectado

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
bool ledState = false;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  int value = payload[0] - '0'; // Converte o payload para um número inteiro

  if (value == 1) {
    ledState = true;
    lastMsg = millis();
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ligado");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao servidor MQTT...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("Conectado!");
      client.subscribe(topic);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  setup_wifi();
  client.setServer(mqtt_broker_address, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (ledState && millis() - lastMsg > 5000) {
    ledState = false;
    digitalWrite(ledPin, LOW);
    Serial.println("LED desligado após 5 segundos sem receber 1");
  }
}
