#include<EEPROM.h>
#include<NewPing.h>

NewPing sonarr(12,12,50);
NewPing sonarl(10,10,50);
uint32_t tr , tl ;
int sr , sl;
int wall_mid = 20 , wall_limit=30; 

#define lms 3
#define lmf 5
#define lmb 4
#define rmf 6
#define rmb 7
#define rms 9
#define node_delay 30
#define stop_timer 90
#define u_turn_delay 110
#define turn_brake 40
#define brake_time 70
int s[6], sum;
int base[6] = { 1, 2, 4, 8, 16, 32 };
int position[6] = { 1, 2, 3, 4, 5, 6 };
int sensor;
int spl = 7, spr = 7;
int line_prop=2;
int maximum[6] , minimum[6],mid[6];
uint32_t m1 , m2 , m3;
int pos;
char flag= 's';
char cross = 's';
char side = 'l';
byte path[50] = {2, 3 , 2};
byte counter = 0;
int count = 0 ;
bool inverse_mode = 0;
int inverse_timer = 70;


void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  tr = tl = millis();
  // cal();
  // for(int i=0;i<6;i++){
  //   mid[i]=EEPROM.read(i)*4; 
  //   maximum[i]=EEPROM.read(i+6)*4; 
  //   minimum[i]=EEPROM.read(i+12)*4; 
  //   // Serial.println(String(maximum[i]) + "  " + String(mid[i]) + "  " + String(minimum[i]));
  // }


}

void loop() {
  // one_round_line_follow();
  two_round_line_follow();
  // show();
  // calibration_show();
  // maze_scan();
  // Serial.println(side);
    // motor(10* spl, 10* spr);
    // Serial.println(sonarr.ping_cm());


}





