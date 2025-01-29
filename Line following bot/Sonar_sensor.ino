void wall_follow(){
  while(!sum){
    reading();
    while(sonarr_read(1)){
      if (wall_mid - sr < -2) motor(70,0);
      else if (wall_mid - sr > 2) motor(0,70);
      else motor(70,70);
    }
    while(sonarl_read(1)){
      if (wall_mid - sl < -2) motor(0,70);
      else if (wall_mid - sl > 2) motor(70,0);
      else motor(70,70);
    }
    motor(70,70);
  }
}

bool sonarr_read(bool mode){
  if((tr - millis() > 30) || mode){
    tr= millis();
    sr = sonarr.ping_cm();
    if (sr == 0) sr = 50 ;

  }
   if(sr < wall_limit) return 1 ;
   else return 0 ;
}

bool sonarl_read(bool mode ){
  if((tl - millis() > 30) || mode){
    tl= millis();
    sl = sonarl.ping_cm();
    if (sl == 0) sl = 50 ;
    
  }
  if(sl < wall_limit) return 1 ;
  else return 0 ;
}