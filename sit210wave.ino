// This #include statement was automatically added by the Particle IDE.
#include <MQTT.h>

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("broker.emqx.io", 1883, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    

    if (!strcmp(p, "wave")){
        client.publish("SIT210/wave","Hello Yashraj Koge");
        wave_flash();
    } else if (!strcmp(p, "pat")){
        pat_flash();
    }

    delay(1000);
}



// Define the pins for the LED and the distance sensor
int ledPin = D7;
int trigPin = D4;
int echoPin = D5;

// Define the threshold distance in centimeters
int thresholdDist = 15;

void wave_flash() {
    for (int i = 0; i < 3; i++) 
    {
        digitalWrite(ledPin, HIGH);
        delay(100); 
        digitalWrite(ledPin, LOW);
        delay(100);
    }
}

void pat_flash() {
    digitalWrite(ledPin, HIGH);
    delay(1000); 
    digitalWrite(ledPin, LOW);
    delay(1000);
}

// Define the variables for the distance measurement
long duration;
int distance;



void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
 
  
   client.connect("e00fce68d324327b15e38435");
   
   RGB.control(true);

// connect to the server(unique id by Time.now())
    client.connect("sparkclient_" + String(Time.now()));

    // publish/subscribe
    if (client.isConnected()) 
    {
        client.publish("SIT210/wave","Hello Yashraj Koge");
        Serial.println("The above message has been successfully received");
        client.subscribe("SIT210/wave");
        Serial.println("System has subscribed for our messages");

    }

}
void loop() 
{
    
    if (client.isConnected())
    {
        client.loop();
    }
  // Send a pulse to the ultrasonic sensor to start a measurement
  digitalWrite(trigPin, LOW);
  delay(20);
  
  digitalWrite(trigPin, HIGH);
  delay(20);
  
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance is : ");
  Serial.print(distance);
  Serial.println(" cm");

  // If the distance is greater than the threshold, turn on the LED
    if (distance < thresholdDist)
    {
    
        client.publish("SIT210/wave", "Hello Yashraj Koge");
        Serial.println("The above message has been successfully received");
        wave_flash();
    }
    else 
    {
        digitalWrite(ledPin, LOW);
    }

  // Wait a bit before taking another measurement
  delay(1000);
}

