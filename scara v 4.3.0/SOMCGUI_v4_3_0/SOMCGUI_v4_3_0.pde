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
boolean f1;
Knob myKnobA;


String Datain;
int rec_count;
int distance;
int pos1;
int pos2;
int pos3;
int pos4;

int autorun;

int m1Speed;
int m2Speed;
int m3Speed;
int m4Speed;

void setup() { //same as arduino program


  frameRate(10);
  smooth();
  size(1500, 1500);    //window size, (width, height)

  printArray(Serial.list());   //prints all available serial ports

  port = new Serial(this, "COM3", 250000);  //i have connected arduino to com3, it would be different in linux and mac os
  port.bufferUntil('\n');
  //lets add buton to empty window

  cp5 = new ControlP5(this);
  font = createFont("TR Larabiefont", 20);    // custom fonts for buttons and title

  cp5.addButton("ZPLUS")     //"red" is the name of button
    .setPosition(500, 150)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;

  cp5.addButton("ZMINUS")     //"yellow" is the name of button

    .setPosition(500, 250)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("DISM")    //distance at 1000

    .setPosition(400, 150)  //x and y coordinates of upper left corner of button
    .setSize(70, 50)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("AUTORUN")    //distance at 1000

    .setPosition(250, 500)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("DISD")     //distance at 500

    .setPosition(400, 200)  //x and y coordinates of upper left corner of button
    .setSize(70, 50)      //(width, height)
    .setFont(font)
    ;

  cp5.addButton("DISC")     //distance at 100

    .setPosition(400, 250)  //x and y coordinates of upper left corner of button
    .setSize(70, 50)      //(width, height)
    .setFont(font)
    ;
    cp5.addButton("DISXT")     //distance at 100

    .setPosition(400, 300)  //x and y coordinates of upper left corner of button
    .setSize(70, 50)      //(width, height)
    .setFont(font)
    ;

  myKnobA = cp5.addKnob("knob")
    .setRange(0, 5000)
    .setValue(50)
    .setPosition(50, 500)
    .setRadius(50)
    .setDragDirection(Knob.VERTICAL)
    ;

  cp5.addButton("YPLUS")     //"blue" is the name of button
    .setPosition(650, 250)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("YMINUS")     //"alloff" is the name of button
    .setPosition(800, 250)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;

  cp5.addButton("XMINUS")     //"alloff" is the name of button
    .setPosition(800, 150)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("XPLUS")     //"blue" is the name of button
    .setPosition(650, 150)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;

  cp5.addButton("RYPLUS")     //"blue" is the name of button
    .setPosition(650, 350)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("RYMINUS")     //"alloff" is the name of button
    .setPosition(800, 350)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("HOMEPOS")     //"alloff" is the name of button
    .setPosition(850, 500)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("ABORT")     //"alloff" is the name of button
    .setPosition(400, 500)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("RECUP")     //"alloff" is the name of button
    .setPosition(550, 500)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
  cp5.addButton("RECDOWN")
    //"alloff" is the name of button
    .setPosition(700, 500)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      //(width, height)
    .setFont(font)
    ;
}
void knob(int theValue) {
  println(theValue);
  port.write('X');
  port.write(theValue);
}

void draw() {  //same as loop in arduino





  background(38, 38, 38); // background color of window (r, g, b) or (0 to 255)
  fill(200, 200, 200);
  rect(90, 120, 300, 300);


  //lets give title to our window
  fill(255, 255, 100);               //text color (r, g, b)
  textFont(font);
  text("MANUAL CONTROL", 80, 50);  // ("text", x coordinate, y coordinat)
  text("Make by Varis Vipavanich VAYO    IPRDEV.com", 500, 590);

  fill(0, 0, 0);
  text("CURRENT POSITION", 100, 140);  // ("text", x coordinate, y coordinat)
  fill(0, 0, 0);
  text("POS STEP 1 :", 100, 160);
  text("POS STEP 2 :", 100, 180);
  text("POS STEP 3 :", 100, 200);
  text("POS STEP 4 :", 100, 220);

  text(pos1, 250, 160);
  text(pos2, 250, 180);
  text(pos3, 250, 200);
  text(pos4, 250, 220);

  text("CURRENT SPEED", 100, 250);  // ("text", x coordinate, y coordinat)
  fill(0, 0, 0);
  text("SPEED STEP 1 :", 100, 270);
  text("SPEED STEP 2 :", 100, 290);
  text("SPEED STEP 3 :", 100, 310);
  text("SPEED STEP 4 :", 100, 330);

  text(m1Speed, 250, 270);
  text(m2Speed, 250, 290);
  text(m3Speed, 250, 310);
  text(m4Speed, 250, 330);


  text("Position :", 100, 380);
  text(rec_count, 250, 380);
  text("Distance to move :", 100, 400);
  text(distance, 300, 400);
  fill(255, 255, 255);
}
// data support from the serial port
void serialEvent( Serial port)
{
  // read the data until the newline n appears
  Datain = port.readStringUntil('\n');

  if (Datain != null)
  {
    Datain = trim(Datain);
    f1 = false;
    // break up the decimal and new line reading
    int[] Datains = int(splitTokens(Datain, ","));

    // we assign to variables
    rec_count =Datains[0];
    pos1 = Datains[1];
    pos2 = Datains[2];
    pos3 = Datains[3];
    pos4 = Datains[4];
    m1Speed = Datains[5];
    m2Speed = Datains[6];
    m3Speed = Datains[7];
    m4Speed = Datains[8];
    distance = Datains[9];
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
void AUTORUN() {
  port.write('A');
}
void RYPLUS() {
  port.write('U');
}
void RYMINUS() {
  port.write('I');
}
void DISM() {
  port.write('1');
}
void DISXT() {
  port.write('4');
}
void DISD() {
  port.write('2');
}
void DISC() {
  port.write('3');
}
void HOMEPOS() {
  port.write('B');
}
void RECUP() {
  port.write('M');
}
void RECDOWN() {
  port.write('N');
}

void ABORT() {
  port.write('J');
}
