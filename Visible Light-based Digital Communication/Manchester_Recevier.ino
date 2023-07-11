// This script is an implementation of a Manchester encoding receiver which reads an input signal from a photodiode and translates the Manchester-encoded bits into ASCII characters.
// AYDIN UZUN
// 19.12.2018
// pin assignment for the photodiode
int photoPin = A0;

// initial setup for delay and threshold variables
int delayTime = 1;
int threshold = 0;

// flag to track whether the threshold has been set or not
int flag1 = 0;

// variable to store current value of the input signal
int current_value;

// delay time for reading the encoded signal
int delayTime_2 = 8;

void setup() {
  Serial.begin(9600); // begin the serial communication
  pinMode(photoPin, INPUT); // set the photodiode pin as an input
}

void loop() {

  // if the threshold has not been set yet
  if (flag1 == 0) {
    // setting up variables for calculating threshold
    int change_detect = 100; // change detect value
    int meanValue = 0; // to store the mean value
    int threshold_offset = 100; // offset to be added to the mean value to calculate the threshold
    int normal = 750; // the value to be compared with
    int analogValue[20]; // an array to store the 20 last read values

    // while loop to calculate the threshold
    while (1) {
      int temp = 0;
      temp = analogRead(photoPin); // read the value from the photodiode
      // if there is a significant change in the signal
      if (normal - temp > change_detect) {
        for ( int i = 0 ; i < 20 ; i++ ) {
          analogValue[i] = analogRead(photoPin); // read 20 values
          // print the read values to the serial monitor
          Serial.print("my analog value is: ");
          Serial.print(analogValue[i] );
          Serial.print("\n");
          delay(5);
        }
        flag1 = 1; // set the flag to indicate that the threshold has been calculated
        // calculate the mean value
        for ( int i = 0 ; i < 20 ; i++ ) {
          meanValue = meanValue + analogValue[i];
        }
        meanValue = meanValue / 20;
        // calculate the threshold
        threshold = meanValue + threshold_offset;
        // print the mean and threshold values
        Serial.print("Mean value: "); Serial.println(meanValue);
        Serial.print("Threshold value: "); Serial.println(threshold);
        break;
      }
      else {
        normal = temp; // update the comparison value
      }
    }
  }

  // setup variables for reading the Manchester encoded signal
  int check_start = 0;
  int start_count = 0;
  int bits[14];
  int orig_bits[7];
  int location = 0;
  int past_bit = 1;
  int next_bit = 0;
  int duration = 0;
  int past_bit_num;

  // while loop to read the Manchester encoded signal
  while (1) {
    // if the start of the signal has not been detected yet
    if (check_start == 0) {
      current_value = analogRead(photoPin); // read the value from the photodiode
      if (current_value < threshold) {
        start_count++;
      }
      else {
        start_count = 0;
      }
      if (start_count == 7) {
        check_start = 1;  // if a continuous low signal is detected, it indicates the start of the signal
      }
      delay(10);
    }
    if (check_start == 1) {
      // setup variables for decoding the Manchester encoded signal
      int decimal_ascii = 0;
      int power = 1;
      current_value = analogRead(photoPin); // read the value from the photodiode
      if (current_value > threshold) {
        next_bit = 0; // if the signal is high, the bit is 0
      }
      else {
        next_bit = 1; // if the signal is low, the bit is 1
      }
      // check for changes in the signal
      if (next_bit != past_bit) {
        // if a change is detected, it means the current bit has ended and the next bit has started
        // calculate the duration of the past bit
        past_bit_num = duration / 8 / delayTime_2;
        duration = 0;
        // for each duration, assign the past bit value to the bits array
        for (int i = 0; i < past_bit_num - 1; i++) {
          bits[location] = past_bit;
          location++;
          // if 14 bits have been read (each bit is encoded as two bits in Manchester encoding)
          if (location == 14) {
            location = 0;
            // decode the Manchester encoded bits
            // for each pair of encoded bits, check the value and assign the corresponding decoded value
            // to the orig_bits array
            if (bits[0] == 1 && bits[1] == 0) {
              orig_bits[0] = 0;
            }
            else if (bits[0] == 0 && bits[1] == 1) {
              orig_bits[0] = 1;
            }
            if (bits[2] == 1 && bits[3] == 0) {
              orig_bits[1] = 0;
            }
            else if (bits[2] == 0 && bits[3] == 1) {
              orig_bits[1] = 1;
            }
            if (bits[4] == 1 && bits[5] == 0) {
              orig_bits[2] = 0;
            }
            else if (bits[4] == 0 && bits[5] == 1) {
              orig_bits[2] = 1;
            }
            if (bits[6] == 1 && bits[7] == 0) {
              orig_bits[3] = 0;
            }
            else if (bits[6] == 0 && bits[7] == 1) {
              orig_bits[3] = 1;
            }
            if (bits[8] == 1 && bits[9] == 0) {
              orig_bits[4] = 0;
            }
            else if (bits[8] == 0 && bits[9] == 1) {
              orig_bits[4] = 1;
            }
            if (bits[10] == 1 && bits[11] == 0) {
              orig_bits[5] = 0;
            }
            else if (bits[10] == 0 && bits[11] == 1) {
              orig_bits[5] = 1;
            }
            if (bits[12] == 1 && bits[13] == 0) {
              orig_bits[6] = 0;
            }
            else if (bits[12] == 0 && bits[13] == 1) {
              orig_bits[6] = 1;
            }
            for (int i = 0; i < 7; i++) {
              decimal_ascii = decimal_ascii + orig_bits[6 - i] * power ;
              power = power * 2 ;
            }
            byte ASCIIvalue = decimal_ascii;
            Serial.write(ASCIIvalue);
            // write the ASCII character corresponding to the decimal value to the serial monitor
          }
        }
        bits[location] = next_bit;
        location++;
        past_bit = next_bit;
      }
      else {
        duration = duration + 1;
      }
      // similar operations are performed when the location reaches 14 as in the if block inside the for loop above
      if (location == 14) {
        location = 0;

        if (bits[0] == 1 && bits[1] == 0) {
          orig_bits[0] = 0;
        }
        else if (bits[0] == 0 && bits[1] == 1) {
          orig_bits[0] = 1;
        }
        if (bits[2] == 1 && bits[3] == 0) {
          orig_bits[1] = 0;
        }
        else if (bits[2] == 0 && bits[3] == 1) {
          orig_bits[1] = 1;
        }
        if (bits[4] == 1 && bits[5] == 0) {
          orig_bits[2] = 0;
        }
        else if (bits[4] == 0 && bits[5] == 1) {
          orig_bits[2] = 1;
        }
        if (bits[6] == 1 && bits[7] == 0) {
          orig_bits[3] = 0;
        }
        else if (bits[6] == 0 && bits[7] == 1) {
          orig_bits[3] = 1;
        }
        if (bits[8] == 1 && bits[9] == 0) {
          orig_bits[4] = 0;
        }
        else if (bits[8] == 0 && bits[9] == 1) {
          orig_bits[4] = 1;
        }
        if (bits[10] == 1 && bits[11] == 0) {
          orig_bits[5] = 0;
        }
        else if (bits[10] == 0 && bits[11] == 1) {
          orig_bits[5] = 1;
        }
        if (bits[12] == 1 && bits[13] == 0) {
          orig_bits[6] = 0;
        }
        else if (bits[12] == 0 && bits[13] == 1) {
          orig_bits[6] = 1;
        }

        for (int i = 0; i < 7; i++) {
          decimal_ascii = decimal_ascii + orig_bits[6 - i] * power ;
          power = power * 2 ;
        }
        byte ASCIIvalue = decimal_ascii;
        Serial.write(ASCIIvalue);
      }
    }
  }
