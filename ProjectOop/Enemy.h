#pragma once


class Enemy {
protected:
	float x, y;
	int hp;
	int gemdrop;
	bool isencased;
	float speed;
public:
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void hit() = 0;
	virtual ~Enemy() {}

	int getHP() const {
		return hp;
	}
	bool get_encased() const {
		return isencased;
	}
	float getx() const {
		return x;
	}
	float gety() const {
		return y;
	}


};