void one_round_line_follow() {
  while (1) { // infinite loop
   reading() ;
    if (sum == 0) {
      if (flag != 's') {
        brake();
        (flag == 'l') ? motor(-8 * spl, 8 * spr) : motor(8 * spl, -8 * spr);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-8 * spl, 8 * spr) : motor(8 * spl, -8 * spr);
        delay(turn_brake);
        flag = 's'; cross = 's'; pos = 0;
      }
      else if (pos > -3 && pos < 3) {
        m3 = millis();
        while (sum == 0) {
          reading();
          if (millis() - m3 > u_turn_delay) {
            brake();
            (side == 'l') ? motor(-8 * spl, 8 * spr) : motor(8 * spl, -8 * spr);
            while (s[2] == 0 && s[3] == 0) reading();
            (flag == 'r') ? motor(-8 * spl, 8 * spr) : motor(8 * spl, -8 * spr);
            delay(turn_brake);
            pos = 0; break;
          }
        }
      }
    }
    else if (sum == 1 || sum == 2) {  // only for straight line
      if (cross != 's') {
        brake();
        (cross == 'l') ? motor(-8 * spl, 8 * spr) : motor(8 * spl, -8 * spr);
        while (s[4] + s[3] + s[2] + s[1] > 0) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-8 * spl, 8 * spr) : motor(8 * spl, -8 * spr);
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
        if (pos < 1) pos = 1; motor(10 * spl, 6 * spr);
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
        if (pos > -1) pos = -1; motor(6 * spl, 10 * spr);
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
    else if (sum == 3 || sum == 4 || sum == 5) {
      if (s[5] == 1 && s[0] == 0 && s[2] + s[3] > 0) {
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
          if(count == 1) {
            brake();
            motor(0, 0); // stop on second endpoint pass
            while (sum == 6) reading();
            side='r';
            count = 0;
            return;
            
          }
          while (sum == 3 || sum ==4 || sum == 5 || sum == 6 ) reading();
          count++;
          side = 'l'; // set side to left after first endpoint pass
          flag = 's'; cross = 's';
          return ;
        }
      }
      delay(node_delay);
      reading();
      if (sum != 0) cross = side;
    }
    m2 = millis();
    if (m2 - m1 > 500) flag = 's';
  }
}
