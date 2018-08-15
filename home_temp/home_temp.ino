#include <DHT.h>
#include <Adafruit_Sensor.h>

#define echoPin 6
#define trigPin 7

#define ag_ismi "JAVA_HOME"
#define ag_sifresi "zxc*123456"
#define IP "184.106.153.149"
  
  void setup()
  {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    Serial.begin(115200);
    Serial.println("AT");
    delay(1000); 
    analogReference(INTERNAL);
    if(Serial.find("OK")){
      Serial.println("AT+CWMODE=1"); 
      delay(1000);
      String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
      Serial.println(baglantiKomutu);
    }
  }
 
  void loop(){
    mesafe();
    delay(6000);
  }

  void mesafe(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  delay(50);
  Serial.println(distance);

  sicaklik_yolla(distance); 
}
   
  void sicaklik_yolla(float sicaklik){
    Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");
    delay(1000);
    String yollanacakkomut = "GET /update?key=JT2XYKVRYAQOEQAK&field1=";
    yollanacakkomut += (int(sicaklik));
    yollanacakkomut += "\r\n\r\n";
    delay(2000);
    Serial.print("AT+CIPSEND=");
    Serial.println(yollanacakkomut.length()+2);
    delay(2000);
    Serial.print(yollanacakkomut);
    Serial.print("\r\n\r\n");
  }
  
