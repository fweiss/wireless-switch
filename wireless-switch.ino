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

const char WiFiAPPSK[] = "sparkfun";

const int LED_PIN = 4; // Thing's onboard, green LED
const int STATUS_PIN = 5;

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
    String contentType = getContentType(path);
    String pathWithGz = path + ".gz";
    if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
        if(SPIFFS.exists(pathWithGz))
            path += ".gz";
        File file = SPIFFS.open(path, "r");
        size_t sent = server.streamFile(file, contentType);
        file.close();
    }
    server.send(404, "text/plain", "FileNotFound");
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
      handleFileRead("/index.html");
    });
    server.on("/main.css", HTTP_GET, []() {
      handleFileRead("/main.css");
    });
    server.on("/main.js", HTTP_GET, []() {
      handleFileRead("/main.js");
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
        switchOn(state);
        server.send(200);
    });
    server.begin();
}

void loop() {
    server.handleClient();
    boolean cc = WiFi.status() == WL_CONNECTED;
    digitalWrite(STATUS_PIN, cc ? HIGH : LOW);
}

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

void initHardware() {
  pinMode(LED_PIN, OUTPUT_OPEN_DRAIN); // OUTPUT, OUTPUT_OPEN_DRAIN
  pinMode(STATUS_PIN, OUTPUT);
}
