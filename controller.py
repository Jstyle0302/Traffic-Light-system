import serial
from time import sleep
import cv2
import requests

#connect the arduino, please set the port number as your actual number
s=serial.Serial("COM5",9600)

#You can get a free key here for your try
#https://azure.microsoft.com/en-us/try/cognitive-services/

subscription_key = "PLEASE_TYPE_YOUR_KEY_HERE"
assert subscription_key

#set the request format
vision_base_url = "https://eastasia.api.cognitive.microsoft.com/vision/v1.0/"
vision_analyze_url = vision_base_url + "analyze"
headers  = {'Ocp-Apim-Subscription-Key': subscription_key ,'Content-Type':'application/octet-stream'}
params   = {'visualFeatures': 'Tags'}

cap = cv2.VideoCapture(1)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    cv2.imshow('frame',frame)
	# encode image as jpeg
    _, img = cv2.imencode('.jpg', frame)
    
	#request the tag label
	response = requests.post(vision_analyze_url, headers=headers, params=params, data=img.tostring())
    response.raise_for_status()
    analysis = response.json()
    image_analysis = analysis["tags"]
    search_list = {"man","person","woman"}
    
	#when something wrong, break
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
	
	#check whether the target object is close
    flag = 0
    for idx in range(len(image_analysis)):
        if(image_analysis[idx]["name"] in search_list):
            print(image_analysis[idx])
            flag = 1
			
    #send the information for the Arduino
	if(flag):
        s.write('H'.encode())
        sleep(4.5)
    else:
        s.write('L'.encode())
        sleep(4.5)
		
	#use for test the result
    print(image_analysis)
    
    
    

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()