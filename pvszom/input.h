#pragma once
#include <easyx.h>

class input {
public:
	static input& instance() {
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
		return  buttonx <= x && x <= buttonx + buttonw && buttony <= y && y < buttony + buttonh;
	}
	bool isleftdown()const {
		return leftdown;
	}
	bool isdragging() const {
		return dragging;
	}
	void userclick();
private:
	input() = default;
	input(const input&) = delete;
	input& operator=(const input&) = delete;
	int x, y;
	bool clicked, dragging, leftdown;
};