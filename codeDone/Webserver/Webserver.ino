/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-async-web-server-espasyncwebserver-library/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <Arduino_JSON.h>
// -------------- Global --------------

char eRead[25];
byte len;
const char* PARAM_INPUT_1 = "Output";
const char* PARAM_INPUT_2 = "Status";
String CodeId = "131220-2-4-33-L3";
String Password = "admin";
String Tocken = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsIng1dCI6IkhCeGw5bUFlNmd4YXZDa2NvT1UyVEhzRE5hMCIsImtpZCI6IkhCeGw5bUFlNmd4YXZDa2NvT1UyVEhzRE5hMCJ9.eyJhdWQiOiI0Zjg4MjE1MS1jODU1LTQ1YTAtYjgwNS04OWE0YTZjYTFiNDAiLCJpc3MiOiJodHRwczovL3N0cy53aW5kb3dzLm5ldC8zNmRhNDVmMS1kZDJjLTRkMWYtYWYxMy01YWJlNDZiOTk5MjEvIiwiaWF0IjoxNTU5Mzc2ODc0LCJuYmYiOjE1NTkzNzY4NzQsImV4cCI6MTU1OTM4MDc3NCwiYWNyIjoiMSIsImFpbyI6IjQyWmdZTWdNa011L1pDNFZNL0hTWXZiWUFCT1ZueFljMFZHcEJRR2NDWC9LR3E3NVRRQUEiLCJhbXIiOlsicHdkIl0sImFwcGlkIjoiMTE1ZWMyOWUtYTllNi00YzBhLWI2NzEtM2RlNWFjMGRlMzg0IiwiYXBwaWRhY3IiOiIxIiwiZmFtaWx5X25hbWUiOiJMZSIsImdpdmVuX25hbWUiOiJUb2FuIiwiaXBhZGRyIjoiMjcuNzQuMjQ5Ljc1IiwibmFtZSI6IkxlLCBUb2FuIChVUyAtIFByaW5jZXRvbikiLCJvaWQiOiJjOGUwMmYzNy02MmU3LTQzNGItODU2MS02OWUyMDljYTc5ZDYiLCJvbnByZW1fc2lkIjoiUy0xLTUtMjEtMjM4NDQ3Mjc2LTEwNDA4NjE5MjMtMTg1MDk1Mjc4OC0yNTEwODQ2Iiwic2NwIjoidXNlcl9pbXBlcnNvbmF0aW9uIiwic3ViIjoiUzJSd0k4bTZMZ3R4OHZXNGtFZ0dPcXRVYlJUc252Y003VUdDRENoNkpQayIsInRpZCI6IjM2ZGE0NWYxLWRkMmMtNGQxZi1hZjEzLTVhYmU0NmI5OTkyMSIsInVuaXF1ZV9uYW1lIjoidG9hbmxlQGRlbG9pdHRlLmNvbSIsInVwbiI6InRvYW5sZUBkZWxvaXR0ZS5jb20iLCJ1dGkiOiJoNVk4YS1OU1NFS3F6bmtmeHVJTUFBIiwidmVyIjoiMS4wIn0.TALL1k7AScj0OtiyoAoNE0ZIdT4ylyvDDCU-0EnehThG_lqJaoBRepupRGKkzaSo5P61B8tPdXEpXVr3ulsNCOwKMfhI1yWiDK-EPO0UH0Cx86j3cAf4LEA9jeka_2mpBIBLZda92w0mFzOTj4QXizxFpYe6Jga7kehqzF3HLuOtPsIpouat6PsJG-GwzFnZrasp60Z6QqDwkSSiY-qe4JLqZlUZuAljY2jJLH-316RiLkPWb3e6yP7hMu9mrnRq0sQ8UcYadfMprqZ0eMNrUQu3poqVzP1NwomELsRKrUJJ7bTXdzS21azF3XTAMP-UlNQEVNwWhNnDKa6tFwoRjw";
// -------------- Functions --------------
String outputState(int output){
  if(digitalRead(output)){
    return "1";
  }
  else {
    return "0";
  }
}
// Saves string do EEPROM
void SaveString(int startAt, const char* id)
{
  for (byte i = 0; i <= strlen(id); i++)
  {
    EEPROM.write(i + startAt, (uint8_t) id[i]);
  }
  EEPROM.commit();
}

// Reads string from EEPROM
void ReadString(byte startAt, byte bufor)
{
  for (byte i = 0; i <= bufor; i++)
  {
    eRead[i] = (char)EEPROM.read(i + startAt);
  }
  len = bufor;
}

//Saves byte to EEPROM
void SaveByte(int startAt, byte val)
{
  EEPROM.write(startAt, val);
  EEPROM.commit();
}

