# Módulo Atenuador ESP32

Este código representa o firmware para os módulos atenuadores. A principal função desses módulos é receber mensagens via MQTT e ajustar a intensidade luminosa de uma lâmpada de acordo com os parâmetros fornecidos. É importante notar que, por enquanto, a implementação do dimmer não está completa, razão pela qual o LED interno da ESP32 foi utilizado como exemplo para demonstrar o funcionamento.

## Como o código funciona?

1. Conexão à Rede Wi-Fi

Ao iniciar, o módulo atenuador tentará se conectar à rede Wi-Fi configurada. Ele usa as credenciais (SSID e senha) fornecidas no código para estabelecer uma conexão Wi-Fi. O progresso dessa conexão é exibido no Monitor Serial. 

2. Conexão ao Broker MQTT

Após se conectar à rede Wi-Fi, o módulo atenuador tentará se conectar ao broker MQTT. O endereço do broker MQTT, o nome de usuário e a senha são configurados no início do código. O módulo utiliza a biblioteca PubSubClient para lidar com a comunicação MQTT.

Se a conexão for estabelecida com sucesso, o módulo se inscreverá no tópico "esp32/atenuador". Isso significa que ele estará aguardando mensagens nesse tópico para ajustar a intensidade luminosa.

3. Controle de Intensidade Luminosa

Quando uma mensagem é publicada no tópico "esp32/atenuador", o módulo a recebe no método de callback 'callback'.

Dentro do callback, o valor da mensagem é extraído do payload e interpretado. Atualmente, o valor '1' aciona o LED interno da ESP32 (ou futuro dimmer) para ligar, enquanto outros valores ou a ausência de mensagens podem desligar o LED após 5 segundos.

Observação Importante: O LED interno é utilizado para simular o controle de luminosidade até que o dimmer real seja implementado. A substituição do LED pelo hardware real do dimmer será necessária quando disponível.
## Configurações

'''cpp
const char* ssid = "SuaRedeWiFi";const char* password = "SuaSenhaWiFi";
const char* mqtt_username = "SeuUsuarioMQTT";
const char* mqtt_password = "SuaSenhaMQTT";
const char* mqtt_broker_address = "EnderecoDoBrokerMQTT";
const char* topic = "esp32/atenuador";
const int ledPin = 2; // GPIO onde o LED (ou futuro dimmer) está conectado
'''

## Notas adicionais:

 O broker MQTT está hospedado em uma instância na nuvem da AWS, executando em um contêiner Docker.
 
 O código está em constante desenvolvimento, e a implementação final dependerá da integração bem-sucedida do hardware real do dimmer.

Seguindo esses passos, o módulo atenuador IoT é capaz de receber comandos de controle remoto via MQTT e ajustar a intensidade luminosa conforme necessário. Certifique-se de ajustar as configurações, como credenciais Wi-Fi e endereço do broker MQTT, para o seu ambiente específico.

