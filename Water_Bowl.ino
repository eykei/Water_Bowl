
int Echo = A1;
int Trig = A2;
int Relay = A0;
int threshold = 12;
int distance;

int getDistance() {
    //set trig pin to low for 2 microsec to clear it
    digitalWrite(Trig, LOW); 
    delayMicroseconds(2);

    //emit ultrasound for 10 microsec
    digitalWrite(Trig, HIGH); 
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);

    //measure the time (in microsec) that echo reads high. this is the time between when the wave was sent vs received. 
    int echoTime = pulseIn(Echo, HIGH);

    distance = echoTime * 0.017; // 0.017 = 0.034 /2... 340 m/s (speed of sound) - > 0.034 cm / microsec and divide by 2 to account for 2 way travel
    
    return distance; // returns distance in centimeters    
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Relay, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = getDistance();
  Serial.println(distance);
  if (distance > threshold){ //if water too low
    Serial.println("Turning On!");
    digitalWrite(Relay, HIGH);
    while (distance > 3){
      distance = getDistance();
      delay(500);
      Serial.println(distance);
    }
    Serial.println("Turning Off!");
    digitalWrite(Relay, LOW);
  }
  delay(5000);
}
