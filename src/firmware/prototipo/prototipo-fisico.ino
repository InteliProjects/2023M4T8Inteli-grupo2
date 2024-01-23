#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <TinyGPSPlus.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configurações do GPS
TinyGPSPlus gps;
const int RXPin = 16, TXPin = 17;
HardwareSerial gpsSerial(2);

// Variáveis para controle de envio de dados
unsigned long lastPositionSendTimestamp = 0;
unsigned long lastSignalCheckTimestamp = 0;
const unsigned long positionSendInterval = 60000; // 1 minuto
const unsigned long signalCheckInterval = 30000; // 30 segundos

// Configurações do Wi-Fi e MQTT
const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_server = "mqtt_server";

// Configurações do LED
const int LED_INTERNET = 2;
const int LED_SERVER = 32;

// Configurações do LCD
int lcdAddress = 0x27; // Use o endereço correto do seu módulo
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows); // Inicializa o LCD

WiFiClient espClient; // Cria o cliente Wi-Fi
PubSubClient client(espClient); // Cria o cliente MQTT

// Função para atualizar a mensagem no LCD
void updateLCDMessage(const String& message) {  //use a essa função para atualizar a mensagem no LCD updateLCDMessage("Mensagem");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
}

// Função para piscar o LED
void blinkLED(int pin) {
    digitalWrite(pin, HIGH);
    delay(250);
    digitalWrite(pin, LOW);
    delay(250);
}

// Conectar ao Wi-Fi
void connectToWiFi() {
    pinMode(LED_INTERNET, OUTPUT); // Configura o pino do LED como saída
    digitalWrite(LED_INTERNET, LOW); // Desliga o LED inicialmente

    while (WiFi.status() != WL_CONNECTED) { // Enquanto não estiver conectado
        updateLCDMessage("Conectando WiFi...");
        WiFi.begin(ssid, password); // Tenta conectar
        for (int i = 0; i < 20; ++i) {  // Espera até 10 segundos para conectar
            if (WiFi.status() == WL_CONNECTED) {
                digitalWrite(LED_INTERNET, HIGH); // Acende o LED quando conectado
                updateLCDMessage("WiFi Conectado"); // Atualiza o LCD
                return;
            }
            delay(500);
            blinkLED(LED_INTERNET); // Pisca o LED
        }
        updateLCDMessage("Falha na conexão WiFi"); // Atualiza o LCD
    }
}

// Reconectar ao MQTT
void mqttReconnect() { 
    pinMode(LED_SERVER, OUTPUT); // Configura o pino do LED como saída
    updateLCDMessage("Conectando MQTT"); // Atualiza o LCD
    while (!client.connected()) { // Enquanto não estiver conectado
        if (client.connect("ESP32Client")) { // Tenta conectar
            digitalWrite(LED_SERVER, HIGH); // Acende o LED quando conectado
            client.subscribe("status"); // Assina o tópico "status"
            updateLCDMessage("MQTT Conectado"); // Atualiza o LCD
        } else {
            digitalWrite(LED_SERVER, LOW); // Desliga o LED quando não conectado
            delay(5000);
        }
    }
}

// Formatar timestamp
String formatTimestamp() { // Formata o timestamp para o formato YYYY-MM-DD HH:MM:SS
    if (gps.date.isValid() && gps.time.isValid()) { // Se a data e hora forem válidas
        char buffer[32]; // Buffer para armazenar o timestamp
        sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", // Formata o timestamp
                gps.date.year(), gps.date.month(), gps.date.day(), // Data
                gps.time.hour(), gps.time.minute(), gps.time.second()); // Hora
        return String(buffer); // Retorna o timestamp formatado
    } else {
        return String("Data/Hora Inválida"); // Retorna mensagem de erro
    }
}

// Enviar dados do GPS
void sendGPSData() { // Envia os dados do GPS para o servidor
    if (gps.location.isValid()) { // Se a localização for válida
        updateLCDMessage("Enviando dados GPS"); // Atualiza o LCD

        StaticJsonDocument<256> doc; // Cria um documento JSON
        doc["id"] = 1; // ID do dispositivo
        doc["lat"] = gps.location.lat(); // Latitude
        doc["long"] = gps.location.lng(); // Longitude
        doc["timestamp"] = formatTimestamp(); // Timestamp
        String jsonString; // String para armazenar o JSON
        serializeJson(doc, jsonString); // Serializa o JSON
        client.publish("status", jsonString.c_str()); // Envia o JSON para o servidor

        delay(2000); // Tempo para ler a mensagem
    }
}

