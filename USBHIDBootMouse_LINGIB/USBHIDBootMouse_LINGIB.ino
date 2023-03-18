// USB
#include <usbhub.h>
USB     Usb;
USBHub     Hub(&Usb);

// Human Interface Device
#include <hidboot.h>
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

// SPI
#include <SPI.h>

// Mouse variables
int dx;
int dy;
int X = 0;
int Y = 0;

// ----- Mouse Report Parser
class MouseRptParser : public MouseReportParser
{
  protected:
    void OnMouseMove  (MOUSEINFO *mi);
    void OnLeftButtonUp (MOUSEINFO *mi);
    void OnLeftButtonDown (MOUSEINFO *mi);
    void OnRightButtonUp  (MOUSEINFO *mi);
    void OnRightButtonDown  (MOUSEINFO *mi);
    void OnMiddleButtonUp (MOUSEINFO *mi);
    void OnMiddleButtonDown (MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
  // ----- Code by LINGIB
  int dx = mi->dX;
  int dy = mi->dY;
  X += dx;
  Y += dy;

  Serial.print("dx=");
  Serial.print(dx);
  Serial.print(" dy=");
  Serial.print(dy);
  Serial.print(" X=");
  Serial.print(X);
  Serial.print(" Y=");
  Serial.println(Y);

  //    // ----- Original code
  //    Serial.print("dx=");
  //    Serial.print(mi->dX, DEC);
  //    Serial.print(" dy=");
  //    Serial.println(mi->dY, DEC);
};
void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi)
{
  Serial.println("L Butt Up");
};
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi)
{
  Serial.println("L Butt Dn");
};
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi)
{
  Serial.println("R Butt Up");
};
void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi)
{
  Serial.println("R Butt Dn");
};
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi)
{
  Serial.println("M Butt Up");
};
void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi)
{
  Serial.println("M Butt Dn");
};
MouseRptParser                               Prs;

// -----------------
//  setup()
// -----------------
void setup()
{
  // Serial port
  Serial.begin( 115200 );

  // Inititialise USB card
  Usb.Init();
  HidMouse.SetReportParser(0, &Prs);

  // Clear mouse variables
  Serial.println("Mouse Ready");
  X = 0;
  Y = 0;
}

// -----------------
//  loop()
// -----------------
void loop()
{
  Usb.Task();
}
