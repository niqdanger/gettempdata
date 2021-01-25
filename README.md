# gettempdata

NodeMCU code modified from BRUH Automation code and demo DHT22 code. HTML tags to allow for easy scraping of sensor data via python script. Light blinks 4 times for successful link up with Wifi.

Python script will pull data from sensors, then upload into an influxdb. Light blinks when grabbing data. Easily then displayed using Grafana.

Currently only humidity and temperature pulled and logged. 
