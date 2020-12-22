# Haptic Breath Guide

![Img](https://github.com/tk2325/haptic-breath/blob/master/header-img-2.jpg)
![Img](https://github.com/tk2325/haptic-breath/blob/master/header-img-1.jpg)
<br><br>

**_This is an ongoing, open-source project._**
<br>

This project was a wearable art piece designed for my undergraduate thesis at NYU. It is face masks with embedded electronics that allow you to stay connected with your friends and loved ones. Both face masks contain a breath sensor at the front and a vibrating motor that wraps around the back of each wearer’s neck. As one person breathes in and out, the haptic motor vibrates on the other person's end, and vice versa. The wearable is meant to be integrated into each wearer’s day-to-day routine. The haptic messages delivered via a BLE connection provides a sense of presence for the other person on the other side. The breathing was chosen as to make the experience of embodiment more intimate and less of a structured interaction. Using the form of a face mask, the project is in dialogue with our current state of social distancing practice due to COVID-19, not just as an artifact but also as a product of the pandemic.


## Materials Used

- [Arduino Nano 22 BLE](https://store.arduino.cc/usa/nano-33-ble)
- [NPN Bipolar Transistors (PN2222)](https://www.adafruit.com/product/756)
- [Vibrating Mini Motor Discs](https://www.adafruit.com/product/1201)
- [1N4001 Diodes](https://www.adafruit.com/product/755)
- [Air Quality Sensor Breakouts (VOC and eCO2)](https://www.adafruit.com/product/3709)
- [3 x AAA Battery Holders](https://www.adafruit.com/product/727)
- [20mm Coin Cell Breakout Board (CR2032)](https://www.adafruit.com/product/1870)
- CR2032 Lithium Coin Cell Battery
- Black Spandex Legging Fabric
- Patterned Giftwrap Paper
- Double-Sided Sequins
- Vibration Motors
- Black Wire
- Yarn

## Breadboard Setup

![Img](https://github.com/tk2325/haptic-breath/blob/master/instruct-img/fritz.png)
![Img](https://github.com/tk2325/haptic-breath/blob/master/instruct-img/full-assembly.jpg)

## Code

**_Arduino libraries used_**
- [ArduinoBLE](https://www.arduino.cc/en/Reference/ArduinoBLE)
- [Adafruit_SGP30](https://github.com/adafruit/Adafruit_SGP30)
```c
#include <ArduinoBLE.h>
#include <Adafruit_SGP30.h>
```
<br>

**_BLE advertising setup_**
```c
  BLE.begin();
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  BLE.setAdvertisedService(hapticService);
  hapticService.addCharacteristic(hapticCharacteristic);
  BLE.addService(hapticService);
  hapticCharacteristic.writeValue(0);
  BLE.advertise();
```
<br>

**_BLE characteristic read and write loop_**

```c
  while (connected()) {
    breath_sensor.IAQmeasureRaw();
    breathe_val = breath_sensor.rawH2;

    if(calibrator_counter > 100) {
      initial_value = breathe_val;
      calibrator_counter = 0;
    }

    calibrator_counter = calibrator_counter + 1;
    
      if (breathe_val < initial_value - 100) {
        hapticCharacteristic.writeValue((byte)0x01);
        
      } else {
        hapticCharacteristic.writeValue((byte)0x00);
      }
      
    if (hapticTalkCharacteristic.written()) {
        if (hapticTalkCharacteristic.value()) {
          digitalWrite(hapticPin, HIGH);

        } else {
          digitalWrite(hapticPin, LOW);

        }
     }
  }
```


## Mask Assembly


This [tutorial](https://www.cdc.gov/coronavirus/2019-ncov/prevent-getting-sick/how-to-make-cloth-face-covering.html) by the Centers for Disease Control and Prevention (CDC) helps illustrate how to sew your own mask.
 

![Img](https://github.com/tk2325/haptic-breath/blob/master/instruct-img/sketch.png)
![Img](https://github.com/tk2325/haptic-breath/blob/master/instruct-img/materials.png)
![Img](https://github.com/tk2325/haptic-breath/blob/master/instruct-img/final-assembly.jpg)



## Demo

- [Video demo](https://youtu.be/656ncj0uiaQ)
- [Image series](https://github.com/tk2325/haptic-breath/tree/master/image-series)

![Img](https://github.com/tk2325/haptic-breath/blob/master/image-series/IMG_3161.JPG)
![Img](https://github.com/tk2325/haptic-breath/blob/master/image-series/IMG_3169.JPG)
![Img](https://github.com/tk2325/haptic-breath/blob/master/image-series/IMG_3186.JPG)
![Img](https://github.com/tk2325/haptic-breath/blob/master/image-series/IMG_3342.JPG)
![Img](https://github.com/tk2325/haptic-breath/blob/master/image-series/IMG_3324.JPG)
![Img](https://github.com/tk2325/haptic-breath/blob/master/image-series/IMG_3360.JPG)

## Credits
- **Creator:** Thomas Knoepffler <br>
- **Advisor:** Scott Fitzgerald <br>
- **Program:** Integrated Digital Media, NYU <br>
- **Semester:** Fall 2020