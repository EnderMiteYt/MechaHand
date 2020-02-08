#include <Servo.h>
#include <SoftwareSerial.h>

#define hand_pin 2
#define hand_servo_pin 3
#define servo1_pin 4
#define servo2_pin 5
#define pot1_pin 14
#define pot2_pin 15
#define pot3_pin 16
#define pot4_pin 17
#define bt_rx_pin 10
#define bt_tx_pin 11
#define pot_mode 0
#define serial_mode 1
#define auto_mode 1
SoftwareSerial Bluetooth(bt_rx_pin, bt_tx_pin);
Servo hand, hand_servo, servo1, servo2;

String bt_cmd;
char bt_Cmd;
int bt_Int;
void setup()
{
  Bluetooth.begin(9600);
  Serial.begin(9600);
  
  hand.attach(hand_pin);
  hand_servo.attach(hand_servo_pin);
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  hand.write(180);
  hand_servo.write(0);
  servo1.write(0);
  servo2.write(0);
  
  if (serial_mode == 1)
  {
    Serial.println("---------------------------- Режим монитора порта ----------------------------");
    Serial.println("---------------------------- Запуск блютуза ----------------------------");
    Bluetooth.print("AT\r\n");
    Bluetooth.print("AT\r\n");
    Bluetooth.print("AT\r\n");
 
    while (Bluetooth.available()) Serial.println(Bluetooth.read());
    Serial.write("Если тут не все значения OK значит возникла ошибка (код 53)");
  }
  Bluetooth.println("Привет");
}

void loop()
{
  if (Serial.available())
  {
    delay(50);

    while (Serial.available() && (serial_mode == 1))
    {
      bt_Cmd = Serial.read();
      bt_Int = Serial.parseInt();
      
      if (bt_Cmd == 'A')
        if (bt_Int == 1) {
          hand.write(0);
          Serial.println("Клешня открыта");
        }
      if (bt_Int  == 2) {
        hand.write(180);
        Serial.println("Клешня закрыта");
      }
      if (bt_Cmd  == 'B') {
        hand_servo.write(bt_Int);
        Serial.println("B Сервопривод повёрнут на " + (String)bt_Int);
      }
      if (bt_Cmd  == 'C') {
        servo1.write(bt_Int);
        Serial.println("C Сервопривод повёрнут на " + (String)bt_Int);
      }
      if (bt_Cmd  == 'D') {
        servo2.write(bt_Int);
        Serial.println("D Сервопривод повёрнут на " + (String)bt_Int);
      }
    }
    
  }

  if(Bluetooth.available())
  {
    delay(50);
    
    while (Bluetooth.available())
    {
      bt_Cmd = Bluetooth.read();
      bt_Int = Bluetooth.parseInt();
      
      if (bt_Cmd == 'A')
        if (bt_Int == 1) {
          hand.write(0);
          Bluetooth.println("Клешня открыта");
        }
      if (bt_Int  == 2) {
        hand.write(180);
        Bluetooth.println("Клешня закрыта");
      }
      if (bt_Cmd  == 'B') {
        hand_servo.write(bt_Int);
        Bluetooth.println("B Сервопривод повёрнут на " + (String)bt_Int);
      }
      if (bt_Cmd  == 'C') {
        servo1.write(bt_Int);
        Bluetooth.println("C Сервопривод повёрнут на " + (String)bt_Int);
      }
      if (bt_Cmd  == 'D') {
        servo2.write(bt_Int);
        Bluetooth.println("D Сервопривод повёрнут на " + (String)bt_Int);
      }
    }
    if (pot_mode == 1)
    {
      //    hand.write(analogRead(pot1_pin));
      hand_servo.write(analogRead(pot2_pin));
      servo1.write(analogRead(pot3_pin));
      servo2.write(analogRead(pot4_pin));
      Serial.println((String)analogRead(pot2_pin) + " " + (String)analogRead(pot3_pin) + "  " + (String)analogRead(pot4_pin));
    }
    while (Bluetooth.available()) Serial.print((char)Bluetooth.read());
  }


}
