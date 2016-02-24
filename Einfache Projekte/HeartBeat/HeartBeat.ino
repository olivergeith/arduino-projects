// Pulse Monitor Test Script
 
int ledPin = 13;
int sensorPin = 0;
double alpha = 0.75;
int period = 20;
double change = 0.0;
void setup()                   
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledPin, LOW);    
}
 
void loop()                    
{
    static double oldValue = 0;
    static double oldChange = 0;
    int rawValue = analogRead(sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
    Serial.print(rawValue);
    Serial.print(",");
    double change = value - oldValue;
    Serial.println(change);

 //   if (change <0)
 //   change = cange* -1;

    if (change > 0)
      digitalWrite(13, HIGH);     
    else
      digitalWrite(13, LOW);    
    oldValue = value;
    delay(period);
}
