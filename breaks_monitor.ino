#define TOUCH_PIN 16  // D0

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
IPAddress graphiteIP;
WiFiUDP Udp;
WiFiClient client;

const char* ssid = "WIFI-Name";
const char* password =  "WIFI-password";
const char* remote_host = "www.google.com";
const char* graphiteHost = "graphite-server";
const char* UUID = "graphite-uuid";
unsigned int graphitePort = 2003;  //graphite server port
unsigned int localPort = 2003;
int outputValue = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to WiFI");
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.println(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(TOUCH_PIN, INPUT);
  
  timeClient.begin();
}

void loop()
{ 
  timeClient.update();
  unsigned long metric_time = timeClient.getEpochTime();
  Serial.println(metric_time);
  int outputValue = digitalRead(TOUCH_PIN);
  send_metrics("graphite-uuid.chair.occupied", outputValue, metric_time);
  delay(5000);
}

void send_metrics(const char* metric, const int value, const unsigned long timestamp) {
  if (client.connect(graphiteHost, graphitePort)) {
    Serial.println("connected");
    // Send metrics:
    client.print(metric);
    client.write(" ");
    client.print(value);
    client.write(" ");
    client.println(timestamp);
  }
  else{
    Serial.println("Error :(");
  }

  Serial.print(metric);
  Serial.write(" ");
  Serial.print(value);
  Serial.write(" ");
  Serial.println(timestamp);
}