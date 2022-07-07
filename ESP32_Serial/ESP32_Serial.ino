double i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  char str[100];
  sprintf(str,"SIN,%f",100*sin(i));
  Serial.println(str);
  sprintf(str,"COS,%f",100*cos(i));
  Serial.println(str);
  i = i + 0.1;
  delay(100);
}
