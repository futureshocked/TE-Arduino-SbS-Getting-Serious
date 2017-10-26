import processing.serial.*;

 // Magnetometer sketch
 
 // This program creates a simple bar graph
 // by getting data from a magnetometer running on
 // an Arduino. 
 
 // Created 15 June 2014
 // by Peter Dalmaris
 // This example code is in the public domain.
 
 import processing.serial.*;
 
 Serial myPort;        // The serial port
 int cycles = 0;
 
 void setup () {
 // set the window size:
 size(250, 400);      

 myPort = new Serial(this, "/dev/tty.usbmodem3d11", 9600);
 // don't generate a serialEvent() unless you get a newline character:
 myPort.bufferUntil('\n');
 // set inital background:
 background(0);
 }
 void draw () {
 // everything happens in the serialEvent()
 }
 
 void serialEvent (Serial myPort) {
   // get the ASCII string:
   String inString = myPort.readStringUntil('\n');
   print("inString:");
   print(inString);
   if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    String[] q = splitTokens(inString,",");
 
    if (q.length == 3) {
       // convert to an int and map to the screen height:
       float x = float(q[0]);
       float y = float(q[1]);
       float z = float(q[2]);

       x = map(x, 0, 1024, 0, height);
       y = map(y, 0, 1024, 0, height);
       z = map(z, 0, 1024, 0, height);

       stroke(204, 102, 0);
       fill(153);
       rect(30, height/2, 55, x);
       fill(204, 102, 0);
       rect(90, height/2, 55, y);
       fill(204, 102, 100);
       rect(150, height/2, 55, z);
  
       if (cycles >= 10) {
         cycles = 0;
         background(0); 
       }
       cycles++;
     }
   }
 }
