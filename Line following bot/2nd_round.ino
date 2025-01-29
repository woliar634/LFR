void two_round_line_follow() {
  int z=9;
  while (1) { // infinite loop
   reading();
    if (sum == 0) {
      if (flag != 's') {
        brake();
        (flag == 'l') ? motor(-z * spl, z * spr) : motor(z * spl, -z * spr);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-z * spl, z * spr) : motor(z * spl, -z * spr);
        delay(turn_brake);
        flag = 's'; cross = 's'; pos = 0;
      }
      
      else if (pos > -3 && pos < 3){
        if(sonarl_read(0) || sonarr_read(0)) wall_follow();
        else  {
          m3 = millis();
          while (sum == 0) {
            reading();
            if (millis() - m3 > u_turn_delay) {
              brake();
             (side == 'l') ? motor(-z * spl, z * spr) : motor(z * spl, -z * spr);
              while (s[2] == 0 && s[3] == 0) reading();
                (flag == 'r') ? motor(-z * spl, z * spr) : motor(z * spl, -z * spr);
                delay(turn_brake);
                pos = 0; break;
               }
            }
          }
      }
    }
    else if (sum == 1 || sum == 2) {  // only for straight line
      if (cross != 's') {
        brake();
        (cross == 'l') ? motor(-z * spl, z * spr) : motor(z * spl, -z * spr);
        while (s[4] + s[3] + s[2] + s[1] > 0) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-z * spl, z * spr) : motor(z * spl, -z * spr);
        delay(turn_brake);
        cross = 's'; flag = 's'; pos = 0;
      }
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          (pos > 0) ? delay(pos * 5) : delay(-pos * 5); pos = 0;
        }
        motor(10 * spl, 10 * spr);
      }
      else if (sensor == 0b000100) motor(10 * spl, 9 * spr);
      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1; motor(10 * spl, z * spr);
      }
      else if (sensor == 0b000010) {
        if (pos < 2) pos = 2; motor(10 * spl, 3 * spr);
      }
      else if (sensor == 0b000011) {
        if (pos < 3) pos = 3; motor(10 * spl, 0 * spr);
      }
      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4; motor(10 * spl, -3 * spr);
      }
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1; motor(z * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        if (pos > -2) pos = -2; motor(3 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        if (pos > -3) pos = -3; motor(0 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        if (pos > -4) pos = -4; motor(-3 * spl, 10 * spr);
      }
    }
    else if (sum >=3 && sum <= 5) {
      if (s[5] && s[0] && sum < z) {  //inverse line detection
    uint32_t timer = millis();
    while ((s[5] || s[0]) && sum < z) {
      reading();
      if (millis() - timer > inverse_timer) {
        inverse_mode = !inverse_mode;
        digitalWrite(13, inverse_mode);
        cross = 's'; //to avoid any unnecessary sharp turns
        break;
      }
    }
    flag = 'l'; //specific guided turn for Y section
  }
      else if (s[5] == 1 && s[0] == 0 && s[2] + s[3] > 0) {
        flag = 'l';
        while (s[5] == 1 && s[0] == 0) reading();
        if (s[0] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) if (side == 'l') cross = 'l';
        }
      }
      else if (s[0] == 1 && s[5] == 0 && s[2] + s[3] > 0) {
        flag = 'r';
        while (s[5] == 0 && s[0] == 1) reading();
        if (s[5] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) if (side == 'r') cross = 'r';
        }
      }
      m1 = millis();
    }
  
    else if (sum == 6) {
      flag = side;
      m3 = millis();
      while (s[5] == 1 || s[0] == 1) {
        reading();
        if (millis() - m3 > stop_timer) {
          motor(0, 0);
          while (sum == 6) reading();
          return;
        }
      }
    }
    m2 = millis();
    if (m2 - m1 > 500) flag = 's';
  }
}
