// a receiver which captures and interprets signals from a transmitter, specifically an analog signal from a photoresistor.
// No Manchester encoding here 
// AYDIN UZUN
// 19.12.2018

// Definition of global variables
int photoPin = A0; // Pin number where photoresistor is connected
int delayTime = 1; // Delay time 
int threshold = 0; // Threshold for detecting signal
int flag1 = 0; // Flag to monitor state
int current_value; // Variable to store the current analog reading
char value; 
int delayTime_2 = 10; // Second delay time

void setup() { 
  Serial.begin(9600); // Begin serial communication at 9600 baud rate
  pinMode(photoPin,INPUT); // Set the photoPin as Input
}

void loop() {
  if (flag1==0){ 
    // Definitions for signal detection
    int change_detect = 100;
    int meanValue = 0;
    int threshold_offset = 100;
    int normal = 750;
    int analogValue[20]; 

    while(1){
      // Calculating threshold based on received signal
      int temp = 0;
      temp = analogRead(photoPin);
      if(normal-temp>change_detect){
        for ( int i = 0 ; i<20 ; i++ ){
          analogValue[i] = analogRead(photoPin);
          Serial.print("my analog value is: ");
          Serial.print(analogValue[i] );
          Serial.print("\n");
          delay(5);
        }
        flag1 = 1;
        for ( int i = 0 ; i<20 ; i++ ) {
          meanValue = meanValue + analogValue[i];
        }
        meanValue = meanValue/20;
        threshold = meanValue + threshold_offset;
        Serial.print("Mean value: "); Serial.println(meanValue);
        Serial.print("Threshold value: "); Serial.println(threshold);
        break;
      }
      else{
        normal=temp;
      }
    }  
  }
  
  // Definitions for receiving and decoding the data
  int check_start = 0;
  int start_count = 0;
  int bits[7];
  int location = 0;
  int past_bit = 0;
  int next_bit = 0;
  int duration = 0;
  int past_bit_num;

  while(1){
    if(check_start == 0){
      // Checking for start signal
      current_value = analogRead(photoPin);
      if (current_value < threshold){
        start_count++;
      }
      else{
        start_count = 0;
      }
      if(start_count == 7){
        check_start = 1;  
      }
      delay(10);
    }
    if(check_start==1){ 
      // Receiving and decoding the data
      int decimal_ascii = 0;
      int power = 1;
      current_value = analogRead(photoPin);
      if (current_value > threshold){ 
        next_bit = 0; 
      }
      else {
        next_bit = 1;
      }
      if (next_bit != past_bit){
        past_bit_num = duration/8/delayTime_2;
        duration = 0;
        for(int i=0; i<past_bit_num-1; i++){
          bits[location] = past_bit;
          location++;
          if(location == 7){
            location = 0;
            for(int i=0;i<7;i++){
              decimal_ascii = decimal_ascii + bits[6-i]*power ;
              power = power *2 ;
            }
            byte ASCIIvalue = decimal_ascii;
            Serial.write(ASCIIvalue);
          }
        }
        bits[location] = next_bit;
        location++;
        past_bit = next_bit;
      }
      else{
        duration = duration + 1;
      }
      if(location == 7){
        location = 0;
        for(int i=0;i<7;i++){
          decimal_ascii = decimal_ascii + bits[6-i]*power ;
          power = power *2 ;
        }
        byte ASCIIvalue = decimal_ascii;
        Serial.write(ASCIIvalue);
      }
    }
  }
}
