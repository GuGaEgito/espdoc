#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // <--- Adicione esta biblioteca

const char* ssid = "REDE_WIFI"; //NOME DE SUA REDE WIFI
const char* password = "SENHA_WIFI"; //SENHA DA SUA REDE WIFI
const int ledInterno = 2; 

void setup() {
  Serial.begin(115200);
  pinMode(ledInterno, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nConectado!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://SEU_IP:5050/status"); //SEU IP 
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("Recebido: " + payload);

      // --- LÓGICA PARA TRATAR O JSON ---
      JsonDocument doc; // Cria um documento para guardar o JSON
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        // Agora você acessa a propriedade "led" do objeto
        const char* statusLed = doc["led"]; 

        if (strcmp(statusLed, "ON") == 0) {
          digitalWrite(ledInterno, HIGH);
          Serial.println("LED LIGADO");
        } else if (strcmp(statusLed, "OFF") == 0) {
          digitalWrite(ledInterno, LOW);
          Serial.println("LED DESLIGADO");
        }
      } else {
        Serial.print("Falha no parse do JSON: ");
        Serial.println(error.f_str());
      }
      // ---------------------------------
      
    } else {
      Serial.printf("Erro HTTP: %d\n", httpResponseCode);
    }
    http.end();
  }
  delay(1000); 
}
