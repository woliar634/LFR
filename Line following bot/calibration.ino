void cal() {
  // Initialize maximum and minimum arrays
  for (int j = 0; j < 6; j++) {
    maximum[j] = 0;
    minimum[j] = 1023;
  }
  
  // Rotate robot in place for calibration
  motor(100, -100);
  for (int k = 0; k < 5000; k++) {
    for (int j = 0; j < 6; j++) {
      s[j] = analogRead(j);  // Read sensor data
      maximum[j] = max(maximum[j], s[j]);
      minimum[j] = min(minimum[j], s[j]);
    }
  }
  
  // Stop the motors after calibration
  motor(0, 0);

  // Calculate midpoints and store in EEPROM
  for (int j = 0; j < 6; j++) {
    mid[j] = (maximum[j] + minimum[j]) / 3;

    // Store values in EEPROM with minimal delay
    EEPROM.write(j, mid[j] / 4); delay(5);
    EEPROM.write(j + 6, maximum[j] / 4); delay(5);
    EEPROM.write(j + 12, minimum[j] / 4); delay(5);
  }
}
