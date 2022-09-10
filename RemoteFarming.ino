
#include <Adafruit_AHTX0.h>
#include <SoftwareSerial.h>



Adafruit_AHTX0 aht;
const int Photocell = A3;
const int Sck = A5;
const int Sda = A4;
const int Valve_LED = 5;
const int Temp_LED = 2;
const int Steam_LED = 3;
const int Light_LED = 4;
const String Phone = "+989375204907";
int Brightness;

boolean Automatic = true;
String Valveopen;


//Create software serial object to communicate with SIM800L
SoftwareSerial sim800(9, 10); //SIM800L Tx & Rx is connected to Arduino #9 & #10




void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit AHT10/AHT20 demo!");
  pinMode (Sck, INPUT);
  pinMode (Sda, INPUT);
  pinMode (Photocell, INPUT);
  pinMode (Temp_LED, OUTPUT);
  pinMode (Steam_LED, OUTPUT);
  pinMode (Light_LED, OUTPUT);
  pinMode (Valve_LED, OUTPUT);
  



  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }


  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  sim800.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  sim800.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  
  sim800.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  sim800.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived sms messages should be handled
  updateSerial();
}

void loop() {

      if (Automatic){
        Serial.println("Auto");
          Auto_control();
//          Reply("Automatic control is active");
        } else {
          Serial.println("Manual");
          

          Manual_control();
//          Reply("Manual control is active");
          }
 

}

void Auto_control (){
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Brightness = analogRead(Photocell);
//  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
//  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
//  Serial.print("Light: "); Serial.print(Brightness); Serial.println(" LMS");
  delay(1000);

  if (temp.temperature * 100 > 2800) {
    digitalWrite (Temp_LED, HIGH);
  } else {
    digitalWrite (Temp_LED, LOW);
  }
  if (Brightness < 35) {
    digitalWrite (Light_LED, HIGH);
  } else {
    digitalWrite (Light_LED, LOW);
  }
  if (humidity.relative_humidity * 100 > 4500) {
    digitalWrite (Steam_LED, HIGH);
  } else {
    digitalWrite (Steam_LED, LOW);
  }
  if (millis()%5000 <= 2000){

    digitalWrite(Valve_LED,HIGH);
  }
  else {
    digitalWrite(Valve_LED,LOW);
    }
    if (digitalRead(Valve_LED)){
      Valveopen = "Open";
      } else {
        Valveopen = "Close";
        }

    while(sim800.available()){
      String sms = sim800.readString();
      if (sms.indexOf(Phone)>-1){
        if (sms.indexOf("Status")>-1){
          
          Reply("Temp: " + String(temp.temperature) + " Celsius\n Humidity: " + String(humidity.relative_humidity) + " %\n " + "Light: " + String(Brightness) + " LMS\n Valve: " + Valveopen);
          
          } else if (sms.indexOf("Temp")>-1){
                Reply("Temp: " + String(temp.temperature) + " Celsius");
                } else if (sms.indexOf("Hum")>-1){
                  Reply("Humidity: " + String(humidity.relative_humidity) + " %");
                  } else if (sms.indexOf("Brightness")>-1){
                    Reply("Brightness: " + String(Brightness) + " LMS");
                    } else if (sms.indexOf("Valve")>-1){
                      Reply("Valve: " + Valveopen);
                      }
            else if (sms.indexOf("Manual")>-1){
              Automatic = false;
               Reply("Manual control is active");
              } 
        }

      
      }
    
  }

  void Manual_control(){
    while(sim800.available()){
      String sms = sim800.readString();
      if(sms.indexOf(Phone) > -1){
       if (sms.indexOf("HeaterON") > -1){
        digitalWrite(Temp_LED,HIGH);

        Reply("Heater is on");
        
        } else if (sms.indexOf("HeaterOFF")> -1){
           digitalWrite(Temp_LED,LOW);

                Reply("Heater is off");
                
          } else if (sms.indexOf("SteamON") >-1){
           digitalWrite(Steam_LED,HIGH);

                    Reply("Steam is on");
           
          } else if (sms.indexOf("SteamOFF")>-1){
           digitalWrite(Steam_LED,LOW);

                    Reply("Heater is off");
           
           } 
            else if (sms.indexOf("LightON")>-1){
              digitalWrite(Light_LED,HIGH);

                    Reply("Light is on");
                    
              }else if (sms.indexOf("LightOFF")>-1){
              digitalWrite(Light_LED,LOW);

                    Reply("Light is off");
              
              }else if (sms.indexOf("WaterON")>-1){
              digitalWrite(Valve_LED,HIGH);

                    Reply("Valve is open");
              
              }else if (sms.indexOf("WaterOFF")>-1){
              digitalWrite(Valve_LED,LOW);

                    Reply("Valve is closd");
              
              } else if (sms.indexOf("AllON")>-1){
                digitalWrite(Temp_LED,HIGH);
                digitalWrite(Steam_LED,HIGH);
                digitalWrite(Light_LED,HIGH);
                digitalWrite(Valve_LED,HIGH);

                    Reply("All tools are on");
                
                } else if (sms.indexOf("AllOFF")>-1){
                  digitalWrite(Temp_LED,LOW);
                digitalWrite(Steam_LED,LOW);
                digitalWrite(Light_LED,LOW);
                digitalWrite(Valve_LED,LOW);

                    Reply("All tools are off");
                
                  } else if (sms.indexOf("Auto")>-1){
                    Automatic = true;
                    Reply("Automatic control is active");
                    } 
      }
}
    }

  void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim800.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(sim800.available()) 
  {
    Serial.write(sim800.read());//Forward what Software Serial received to Serial Port
  }
}
void Reply(String text)
{
  sim800.println("AT+CMGF=1");
  updateSerial();
  sim800.println("AT+CMGS=\"+989375204907\"");
  updateSerial();
  sim800.print(text);
  updateSerial();
  sim800.write(26);
}
 
