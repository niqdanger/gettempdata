#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

const char* ssid = "XXXXX";
const char* password = "XXXXX";
int ledPin = 12; // GPIO12---D6 of NodeMCU

DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);

 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  // Blink the light 4 times fast to show the system is up and running.
  for (int i=0; i<4; i++) {
       digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
       delay(333);              // wait for a second
       digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
       delay(222);              // wait for a second
  }
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  client.print("<center><h3 style='font-size:300%;'><br>TESTING UNIT!! Temp and Humidity<br></h3>");
  
  client.print("<img src='data:image/jpg;base64,");
  client.print("iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAABHNCSVQICAgIfAhkiAAAFrRJREFU");
  client.print("eJzt3X2MHVd5x/Ev29XKbF1rWZbItUxkuZHlGtey0mBc47jbNDJp4qYIaGpQGkOUIoSCBFGEIl5K");
  client.print("UYRQhKIIoRTxRxRZKEKoRAhFqKIWGErdKHUpDUlIAg0hCS6BvDq249iJvf3j2Vuv17t7Z855zpw5");
  client.print("M7+PdOS83Hvu8czc5z5z5ryAiIiIiIiIFOw9wIxjub/Z5kuTRnI3QNy90vL6pEUUALrnZMvrkxZR");
  client.print("AOgeZQBSmQJA9ygDkMpGczdAKpkEVgLLgfHZPwf/vGL2z98FPo3/F3aQAVwCbAGOAi/PlqNz/v0o");
  client.print("8CzwW+fPF+m9m6nWYz8ObKj42qrla7NtuLXCa+9K8reXZHQLUIbnKr5uGen6AJZVeO3zzp8tiSkA");
  client.print("lKHqF2sZ6foAFAA6SAGgDC9WfF3uDKBqpiItoQBQhtIygNuBNc7tkAQUANptYrbUCQCpMoCxCq99");
  client.print("Hmvvh4GHgVtm/11aSgGgnUaxL9GjwGbqZwCnHdtyYvbP8QqvfR57ZDloy8eBx7C/i661FtJJaZ8t");
  client.print("wI+xNPo8YIp6AQB8bwMGdVXNAKbm/bdJ7O9yENjk2C5xoADQHmPA54ADwMY5/30S+xIerVBHigBQ");
  client.print("9zHg5CL/70LgR8DnqRZMpAEKAO2wAfvV/wTnjs4c/KJWyQIGX1LPfoCqnYCnsacV8zOAuUaBm4B7");
  client.print("gQvimyaxFADy242lxxsW+f9vmv2zTgDIkQG8BLzG0gFg4EJsnYFrItolDhQA8hkDvoQNtV2qg22Q");
  client.print("Urc9Axi0740V6x0H9mLHQHNSMlEAyGMC+DZwfYXXhtwC5MgABu2rkgHMdT3wLfS4MAsFgOatBvYD");
  client.print("l1Z8fSkZwGC04mKdgEu5HPgBdmykQQoAzVqPdYBtrvGe3J2AqTOAgU3YE5A1ge+XAAoAzVmP/fLX");
  client.print("/ZUbfKFeqPDa18/+6T0OYJTh9+mxAQDgfOCH2LGSBigANGMj9uVfGfDeFdiX79kKr02VAdSZBxBy");
  client.print("CzDXaux2YLGnIuJIASC9dcB3Cfvyg52jSfJ1Ap6k3kzAmAxg4DxgH5YRSEIKAGmtAr6DXdAxJqk2");
  client.print("JTh3BjBe8bVVrMKCwCqn+mQBCgDprMAe9a1xqKvqfICcGcBC8wBirQPuodpEJAmgAJDGCPB16vX2");
  client.print("L6VqABiMsc+VAXgHALBRg3cmqFdQAEjlFuAyx/rOo1oAGPxS5soAYm91FnMVNlFKnCkA+HsXcINz");
  client.print("nVPY0tvDftlz9wGkCgBgk4jembD+XlIA8LUOG9/ufVyrTgga3AJ0pQ9grhHsVkCjBR0pAPgZwyb2");
  client.print("LE9Q9+CXdVgA8O4EPE21AHB09nVvGvK6WBNY34omDzlRAPDzaazDKoW6AeC40+fWnQmY8hZgYBvw");
  client.print("mQY+pxcUAHxsxe5RU6k6H8A7A6gbAFLeAsx1E35PWHpNASDeGHAHadPSuhmAVydg3YlATWQAYMf6");
  client.print("TnQrEE0BIN4NpB+3PgWsZfhqv7kygJNY+0KHO4fYjP/TFpFaLgCO4bsZZ0w5PNuuq53q+/lsfTe2");
  client.print("4O+2UDmG5gtEUQYQ5zbaNUw1VwaQyzg26EoCKQCEmwZ25W7EPGPYOfXuA3j9kq/KazewPXcjSqUA");
  client.print("EO4LuRuwCM/9AdueAQzcmrsBpVIACHMVcFHuRizCc3/AOpuC5LSF9mVjRVAAqG8EG/TTVn3MAAA+");
  client.print("m7sBJVIAqO9Kzt66q236mAGAjcK8MncjSqMAUN8nczdgiL5mAND+c9M6CgD1TNPee/+BvmYAYH0B");
  client.print("W3I3oiQKAPV8JHcDKuhzBgDwsdwNKIkCQHWrKOMes88ZANiCLFpItCIFgOquo4zJJ33PAMaA9+du");
  client.print("RCkUAKr7QO4GVNT3DABgT+4GlEIBoJptlLNnXd8zALCl2dQZWIECQDXvzd2AGpZh04Zfc6jrxJw6");
  client.print("S/O3uRtQAgWA4Uawob+l8FwUpNRbALDOQBlCAWC4rTS30o0HzynBpd4CgD0JaPuYjewUAIa7IncD");
  client.print("avIMACVnAAB/mbsBbacAMNzluRtQ02DuvsctwEns0Wep14lmCA5R6oltynnAptyNqMk7Ayj11x9s");
  client.print("3cDJ3I1oMwWApW2nvGPk2QlYdVegthpBqwUtqbSLu2kX525AAGUAZyvxHDZGAWBp23I3IIAygLMp");
  client.print("A1hCCWPbcxmlvPt/sGWyL8Vnj8JN2Hr/JduM/dAN21Ohl16XuwEttgF4KHcjxMUfAo/kbkQb6RZg");
  client.print("cW1e9kvq0blchALAuUawR0dvz90QcXMxdk51vc+jWwDbc34n8GfY0NFN2Jxy6Z6TwE+A/wT2A/8C");
  client.print("vJi1RZLFcmyBj/3Aq+Tf404lT3kV+C5wLT6dptJyq7EdfV4g/8Wn0q7yHHZtaDmxDhoDbgaOk/9C");
  client.print("U2l3OY5tMqJH5B2xBrif/BeWSlnlID3YerzrnYBrgQPAytwNkSI9jT0N+kXuhqTS9QBwEC0KIXH+");
  client.print("A3hb7kak0uUAcBEWAERivRV7dNg5XR4YobRfvJS0JFwtXc4AJoGngPHcDZGivQy8GXg+d0NS+J3c");
  client.print("DUjoOHAU+IvcDZGi3QD8IHcjUulyAAC4D7vN+dPcDZHinAb+ARscJIW7ErsdyP1sWaWM8hjlLQYr");
  client.print("Q0wAnwMOk/8CU2lv2Yv6jTptOXZf9xj5LzaV9pVpeqTLTwGquB74Uu5GSKu8kY72+C+k7xMevh/x");
  client.print("3ieB253aIX7+CLg68L1P06Mvv9iKt6cISxUfztBeGe46wtP/72Rob1ZdHglYxSvYL3mIzo4OK1zM");
  client.print("efmpWysK0fcAAPCzwPdNoKXD2uj3I977gFsrCqEAEB4ARujBfPECxZyTn7i1ohAKAPBoxHvXeDVC");
  client.print("3KwJfN9pdAvQS/8T8d7Sd83pojWB7/slNvGnVxQAwm8BwHackfZYDawIfG/v0n9QAACL/KEbaa53");
  client.print("bIfEizkfD7q1oiAKAHbvF7rmm7acapeY89HLfSAVAEzobcBqNB6gTf444r26BeixmH4ALTraHqHn");
  client.print("4iRx10CxFABMzACQzq4YW5gJYF3gex8BXnNsSzEUAMx/Rbx3u1srJMY2wq/nXqb/oAAw8Ai2fmCI");
  client.print("rWhWZRtcHPHe+9xaURgFAHMa2wAixDgWBCSvSyLeG3rui6cAcMa/Rbz3HW6tkBCThHcAvkzcLWDR");
  client.print("FADOOBDx3p1urZAQlxJ+Lf87Pe0AlLONAycIW0jiFNpXPqevEb4IyKcytFdaaj/hF9L1GdortiZD");
  client.print("zErPW5pvcnvoFuBs+yLe+263VkgdOwmfAPQ8Hd30U8JsIvyX5BRaICSHmPT/rgztlZZ7gvAL6uMZ");
  client.print("2ttny4FjhJ+vq5pvsrTdFwm/oGJWF5L6Pkj4uTpB+K2DdNg2wi+qGeyRlDTjx4Sfp29laK8UYIS4");
  client.print("jUT/qfkm99JW4gL1+5pvspTiFsIvrFfRYqFN+Drh5+gI1n8gsqCNxP263NZ8k3vlfCzQhp6fvc03");
  client.print("WUpzH+EX2DFgqvkm98aXiAvQ0423WIpzLXEX2S3NN7kXVgPHCT8v2tNRKllO3BDTwygLSOF24gLz");
  client.print("R5tvspTqVuIuNm0f7usCwidsDYLyROOtlmKtIa6z6QTaPchTTM//DDbIS6SWmLHmM8A9zTe5k6aJ");
  client.print("Ow+vomAsAWImCA3K5Y23ultGsZWbY86BJv5IsHuIu/geRwNPYnycuON/Cu3iJBE2YxdRzEX4lcZb");
  client.print("3Q0biOv406+/uPgm8b9CmihUzyhxA7IG9/7axFWirSP+l+gQGhtQx+eIO94zwJcbb7V0VuwglBk0");
  client.print("DbWqaeIewc5gz/21eau4mQKeIT4IaCXapa0GfkP8cb6x6YZL932I+AvzFLCr6YYXYhw4SPwxfhhb");
  client.print("MVjE1QhwL/EX6GHs6YKcMYItqOIRYGO2ChNZ0ibiOwRnsAVItZLwGbFzLwbljqYbLv3zWXwu1oeB");
  client.print("lQ23vY0+hc/xPITtFSiS1BjwI3wu2h/T78eDN+BzHE+hfRqlQRuIW5d+brmffj6yuhGf4zeDpl9L");
  client.print("BtfhdwE/hM1574ub8Tt29wPLmm2+iImdMjz/HvbCZpvfuDFsYU6vY3YEy8ZEshgnfrrq3HKM7q5b");
  client.print("vxI4gN+xmgHe1ejfQGQB64AX8L2wP49NiOmKLcTtvbhQubXRv4HIEqbxGR8wt/yI8tPbUWxiT+zY");
  client.print("/vnlbrTFvbRM7HLiC5Uj2KIYJWYDFxI/pXexwKhFVqSVvAYJzS/3YZuXlmAFtjeCd0Y0A/wcWNXc");
  client.print("X0Wkvphtxpcqp7CnDm0dQjyCPRr1mM23UDmE9l6UQtxJmi/BDHY/fQft+TKMYrc/3p18c8szaHUf");
  client.print("KcgIthZgqi/EICO4h3z73Z2H3fKk+sUflF+jL78U6jbSfjkG5SngC6QfSDQFvB/4AfGLpVYpT6A1");
  client.print("/aVwXrPd6vxi3oml5esi274CuAwbunsvzXzpB+UB2tvfUbzX5W5Az1yN3bfnWKnmKPDIbHkS60x7");
  client.print("FjgJvDb7mmXYqMZVwJuxeQnrsSW6cjxv/x7wbuDFDJ8tksQO7Ne5yWygxHI7WtJLOmoVPsuKdbEc");
  client.print("x/oXRDptGT7LjHepPIrNFxDpjcvQLcEM1jeiob3SS6vwWQ23xHIIeE/8IRQp3y7SjqRrUzmF3QKt");
  client.print("cDlyIh2xAlsHwGutwTaWA8B2rwMm0kWrsG2tmxx0k7o8jtJ9kVouwNbP815Mo8nyEDYISot3iARa");
  client.print("hy1/5bE5aRPlFLAP2E2ZC5mItNIybKDMAdp5e/AbbC2EPi1vLpLFamxXnYPkDQbPYBOPdqA0XySL");
  client.print("SSzdvgt4jLRf+CPAfmyGo3Y4LphmA/obwb4UO4BvAL/K1I4pbFjtBuAt2Ky+87EFPKrek78IPA38");
  client.print("DJtF+BDw38CDwGnn9i7lGmxi0PeAXzT4uZ2nAOBjA7Yf/TuwL/5gcMtvgfdiF25bjGDZwhQ29Xcc");
  client.print("61d4DXh5tryEtf2VTG0cWAZ8mbMnB/0KO54/RAFBMlmLLXz5dYb3yr8KfALdG9e1Fts1edjtyFPY");
  client.print("Y9LrUMejJLIKe469F7vgQu6bv432ra9qJ/AcYcf5KeCrKCBIhElsxNpX8O1Qe5zub/wZYwT4e3yf");
  client.print("aCggyFAT2ESc27COrpSP1I4DH2zmr1WUCeBbpH16MT8gaJXhnhoHLsUm3RwkzzDbvbPtENiI7fbT");
  client.print("9DkYBISvoYDQaaPYI7GbsOGpbZlpdxANk90CHCb/uRiUx7FBTdeg1YiLNQpchG2ouQ9Lu3NfWIuV");
  client.print("XYmOQSn2kv8cLFUOYRnCByl/l+ZzdGkcwDrsWfwVnP0svu2+Afx1orpvwDfD+EdseXEvY9jcgQnH");
  client.print("OlN7GvhX4J+B7wO/zNmYPltP9WfxbS4nSPN4cGuCtr7PuY2XJ2hj0+XX2DX4ITqYIbTJGmxEWMyz");
  client.print("+LaWD7sdpTNSbEf2Tec23pmgjbnLICB8GAWEKBPAldhQ0NSTW3KXe52O2VwpguRx/FbuHSV8sE9J");
  client.print("5RksIFyLxiFUtov29NQ3VTwfQaVI/wfF6zbgsoRtbHN5FJuQ1QptHJ++G7ib/j0j3+NY19841jWf");
  client.print("V4dlqo7PtluHDURq43cvu2tp5yo3TZSn8LsoUi4t7nEb0Jf0f6nyichj2DkfIv9JyV12Rh9F2NZA");
  client.print("O6+ObGNf0/+55RQwHXkco7UlDbka2ySi7/Y41NFEav3uyPf3Nf2fawS7FZjK3ZDcprFn4bkjchvK");
  client.print("MeIHMDXxiPR4RDtHKXvchne5O/A4dsIG2jUOvA3luojj2UT6PyihtwE7G2xjKcV7gFVlOW8BBtM/");
  client.print("Sxmy25Q9Ee9N2fs/X2gar/T/XF+kh7cC3yZ/5G1rCRkwMkKzIyRDbgOU/i9evlrzWLrIlQHchI0D");
  client.print("l4XtCXjPVmyfgKYsw0Zq1jFND3/pKtpNhunHOQLAZuCzGT63JCH76O1I0ZAhLq75+iZvUUozCnwk");
  client.print("dyNSGwMeIH+6VUKZrnlsR4CbaW4g1R1YFlCV0v/h5Tn85lq00qfIf5BLKXsDj/HlpH2ycoKwJxWX");
  client.print("JmxTl0qKmaGtsJZ2r8zTtnKE8F+DdaTJtJ7A+hpCfCVBe7pYHgg8vq3XxIqvXSvvDznQs8axnmWv");
  client.print("tuwjvANP6X+9kqM/J6lp8h/UEsv+gGM930eJH2n5BeKWFrsk8vP7Vu4KO8ztdR/5D2qJ5RS2ElKs");
  client.print("mC9gzMjEgS9HfH4fywkaelzaxGPAK7Gln6W+EeJn3kHcQp6xi4COAu+KrKNvxmhoeHATAeCTDXxG");
  client.print("l33AoY7QjjuAP4n87B20aAWcgnic96FSB4Bp9Osfay2wPbKOt0W8N/b8xU4d7qvNwKbUH5I6AHws");
  client.print("cf19sSfy/TEZwIVYShpiBNtkVcI0kgWksob+Lu/lXQ4TvkbilMPnh2YB0w6f3edyiMQ/0ikr/7vE");
  client.print("9ffJCuCdge+N+fWPrUNTf+OsIvGYgFRf0BFsc0XxsyfwfTH3/zF1jKDefw9FTqDSwA//coqw6b77");
  client.print("HD77sYDP3eHwuSo2gjLZDtKpMoD3Jqq3z0LGBIxguyTHWkv9gSlK/31MEf8UaFEpAsAo4fersrQ9");
  client.print("NV+/Hr+dd+v0A6j339dfpao4RQDYhlZ9SWU99b6InmMw6gwI2g6sdPzsvtuVquIUAeCKBHXKGXWy");
  client.print("AI8OwIE6wUTpv68L8N078v+lCAAeu9vI4q6i+ko8Ho8ABy6i2vWi3v80kqyh6R0AzqOB4Ys9N0m1");
  client.print("lHAc2Oj4uRNU+xXahj2/Fl9/nqJS7wCwPUGdcq4qQ0Qvwv/xUZXbgCKfWxdgB+FDshfl/WWtu0qs");
  client.print("hNnJ8E42z/R/YFhHoNL/dJaTYGKddwDQzL9mjDJ8vvhbE3zusPO7FaX/KV3iXaFnABjFpjBKM4bd");
  client.print("BqTIADay9KQkpf9pvd27Qs8AsJ7wGWtS30Zsqu5CVpFml6BRFh9ZqPQ/vS04Z+2elan3v3mLZQEp");
  client.print("fv2H1d301mR9VPVJTGWeAeAtjnVJNbtZuGc4dhmvpSw2uEiDf5rhGtw9A8A6x7qkmikWHiCSsjN2");
  client.print("oQtQY/+b49q56xkAQra0lnjzhwYvdZ/uYaH+BaX/zXG91VYAKN8uzp58Nayn3sP8LEDpf3M8R3e6");
  client.print("BYAJOr6raYvNHxPQxFiMuf0ASv+btQJbn8GFVwBQ+pfX3NuAlB2AA1vm/bPOf7PcsgCvAKC533ld");
  client.print("yJmLookMYO48A6X/zXPrcPcKAJNO9Ui4D2DpYZJ54/OMc6YzSul/8/7AqyKv2WIKAPm9D1sAtKnZ");
  client.print("mFuwMQjnN/R5coZbH4BXAPBad07CrQQ+0+DnvQ3HXyKppXUB4A1O9UiclEOAF/qsqisTia81WKZ3");
  client.print("OrYi3QJIqCb6GmRho9jYj9/GVuR1v+i+UomILMlly3WvAJBs5xIRWZDLo3cFAJEyKQMQ6TEFAJEe");
  client.print("c5l74xUAtBS4SLN+z6MSry/uK071iEg1rcoAFABEmuWy5oMCgEiZWpUBvOxUj4hU4/LdVQYg0mNe");
  client.print("AeCYUz0i0iCvAPCsUz0i0iCvAPC8Uz0i0iBlACJlOulRiQKASJmOelSiACBSJgUAkR5zGXvjOQ5A");
  client.print("QUCkOUc8KvGcxfdLx7pEZGkveVTiGQCedKxLRJbmknErAIiU6WmPSjwDwBOOdYnI0qKXBAdlACKl");
  client.print("al0A+IVjXSKyuJM4Db/3DAA/w2GrIhEZ6n+9KvIMAC+j2wCRJrhl296r+f7UuT4ROVdrA8AjzvWJ");
  client.print("yLke96rIOwA87FyfiJxLGYBIj7kFgNd5VTRrAnjBuU4ROdsbgBc9KvLOAF4EfuVcp4ic8SROX35I");
  client.print("s6ffTxLUKSLG9UlbigDwYII6RcS4/sCmCAAPJKhTRMxDnpXpFkCkLMqwRUREREQk1P8BZmL0WF2o");
  client.print("QmgAAAAASUVORK5CYII=");

  client.print("'>");

  client.println("<br><br>");

   client.println("<div><h3 style='font-size:2em;'>");
  client.print("<br>Humidity: ");
  client.print("<span class='Humidity'>");
  client.print(h);
  client.println("</span>");
  client.print("%\t");
  client.print("<br>Temperature: ");
  client.print("<span class='Temperature'>");
  client.print(f);
  client.println("</span>");
  client.print("*F\t");
   client.print("<br>Led is now: ");
  client.print("<span class='Light'>");
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("</span></div>");
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Off </button></a><br /><p></p>");

  client.println("</h3></html>");
    
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
