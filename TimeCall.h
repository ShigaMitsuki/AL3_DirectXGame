#pragma once
#include "Vector3.h"
#include <functional>

class TimeCall {

public:
	TimeCall(std::function<void(void)> func, uint32_t time);

	void Update();

	bool IsFinished() { return Finished; };

private:

	std::function<void(void)> Func;
	Vector3 V[2];

	uint32_t Time_;

	bool Finished = false;
};
