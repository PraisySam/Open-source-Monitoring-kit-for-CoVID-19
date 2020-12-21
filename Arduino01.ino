int switch1=6;
int switch2=5;
int switch3=4;
int switch4=3;
int buzzer=7;
int gas;
int  buttonPin = 8;    // the pin that the pushbutton is attached to
int redled = 13;
int greenled = 12;
int blueled =11;
int counter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
float rate=0;
float time=0;
int tmpsensor = 0;
int photosensor = 1;
int motor = 9;
int A2_output = 10;
int warning;
int gas_sensor = A2;

void setup() {
  pinMode(buttonPin,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(switch1,INPUT);
  pinMode(switch2,INPUT);
  pinMode(switch3,INPUT);
  pinMode(switch4,INPUT);
  pinMode(redled,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(blueled,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(A2_output,OUTPUT);
  Serial.begin(10000);
  Serial.println("Welcome to Open Source CoVID Monitoring/ Diagnostic Kit");
  Serial.println("Press Switch 1 - Heart Rate sensor");
  Serial.println("Press Switch 2 - Body Temperature sensor");
  Serial.println("Press Switch 3 - Pulse Oximeter sensor");
  Serial.println("Press Switch 4 - CO2 Breath sensor");
  Serial.println("");
}

void loop() {
  int switch_value1= digitalRead(switch1);
  int switch_value2= digitalRead(switch2);
  int switch_value3= digitalRead(switch3);
  int switch_value4= digitalRead(switch4);
if (switch_value1 == HIGH) {
  buttonState = digitalRead(buttonPin);
  time=millis();
    // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      counter=counter+1;
      rate = (counter/time)*10000;
      Serial.print("Heart Rate: "); Serial.print(rate);
      delay(50);
   if (rate < 50){
    Serial.println("  Bradycardia shocks !!");
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
    digitalWrite(blueled,LOW);
    digitalWrite(buzzer,HIGH);
    digitalWrite(motor,HIGH);  
    warning = 1;
    delay(10);
  }
  if (rate > 100){
    Serial.println("  Tachycardia shocks !!");
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
    digitalWrite(blueled,LOW);
    digitalWrite(motor,HIGH);
    digitalWrite(buzzer,HIGH);
    warning = 1;
    delay(10);
  }
    if (rate>50 && rate<100) {
    Serial.println("  Normal Heart rate");
    digitalWrite(redled,LOW);
    digitalWrite(greenled,HIGH);
    digitalWrite(blueled,LOW);
    digitalWrite(buzzer,LOW);
    digitalWrite(motor,LOW);
    delay(10);
    warning = 0;
    }
   }
  }
  lastButtonState = buttonState;
  }
if (switch_value2 == HIGH) {
  // tmp sensor code //
int reading = analogRead(tmpsensor);
float voltage = reading*5.0;
voltage /=1024; 
float temperatureC = (voltage - 0.5)*100 ;
Serial.print("Temperature: "); Serial.println(temperatureC);
delay(10);
  if (temperatureC < 32 && temperatureC > 40 ) {
     digitalWrite(buzzer,HIGH);
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
     digitalWrite(blueled,LOW);
    warning = 1;}
  if (temperatureC > 40) {
    digitalWrite(buzzer,HIGH);
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
        digitalWrite(blueled,LOW);
    warning = 1;}
  if (temperatureC > 32 && temperatureC < 40) {
    digitalWrite(buzzer,LOW);
    digitalWrite(redled,LOW);
    digitalWrite(greenled,HIGH);
        digitalWrite(blueled,LOW);
    warning = 0;}    
  }
if (switch_value3 == HIGH) {
  // pulse oximeter code //
int absorbed_light = analogRead(photosensor);
float incident_light = 1020;
float spo2 = (absorbed_light)/(incident_light)*100;
Serial.print("SPO2 level: "); Serial.println(spo2);
delay(10);
  if (spo2 < 95) {
    digitalWrite(buzzer,HIGH);
    digitalWrite(motor,HIGH);
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
      digitalWrite(blueled,LOW);
    warning = 1;}
  if (spo2 >95) {
    digitalWrite(buzzer,LOW);
    digitalWrite(motor,LOW);
    digitalWrite(redled,LOW);
    digitalWrite(greenled,HIGH);
      digitalWrite(blueled,LOW);
    warning = 0;}
  }
if (switch_value4 == HIGH) {
  int gasval = analogRead(gas_sensor);
  gas = gasval*3;
  Serial.print("Exhaled CO2 Concentration: ");
  Serial.println(gas);
  delay(10);
  if (gas < 500) {
    digitalWrite(buzzer,HIGH);
    digitalWrite(motor,HIGH);
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
      digitalWrite(blueled,LOW);
    warning = 1;}
  if (gas >= 500) {
    digitalWrite(buzzer,LOW);
    digitalWrite(motor,LOW);
    digitalWrite(redled,LOW);
    digitalWrite(greenled,HIGH);
      digitalWrite(blueled,LOW);
    warning = 0;}
}
 if (switch_value1 == LOW && switch_value2 == LOW && switch_value3 == LOW && switch_value4 == LOW) {
    warning = 0;
    digitalWrite(redled,LOW);
    digitalWrite(blueled,HIGH);
    digitalWrite(greenled,LOW);
    digitalWrite(buzzer,LOW);
    digitalWrite(motor,LOW);}
digitalWrite(A2_output,warning);

}