#include"input.h"
float msgx, msgy;
bool clicked = false;
void userclick() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		msgx = msg.x;
		msgy = msg.y;
		if (msg.message == WM_LBUTTONDOWN) {
			clicked = true;
		}
	}
}