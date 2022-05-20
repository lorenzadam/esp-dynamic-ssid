#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "HTML.h"

//Konfigurasi WiFi
const char *ssid = "Dashboard-IoT";
const char *password = "";

String ssidNew = "", passNew;

ESP8266WebServer server(80); //Server pada port 80

void handleRoot() {
 server.send(200, "text/html", index_html); //Send web page
}

void handleForm() {
  ssidNew = server.arg("ssidNew"); 
  passNew = server.arg("passNew");
  
  server.send(200, "text/html", sukses_html); //Kirim web page
  delay(2000); //agar tidak langsung disconnect sehingga bisa menampilkan halaman informasi bahwa pengaturan telah disimpan

  WiFi.softAPdisconnect (true);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidNew, passNew);     //Connect to your WiFi router
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Menghubungkan ke WiFi");
  }

  Serial.println("Terhubung Ke Jaringan");
  delay(1000); //agar pesan terhubung ke jaringan bisa tampil
}

void setup() {
  Serial.begin(9600);
  //start Soft AP
  WiFi.softAP(ssid, password);
  String IP = WiFi.softAPIP().toString();

  Serial.println(IP);

  server.on("/", handleRoot);//Which routine to handle at root location
  server.on("/action_page", handleForm); //form action is handled here

  server.begin();//Start server
}

void loop() {
  if(ssidNew == ""){
    server.handleClient();
  } else {
    //BUAT KODE PROGRAM DISINI//
  }
}
