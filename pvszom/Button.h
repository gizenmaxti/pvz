#pragma once
#include "easyx.h"
class Button {
public:
	Button(int x, int y, int w, int h, const std::string& imgpath, const std::string& hoverpath) :
		x(x), y(y), width(w), height(h) {
		loadimage(&img, imgpath.c_str(), w, h);
		loadimage(&hoverimg, hoverpath.c_str(), w, h);
	};

	int getx() const { return x; };
	int gety() const { return y; };
	int getw() const { return width; };
	int geth() const { return height; };
	const IMAGE& getimg() const { return img; };
	const IMAGE& gethover() const { return hoverimg; };

	virtual void onClick(bool clicked) = 0;

	virtual bool ishover(int mousex, int mousey) const {
		return mousex >= x && mousex < x + width && mousey >= y && mousey < y + height;
	}

	virtual void hover(bool hovered) = 0;

	IMAGE& getimg() { return img; };
	IMAGE& gethover() { return hoverimg; };

private:
	int x, y, width, height;
	IMAGE img, hoverimg;
};