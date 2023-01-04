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


  frameRate(10);
  smooth();
  size(700, 600);    //window size, (width, height)

  printArray(Serial.list());   //prints all available serial ports

  port = new Serial(this, "COM4", 115200);  //i have connected arduino to com3, it would be different in linux and mac os

  //lets add buton to empty window

  cp5 = new ControlP5(this);
  font = createFont("TR Larabiefont", 20);    // custom fonts for buttons and title

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
     cp5.addButton("REC")     //"alloff" is the name of button
    .setPosition(250, 500)  //x and y coordinates of upper left corner of button
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
}

float cnt;

void draw() {  //same as loop in arduino

  String Datain = "";
  String sAry[];
  int pos1;
  int pos2;
  int pos3;
  int pos4;

  int codex;
  while ( port.available() > 0) {  // If data is available,
    if (Datain == null) break;
    Datain = port.readString();

    Datain = trim(Datain);

    sAry = split(Datain, ",");
    if (sAry.length==6 && sAry[1].equals("A")&&sAry[6].equals("Z"))
    {

      pos1 = parseInt(sAry[1]);
      pos2 = parseInt(sAry[2]);
      pos3 = parseInt(sAry[3]);
      pos4 = parseInt(sAry[4]);
    }
  }
  codex = port.read();
  if (codex == '1') {
    fill(255, 0, 0);
    circle(100, 150, 30);
  }
  if (codex == '0') {

    fill(255, 165, 0);
    circle(100, 150, 30);
  }
  background(53, 92, 125); // background color of window (r, g, b) or (0 to 255)
  fill(0, 0, 0);
  rect(90, 80, 300, 30);
  //lets give title to our window
  fill(255, 255, 100);               //text color (r, g, b)
  textFont(font);
  text("MANUAL CONTROL", 80, 50);  // ("text", x coordinate, y coordinat)
  text("CURRENT POSITION", 80, 70);  // ("text", x coordinate, y coordinat)
  text(Datain, 100, 100);
  fill(255, 255, 255);


  delay(10);
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

void REC() {
  port.write('M');
}
void ABORT() {
  port.write('J');
}
