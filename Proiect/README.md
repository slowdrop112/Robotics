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
So the Software Design is very practical and easy to understand. First of all we have got the libraries Wire.h and LiquidCrystal.h. 
<h2>The Wire.h library </h2>
is used to communicate with the Inter-integrated Circuit, and it facilitates communication between the Arduino and peripherals connected, like sensors or displays.
  
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



