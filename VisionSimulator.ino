boolean gpioState = false;
const int gpioPin = 7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);
  Serial1.begin(1200); //For Sending Box Number
  Serial2.begin(1200);
  pinMode(gpioPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String receive = Serial.readString();
    receive.trim();
    Serial.print("Received: " + receive);
    if(!((receive[0] == '1' || receive[0] == '2' || receive[0] == '0') && receive[1] == '-')) return;
    switch(receive[0]){
      case '0': {
        gpioState = !gpioState;
        digitalWrite(gpioPin, gpioState);
        Serial.println("GPIO State is: " + String(gpioState));
        break;
      }
      case '1': {
        Serial.println("Sent " + receive.substring(2, receive.length()) + " via Serial1");
        Serial1.println(receive.substring(2, receive.length()));
        break;
      }
      case '2': {
        Serial.println("Sent " + receive.substring(2, receive.length()) + " via Serial2");
        Serial2.println(receive.substring(2, receive.length()));
        break;
      }
    }
  }
  if(Serial1.available()){
    Serial.println("From Serial1: " + Serial1.readString());
  }
}
