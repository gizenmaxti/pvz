#pragma once
#include<easyx.h>
#include"Button.h"
class UIconfig {
public:
	static UIconfig& instance() {
		static UIconfig uiconfig;
		return uiconfig;
	}
	void load();
	IMAGE& getblack() {
		return black;
	}
	IMAGE black;
};
