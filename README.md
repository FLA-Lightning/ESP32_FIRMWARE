# Módulos Atenuadores ESP32

## Configuração

Antes de usar, ajuste as configurações de WiFi e MQTT no início do arquivo `seu_codigo.ino`:

```cpp
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA_WIFI";
const char* mqtt_username = "SEU_USUARIO_MQTT";
const char* mqtt_password = "SUA_SENHA_MQTT";
const char* mqtt_broker_address = "ENDERECO_DO_BROKER_MQTT";
const char* topic = "esp32/atenuador";
const int ledPin = 2; // GPIO do LED
