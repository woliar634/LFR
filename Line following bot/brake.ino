void brake(){
  motor(-250, -250); delay(brake_time);
  motor(0,0); delay(100);
}