'''
Assignment 2:

Build a python code, Assume u get temperature and humidity values (generated 
with a random function to a variable) and write a condition to detect an
alarm in case of high temperature continuously.

DONE BY 

ROLLNO	: 911719104002

BRANCH	: Computer Science Engineering

COLLEGE	: MOUNT ZION COLLEGE OF ENGINEERING AND TECHNOLOGY

'''
#import the necessary package!
import requests
import random
from time import *
from statistics import mean

'Storing Temperature and Humidity in array'

temp = [];
hum = [];

pause = True;

while(pause):
    sleep(0.25);
    print("Analysis happens every 20 seconds");
    randomtemp = random.randint(0,70);
    randomhum = random.randint(0,100);
    print("Temperature =",randomtemp,"Humidity = ",randomhum);
    temp.append(randomtemp);
    hum.append(randomhum);
    if(len(temp) == 60 and len(hum) == 60 ):
        print("Average temperature is " + str( round(mean(temp))));
        print("Average Humidity is " + str( round( mean(hum))));
        'Room temperature analysis'
        if (mean(temp) > 50 ):
            print("\n\nKindly move to cooler place");
        elif (mean(temp) < 15):
            print("\n\nYour room temperature is too low");
        elif (mean(temp) > 15 and mean(temp) < 35 ):
            print("\n\nYour room temperature is Normal");
        elif (mean(temp) > 35 and mean(temp) < 50 ):
            print("\n\nYour room temperature is slightly hotter");
        'Room humidity analysis'
        if (mean(hum) < 30 ):
            print("\n\nYour room Humidity is Too Dry");
        elif (mean(hum) > 30 and mean(hum) < 60):
            print("Your room Humidity is Healthy");
        elif (mean(hum) > 60 and mean(hum) < 100 ):
            print("Your room Humidity is Not Healthy");
        temp = [];
        hum = [];
        
        sleep(5);
      
        
        
        
    
