#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de rede WiFi
const char* ssid = "MATHEUS ";
const char* password = "12213490";

// Configurações MQTT
const char* mqtt_username = "admin";
const char* mqtt_password = "1221";
const char* mqtt_broker_address = "35.208.123.29";
const char* topic = "esp32/pessoa_det";
const byte ZCP = 13;
const byte TRIAC_PIN = 12;
unsigned int dimDuration = 5000;

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

// Função para conectar ao Wi-Fi
void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("\n\n=====================");
  Serial.println("Conectando no Wi-Fi");
  Serial.println("=====================\n\n");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n\n=====================");
  Serial.println("Conectado ao Wi-Fi!");
  Serial.println("=====================\n\n");
}

// Função de retorno de chamada para mensagens MQTT recebidas
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Pessoa detectada! ");

  int value = payload[0] - '0';

  if (value == 1) {
    lastMsg = millis();
    digitalWrite(TRIAC_PIN, HIGH);
    Serial.println("Lâmpada ligada!\n");
    
    // Atualiza o valor de dimDuration
    dimDuration = 1000;
    Serial.printf("Intensidade luminosa alterada de 50%% para 100%%");
  }
}

// Função para reconectar ao servidor MQTT
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("\n\n=====================");
    Serial.println("Conectando no MQTT BROKER");
    Serial.println("=====================\n\n");

    if (client.connect("Atenuador1", mqtt_username, mqtt_password)) {
      Serial.println("\n\n=====================");
      Serial.println("Conectado ao MQTT!");
      Serial.println("=====================\n\n");      
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

  pinMode(TRIAC_PIN, OUTPUT);
  digitalWrite(TRIAC_PIN, LOW);

  connectWiFi();

  client.setServer(mqtt_broker_address, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  if (millis() - lastMsg > 5000) {
    digitalWrite(TRIAC_PIN, LOW);
  }
}
