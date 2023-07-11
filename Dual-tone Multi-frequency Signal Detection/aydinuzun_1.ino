// Declare an integer variable named sensorValue and initialize it to 0. 
// This variable will store the value read from the analog pin.
int sensorValue = 0;

// The setup() function is called once when the script starts. It's used to initialize variables, input/output modes, and other setup tasks.
void setup() {
  // Start the serial communication with the computer with a baud rate of 115200. 
  // Baud rate is the rate at which information is transferred in a communication channel.
  // In the serial port context, "115200" baud means that the serial port is capable of transferring a maximum of 115200 bits per second.
  Serial.begin(115200);
}

// The loop() function is called repeatedly and is the heart of most Arduino sketches.
// This is where we put code that we want to run over and over again.
void loop() {
  // Read the value from the analog pin 0 and store it in the sensorValue variable.
  // The analogRead() function reads the value from the specified analog pin. Arduino boards contain a 10-bit analog to digital converter.
  // This means that it will map input voltages between 0 and the operating voltage(5V or 3.3V) into integer values between 0 and 1023.
  sensorValue = analogRead(0);

  // Since the Arduino's analog to digital converter is 10-bit, it will produce values between 0 and 1023.
  // The Serial.write() function, however, expects bytes and will only accept values between 0 and 255.
  // So we divide the sensorValue by 4 to scale it down to a range of 0 to 255.
  sensorValue = sensorValue / 4; 

  // Write the sensorValue to the serial port as a byte. 
  // The Serial.write() function writes binary data to the serial port. This data is sent as a byte or series of bytes.
  Serial.write(sensorValue); 
}
