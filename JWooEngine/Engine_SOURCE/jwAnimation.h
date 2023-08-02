#pragma once
#include "jwResource.h"
#include "jwTexture.h"

namespace jw
{
	using namespace math;
	using namespace graphics;

	class Animator;
	class Animation : public Resource
	{
	public:
		enum class eAnimDirection
		{
			Left = 0,
			Right = 1,

		};
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void Update();
		void LateUpdate();
		void Render();

		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);
		void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, int divideSize
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f);

		void Binds();
		void Reset();

		bool IsComplete() { return mbComplete; }

		void SetAnimDirection(eAnimDirection dir) { mAnimDirection = dir; }

	private:
		std::shared_ptr<graphics::Texture> mAtlas;
		Animator* mAnimator;
		std::vector<Sprite> mSprites;
		int mIndex;
		float mTime;
		bool mbComplete;

		eAnimDirection mAnimDirection;
	};
}
