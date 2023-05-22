#include "TimeCall.h"
#include "ImGui.h"
TimeCall::TimeCall(std::function<void(void)> func, uint32_t time) {


	Time_ = time;
	Func = func;

}

void TimeCall::Update() {

	if (Finished == true) {
		return;
	}
	Time_--;

	if (Time_ <= 0) {
		Finished = true;

		Func();
	}

	ImGui::Begin("Debug1");
	ImGui::Text("%d", Time_);
	ImGui::End();
}
