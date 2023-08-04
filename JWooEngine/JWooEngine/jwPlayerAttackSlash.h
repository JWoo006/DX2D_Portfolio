#pragma once
#include "jwGameObject.h"
#include "jwPlayer.h"

namespace jw
{
	class Animator;
	class PlayerAttackSlash : public GameObject
	{
	public:
		PlayerAttackSlash(Player* player);
		~PlayerAttackSlash();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void AnimComplete();

	private:
		Animator* mAnimator;
		Player* mPlayer;
	};

}
