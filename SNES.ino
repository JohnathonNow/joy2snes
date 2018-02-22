#define DAT P2_0
#define LAT P2_1
#define CLK P2_2

#define DEBUG(x) Serial.println(x)

#define SNES0 P2OUT &= ~1
#define SNES1 P2OUT |= 1
#define SNES_CLK P2IN & (1<<2)
#define SNES_LAT P2IN & (1<<1)
int buttons[13] = {1,1,1,1,1,0,1,1,1,1,1,1,1};

int index = 0;
int clk_old = 0;
int lat_old = 0;

void setup() {
  Serial.begin(9600); 
  //DEBUG("INITIALIZING");
  pinMode(DAT, OUTPUT);
  pinMode(LAT, INPUT);
  pinMode(CLK, INPUT);
}

void loop() {
  int clk_new = SNES_CLK;
  int lat_new = SNES_LAT;
  if (!lat_new && lat_old) {
    index = 0;
    //DEBUG("GO!"); 
  }
  if (clk_new && !clk_old) {
    index++;
    if (buttons[index]) {
      SNES1;
    } else {
      SNES0;
    }
  }
  clk_old = clk_new;
  lat_old = lat_new;
}
