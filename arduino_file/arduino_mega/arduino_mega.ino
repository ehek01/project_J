//Change the file extension from *.txt to *.ino//
/////////////////////////////////////////////////////////////////////////////
//                                           //                            //
// ⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢠⣴⣾⣿⣶⣶⣆⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀⢀  //                            //
// ⢀⢀⢀⣀⢀⣤⢀⢀⡀⢀⣿⣿⣿⣿⣷⣿⣿⡇⢀⢀⢀⢀⣤⣀⢀⢀⢀⢀⢀  //                            //
// ⢀⢀ ⣶⢻⣧⣿⣿⠇ ⢸⣿⣿⣿⣷⣿⣿⣿⣷⢀⢀⢀⣾⡟⣿⡷⢀⢀⢀⢀ //                            //
// ⢀⢀⠈⠳⣿⣾⣿⣿⢀⠈⢿⣿⣿⣷⣿⣿⣿⣿⢀⢀⢀⣿⣿⣿⠇⢀⢀⢀⢀  //                            //
// ⢀⢀⢀⢀⢿⣿⣿⣿⣤⡶⠺⣿⣿⣿⣷⣿⣿⣿⢄⣤⣼⣿⣿⡏⢀⢀⢀⢀⢀  //                            //
// ⢀⢀⢀⢀⣼⣿⣿⣿⠟⢀⢀⠹⣿⣿⣿⣷⣿⣿⣎⠙⢿⣿⣿⣷⣤⣀⡀⢀⢀  //                            //
// ⢀⢀⢀ ⢸⣿⣿⣿⡿⢀⢀⣤⣿⣿⣿⣷⣿⣿⣿⣄⠈⢿⣿⣿⣷⣿⣿⣷⡀⢀ //                            //
// ⢀⢀⢀⣿⣿⣿⣿⣷⣀⣀⣠⣿⣿⣿⣿⣷⣿⣷⣿⣿⣷⣾⣿⣿⣿⣷⣿⣿⣿⣆ //                            //
// ⣿⣿⠛⠋⠉⠉⢻⣿⣿⣿⣿⡇⡀⠘⣿⣿⣿⣷⣿⣿⣿⠛⠻⢿⣿⣿⣿⣿⣷⣦ //                            //
// ⣿⣿⣧⡀⠿⠇⣰⣿⡟⠉⠉⢻⡆⠈⠟⠛⣿⣿⣿⣯⡉⢁⣀⣈⣉⣽⣿⣿⣿⣷ //                            //
// ⡿⠛⠛⠒⠚⠛⠉⢻⡇⠘⠃⢸⡇⢀⣤⣾⠋⢉⠻⠏⢹⠁⢤⡀⢉⡟⠉⡙⠏⣹ //                            //
// ⣿⣦⣶⣶⢀⣿⣿⣿⣷⣿⣿⣿⡇⢀⣀⣹⣶⣿⣷⠾⠿⠶⡀⠰⠾⢷⣾⣷⣶⣿ //                            //
// ⣿⣿⣿⣿⣇⣿⣿⣿⣷⣿⣿⣿⣇⣰⣿⣿⣷⣿⣿⣷⣤⣴⣶⣶⣦⣼⣿⣿⣿⣷ //                            //
//                                           //                            //
/////////////////////////////////////////////////////////////////////////////
// Make    : Kim Dong Hun             //                            ⠀      //
// Update  : KR 2021/03/22 21:23      //                                   //
// E-Mail  : 112303dh@naver.com       //                                   //
// Develope Tool :                    //                                   //
// Visual Stduio Code                 //                                   //
/////////////////////////////////////////////////////////////////////////////

// 0_Car
String Car_status = "0"; //자동:시리얼받아옴
int Car_max_speed = 255;
int Car_speed = 0;

// Bluetooth
String bt_status = "0"; //수동:블루투스받아옴
int enable_auto = 1;    //

// 1_Motor
int ASpeed = 2;
int ALeft = 22;
int ARight = 23;
int BRight = 24;
int BLeft = 25;
int BSpeed = 3;

// 2_LineSensor

// 3_BlockSensor
int enable_block = 0; //자동+수동:속도조절
int distance = 0;
int triggerPin = 52;
int echoPin = 53;
int bPin = 11;

long delay1 = 2000;
long lTime = 0;

// 4_DEBUG_SERIAL

