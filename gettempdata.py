#!/usr/bin/python3

import typer
import requests
from bs4 import BeautifulSoup
import urllib3
from influxdb import InfluxDBClient
import datetime

urllib3.disable_warnings()

sensors = ['test.sens.hackermonkey.com', 'crawl.sens.hackermonkey.com','attic.sens.hackermonkey.com','shed.sens.hackermonkey.com']

app = typer.Typer()

@app.command()
def getdata(adddb: bool = True, debug: bool = False):

  now = datetime.datetime.now()
  if (debug): print("Start time: ", sep=' ', end=' ')
  if (debug): print(str(now))

  for unit in sensors :
      location, subnet, domain, tld = unit.split('.')[-4:]
      if (debug): print("Unit :", unit, "  Loc: ", location)
      onurlget = "http://" + unit + "/LED=ON"
      offurlget = "http://" + unit + "/LED=OFF"
      try:
        response = requests.get(onurlget, timeout=10)
      except requests.exceptions.ConnectTimeout: 
          if (debug): print('Request timeout for host ', unit)
      else:
        soup = BeautifulSoup(response.content, "html.parser")
        if (debug): print(soup.find("span", class_="Light").contents[0], soup.find("span", class_="Temperature").contents[0], soup.find("span", class_="Humidity").contents[0], sep=' ', end=' ')
        if adddb:
          dbClient = InfluxDBClient(host='influxdb', port=8086, username='XXXXX', password='XXXXX', ssl=True, verify_ssl=False)
          dbClient.switch_database('sensorTemps')
          events = [{"measurement":"temperature",
                  "tags": {
                      "host": unit,
                      "location": location
                  },
                  "fields":
                  {
                      "temperature": soup.find("span", class_="Temperature").contents[0]
                  }
              },
              {"measurement":"humidity",
                  "tags": {
                      "host": unit,
                      "location": location
                  },
                  "fields":
                  {
                    "humidity": soup.find("span", class_="Humidity").contents[0]
                  }
              }
          ]
          dbClient.write_points(events)
      try:
        response = requests.get(offurlget, timeout=10)
      except requests.exceptions.ConnectTimeout:
        if (debug): print('2nd Request timeout for host ', unit)
      else:
        soup = BeautifulSoup(response.content, "html.parser")
        if (debug): print(soup.find("span", class_="Light").contents[0])

      now = datetime.datetime.now()
      if (debug): print("End time: ", sep=' ', end=' ')
      if (debug): print(str(now))


if __name__ == "__main__":
    app()
