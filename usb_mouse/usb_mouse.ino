#include <hidboot.h>
#include <usbhub.h>
#include <Servo.h>

// Servo s1;  // define servo names
// Servo s2;
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif
int x;  // mouse x
int y;  // mouse y
int y1;
int x1;
class MouseRptParser : public MouseReportParser {
protected:
  void OnMouseMove(MOUSEINFO *mi);
  void OnLeftButtonUp(MOUSEINFO *mi);
  void OnLeftButtonDown(MOUSEINFO *mi);
  void OnRightButtonUp(MOUSEINFO *mi);
  void OnRightButtonDown(MOUSEINFO *mi);
  void OnMiddleButtonUp(MOUSEINFO *mi);
  void OnMiddleButtonDown(MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi) {
  Serial.print(“x = “);
  x = (x + mi->dX);
  Serial.println(x);
  // x = constrain(x, -2000, 2000);
  // x1 = x;

  // x1 = map(x1, -2000, 2000, 5, 175);
  // s1.write(x1);
  Serial.print(“y = “);
  y = (y + mi->dY);
  Serial.println(y);
  // y = constrain(y, -2000, 2000);
  // y1 = y;

  // y1 = map(y1, -2000, 2000, 5, 175);
  // s2.write(y1);
};
void MouseRptParser::OnLeftButtonUp(MOUSEINFO *mi) {
  Serial.println(“L Butt Up”);
};
void MouseRptParser::OnLeftButtonDown(MOUSEINFO *mi) {
  Serial.println(“L Butt Dn”);
  // x = 5;
  // y = 5;
  // s1.write(5);
  // s2.write(5);
};
void MouseRptParser::OnRightButtonUp(MOUSEINFO *mi) {
  Serial.println(“R Butt Up”);
};
void MouseRptParser::OnRightButtonDown(MOUSEINFO *mi) {
  Serial.println(“R Butt Dn”);
  // x = 175;
  // y = 175;
  // s1.write(175);
  // s2.write(175);
};
void MouseRptParser::OnMiddleButtonUp(MOUSEINFO *mi) {
  Serial.println(“M Butt Up”);
};
void MouseRptParser::OnMiddleButtonDown(MOUSEINFO *mi) {
  Serial.println(“M Butt Dn”);
  // x = 90;
  // y = 90;
  // s1.write(90);
  // s2.write(90);
};

USB Usb;
USBHub Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE> HidMouse(&Usb);

uint32_t next_time;

MouseRptParser Prs;

void setup() {
  Serial.begin(9600);
  // s1.attach(44);  // attaches the servo on pin 44 to the servo
  // s2.attach(46);  // attaches the servo on pin 46 to the servo
  // s1.write(90);
  // s2.write(90);
#if !defined(__MIPSEL__)
  while (!Serial)
    ;  // Wait for serial port to connect – used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println(“Start”);

  if (Usb.Init() == -1)
    Serial.println(“OSC did not start.”);

  delay(200);

  next_time = millis() + 5000;

  HidMouse.SetReportParser(0, &Prs);
}

void loop() {
  Usb.Task();
}