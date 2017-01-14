/* The local-config.h file is not checked in. It contains local secrets as noted below */
#include "local-config.h"
#if 0
#define LOCAL_WIFI_STA_SSID "XXXX"
#define LOCAL_WIFI_STA_PASS "XXXX"
#endif

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "web-template.h"

WebTemplate webTemplate;

const char WiFiAPPSK[] = "sparkfun";

const int LED_PIN = 4; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int DIGITAL_PIN = 12; // Digital pin to be read

boolean state = false;

ESP8266WebServer server(80);

String getContentType(String filename) {
    if(filename.endsWith(".htm")) return "text/html";
    else if(filename.endsWith(".html")) return "text/html";
    else if(filename.endsWith(".css")) return "text/css";
    else if(filename.endsWith(".js")) return "application/javascript";
    else if(filename.endsWith(".png")) return "image/png";
    else if(filename.endsWith(".gif")) return "image/gif";
    else if(filename.endsWith(".jpg")) return "image/jpeg";
    else if(filename.endsWith(".ico")) return "image/x-icon";
    else if(filename.endsWith(".xml")) return "text/xml";
    else if(filename.endsWith(".pdf")) return "application/x-pdf";
    else if(filename.endsWith(".zip")) return "application/x-zip";
    else if(filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

bool handleFileRead(String path){
    if(path.endsWith("/")) path += "index.htm";
    String contentType = getContentType(path);
    String pathWithGz = path + ".gz";
    if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
        if(SPIFFS.exists(pathWithGz))
            path += ".gz";
        File file = SPIFFS.open(path, "r");
        size_t sent = server.streamFile(file, contentType);
        file.close();
        return true;
    }
    return false;
}

// open drain, LOW is on
void switchOn(boolean on) {
    digitalWrite(LED_PIN, on ? LOW : HIGH);
}

void setup() {
    initHardware();
    switchOn(state);
    SPIFFS.begin();

    //  setupWifiAccessPoint();
    setupWifiStation();

    server.on("/", HTTP_GET, []() {
      if (!handleFileRead("/index.html")) {
        server.send(404, "text/plain", "FileNotFound");
      }
    });
    server.on("/main.css", HTTP_GET, []() {
      if (!handleFileRead("/main.css")) {
       server.send(404, "text/plain", "FileNotFound");
      }
    });
    server.on("/main.js", HTTP_GET, []() {
      if (!handleFileRead("/main.js")) {
       server.send(404, "text/plain", "FileNotFound");
      }
    });
    server.on("/api/switch", HTTP_GET, []() {
        String value = state ? "on" : "off";
        String body = "{\"state\":\"" + value + "\"}";
        server.send(200, "application/json", body);
    });
    server.on("/api/switch", HTTP_POST, []() {
        StaticJsonBuffer<200> newBuffer;
        JsonObject& root = newBuffer.parseObject(server.arg("plain"));
        if (! root.success()) {
            server.send(400, "text/plain", "error parsing body");
            return;
        }
        if (! root.containsKey("state")) {
            server.send(400, "text/plain", "missing data 'state'");
        }
        state = strcmp("on", root["state"]) == 0;
        //digitalWrite(LED_PIN, state);
        switchOn(state);
        server.send(200);
    });
    server.begin();
}

void loop() {
    server.handleClient();
}

/*
void xloop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val = -1; // We'll use 'val' to keep track of both the
                // request type (read/set) and value if set.

    if (req.indexOf("/main.css") != -1) {
        client.print(webTemplate.getCss());
        return;
    }
  if (req.indexOf("/led/0") != -1)
    val = 0; // Will write LED low
  else if (req.indexOf("/led/1") != -1)
    val = 1; // Will write LED high
  else if (req.indexOf("/read") != -1)
    val = -2; // Will print pin reads
  // Otherwise request will be invalid. We'll say as much in HTML

  // Set GPIO5 according to the request
  if (val >= 0)
    digitalWrite(LED_PIN, val);

  client.flush();

  // Prepare the response. Start with the common header:
  String style =
    "body { font-size: 200%; }"
    "div { width: auto; padding: 1em 0; }"
    "a { display: block; }"
    "button { width: 100%; height: 10%; margin: 1em 0; font-size: 100%; font-weight: bold; }";

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
//  s += "<style>" + style + "</style>";
    s += "<link rel=\"stylesheet\" href=\"/main.css\"/>";
  s += "</head>";
  s += "<body>";
  // If we're setting the LED, print out a message saying we did
  if (val >= 0)
  {
    s += "LED is now ";
    s += (val)?"on":"off";
  }
  else if (val == -2)
  { // If we're reading pins, print out those values:
    s += "Analog Pin = ";
    s += String(analogRead(ANALOG_PIN));
    s += "<br>"; // Go to the next line.
    s += "Digital Pin 12 = ";
    s += String(digitalRead(DIGITAL_PIN));
  }
  else
  {
    s += "Invalid Request.<br> Try /led/1, /led/0, or /read.";
  }
  s +=       " <label class=\"switch\">";
  s +=                "<input type=\"checkbox\"/>";
  s +=                 "<div class=\"slider\"></div>";
  s +=             "</label>";

 // s += "<div>";
 // s += "<a href=\"/led/1\"><button>Off</button></a>";
 // s += "<a href=\"/led/0\"><button>On</button></a>";
 // s += "</body></html>\n";
 // s += "</div>";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
*/

void setupWifiAccessPoint()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Thing " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void setupWifiStation() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(LOCAL_WIFI_STA_SSID, LOCAL_WIFI_STA_PASS);
}


void initHardware()
{
  Serial.begin(115200);
  pinMode(DIGITAL_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT_OPEN_DRAIN); // OUTPUT, OUTPUT_OPEN_DRAIN
  //digitalWrite(LED_PIN, LOW);
  //state = HIGH;
  // Don't need to set ANALOG_PIN as input,
  // that's all it can be.
}
