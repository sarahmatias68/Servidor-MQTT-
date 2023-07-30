#include <sMQTTBroker.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

class MyBroker : public sMQTTBroker {
public:
    bool onConnect(sMQTTClient *client, const std::string &username, const std::string &password) {
        // check username and password, if ok return true
        return true;
    };
    void onRemove(sMQTTClient*) {
    };
    void onPublish(sMQTTClient *client, const std::string &topic, const std::string &payload) {
        // Store the topic and payload in the lists
        topics.push_back(topic);
        payloads.push_back(payload);
    }
    bool onEvent(sMQTTEvent *event) {
        switch (event->Type()) {
        case NewClient_sMQTTEventType: {
            sMQTTNewClientEvent *e = (sMQTTNewClientEvent*)event;
            e->Login();
            e->Password();
        }
        break;
        case LostConnect_sMQTTEventType:
            WiFi.reconnect();
            break;
        }
        return true;
    }

    std::vector<std::string> topics;
    std::vector<std::string> payloads;
};

MyBroker broker;

void handleRoot(AsyncWebServerRequest *request) {
    String html = "<html><body><h1>Dados dos Topicos</h1><ul>";

    // Iterate through the stored topics and payloads and add them to the HTML
    for (size_t i = 0; i < broker.topics.size(); i++) {
        html += "<li>Topic: " + String(broker.topics[i].c_str()) + ", &#013 Payload: " + String(broker.payloads[i].c_str()) + "</li>";
    }

    html += "</ul></body></html>";
    request->send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    const char* ssid = "Real Fibra MLDS";         // The SSID (name) of the Wi-Fi network you want to connect to
    const char* password = "86315415";     // The password of the Wi-Fi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
    }
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
    
    const unsigned short mqttPort = 1883;
    broker.init(mqttPort);
    
    // Setup web server
    server.on("/", handleRoot);
    server.begin();
}

void loop() {
    broker.update();
}
