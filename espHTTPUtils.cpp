//
// espHTTPUtils v1.0.0
// 2023.12.13
//

#include "espHTTPUtils.h"

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

void simpleHTTPGet(String targetURL) {
  WiFiClient client;
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, targetURL)) {
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
  Serial.println("");
}
