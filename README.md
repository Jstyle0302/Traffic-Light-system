# Traffic-Light-system
Use computer vision technology to detect the cars and pedestrians and help to flip the traffic light signal.

Cloud Computing: Microsoft Azure- Computer Vision  
Environment: Visual Studio 2017, Arduino IDE  
Language: Python3(Opencv3.0), Arudino  
Hardware: Arduino Uno  
Date: 2018/4/1

## The controller
Step1: We will use the camera to catch the frame in front and send to the Azure to help us do the cloud computing.  
Step2: The Azure will return the tags information about the frame for us.  
Step3: After get the tags, we can send the message for the Arduino and control the condition the traffic light.  
Step4: Repeat to the Step1.  


## The traffic light
We set the Red, Yellow and Green light at the pin13, 12, 11.  
The pin 2-7 is connected with the seven segment light.
