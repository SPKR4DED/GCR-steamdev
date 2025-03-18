#include <Keyboard.h>
#include <SD.h>
const int linkcodeChipSelect = 5;
const int Armed = 7;
const int reload = 4; 
int RVal = 1; 
String linkcode;


//funct list
void function_execute();

void setup() {
 pinMode(Armed, INPUT_PULLUP);
 pinMode(reload, INPUT_PULLUP);
 Keyboard.begin();
 Serial.begin(9600); // initialize serial communication

 if (!SD.begin(linkcodeChipSelect)){
  Serial.println("SD card initialization failed!");
    return;
  }                                                    
  // Read the link code from the SD card
  File linkcodeFile = SD.open("linkcode.txt");
  if (linkcodeFile) {
    linkcode = linkcodeFile.readString();
    linkcodeFile.close();
  } else {
    Serial.println("Error opening linkcode.txt on the linkcode SD card");

  }
  function_execute();
}
void loop() {

}


  void function_execute(){
    while(1==1){
      Serial.print("Arming value(0 is on): ");
      Serial.println(digitalRead(Armed));
      Serial.print("reload value(0 is on): ");
      Serial.println(digitalRead(reload));
      Serial.print("RVal value(1 is on): ");
      Serial.println(digitalRead(RVal));
      
     if(digitalRead(reload) == 0){
          Serial.println("check_1");
          RVal=1;
          delay(5000);
          if(digitalRead(reload) == 1){ 
            Serial.println("reload_press = true");
            delay(1000);        
          }
     }
     else if((digitalRead(Armed) == 0)&& (RVal == 1)){
            Serial.println("startmark_1");
            delay(100);
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press('r');
            Keyboard.releaseAll();
            delay(100);
            Keyboard.print("cmd");
            Keyboard.press(KEY_RETURN);
            Keyboard.release(KEY_RETURN);
            delay(1000); 
            Keyboard.print(linkcode);
            Keyboard.press(KEY_RETURN);
            Keyboard.release(KEY_RETURN);
            Keyboard.print("exit");
            Keyboard.press(KEY_RETURN);
            Keyboard.release(KEY_RETURN);
            RVal++;
      
       }
      }
     }
