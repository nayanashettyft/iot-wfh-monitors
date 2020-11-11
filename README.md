# IOT WIFI monitors

This repo contains code and instructions to setup a WIFI chips ESP8266 NodeMCU or ESP32 for monitoring work from home habits by pushing metricss to graphite and visualising it with grafana.

ESP8266 NodeMCU or ESP32 are both WIFI chips. ESP8266 NodeMCU is good enough for our work load and a couple of £s cheaper than ESP32 as well.

## Am I taking enough breaks from my desk - touch sensor monitor

We use a `touch sensor` and a `ESP8266 NodeMCU` to send a metric to graphite if the seat on which the touch sensor is places is occupied or not. We use the ESP32 client to connect to a graphite server and send 0 if the chair is empty and 1 if I am sitting on the chair to `graphite`. Alerts and visualisation is on `grafana`.


## Am I drinking enough water - water bottle monitor

We use a `load cell`, `HX711 load cell amplifier` and a `ESP32 NodeMCU` for measuring the weight of a waterbottle. We then use the ESP32 client to connect to a graphite server and send the weight of the bottle to `graphite`. Alerts and visualisation is on `grafana`.

## WifiMonitor

We use ESP32 client, ping and ntpclient modules to ping `google.com` at regular intervals and send the results to `graphite`. We then visualise the data on `grafana`.

## Referance documentation

* Use https://learn.acrobotic.com/tutorials/post/esp8266-getting-started if you are new to programming with ardino and ESP8266
* https://www.youtube.com/watch?v=m2fEXhl70OY this video is also a good 1 to try before going off on your own
* ESP8266 spec and installation details https://www.handsontec.com/pdf_learn/esp8266-V10.pdf
* Library documentation for usage: https://www.arduino.cc/en/Reference/Libraries
* To buy a ESP8266, https://www.amazon.co.uk/HiLetgo-Internet-Development-Wireless-Micropython/dp/B0791FJB62/ref=sr_1_3?crid=OLIBHT3YPAYW&keywords=esp8266+nodemcu&qid=1558790100&s=gateway&sprefix=esp8266%2Caps%2C145&sr=8-3
* TO buy a touch sensor, https://www.amazon.co.uk/ANGEEK-TTP223B-Digital-Sensor-Capacitive/dp/B07WMNRWVH/ref=sxts_sxwds-bia-wc-nc-drs1_0?cv_ct_cx=touch+sensor&dchild=1&keywords=touch+sensor&pd_rd_i=B07WMNRWVH&pd_rd_r=dc2b9e79-68bc-4141-9c7c-2ca3f0d535b9&pd_rd_w=J5xuo&pd_rd_wg=pAWWd&pf_rd_p=c322b3bb-d864-487b-a904-d8a912bfd542&pf_rd_r=3RE23E9EXFJXHP9RDQFG&psc=1&qid=1605137156&sr=1-1-0f636240-5ebc-47e0-a5f7-bb2a7fa20976
* To buy a ESP32, https://www.amazon.co.uk/ESP-32S-Development-2-4GHz-Bluetooth-Antenna/dp/B071JR9WS9/ref=sr_1_4?dchild=1&keywords=esp32&qid=1605137106&sr=8-4
* To buy a load cell and HX711, https://www.amazon.co.uk/Innovateking-EU-Converter-Breakout-Portable-Electronic/dp/B07GRGT3C3/ref=sr_1_5?crid=12QVGUFAB0E52&keywords=weight+sensor&qid=1558724401&s=gateway&sprefix=weight+senso%2Caps%2C137&sr=8-5
