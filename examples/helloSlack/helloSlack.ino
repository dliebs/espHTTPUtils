//
// espHTTPUtils v1.0.0
// 2023.12.13
//
// Instructions for Slack API:
//  Sign in to Slack and create an app: https://api.slack.com/apps?new_app=1
//  Provide name for app and workspace to associate with, Create App
//  Add features and functionality > Incoming Webhooks > Turn On > Add New Webhook to Workspace
//  Select a channel and click Allow
//  Copy Webhook URL
//
// Thanks to https://lindevs.com/send-message-to-slack-channel-using-incoming-webhooks-and-esp8266-nodemcu
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
  Serial.println("Message #" + (String)counter);
  sendSlackMessage("Message #" + (String)counter, slack_url);
  counter++;
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
