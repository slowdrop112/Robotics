<h1 align = "center" > Gas Detector </h1>

<p>
<h2>Introduction</h2>
So basically, this system determines whether the sensor detects gas or not :).
It works like all the other gas detectors. If gas is not detected, the system is in the "initial" mode, and by initial mode, I mean that the LED is turned off, and the buzzer doesn't make any sound.
But when gas is detected, the buzzer starts making noise, and the LED starts flickering a red light, something like a warning alarm, and at the same time, on the LCD it is showed a warning message.

<p> </p> 
The idea of making a Gas Detector actually came when I was lighting up some coal blocks, and the gas detector started going crazy. And after that, I thought, it is something kind of easy to do, but it's a must-have in everyone's kitchen. 

<p> </p> 
I really think that this system is very useful, a lifesaver I could say, because most of the time, you can't detect all the gas leaks, and if not detected, everyone could blow up :/
</p>


<p>
<h2>Block Scheme</h2>
  
![alt text](https://github.com/slowdrop112/Robotics/blob/main/Photos/block_scheme.png)
  
</p>


<p>
<h2>Hardware Design</h2>

| Number  | Name | Where from |
| :--- | :---: | ---: |
| 1  | Arduino Uno  | LAB |
| 1  | Breadboard  | LAB |
| 1  | Buzzer | LAB| 
| 1  | Mq7 Gas Detector  | [MQ7 SENSOR](https://www.sigmanortec.ro/Senzor-Gaz-MQ-7-Monoxid-carbon-p126101575) |
| 1  | Green LED  | LAB |
| lots  | Wires  | LAB |
| 2  | 220 Ω resistor  | LAB |
| 1  | Breadboard  | LAB | 
| 1  | LCD  | LAB |


<h2>Electrical Scheme</h2>

![alt text](https://github.com/slowdrop112/Robotics/blob/main/Photos/scheme.png)

![alt text](https://github.com/slowdrop112/Robotics/blob/main/Photos/circuit.jpeg)


## Hardware description

### 1. Microcontroller: ATmega328P
* Digital Pin: For LED control, buzzer, and LCD
* Analog Pin: For MQ7 Sensor
* Frequence: 16 MHz
* Power: 5V through USB
  
### 2. Sensor: MQ7
* Type: Analog
* Pin: analog A0
* Power: 5V
* Functionality: Sends an analogic value that's like the detected temperature

### 3.LED
* Pin: digital 6
* Functionality: It indicates whether the system detects gas or not
* Consumption: ~20 mA.

### 4. Buzzer
* Pin : digital 7
* Functionality: It emits a sound for alerts when it detects gas
* Consumption: ~30 mA.


### 5. LCD 16X2
* Type: Character Display
* Pins: 2,3,4,5,11,12
* Functionality: It displays the system data
* Consumption: ~50-100 mA.

### Overall Functionality
So the MQ7 sensor sends analog data to the A0 pin of the Arduino Uno. Then, the LCD displays a message like " !WARNING! GAS DETECTED", and the buzzer and the LED are activated too.

### Overall Consumption
* LED: ~20 mA
* BUZZER: ~30 mA
* LCD: ~20-100 mA
* MQ7 GAS SENSOR: <5mA
* TOTAL:  ~150-200 mA



</p>


<p>
<h2>Software Design</h2>
So the Software Design is very practical and easy to understand. First of all we have got the libraries Wire.h and LiquidCrystal.h. We've got a buzzer and a LED, that work simultaneously.The sensor send analog data, and I have tested out a lot of cases with a possible "Gas leak" we've got 3 levels of detections. First levele, no gas detected or a pointless amount of gas detected that could do no harm, and it displays the level of gas detected and the message "SAFE for now". The next level detect an amount of gas that if haven't realized that is a leak, in some time it could do some damage, and it displays the level of CO, the message says " !WARNING! ", and now the buzzer and the LED start doing some work, because they turn on and off, so that you could see, or maybe for someone blind, hear, that there is something wrong. And for the final level of gas detection, the one that could blow up everything in moments, it displays the CO levels still, the message " DANGER HIGH " pops up, and the incredible duo, the buzzer and the LED now turn on and off at double the speed of the  previous level. 
<h4>The Wire.h library </h4>
is used to communicate with the Inter-integrated Circuit, and it facilitates communication between the Arduino and peripherals connected, like sensors or displays.
<h4>The LiquidCrystal.h library</h4>
is used to control standard character LCD displays that use the Hitachi HD44780 driver(or a compatible one). It provides functions to send text, control the cursor, and manage the display.
<p> </p>
<h3>Interaction With The Code</h3>
So the LiquidCrystal.h library is crucial for this code, because without it, it wouldn't be so practical and the CO levels would be shown only in the terminal.
<p></p>
The Wire.h is as crucial as the other library, because this library communicates with the MQ7 Gas Sensor. So these to are like a a bike. Without one, the other one would be useless.
  
</p>



<p>
<h2>Results</h2>
  <h1></h1>
</p>


<p>
<h2>Inspiration</h2>
  
[I2C VS SPI](https://forum.arduino.cc/t/spi-vs-i2c-display-interface/527963)

[MQ SENSORS](https://robocraze.com/blogs/post/mq-series-gas-sensor)

[INSPO FOR BLOCK SCHEME](https://docs.google.com/drawings/d/1UpxRyJNfczJHhNRvWdeb5kh_7IEUy5173odk93W_GSA/edit)

</p>



