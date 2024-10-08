# Arduino Game Console
 A small game console for arduino + LED Matrices and joystick\
 Uses LedConrol library

 I have tried to make this as flexible as possible, more updates coming soon

# How to use
 If you want to try this for yourself, you can connect the display, joysticks and buttons wherever you want and toggle some variables in gameEngine.h  
 Then, you can try some of the preinstalled games or make your own. As of writing, the game engine is very basic and doesn't support image buffers yet, so your eyes may hurt a bit.

# Further developement
 Game engine is still being developed, upcoming features:
 - Image Buffer  
 - Image draw function that runs smoothly and effeciently

# What will *not* be added
 - Collision because of limited memory

# Documentation for engine

## Public Variables
#### Joystick structs

 The joystick structs (Joystick1 and Joystick2) contain several variables
 > `int buttonState`The current button state  
 > `bool buttonDown` 			 If the button is pressed  
 > `bool buttonUpThisFrame`  	 Was the button released this frame?  
 > `bool buttonDownThisFrame`	 Was the button pressed this frame?  
 > `float buttonDownDuration`	 How long has the button been pressed?  
 > `float x, y`					 Joystick's current x and y positions (from -1 to +1)  

Example

 ```c++
 if (engine.Joystick1.x > 0.5)
 {
	Serial.println("Up!");
 }
 ```

#### Other useful information
> `const int m_displayCount` The number of displays configured  
> `const int m_totalWidth` The number of pixels on the x  
> `const int deltaTime` The time in between this frame and the last few frames, averaged out  


###### As of version 0.0.2
