#pragma once

#include "Animation_UI.h"
#include "Anima_UI_Ptr.h"

#include<list>
#include<memory>

class Model_Animation_UI {
public:
	Model_Animation_UI() = default;

	void initialize();
	void Updata(float deltaTime);
	void Draw() const;

	void UseModelAnimation(MODEL_ID& id, MODEL_ID& id2, int step = 0);

private:
	//std::list<Anima_UI_Ptr> animations_;

	std::unique_ptr<Animation_UI> anm_ui_ptr;
};
