//
//
//  espHTTPUtils - Version 1.0.1
//  This version was not deployed [2023.12.13]
//
//  ESP8266/32 Based
//    Slack message sender
//    HTTP GET requests with either void or String outputs
//
//  Instructions for Slack API: https://lindevs.com/send-message-to-slack-channel-using-incoming-webhooks-and-esp8266-nodemcu
//    Sign in to Slack and create an app: https://api.slack.com/apps?new_app=1
//    Provide name for app and workspace to associate with, Create App
//    Add features and functionality > Incoming Webhooks > Turn On > Add New Webhook to Workspace
//    Select a channel and click Allow
//    Copy Webhook URL
//
//  Changes From Previous Version
//    Comments, cleanup
//
//

/*----------  Libraries  ----------*/

#include <espHTTPUtils.h>

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif

#ifdef ESP32
  #include <WiFi.h>
#endif

/*----------  User Variables  ----------*/

// Slack Webhook API URL
String slack_url = "https://hooks.slack.com/services/TXXXXXXXXXX/BXXXXXXXXXX/XXXXXXXXXXXXXXXXXXXXXXXX";

// WiFi Credentials
#ifndef STASSID
#define STASSID "Your_WiFi_SSID"
#define STAPSK  "Your_WiFi_Pass"
#endif
#define WiFiHostname "slackURL"

/*----------  Program Variables  ----------*/

int counter = 0;

/*----------  Main Functions  ----------*/

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
  // Send message to slack_url, including output of stringHTTPGet (in this case, the external IP)
  sendSlackMessage("Message #" + (String)counter + " from " + stringHTTPGet("https://domains.google.com/checkip"), slack_url);
  counter++;
  // There's also void simpleHTTPGet(String) which is good for turning things on and off or applying settings when we don't care about the output but is not included in this example
  delay(5000);
}

/*---------- WiFi Code ----------*/

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(WiFiHostname);
  WiFi.begin(STASSID, STAPSK);

  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - startTime) <= 10000) // Timeout WiFi connection attempt after 10 sec
  {
    delay(500);
  }
}
