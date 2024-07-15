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

#ifndef espHTTPUtils_h
#define espHTTPUtils_h

/*----------  Libraries  ----------*/

#include "Arduino.h"

#ifdef ESP8266
  #include <ESP8266HTTPClient.h>
  #include <WiFiClientSecure.h>
#endif

#ifdef ESP32
  #include <HTTPClient.h>
  #include <WiFiClient.h>
#endif

/*----------   Functions   ----------*/

// Send message to slackURL
void sendSlackMessage(String, String);
// Poll a webpage, good for turning things on and off or applying settings when we don't care about the output
void simpleHTTPGet(String);
// Returns the contents of the targetURL or the httpCode (-1) as a String if there's an error
String stringHTTPGet(String);

#endif
