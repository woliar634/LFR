void reading() {

  sensor = 0;
  sum = 0;
  for (byte i = 0; i < 6; i++) {
    s[i] = analogRead(i);
    (s[i] > 300) ? s[i] = 1 ^ inverse_mode : s[i] = 0 ^ inverse_mode; //this line converts analog value into digital
    sensor += s[i] * base[i];
    sum += s[i];
  }
}
void show(){
  for (byte i = 0; i <=5; i++) {
    Serial.print(analogRead(i));
    if(i<5){
      Serial.print(" ");
    }
  }
  Serial.println();
}

void calibration_show(){
  for(int i=0 ; i<6; i++){ 
  Serial.println(String(maximum[i]) + "  " + String(mid[i]) + "  " + String(minimum[i]));
  }
}
