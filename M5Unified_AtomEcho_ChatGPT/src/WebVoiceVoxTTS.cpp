#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "WebVoiceVoxRootCA.h"
#include <AudioGeneratorMP3.h>
#include <AudioFileSourceBuffer.h>
#include "AudioFileSourceHTTPSStream.h"

//-----------------------------------------------------
extern String VOICEVOX_API_KEY;
extern AudioGeneratorMP3 *mp3;
extern AudioFileSourceBuffer *buff;
extern AudioFileSourceHTTPSStream *file;
extern int preallocateBufferSize;
extern uint8_t *preallocateBuffer;
void StatusCallback(void *cbData, int code, const char *string);
void playMP3(AudioFileSourceBuffer *buff);
//-----------------------------------------------------

String https_get(const char* url, const char* root_ca) {
  String payload = "";
  WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    client -> setCACert(root_ca);
    {
      // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
      HTTPClient https;
  
      Serial.print("[HTTPS] begin...\n");
      if (https.begin(*client, url)) {  // HTTPS
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();
  
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
  
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            payload = https.getString();
          }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }  
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
      // End extra scoping block
    }  
    delete client;
  } else {
    Serial.println("Unable to create client");
  }
  return payload;
}

bool voicevox_tts_json_status(const char* url, const char* json_key, const char* root_ca) {
  bool json_data = false;
  DynamicJsonDocument doc(1000);
  String payload = https_get(url, root_ca);
  if(payload != ""){
    Serial.println(payload);
    DeserializationError error = deserializeJson(doc, payload.c_str());
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return json_data;
    }
    json_data = doc[json_key];
//    Serial.println(json_data);
  }
  return json_data;
}

//String tts_status_url;
String voicevox_tts_url(const char* url, const char* root_ca) {
  String tts_url = "";
  WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    client -> setCACert(root_ca);
    {
      // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
      HTTPClient https;
  
      Serial.print("[HTTPS] begin...\n");
      if (https.begin(*client, url)) {  // HTTPS
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();
  
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
  
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload.c_str());
            if (error) {
              Serial.print(F("deserializeJson() failed: "));
              Serial.println(error.f_str());
              return tts_url;
            }
  String json_string;
  serializeJsonPretty(doc, json_string);
  Serial.println("====================");
  Serial.println(json_string);
  Serial.println("====================");

            if(!doc["success"]) return tts_url;
//            const char* mp3url = doc["mp3DownloadUrl"];
            const char* mp3url = doc["mp3StreamingUrl"];
            Serial.println(mp3url);
            Serial.print("isApiKeyValid:");
            if(doc["isApiKeyValid"]) Serial.println("OK");
            else Serial.println("NG");
            tts_url = String(mp3url);
          }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }  
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
      // End extra scoping block
    }  
    delete client;
  } else {
    Serial.println("Unable to create client");
  }
  return tts_url;
}

static String URLEncode(const char* msg) {
  const char *hex = "0123456789ABCDEF";
  String encodedMsg = "";

  while (*msg != '\0') {
    if ( ('a' <= *msg && *msg <= 'z')
         || ('A' <= *msg && *msg <= 'Z')
         || ('0' <= *msg && *msg <= '9')
         || *msg  == '-' || *msg == '_' || *msg == '.' || *msg == '~' ) {
      encodedMsg += *msg;
    } else {
      encodedMsg += '%';
      encodedMsg += hex[*msg >> 4];
      encodedMsg += hex[*msg & 0xf];
    }
    msg++;
  }
  return encodedMsg;
}

void Voicevox_tts(char *text,char *tts_parms){
  String tts_url = String("https://api.tts.quest/v3/voicevox/synthesis?key=")+ VOICEVOX_API_KEY +  String("&text=") +  URLEncode(text) + String(tts_parms);
  String URL = voicevox_tts_url(tts_url.c_str(), root_ca);
//  Serial.println(tts_url);

  if(URL == "") return;
  file = new AudioFileSourceHTTPSStream(URL.c_str(), root_ca);
  buff = new AudioFileSourceBuffer(file, 10240);
  playMP3(buff);
}
