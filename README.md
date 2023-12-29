# Módulo Atenuadore ESP32

Este código representa o firmware para os módulos atenuadores. A principal função desses módulos é receber mensagens via MQTT e ajustar a intensidade luminosa de uma lâmpada de acordo com os parâmetros fornecidos. É importante notar que, por enquanto, a implementação do dimmer não está completa, razão pela qual o LED interno da ESP32 foi utilizado como exemplo para demonstrar o funcionamento.

## Funcionalidades Principais

### Controle Remoto da Intensidade Luminosa:
O módulo atenuador se conecta ao broker MQTT e assina o tópico "esp32/atenuador". Quando uma mensagem é recebida nesse tópico, o ajuste de intensidade luminosa será implementado assim que a funcionalidade completa do dimmer estiver pronta.

### LED Interno como Exemplo:
Até o desenvolvimento do dimmer, o LED interno da ESP32 é utilizado como exemplo para simular o controle da intensidade luminosa.
