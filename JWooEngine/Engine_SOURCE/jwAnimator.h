#pragma once
#include "jwComponent.h"
#include "jwAnimation.h"

namespace jw
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f);
		void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop, Vector2 size
			, UINT columnLength
			, int divideSize
			, Vector2 offset
			, float duration);

		Animation* CreateAnimations(const std::wstring& name, const std::wstring& path, int divideSize, float duration, Vector2 offset = Vector2::Zero);
		void CreateAnimation(const std::wstring& name, const std::wstring& path, Vector2 leftTop, Vector2 size, float duration);

		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);
		void Binds();

		std::function<void()>& StartEvent(const std::wstring key);
		std::function<void()>& CompleteEvent(const std::wstring key);
		std::function<void()>& EndEvent(const std::wstring key);

		void SetAnimDirection(Animation::eAnimDirection dir) { mAnimDir = dir; }
		Animation::eAnimDirection GetAnimDirection() { return mAnimDir; }

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;

		std::shared_ptr<graphics::Texture> mImageAtlas;

		Animation::eAnimDirection mAnimDir;

		bool mbLoop;
	};
}
