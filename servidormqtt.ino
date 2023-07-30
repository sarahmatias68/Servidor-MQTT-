#include <sMQTTBroker.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer servidorWeb(80);

class MeuBroker : public sMQTTBroker {
public:
    void RemoverCliente(sMQTTClient*) {
    };
    void Publicar(sMQTTClient *cliente, const std::string &topico, const std::string &pacote) {
        // Armazena o tópico e a pacote nas listas
        topicos.push_back(topico);
        pacotes.push_back(pacote);
    }
    bool OcorrerEvento(sMQTTEvent *evento) {
        switch (evento->Type()) {
        case LostConnect_sMQTTEventType:
            WiFi.reconnect();
            break;
        }
        return true;
    }

    std::vector<std::string> topicos;
    std::vector<std::string> pacotes;
};

MeuBroker meuBroker;

void PaginaPrincipal(AsyncWebServerRequest *requisicao) {
    String html = "<html><body><h1>Dados dos Topicos</h1><ul>";

    // Itera sobre os tópicos e pacotes armazenados e os adiciona ao HTML
    for (size_t i = 0; i < meuBroker.topicos.size(); i++) {
        html += "<li>Tópico: " + String(meuBroker.topicos[i].c_str()) + ", &#013 Pacote: " + String(meuBroker.pacotes[i].c_str()) + "</li>";
    }

    html += "</ul></body></html>";
    requisicao->send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    const char* ssid = "******";         // Entre com o nome da rede Wi-fi local
    const char* senha = "*****";        // Entre com a senha da rede Wi-fi
    WiFi.begin(ssid, senha);
    while (WiFi.status() != WL_CONNECTED) { // Espera pela conexão
        delay(1000);
    }
    Serial.println("Conexão estabelecida!");  // Conectado, obtendo IP
    Serial.print("Endereço IP:\t");
    Serial.println(WiFi.localIP()); // Mostra no Serial o endereço IP local obtido
    
    const unsigned short portaMQTT = 1883; // Define a porta padrão do MQTT 
    meuBroker.init(portaMQTT);
    
    // Configuração do servidor web
    servidorWeb.on("/", PaginaPrincipal);  
    servidorWeb.begin();
}

void loop() {
    meuBroker.update();
} 
