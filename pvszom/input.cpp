#include"input.h"
void input::userclick() {
	clicked = false;
	leftdown = false;
	ExMessage msg;
	while (peekmessage(&msg)) {
		x = msg.x;
		y = msg.y;
		if (msg.message == WM_LBUTTONDOWN) {
			clicked = true;
			dragging = true;
		}
		if(msg.message== WM_LBUTTONUP) {
			dragging = false;
			leftdown = true;
		}
	}
}

