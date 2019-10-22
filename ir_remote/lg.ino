#include <IRremote.h>
//hadware transistor: BC547, ir led: TSAL6100, ir reciever: TSOP4838

IRsend irsend; //send pin = 13
IRrecv irrecv(11); //recieve pin = 11
decode_results results;

/*
 ***********************
 *                     *
 *  LG Remote Buttons  *
 *                     *
 ***********************
 */
 
#define          REMOTE_KEY_INPUT                0x20DFD02F
#define          REMOTE_KEY_ENERGY_SAVING        0x20DFA956
#define          REMOTE_KEY_POWER                0x20DF10EF
#define          REMOTE_KEY_TVRADIO              0x20DF0FF0
#define          REMOTE_KEY_AV_MODE              0x20DF0CF3
#define          REMOTE_KEY_1                    0x20DF8877
#define          REMOTE_KEY_2                    0x20DF48B7
#define          REMOTE_KEY_3                    0x20DFC837
#define          REMOTE_KEY_4                    0x20DF28D7
#define          REMOTE_KEY_5                    0x20DFA857
#define          REMOTE_KEY_6                    0x20DF6897
#define          REMOTE_KEY_7                    0x20DFE817
#define          REMOTE_KEY_8                    0x20DF18E7
#define          REMOTE_KEY_9                    0x20DF9867
#define          REMOTE_KEY_0                    0x20DF08F7
#define          REMOTE_KEY_LIST                 0x20DFCA35
#define          REMOTE_KEY_QVIEW                0x20DF58A7
#define          REMOTE_KEY_VOLUMEUP             0x20DF40BF
#define          REMOTE_KEY_VOLUMEDOWN           0x20DFC03F
#define          REMOTE_KEY_MUTE                 0x20DF906F
#define          REMOTE_KEY_CHANNELUP            0x20DF00FF
#define          REMOTE_KEY_CHANNELDOWN          0x20DF807F
#define          REMOTE_KEY_UP                   0x20DF02FD
#define          REMOTE_KEY_DOWN                 0x20DF827D
#define          REMOTE_KEY_LEFT                 0x20DFE01F
#define          REMOTE_KEY_RIGHT                0x20DF609F
#define          REMOTE_KEY_OK                   0x20DF22DD
#define          REMOTE_KEY_MENU                 0x20DFC23D
#define          REMOTE_KEY_EXIT                 0x20DFDA25
#define          REMOTE_KEY_RED                  0x20DF4EB1
#define          REMOTE_KEY_GREEN                0x20DF8E71
#define          REMOTE_KEY_YELLOW               0x20DFC639
#define          REMOTE_KEY_BLUE                 0x20DF8679
#define          REMOTE_KEY_TEXT                 0x20DF04FB
#define          REMOTE_KEY_TOPT                 0x20DF847B
#define          REMOTE_KEY_SUBTITLE             0x20DF9C63
#define          REMOTE_KEY_SIMPLILINK           0x20DF7E81
#define          REMOTE_KEY_QMENU                0x20DFA25D
#define          REMOTE_KEY_INFO                 0x20DF55AA
#define          REMOTE_KEY_GUIDE                0x20DFD52A
#define          REMOTE_KEY_FAVORITES            0x20DF7887
#define          REMOTE_KEY_RECORD               0x20DFBD42
#define          REMOTE_KEY_BACK                 0x20DF14EB
#define          REMOTE_KEY_HOME                 0x20DF3EC1
#define          REMOTE_KEY_RECORD               0x20DFBD42
#define          REMOTE_KEY_STOP                 0x20DF8D72
#define          REMOTE_KEY_PLAY                 0x20DF0DF2
#define          REMOTE_KEY_PAUSE                0x20DF5DA2
#define          REMOTE_KEY_FORWARD              0x20DF718E
#define          REMOTE_KEY_BACKWARD             0x20DFF10E



void setup() 
{
}

void loop() 
{
    irsend.sendNEC(REMOTE_KEY_POWER, 32);
    delay(300);
}
/*
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(500);
} 
*/

