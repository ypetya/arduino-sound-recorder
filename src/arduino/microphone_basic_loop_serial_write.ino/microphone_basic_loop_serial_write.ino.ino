#define BUFFER_SIZE 25
byte buffer[BUFFER_SIZE];
int bx=0;

int sensorPin = A0;
int sensorValue = 0;

void setup();
byte convert(int data);

void loop() {
  sensorValue = analogRead(sensorPin);

  buffer[bx++] = convert(sensorValue);

  if(bx==BUFFER_SIZE) {
    Serial.write(buffer,BUFFER_SIZE);
    bx=0;
  }
}

#define BIAS_LEN 100
int bias=0;
int biasW[BIAS_LEN];
int biasI=0;

byte convert(int data) {
  //if(bias>0)
  //  return (byte) ((data-bias) & 255);
/*
  biasW[biasI++] = data;

  if(biasI==BIAS_LEN) {
    biasI=0;
  }
  int sum=0;
  for(int i=0;i<BIAS_LEN;i++){
    sum+=biasW[i];
  }
  bias = sum/10 - 128;
*/
  return (byte) (data);
}

void setup() {
  Serial.begin(115200);
}

