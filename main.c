#include <Adafruit_Fingerprint.h>  // fingerprint sensor library
#include <HardwareSerial.h>         // for esp 32
#include <WiFi.h>            // for wifi connection
#include <Wire.h>           // for oled connection i2c
#include <Adafruit_GFX.h>   // for oled display
#include <Adafruit_SSD1306.h>  // for oled display
#include <SPI.h>      // for oled connection spi
#define SCREEN_WIDTH 128  // screen height and width of oled
#define SCREEN_HEIGHT 32 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C                
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* NAME;     // 3 coloumns are created for name ,registration and roll number 
const char* ID;
const char* rollno;

int buzz=18;        //buzzer pin 18
 
String Event_Name = "fingerprint";     // evernt name in webhook

String Key = "j61K9MUrfwDx6DnCXvsHCd85cA1z5ovEub7YjZm3R_i";     // unique string key different for every user

// Replace with your unique IFTTT URL resource
String resource = "/trigger/" + Event_Name + "/with/key/" + Key;   

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";                  // website name 

// Replace with your SSID and Password
const char* ssid     = "Wifi M12";       // this wifi name and password is given from srinjoy chakroborty's smart phone 
const char* password = "galaxym12";

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

void setup()
{
   pinMode(buzz,OUTPUT);
  Serial.begin(115200);
  Serial2.begin(115200);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");

  Serial.print("Connecting to: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);

  int timeout = 10 * 4; // 10 seconds
  while (WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());                  
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());



   display.display();
   display.setTextSize(1);
    display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("WiFi connected in: "); //when wifi get connected oled dispaly show "wifi connected in"
  display.println(", IP address: ");//                                               "ip adress:xxxx.xxxx.xxxx.xxxx"
  display.println(WiFi.localIP());
  display.display();
  delay(5000);                         // it will show for 5 sec after that screen will blank
  display.clearDisplay();
  display.display();
}
void buzzer()
{
digitalWrite(buzz,HIGH);      // when attendendence will marked buzzer will make a noise for 1sec
delay(1000);
digitalWrite(buzz,LOW);
delay(1000);
}
void loop()                     // run over and over again
{
  getFingerprintIDez();
  if (finger.fingerID == 1) {   // unique id per person aas given in r307 sensor
                              // id 1 for saptarshi mondal
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "Saptarshi Mondal";
    ID = "D212223112";
    rollno="DJCGETCES6//10023142";
    if (finger.confidence >= 60) {     // when finger print accuracy is more than 60% attendance will marked
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();                 // its for send data into the server
      buzzer();
       display.display();
   display.setTextSize(1);
    display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Attendace Marked for ");    // oled display show "Attendence marked for "
  display.println(NAME);                       //                   "name" for 5 sec
   display.display();
   delay(5000);
    display.clearDisplay();                     // after that the screen will clear
     display.display();

      // digital write - open the door
    }

  }

  if (finger.fingerID == 2) {    // id 2 for srinjoy chakroborty
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "Srinjoy Chakrabarty";
    ID = "D202110097";
    rollno="DJCGETCES6//10010225";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      buzzer();
       display.display();
   display.setTextSize(1);
    display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Attendace Marked for ");
  display.println(NAME);
  display.display();
   delay(5000);
    display.clearDisplay();
     display.display();
      // digital write - open the door
    }      //don't ned to run this at full speed.

  }
   if (finger.fingerID == 3 ) {    // id 3 for swastik dutta
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "Swastik Dutta";
    ID = "D202110103";
    rollno="DJCGETCES6//10010231";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      buzzer();
       display.display();
   display.setTextSize(1);
    display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Attendace Marked for ");
  display.println(NAME);
  display.display();
   delay(5000);
    display.clearDisplay();
     display.display();
      // digital write - open the door
    } 
    
  }   
  if (finger.fingerID == 4 ) {     // id 4 for suman dey
    Serial.print("!!--");
    Serial.println(finger.fingerID);
    digitalWrite(2, LOW);
    NAME = "Sumon Dey";
    ID = "D21212222";
    rollno="DJCGETCES6//10010512";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      makeIFTTTRequest();
      buzzer();
       display.display();
   display.setTextSize(1);
    display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Attendace Marked for ");
  display.println(NAME);
   display.display();
   delay(5000);
    display.clearDisplay();
     display.display();
      // digital write - open the door
    } 
    
  }     //  //don't ned 
  finger.fingerID = 0;
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resource);

  // Temperature in Celsius
  String jsonObject = String("{\"value1\":\"") + NAME + "\",\"value2\":\"" + ID + "\",\"value3\":\"" + rollno
                      + "\"}";     // 3 different value will send in server

  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}