Parts nedded: 
1- AHT10 or AHT20 Humidity & Temperature sensor 
(Connect SDA & SCK to A4 & A5 of Arduino or change Sck and Sda values in the code.)

2- Photocell or LDR
(Conncet to A3 of Arduino or change Photocell value in the code.)

3- Sim800 GSM Module 
(If you use SIM800C connect PWK to ground of arduino,
also connect Tx of sim800 to digital pin 9 and Rx to digital pin 10 of arduino or change the numbers in SofwareSerial line accordingly,
Be careful not to connect Rx & Tx to digital pin 0 or 1 cause you can't upload code in your board,
WARNING 1: Sim800 is a sensetive module, it needs between 4.0 and 4.2 V 2 A power supply to operate correctly. LM2596 can do good. Be careful no to damage module with overvoltage.
WARNING 2: Ground of SIM800 MUST be connected to Arduino's ground or it might not connect to the network.)

NOTE: To test, you might connect LEDs in different colors and connect in order to digital pins: 2, 3, 4, 5 or you can change values in the code.

How it works:
When you turn on the board, It automatically starts to change digital outputs according to Temperature, Humidity, Brightness & timer. You can switch to manual mode and turn on and off outputs using SMS yourself.
Also you can get report of current situation in Auto mode using SMS.

To use and test:
To change to Mnual mode, send "Manual" to sim card.
To change back to Auto, send "Auto:

In Auto mode:
To get all of the info, send "Status",
to get the temperature, send "Temp",
to get the humdity, send "Hum",
to get the Brighnessn send "Brightness",
To see if valve output (LED 5) is on, send "Valve"

In Manual Mode:

To control LED 2:
"HeaterON" turns on, "HeaterOFF" turns off

To control LED 3:
"SteamON" turns on, "SteamOFF" turns off

To control LED 4:
"LightON" turns on, "LightOFF" turns off

To control LED 5:
"WaterON" turns on, "WaterOFF" turns off


 