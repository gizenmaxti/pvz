#pragma once
class scene {
public:
	virtual ~scene() {}
	virtual void load() = 0;
	virtual void update() = 0;
	virtual void unload() = 0;
};