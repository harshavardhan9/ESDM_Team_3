#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed
const int buttonPin = 13; // Connect your button to pin #13
const char* ssid = "Amsa";//OverHead
const char* wifi_password = "tech@8051";//OverHead

const char* mqtt_server = "192.168.1.37";//192.168.43.22
const char* mqtt_topic = "Your Topic";
const char* mqtt_username = "overhead";
const char* mqtt_password = "overhead";
const char* clientID = "Water";

unsigned int FirstIndex = 0, SecondIndex = 0;
String Encode_Data = "";

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
  
}

void loop() {
      String data = "";
  char inchar, Esc_Flag = 1;
const char* Rx;
  int i =0;
  do {
    Serial.flush();
    if ( '$' == Rec_Buff())
    {
      if ( '#' == Rec_Buff())
      {
        if ( '@' == Rec_Buff())
        {
          while ('#' != (inchar = Rec_Buff())) 
          {
            data += inchar;
//            Rx[i] = inchar;
            i++;
          }
          inchar = 0;
          Esc_Flag = 0;
        }
      }
    }
    yield();
  } while (Esc_Flag == 1);
  Serial.println(data);
  Rx = data.c_str();
//  data.toCharArray( Rx , 50);  
  Serial.println(Rx);
    if (client.publish(mqtt_topic, Rx)) {
      Serial.println(data);
    }
}


char Rec_Buff(void)
{
  while (Serial.available() == 0)
  {
     yield();
    }
  return ((char)Serial.read()); 
}