//Reads byte from EEPROM
byte ReadByte(byte startAt)
{
  byte Read = -1;
  Read = EEPROM.read(startAt);
  return Read;
}
String encryption(String s) 
{ 
    int l = s.length(); 
    int b = ceil(sqrt(l)); 
    int a = floor(sqrt(l)); 
    String encrypted; 
    if (b * a < l) { 
        if (min(b, a) == b) { 
            b = b + 1; 
        } 
        else { 
            a = a + 1; 
        } 
    } 
  
    // Matrix to generate the  
    // Encrypted String 
    char arr[a][b]; 
    memset(arr, ' ', sizeof(arr)); 
    int k = 0; 
      
    // Fill the matrix row-wise 
    for (int j = 0; j < a; j++) { 
        for (int i = 0; i < b; i++) { 
            if (k < l){ 
                arr[j][i] = s[k]; 
            } 
            k++; 
        } 
    } 
  
    // Loop to generate  
    // encrypted string 
    for (int j = 0; j < b; j++) { 
        for (int i = 0; i < a; i++) { 
            encrypted = encrypted +  
                         arr[i][j]; 
        } 
    } 
    return encrypted; 
} 
  
// Function to decrypt the string 
String decryption(String s){ 
    int l = s.length(); 
    int b = ceil(sqrt(l)); 
    int a = floor(sqrt(l)); 
    String decrypted; 
  
    // Matrix to generate the  
    // Encrypted String 
    char arr[a][b]; 
    memset(arr, ' ', sizeof(arr)); 
    int k = 0; 
      
    // Fill the matrix column-wise 
    for (int j = 0; j < b; j++) { 
        for (int i = 0; i < a; i++) { 
            if (k < l){ 
                arr[j][i] = s[k]; 
            } 
            k++; 
        } 
    } 
  
    // Loop to generate  
    // decrypted string 
    for (int j = 0; j < a; j++) { 
        for (int i = 0; i < b; i++) { 
            decrypted = decrypted +  
                         arr[i][j]; 
        } 
    } 
    return decrypted; 
} 
// Create AsyncWebServer object on port 80
AsyncWebServer server(147);
// Set your Static IP address
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

void setup(){
 
  // Serial port for debugging purposes
   EEPROM.begin(512);
  Serial.begin(115200);
  delay(1000);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
    byte x = -2;
  String ssidd = "";
  String passwordd = "";
   // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  // Connect to Wi-Fi
  Serial.println("\n\tConnecting to Wi-Fi");
      //SaveByte(2,strlen(ssid));
      //SaveByte(3,strlen(password));
      //SaveString(5,ssid);
      //SaveString(31,password);
     x = ReadByte(2);
    Serial.print("\t\tValue of byte at adress 2 = "); Serial.println(x);
   
    ReadString(5, x);
    for (byte i = 0; i < len; i++)
    {
      ssidd += eRead[i];
    }
    const char* ssid = ssidd.c_str();
    Serial.print("\t\tReaded ssid = "); Serial.println(ssid);
    x = ReadByte(3);
    Serial.print("\t\tValue of byte at adress 3 = "); Serial.println(x);
    ReadString(31, x);
    for (byte i = 0; i < len; i++)
    {
      passwordd += eRead[i];
    }
    const char* password = passwordd.c_str();
    Serial.print("\t\tReaded password = "); Serial.println(password);
    WiFi.disconnect();
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

// Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
//  server.on("/131220-2-4-33-L3/output", HTTP_GET, [] (AsyncWebServerRequest *request)
//  {},NULL,[](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
//    
//     String result = outputState(2)+outputState(4)+outputState(33);
//     Serial.println(result);
//    request->send(200, "application/json","{}");
//    });

  server.on(
   "/131220-2-4-33-L3/Login",
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request,uint8_t* data, size_t len, size_t index, size_t total) {
      String result;
      for (size_t i = 0; i < len; i++) {
        result += (char)data[i];
        //Serial.write(data[i]);
      }
      JSONVar myObject = JSON.parse(result);
       JSONVar keyObject = myObject.keys();
      for (int i = 0; i < keyObject.length(); i++) {
        JSONVar value = myObject[keyObject[i]];
        Serial.print(keyObject[i]);
        Serial.print(" = ");
        Serial.println(value);
      }
      if(myObject[keyObject[0]] == CodeId && myObject[keyObject[1]] == Password)
      {
        request->send(200, "application/json","{\"Status\" : True,\"Tocken\" : "+Tocken+"}");
      }
     //Serial.println(result);
     request->send(301, "application/json","{'Status' : 'False'}");
  });

  server.on(
   "/131220-2-4-33-L3/output",
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request,uint8_t* data, size_t len, size_t index, size_t total) {
 
      for (size_t i = 0; i < len; i++) {
        Serial.write(data[i]);
      }
 
     request->send(200, "application/json","{}");
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/131220-2-4-33-L3", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
       request->send(200, "text/plain", outputState(inputMessage1.toInt()));
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
      request->send(301, "text/plain","Fail");
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
  });

  // Start server
  server.begin();
}

void loop() {

}
