#include <DHT.h>
#include <Adafruit_Sensor.h>

#define ag_ismi "JAVA_HOME"
#define ag_sifresi "avcz3463"
#define IP "184.106.153.149"

#define DHTPIN 7
#define DHTTYPE DHT22
  DHT dht(DHTPIN, DHTTYPE);
  float sicaklik;
  
  void setup()
  {
    Serial.begin(115200);
    dht.begin();
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
    float sicaklik = dht.readTemperature();
    Serial.println(sicaklik);
    sicaklik_yolla(sicaklik);
    delay(60000);
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
  
