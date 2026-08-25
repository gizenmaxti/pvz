#include"input.h"
void input::userclick() {
	ExMessage msg;
	while (peekmessage(&msg)) {
		clicked = false;
		x = msg.x;
		y = msg.y;
		if (msg.message == WM_LBUTTONDOWN) {
			clicked = true;
			dragging = true;
		}
		if(msg.message== WM_LBUTTONUP) {
			dragging = false;
		}
	}
}

