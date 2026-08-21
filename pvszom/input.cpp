#include"input.h"
//int msgx, msgy;
//bool clicked = false;
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



//void userclick() {
//	ExMessage msg;
//	while (peekmessage(&msg)) {
//		msgx = msg.x;
//		msgy = msg.y;
//		if (msg.message == WM_LBUTTONDOWN) {
//			clicked = true;
//		}
//	}
//}