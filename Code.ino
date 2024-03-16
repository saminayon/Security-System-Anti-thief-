#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "BTS";
const char* password = "1111111888";

#define BOTtoken "6999476782:AAG7Ko644C8ciRJSzWPkQ2GiRTMG2GH5Fzk"
#define CHAT_ID "5168751835"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int motionSensor = 14; (ESP 8266, Pin no. D5)
const int ledPin = LED_BUILTIN;
bool motionDetected = false;

void ICACHE_RAM_ATTR detectsMovement() {
  motionDetected = true;
}

void setup() {
  Serial.begin(9600);
  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(ledPin, OUTPUT);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Blink the LED to indicate successful WiFi connection
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {
  if (motionDetected) {
    bot.sendMessage(CHAT_ID, "Alert! Someone is moving", "");
    Serial.println("Tomar basai chor dhukche");
    motionDetected = false;
  }
}
