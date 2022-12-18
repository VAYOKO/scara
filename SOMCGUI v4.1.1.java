import controlP5.*; //import ControlP5 library
import processing.serial.*;

Serial port;
int incomingser;
Slider2D s;
int pos;
int posx;
int posy;
ControlP5 cp5; //create ControlP5 object
PFont font;
boolean f1 = false;
void setup() { //same as arduino program



  smooth();
  size(1000, 700);    //window size, (width, height)

  printArray(Serial.list());   //prints all available serial ports

  port = new Serial(this, "COM3", 115200);  //i have connected arduino to com3, it would be different in linux and mac os

  //lets add buton to empty window

  cp5 = new ControlP5(this);
  font = createFont("calibri light bold", 20);    // custom fonts for buttons and title

  cp5.addButton("ZPLUS")     //"red" is the name of button
    .setPosition(200, 150)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;

  cp5.addButton("ZMINUS")     //"yellow" is the name of button

    .setPosition(200, 250)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;


  cp5.addButton("YPLUS")     //"blue" is the name of button
    .setPosition(350, 250)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("YMINUS")     //"alloff" is the name of button
    .setPosition(500, 250)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;

  cp5.addButton("XMINUS")     //"alloff" is the name of button
    .setPosition(500, 150)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("XPLUS")     //"blue" is the name of button
    .setPosition(350, 150)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;

  cp5.addButton("RYPLUS")     //"blue" is the name of button
    .setPosition(350, 350)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("RYMINUS")     //"alloff" is the name of button
    .setPosition(500, 350)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("HOMEPOS")     //"alloff" is the name of button
    .setPosition(500, 500)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("ABORT")     //"alloff" is the name of button
    .setPosition(100, 500)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;

  cp5.addSlider2D("pos")
    .setPosition(700, 300)
    .setSize(400, 200)
    .setMinMax(-120, -120, 120, 120)
    .setValue(0, 0)
    ;

  cp5.addKnob("speed")
    .setPosition(700, 135)
    .setRadius(60)
    .setRange(10, 60)
    .setValue(50)
    ;
}

float cnt;
void draw() {  //same as loop in arduino




  background(53, 92, 125); // background color of window (r, g, b) or (0 to 255)

  //lets give title to our window
  fill(255, 255, 100);               //text color (r, g, b)
  textFont(font);
  text("MANUAL CONTROL", 80, 30);  // ("text", x coordinate, y coordinat)





  if ( port.available() > 0) {  // If data is available,
    incomingser = port.read();  // read it and store it in val
  }
}



//lets add some functions to our buttons
//so whe you press any button, it sends perticular char over serial port

void ZPLUS() {
  port.write('Q');
}

void ZMINUS() {
  port.write('W');
}

void XPLUS() {
  port.write('E');
}
void XMINUS() {
  port.write('R');
}

void YPLUS() {
  port.write('K');
}
void YMINUS() {
  port.write('Y');
}



void RYPLUS() {
  port.write('U');
}
void RYMINUS() {
  port.write('I');
}

void HOMEPOS() {
  port.write('B');
}

void ABORT() {
  port.write('J');
}
