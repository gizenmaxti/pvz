#pragma once
#include<easyx.h>
class UIconfig {
public:
	static UIconfig& instance() {
		static UIconfig uiconfig;
		return uiconfig;
	}
	void load();
	IMAGE &getblack() {
		return black;
	}
private:
	IMAGE black;
};