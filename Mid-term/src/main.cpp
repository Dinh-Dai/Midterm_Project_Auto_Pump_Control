#include <Arduino.h>
#include <Ticker.h>
#include "secrets/wifi.h"
#include "wifi_connect.h"
#include "ca_cert.h"
#include "secrets/mqtt.h"
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// WiFi credentials
const char *wifiSSID = WiFiSecrets::ssid;
const char *wifiPassword = WiFiSecrets::pass;

// MQTT broker settings
const char *mqttRelayTopic = "esp32/relay";
const char *mqttSoilTopic = "esp32/moisture";
const char *mqttModeTopic = "esp32/mode";
const char *mqttLWTTopic = "esp32/lwt";
const char *mqttLWTMessage = "ESP32 unexpectedly disconnected.";
const int mqttKeepAlive = 15;
const int mqttSocketTimeout = 5;

// Pin definitions
const int pinSoilSensor = 34;
const int pinRelay = 26;

// Soil moisture configuration
const float soilThreshold = 80.0;
const int soilMaxValue = 4095;

// Ticker interval for publishing soil data
const int tickerInterval = 5000; // 5 seconds

// Control modes
enum ControlMode
{
    AUTO,
    MANUAL
};
ControlMode controlMode = AUTO; // Default to AUTO mode

// MQTT client setup
WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);
Ticker soilDataTicker;

// Function prototypes
void onMQTTMessage(char *topic, byte *payload, unsigned int length);
void publishSoilData();
void reconnectMQTT();
void setupRelay();
void controlRelay(float soilMoisture);
void publishSystemState();

void setup()
{
    Serial.begin(115200);
    delay(100);

    // Pin setup
    pinMode(pinSoilSensor, INPUT);
    setupRelay();

    // Connect to WiFi
    setup_wifi(wifiSSID, wifiPassword);

    // Configure secure MQTT connection
    secureClient.setCACert(ca_cert);
    mqttClient.setServer(MQTT::broker, MQTT::port);
    mqttClient.setCallback(onMQTTMessage);

    // Start publishing soil data periodically
    soilDataTicker.attach_ms(tickerInterval, publishSoilData);
}

void loop()
{
    // Reconnect to MQTT if disconnected
    if (!mqttClient.connected())
    {
        reconnectMQTT();
    }
    mqttClient.loop();
}

// Function to set relay to default state
void setupRelay()
{
    pinMode(pinRelay, OUTPUT);
    digitalWrite(pinRelay, HIGH); // Relay is OFF by default
}

// Callback function for MQTT messages
void onMQTTMessage(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("Message received on topic: %s\n", topic);

    String message = "";
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    Serial.printf("Payload: %s\n", message.c_str());

    // Handle mode control messages
    if (String(topic) == mqttModeTopic)
    {
        if (message == "MANUAL")
        {
            controlMode = MANUAL;
            Serial.println("Switched to MANUAL mode");
        }
        else if (message == "AUTO")
        {
            controlMode = AUTO;
            Serial.println("Switched to AUTO mode");
        }
        publishSystemState();
    }

    // Handle relay control messages in MANUAL mode
    if (controlMode == MANUAL && String(topic) == mqttRelayTopic)
    {
        if (message == "ON")
        {
            digitalWrite(pinRelay, LOW); // Turn relay ON
        }
        else if (message == "OFF")
        {
            digitalWrite(pinRelay, HIGH); // Turn relay OFF
        }
        publishSystemState();
    }
}

// Function to publish soil moisture data
void publishSoilData()
{
    int rawValue = analogRead(pinSoilSensor);
    float soilMoisture = (rawValue / float(soilMaxValue)) * 100;

    // Relay control logic in AUTO mode
    if (controlMode == AUTO)
    {
        controlRelay(soilMoisture);
    }

    // Publish soil moisture data to MQTT
    String moistureString = String(100 - soilMoisture, 2); // Invert to represent dryness
    mqttClient.publish(mqttSoilTopic, moistureString.c_str(), false);

    Serial.printf("Soil Moisture: %.2f%% (Published)\n", soilMoisture);
}

// Function to control relay based on soil moisture
void controlRelay(float soilMoisture)
{
    if (soilMoisture > soilThreshold)
    {
        digitalWrite(pinRelay, LOW);
        Serial.println("Relay ON (Soil Moisture > Threshold)");
    }
    else
    {
        digitalWrite(pinRelay, HIGH);
        Serial.println("Relay OFF (Soil Moisture <= Threshold)");
    }
}

// Function to reconnect to MQTT
void reconnectMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.println("Reconnecting to MQTT...");
        String clientID = "ESP32-" + String(WiFi.macAddress());
        if (mqttClient.connect(clientID.c_str(), MQTT::username, MQTT::password, mqttLWTTopic, 0, false, mqttLWTMessage))
        {
            Serial.printf("Connected to MQTT as %s\n", clientID.c_str());
            mqttClient.subscribe(mqttRelayTopic);
            mqttClient.subscribe(mqttModeTopic);
            publishSystemState();
        }
        else
        {
            Serial.printf("Failed to connect, MQTT state: %d. Retrying in 1 second...\n", mqttClient.state());
            delay(1000);
        }
    }
}

// Function to publish system state (mode and relay state)
void publishSystemState()
{
    String modeString = (controlMode == AUTO) ? "AUTO" : "MANUAL";
    mqttClient.publish(mqttModeTopic, modeString.c_str(), false);

    String relayState = digitalRead(pinRelay) == LOW ? "ON" : "OFF";
    mqttClient.publish("esp32/relayState", relayState.c_str(), false);

    Serial.printf("System State: Mode=%s, Relay=%s\n", modeString.c_str(), relayState.c_str());
}
