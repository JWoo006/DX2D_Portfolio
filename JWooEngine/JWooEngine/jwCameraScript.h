#pragma once
#include <jwScript.h>
#include "jwPlayer.h"

namespace jw
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		virtual ~CameraScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void KeyBoardMove();
		void TargetMove();

		void CameraFollowOn() { mbCameraFollowX = true;  mbCameraFollowY = true; }
		void CameraFollowOnX() { mbCameraFollowX = true; }
		void CameraFollowOnY() { mbCameraFollowY = true; }
		void CameraFollowOff() { mbCameraFollowX = false;  mbCameraFollowY = false; }
		void CameraFollowOffX() { mbCameraFollowX = false; }
		void CameraFollowOffY() { mbCameraFollowY = false; }

		void SetPlayer(Player* _player) { mPlayer = _player; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		class Player* mPlayer;

		bool mbCameraFollowX;
		bool mbCameraFollowY;
	};
}
