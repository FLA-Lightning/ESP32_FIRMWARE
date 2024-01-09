# Módulo Atenuador

Este código representa o firmware para os módulos atenuadores. A principal função desses módulos é receber mensagens via MQTT e ajustar a intensidade luminosa de uma lâmpada de acordo com os parâmetros fornecidos.

## Como o código funciona?

1. Conexão à Rede Wi-Fi

Ao iniciar, o módulo atenuador tentará se conectar à rede Wi-Fi configurada. Ele usa as credenciais (SSID e senha) fornecidas no código para estabelecer uma conexão Wi-Fi. O progresso dessa conexão é exibido no Monitor Serial. 

2. Conexão ao Broker MQTT

Após se conectar à rede Wi-Fi, o módulo atenuador tentará se conectar ao broker MQTT. O endereço do broker MQTT, o nome de usuário e a senha são configurados no início do código. O módulo utiliza a biblioteca PubSubClient para lidar com a comunicação MQTT.

Se a conexão for estabelecida com sucesso, o módulo se inscreverá no tópico "esp32/det_pessoa". Isso significa que ele estará aguardando mensagens nesse tópico para ajustar a intensidade luminosa.

3. Controle de Intensidade Luminosa

Quando uma mensagem com valor '1' é recebida, indicando a detecção de uma pessoa, o código aciona o dimmer, aumentando a intensidade luminosa da lâmpada de 50% para 100%. A lâmpada permanece acesa enquanto detecta uma pessoa. Se não houver detecção por 5 segundos, a lâmpada diminui a intensidade para 50%.