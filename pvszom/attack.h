#pragma once
class attackponent {
public:
	virtual ~attackponent() {};
	virtual void update(int owner_x, int owner_y) = 0;
	virtual void draw() = 0;
	virtual bool isActive()const = 0;
	virtual int getX()const = 0;
	virtual int getY()const = 0;
	virtual int getDamage()const = 0;
private:
	int x, y;
	int damage;
	int speed;
	bool active;
};