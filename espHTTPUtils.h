//
// espHTTPUtils v1.0.0
// 2023.12.13
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

void sendSlackMessage(String, String);
void simpleHTTPGet(String);

#endif