// Mensagem de perda de sinal GPS
void sendSignalLossMessage() {// Envia mensagem de perda de sinal GPS
    updateLCDMessage("Perda de sinal GPS"); // Atualiza o LCD

    StaticJsonDocument<256> doc; // Cria um documento JSON
    doc["id"] = 1;
    doc["message"] = "GPS signal lost";
    doc["timestamp"] = formatTimestamp();
    String jsonString;
    serializeJson(doc, jsonString);
    client.publish("status", jsonString.c_str()); // Envia o JSON para o servidor

    delay(2000); // Tempo para ler a mensagem
}
bool isNodeOn = true; // Variável para controle do status do nó
void callback(char* topic, byte* message, unsigned int length) { // Função de callback para o status do servidor
    String messageTemp;
    for (int i = 0; i < length; i++) { // Lê a mensagem
        messageTemp += (char)message[i]; // Concatena a mensagem
    }

    if (String(topic) == "status") { // Se o tópico for "status"
        if (messageTemp == "NODE:ON") { // Se a mensagem for "NODE:ON"
            digitalWrite(LED_SERVER, HIGH); // Acende o LED 
            isNodeOn = true; // Atualiza o status
        } else if (messageTemp == "NODE:OFF") { // Se a mensagem for "NODE:OFF"
            digitalWrite(LED_SERVER, LOW); // Desliga o LED
            isNodeOn = false;           // Atualiza o status
        }
    }
}


// Configuração inicial
void setup() {
    Serial.begin(9600);
    gpsSerial.begin(9600, SERIAL_8N1, RXPin, TXPin); // Inicializa o GPS

    connectToWiFi(); // Substitui a chamada anterior de setup_wifi()
    client.setServer(mqtt_server, 1883); // Configura o servidor MQTT
    client.setCallback(callback); // Configura a função de callback
    mqttReconnect(); // Substitui a chamada anterior de reconnect()

    // Inicializa o LCD
    Wire.begin(21, 22); // SDA, SCL pinos
    lcd.init(); // Inicializa o LCD
    lcd.backlight(); // Liga o backlight
    updateLCDMessage("Inicializando..."); // Atualiza o LCD
}
// Loop principal
void loop() {
    if (WiFi.status() != WL_CONNECTED) { // Se o Wi-Fi não estiver conectado
        digitalWrite(LED_INTERNET, LOW); // Desliga o LED do Wi-Fi
        digitalWrite(LED_SERVER, LOW);   // Desliga o LED do servidor
        connectToWiFi();                 // Tenta reconectar ao Wi-Fi
    } else {
        // Se o Wi-Fi estiver conectado, mas o MQTT não, tenta reconectar
        if (!client.connected()) {
            digitalWrite(LED_SERVER, LOW); // Desliga o LED do servidor antes de tentar reconectar
            mqttReconnect(); // Tenta reconectar ao MQTT
        }
        client.loop(); // Mantém a conexão com o servidor
    }

    client.loop();// Mantém a conexão com o servidor

    bool isGPSValid = false; // Variável para controle do status do GPS
    while (gpsSerial.available()) { // Enquanto houver dados disponíveis
        char c = gpsSerial.read(); // Lê o caractere
        if (gps.encode(c)) { // Se o caractere for válido
            if (gps.location.isValid()) { // Se a localização for válida
                isGPSValid = true; // Atualiza o status
                if (millis() - lastPositionSendTimestamp > positionSendInterval) { // Se o intervalo de envio tiver passado
                    lastPositionSendTimestamp = millis(); // Atualiza o timestamp
                    sendGPSData(); // Envia os dados do GPS
                }
            }
        }
    }

    if (millis() - lastSignalCheckTimestamp > signalCheckInterval) { // Se o intervalo de checagem tiver passado
        lastSignalCheckTimestamp = millis(); // Atualiza o timestamp
        if (!gps.location.isValid()) { // Se a localização não for válida
            sendSignalLossMessage(); // Envia mensagem de perda de sinal
        }
    }

    // Atualiza o status no LCD
    lcd.clear(); // Limpa o LCD
    lcd.setCursor(0, 0); // Posiciona o cursor na primeira linha
    if (isGPSValid) { // Se o GPS estiver válido
        lcd.print("GPS ON"); // Exibe "GPS ON"
    } else {
        lcd.print("Aguardando GPS"); // Exibe "Aguardando GPS"
    }
    lcd.setCursor(0, 1); // Posiciona o cursor na segunda linha
    lcd.print(WiFi.isConnected() ? "WiFi On" : "WiFi Off"); // Exibe o status do Wi-Fi
    lcd.print(" "); // Espaço
    Serial.begin(9600); // Inicializa a comunicação serial

    lcd.print(isNodeOn ? "MQTT On" : "MQTT Off"); // Exibe o status do MQTT

    delay(5000); // Atualização a cada 5 segundos
}
