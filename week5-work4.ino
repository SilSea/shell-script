#include<ESP8266WiFi.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPin D4

const char* ssid = "Test01";
const char* password = "123456789";

WiFiServer server(80);

DHT dht(DHTPin, DHTTYPE);

static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

void setup() {
  Serial.begin(115200);
  delay(10);

  dht.begin();
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(10000);
  
  Serial.println(WiFi.localIP());
}
void loop() {
  WiFiClient client = server.available();
  if(client){
    Serial.println("New client");
    boolean blank_line = true;
    while(client.connected())
    {
      if(client.available())
      {
        char c = client.read();
        if(c == '\n' && blank_line)
        {
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          float f = dht.readTemperature(true);

          if(isnan(h) || isnan(t) || isnan(f))
          {
            Serial.println("Failed to read from DHT sensor!");
            strcpy(celsiusTemp, "Failed");
            strcpy(fahrenheitTemp, "Failed");
            strcpy(humidityTemp, "Failed");
          }
          else
          {
            float hic = dht.computeHeatIndex(t, h, false);
            dtostrf(hic, 6, 2, celsiusTemp);
            float hif = dht.computeHeatIndex(f, h);
            dtostrf(hif, 6, 2, fahrenheitTemp);
            dtostrf(h, 6, 2, humidityTemp);
            
            Serial.print("Humidity: ");
            Serial.print(h);
            Serial.print(" %\t Temperature: ");
            Serial.print(t);
            Serial.print("*C ");
            Serial.print(f);
            Serial.print("*F\t Heat index: ");
            Serial.print(hic);
            Serial.print("*C ");
            Serial.print(hif);
            Serial.print("*F ");
            Serial.print("Humidity: ");
            Serial.print(h);
            Serial.print(" %\t Temperature: ");
            Serial.print(t);
            Serial.print("*C ");
            Serial.print(f);
            Serial.print("*F\t Heat index: ");
            Serial.print(hic);
            Serial.print("*C ");
            Serial.print(hif);
            Serial.println(" *F");
          }
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // your actual web page that displays temperature and humidity
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head><link rel=\"stylesheet\" href=\"https://silsea.github.io/shell-script/style.css\"></head><body><h1>ESP8266 - Temperature and Humidity CS UTK</h1><h3>Temperature in Celsius: ");
          client.println(celsiusTemp);
          client.println("*C</h3><h3>Temperature in Fahrenheit: ");
          client.println(fahrenheitTemp);
          client.println("*F</h3><h3>Humidity: ");
          client.println(humidityTemp);
          client.println("%</h3><h3>");
          client.println("</body></html>");
          break;
        }
        if (c == '\n')
        {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r')
        {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
