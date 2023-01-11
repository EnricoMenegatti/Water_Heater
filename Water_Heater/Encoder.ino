void Encoder_Setup()
{
  pinMode(encoderCLK,INPUT);
  pinMode(encoderDT,INPUT);
  pinMode(encoderSW, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderCLK), Encoder_Interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderDT), Encoder_Interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderSW), Encoder_SW_Interrupt, HIGH);

  Serial.println("Encoder setup OK!");
}

void Encoder_SW_Interrupt()
{
  EncoderSW_Pressed != EncoderSW_Pressed;
}

void Encoder_Interrupt() 
{
  int MSB = digitalRead(encoderCLK); //MSB = most significant bit
  int LSB = digitalRead(encoderDT); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(EncoderSW_Pressed)
  {
    //if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
    //if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
    if (sum == 0b1000) encoderValue ++;
    if (sum == 0b0010) encoderValue --;
  }
  
  lastEncoded = encoded; //store this value for next time
}