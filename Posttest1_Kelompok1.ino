#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Galaxy A72988D";
const char* password = "riska2002";

ESP8266WebServer server(80); // Port untuk web server


// Define pins
const int BUZZER_PIN = D4;
const int LED_PIN = D8;
const int ONOFF_BUZZER = D3;
const int ADD_BUZZER = D1;
const int MIN_BUZZER = D2;
const int ONOFF_LED = D7;
const int ADD_LED = D5;
const int MIN_LED = D6;

// Define variables
int kecerahan = 0;
int suara = 0;
int LED_ONOFF;
int BUZZER_ONOFF;
int ONOFFBUZZER = 0;
int ONOFFLED = 0;

void setup() {
  Serial.begin(9600);
  // Initialize pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ONOFF_BUZZER, INPUT_PULLUP);
  pinMode(ADD_BUZZER, INPUT_PULLUP);
  pinMode(MIN_BUZZER, INPUT_PULLUP);
  pinMode(ONOFF_LED, INPUT_PULLUP);
  pinMode(ADD_LED, INPUT_PULLUP);
  pinMode(MIN_LED, INPUT_PULLUP);
  WiFi.begin(ssid, password);

  //Menampilkan dan Menghubungkan ke Web
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); // Halaman utama
  server.on("/kecerahan", handleKecerahan); // Halaman untuk menampilkan kecerahan
  server.on("/suara", handleSuara); // Halaman untuk menampilkan suara
  server.begin(); // Memulai web server
}

void loop() {
  server.handleClient();
  delay(100);
  analogWrite(LED_PIN,kecerahan);
  analogWrite(BUZZER_PIN,suara);
  
  // Check button state
  int LED_ADD = digitalRead(ADD_LED);
  int LED_MIN = digitalRead(MIN_LED);
  int BUZZER_ADD = digitalRead(ADD_BUZZER);
  int BUZZER_MIN = digitalRead(MIN_BUZZER);
  LED_ONOFF = digitalRead(ONOFF_LED);
  BUZZER_ONOFF = digitalRead(ONOFF_BUZZER);

 
 //Atur ON dan OFF LED
  if ( LED_ONOFF == LOW&&ONOFFLED==0) {
    ONOFFLED=1;
    kecerahan=250;
    Serial.println(ONOFFLED);
    
  } else if(LED_ONOFF==LOW&&ONOFFLED==1) {
    ONOFFLED=0;
    kecerahan=0;
    Serial.println(ONOFFLED);
  }
  
 //Atur Kecerahan LED
  if ( LED_ADD == LOW&&kecerahan<250&&ONOFFLED==1) {
    kecerahan+=5; //Tambah Kecerahan
    Serial.println(kecerahan);
    
  } else if(LED_MIN==LOW&&kecerahan>0&&ONOFFLED==1) {
    kecerahan-=5; //Kurangi Kecerahan
    Serial.println(kecerahan);
  }


//Atur ON OFF Suara Buzzer 
    if ( BUZZER_ONOFF == LOW&&ONOFFBUZZER==0) {
    ONOFFBUZZER=1;
    suara=100;
    Serial.println(ONOFFBUZZER);
    
  } else if(BUZZER_ONOFF==LOW&&ONOFFBUZZER==1) {
    ONOFFBUZZER=0;
    suara=0;
    Serial.println(ONOFFBUZZER);
  }
  
//Atur Nilai Suara Buzzer
  if ( BUZZER_ADD == LOW&&suara<2500&&ONOFFBUZZER==1) {
    suara+=5; //Tambah Suara
    Serial.println(suara);
    
  } else if(BUZZER_MIN==LOW&&suara>100&&ONOFFBUZZER==1) {
    suara-=5; //Kurang Suara
    Serial.println(suara);
  }
}


//Tampilan Web
void handleRoot() {
  server.send(200, "text/html", "<html><body><h1>Monitoring Kecerahan LED dan Suara Buzzer </h1><p><a href=\"/kecerahan\">Lihat Kecerahan</a></p><p><a href=\"/suara\">Lihat Suara</a></p></body></html>"); // Menampilkan halaman utama
}

//Baca Nilai Kecerahan
void handleKecerahan() {
  String content = "<html><body><h1>Kecerahan</h1><p>" + String(kecerahan) + " </p><p><a href=\"/\">Kembali ke halaman utama</a></p></body></html>"; 
  server.send(200, "text/html", content);
}


// membaca Nilai Suara
void handleSuara() {
  String content = "<html><body><h1>Suara</h1><p>" + String(suara) + " Hz</p><p><a href=\"/\">Kembali ke halaman utama</a></p></body></html>"; 
  server.send(200, "text/html", content);
}
