#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <DHT.h>
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float h, t, f, hic, hif;

void setup() {
  delay(1000);
  Serial.begin(9600);
  dht.begin();
  WiFi.mode(WIFI_STA);

  WiFiManager wm;
  wm.setAPCallback(configModeCallback);
  if (!wm.autoConnect("ESP32-temperature")) {
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  Serial.println("connected...yeey :)");
  pinMode(22,OUTPUT);
}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    WiFiManager wm;
    wm.setAPCallback(configModeCallback);
    if (!wm.autoConnect("ESP32-temperature")) {
      Serial.println("failed to connect and hit timeout");
      ESP.restart();
    delay(1000);
    }
    Serial.println("connected...yeey :)");
  }
  read_dht();
  kirim_data();
  digitalWrite(22,LOW);
  delay(700);
  digitalWrite(22,HIGH);
  delay(30000);
}

void read_dht() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  hif = dht.computeHeatIndex(f, h);
  hic = dht.computeHeatIndex(t, h, false);
  

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

void kirim_data() {

  float kelembaban, suhuc, suhuf, heatc, heatf;
  kelembaban = h;
  suhuc = t;
  suhuf = f;
  heatc = hic;
  heatf = hif;

  String postData = (String)"kelembaban=" + kelembaban + "&suhuc=" + suhuc
                    + "&suhuf=" + suhuf + "&heatc=" + heatc + "&heatf=" + heatf;

  HTTPClient http;
  http.begin("http://ribut.ngopikode.my.id/esp32-temperature/api.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  auto httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.println(postData);
  Serial.println(payload);

  http.end();
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}