void _0_Controll(void)
{
    //수동조작시 값받아옴
    if (Serial1.available())
    {
        Car_status = _4_readSerial1();
    }

    if (Serial.available())
    {
        Car_status = _4_readSerial();
    }

    switch (Car_status.toInt())
    {
    case -2:
        //수동조작:거리센서
        enable_block = !(enable_block);
        Car_status = "0";
        break;
    case -1:
        //수동조작:auto켜기
        enable_auto = !enable_auto;
        if (enable_auto)
        {
            tone(bPin, 300, 100);
        }
        else if (!enable_auto)
        {
            tone(bPin, 400, 100);
        }
        Car_status = "0";
        break;
    case 1:
        _1_Go(Car_speed);
        break;
    case 2:
        _1_Stop();
        break;
    case 3:
        _1_Back(Car_speed);
        break;
    case 4:
        _1_Left(Car_speed);
        break;
    case 5:
        _1_Right(Car_speed);
        break;
    case 6:
        if (Car_speed - 10 >= 0)
        {
            Car_speed -= 10;
        }
        break;
    case 7:
        if (Car_speed + 10 <= Car_max_speed)
        {
            Car_speed += 10;
        }
        break;
    case 8:
        Car_speed = Car_max_speed;
        break;
    }
}

void _1_Stop(void)
{
    digitalWrite(ALeft, HIGH);
    digitalWrite(ARight, LOW);
    analogWrite(ASpeed, 0);
    digitalWrite(BLeft, HIGH);
    digitalWrite(BRight, LOW);
    analogWrite(BSpeed, 0);
}
void _1_Go(int speed)
{
    digitalWrite(ALeft, HIGH);
    digitalWrite(ARight, LOW);
    analogWrite(ASpeed, speed);
    digitalWrite(BLeft, HIGH);
    digitalWrite(BRight, LOW);
    analogWrite(BSpeed, speed);
}
void _1_Back(int speed)
{
    digitalWrite(ALeft, LOW);
    digitalWrite(ARight, HIGH);
    analogWrite(ASpeed, speed);
    digitalWrite(BLeft, LOW);
    digitalWrite(BRight, HIGH);
    analogWrite(BSpeed, speed);
}
void _1_Right(int speed)
{
    digitalWrite(ALeft, HIGH);
    digitalWrite(ARight, LOW);
    analogWrite(ASpeed, speed);
    digitalWrite(BLeft, LOW);
    digitalWrite(BRight, HIGH);
    analogWrite(BSpeed, speed);
}
void _1_Left(int speed)
{
    digitalWrite(ALeft, LOW);
    digitalWrite(ARight, HIGH);
    analogWrite(ASpeed, speed);
    digitalWrite(BLeft, HIGH);
    digitalWrite(BRight, LOW);
    analogWrite(BSpeed, speed);
}
void _2_Line(void)
{
}
void _3_Block_Sensor(void)
{
    // trigger 핀으로 10㎲의 펄스를 발생
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    // echo 핀 입력으로부터 거리를 cm 단위로 계산
    distance = pulseIn(echoPin, HIGH) / 58.2;
    if (distance < 50)
    {
        Car_speed = Car_max_speed * 0;
        delay1 = 50;
    }
    else if (distance < 100)
    {
        Car_speed = Car_max_speed / 2.5;
        delay1 = 100;
    }
    else if (distance < 150)
    {
        Car_speed = Car_max_speed / 1.5;
        delay1 = 300;
    }
    else
    {
        Car_speed = Car_max_speed;
        delay1 = 1000;
    }

    if (millis() - lTime > delay1)
    {
        lTime = millis();
        tone(bPin, 330, 100);
    }
}
String _4_readSerial(void)
{
    String str = "";
    char ch;
    while (Serial.available() > 0)
    {
        ch = Serial.read();
        if (ch != '\n')
        {
            str.concat(ch);
            Serial.print("Serial : ");
            Serial.println(str);
        }
        delay(10);
    }
    return str;
    //return ch.toInt();
}
String _4_readSerial1(void)
{
    String bstr = "";
    char bch;
    while (Serial1.available() > 0)
    {
        bch = Serial1.read();
        if (bch != '\n')
        {
            bstr.concat(bch);
            Serial.print("Serial1 : ");
            Serial.println(bstr);
        }
        delay(10);
    }
    return bstr;
}
void setup()
{
    // 0_Car
    Serial1.begin(9600);
    // 1_Motor
    pinMode(ALeft, OUTPUT);
    pinMode(ARight, OUTPUT);
    pinMode(BLeft, OUTPUT);
    pinMode(BRight, OUTPUT);

    // 2_RoadSensor

    // 3_BlockSensor
    pinMode(triggerPin, OUTPUT); // trigger 핀 출력으로 설정
    pinMode(echoPin, INPUT);     // echo 핀 입력으로 설정
    // 4_DEBUG_SERIAL
    Serial.begin(9600);
    tone(bPin, 262, 500);
    delay(500);
    tone(bPin, 330, 500);
    delay(500);
    tone(bPin, 392, 500);
    delay(500);
    _1_Stop();
    Car_speed = Car_max_speed;
}
void loop()
{
    _0_Controll();
}
