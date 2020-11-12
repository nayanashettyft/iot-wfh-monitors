/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP32Ping.h>
#include <HX711_ADC.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
IPAddress graphiteIP;
WiFiUDP Udp;
WiFiClient client;

const char *ssid = "WiFI name";
const char *password = "WiFi password";
const char *remote_host = "www.google.com";
const char *graphiteHost = "graphite-server";
const char *UUID = "graphite-uuid";
unsigned int graphitePort = 2003; //graphite server port
unsigned int localPort = 2003;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;
HX711_ADC LoadCell(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

void setup()
{
	Serial.begin(115200);
	delay(10);
	Serial.println("Connecting to WiFI");
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.println(".");
		delay(500);
	}
	Serial.println("");
	Serial.println("IP Address: ");
	Serial.println(WiFi.localIP());
	timeClient.begin();
	LoadCell.begin();			  // start connection to HX711
	LoadCell.start(2000);		  // load cells gets 2000ms of time to stabilize
	LoadCell.setCalFactor(402.0); // calibration factor for load cell
}

void loop()
{
	int success = 0;
	int rttmax = 0;
	int rttmin = -1;
	int rtttotal = 0;

	timeClient.update();
	unsigned long metric_time = timeClient.getEpochTime();
	Serial.println(metric_time);

	LoadCell.update();				   // retrieves data from the load cell
	long reading = LoadCell.getData(); // get output value
	Serial.print("HX711 reading: ");
	Serial.println(reading);

	//send data to graphite
	send_metrics("graphite-uuid.water-bottle.weight", reading, metric_time);

	// Get the avg round trip time
	for (int i = 0; i < 5; i++)
	{
		if (Ping.ping(remote_host))
		{
			success++;
			int rtt = Ping.averageTime();
			if (rtt > rttmax)
			{
				rttmax = rtt;
			}
			if (rttmin == -1 or rtt < rttmin)
			{
				rttmin = rtt;
			}
			rtttotal += rtt;
			Serial.println("Success!!");
		}
		else
		{
			Serial.println("Error :(");
		}
	}
	int rttavg = -1;
	if (success > 0)
	{
		rttavg = int(rtttotal / success);
	}

	int loss = (10 - success) * 10;
	float rssi = WiFi.RSSI();

	send_metrics("graphite-uuid.ping.avg", rttavg, metric_time);
	send_metrics("graphite-uuid.ping.min", rttmin, metric_time);
	send_metrics("graphite-uuid.ping.max", rttmax, metric_time);
	send_metrics("graphite-uuid.ping.loss", loss, metric_time);
	send_metrics("graphite-uuid.ping.rssi", rssi, metric_time);

	delay(5000);
}

void send_metrics(const char *metric, const int value, const unsigned long timestamp)
{
	if (client.connect(graphiteHost, graphitePort))
	{
		Serial.println("connected");
		// Send metrics:
		client.print(metric);
		client.write(" ");
		client.print(value);
		client.write(" ");
		client.println(timestamp);
	}
	else
	{
		Serial.println("Error :(");
	}

	Serial.print(metric);
	Serial.write(" ");
	Serial.print(value);
	Serial.write(" ");
	Serial.println(timestamp);
}