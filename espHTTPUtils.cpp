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

#include "espHTTPUtils.h"

// Send message to slackURL
void sendSlackMessage(String message, String slackURL) {
  String data = "{\"text\":\"" + message + "\"}";

  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure();

  http.begin(client, slackURL);
  http.addHeader("Content-Type", "application/json");
  http.POST(data);
  http.end();
}

// Poll a webpage, good for turning things on and off or applying settings when we don't care about the output
void simpleHTTPGet(String targetURL) {
  WiFiClient client;
  HTTPClient http;
  // Beginning HTTP Connection
  if (http.begin(client, targetURL)) {
    // Start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      // Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        // File found at server, pass to payload
        String payload = http.getString();
        // Serial.println(payload);
      }
    }
    else {
      // There was an error
      // Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    // End HTTP connection
    http.end();
  }
  else {
    // Serial.printf("Unable to connect\n");
  }
}

// Returns the contents of the targetURL or the httpCode (-1) as a String if there's an error
String stringHTTPGet(String targetURL) {
  WiFiClient client;
  HTTPClient http;
  String payload;
  // Beginning HTTP Connection
  if (http.begin(client, targetURL)) {
    // Start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      // Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        // File found at server, pass to payload
        payload = http.getString();
      }
    }
    else {
      // There was an error, should return -1 as a string (should look into what http.errorToString(httpCode) does)
      payload = (String)httpCode;
    }
    // End HTTP connection
    http.end();
  }
  return payload;
}
