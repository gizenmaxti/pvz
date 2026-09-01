#pragma once
#include <easyx.h>
class Button {
public:
	
	Button(int x, int y, int w, int h, const std::string& imgpath, const std::string& hoverpath="") :
		x(x), y(y), width(w), height(h) {
		if (!imgpath.empty())loadimage(&img, imgpath.c_str(), w, h);
		if(!hoverpath.empty())loadimage(&hoverimg, hoverpath.c_str(), w, h);
	};
	int x, y;

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
	int width, height;
	IMAGE img, hoverimg;
};

class Basicbutton :public Button {
public:
	Basicbutton() = default;
	using Button::Button;
	void onClick(bool clicked) {};
	void hover(bool hovered) {};
};