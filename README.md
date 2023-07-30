Descrição do Código - MQTT Broker e Servidor Web
Este repositório contém um código para um ESP32 que atua como um MQTT Broker e também hospeda um servidor web para exibir os tópicos e cargas publicados pelos clientes MQTT.

Funcionalidades Principais
MQTT Broker: O ESP32 atua como um Broker MQTT, permitindo que dispositivos clientes publiquem mensagens em tópicos e se inscrevam para receber essas mensagens.

Armazenamento de Tópicos e Cargas: O código mantém uma lista dos tópicos e pacotes recebidos dos clientes MQTT, armazenando-os em memória para acesso posterior.

Servidor Web: Além de funcionar como Broker MQTT, o ESP32 também hospeda um servidor web que exibe os tópicos e cargas armazenados em uma página HTML.

Como Funciona

Inicialização

Ao ser iniciado, o ESP32 configura-se para conectar-se à rede Wi-Fi local, utilizando o SSID e a senha fornecidos. O dispositivo aguarda a conexão bem-sucedida antes de prosseguir.

Após a conexão ser estabelecida, o Broker MQTT é inicializado na porta 1883, permitindo a comunicação com dispositivos clientes que publicam e se inscrevem em tópicos.

MQTT Broker
O código implementa um Broker MQTT usando a biblioteca sMQTTBroker.h. Ele trata a publicação de mensagens feitas pelos clientes e armazena os tópicos e cargas dessas mensagens em listas internas.

Servidor Web
O ESP32 também atua como um servidor web assíncrono utilizando a biblioteca ESPAsyncWebServer.h. O servidor web expõe uma página HTML com uma lista dos tópicos e cargas recebidos dos clientes MQTT.

Como Utilizar
Instale as bibliotecas: Antes de utilizar este código, certifique-se de ter instalado as bibliotecas sMQTT e ESPAsyncWebServer.

Configuração da Rede Wi-Fi: Substitua as variáveis ssid e senha pelo nome e senha da sua rede Wi-Fi local.

Iniciar o Servidor: Faça o upload do código para o ESP32. Quando o dispositivo for ligado, ele se conectará à rede Wi-Fi e iniciará o Broker MQTT e o servidor web.

Visualizar Tópicos e Pacotes: Conecte-se ao servidor web hospedado no ESP32 digitando o endereço IP local do dispositivo no navegador da web. A página exibirá uma lista dos tópicos e cargas publicados pelos clientes MQTT.

Observações
Este código não inclui recursos avançados de segurança ou autenticação para o servidor web ou o MQTT Broker. Se a segurança for uma preocupação, considere adicionar autenticação e criptografia para proteger o acesso e as comunicações.

Caso queira estender a funcionalidade deste código, você pode adicionar recursos como limpeza das listas de tópicos e pacotes após um certo período ou permitir que os usuários publiquem mensagens para os tópicos diretamente através da página web.

Lembre-se de revisar a documentação das bibliotecas utilizadas para entender melhor suas funcionalidades e opções de configuração.
