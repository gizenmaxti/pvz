#pragma once
#include<easyx.h>
#include<vector>



class plant {
public:
	virtual ~plant() {};
	virtual void load()=0;
	virtual void unload() = 0;
	virtual void update() = 0;

protected:
	IMAGE img;
	int hp;
	int x, y;
};