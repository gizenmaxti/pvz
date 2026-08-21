#pragma once
#include <easyx.h>

class input {
public:
	static input&instance() {
		static input instance;
		return instance;
	}
	int getx() const {
		return x;
	}
	int gety() const {
		return y;
	}
	bool isclicked() const {
		return clicked;
	}
	bool ishover(int buttonx, int buttony, int buttonw, int buttonh) const {
		return  buttonx <=x&& x <= buttonx + buttonw && buttony <= y && y < buttony + buttonh;
	}
	bool isdragging() const {
		return dragging;
	}
	void userclick();
private:
	int x, y;
	bool clicked = false,dragging;
};