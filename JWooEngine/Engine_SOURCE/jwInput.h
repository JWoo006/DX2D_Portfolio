#pragma once
#include "JWooEngine.h"

namespace jw
{
	using namespace jw::math;
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		};

		//GetKey()		Ű�� ������ �ð���ŭ true�� ��ȯ
		//GetKeyDown()	Ű�� ������ ��, �� �ѹ� true�� ��ȯ
		//GetKeyUp()	Ű�� ������ ���� ��, �� �ѹ� true�� ��ȯ

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
		}
		
		static __forceinline Vector2 GetMousePos() { return mMousePos; }
		static __forceinline Vector3 GetWorldMousePos() { return mCursorWorldPos; }
		static __forceinline Vector3 GetUIMousePos() { return mCursorUIPos; }

		static __forceinline void SetWorldMousePos(Vector3 pos)
		{
			mCursorWorldPos = pos;
		}

		static __forceinline void SetUIMousePos(Vector3 pos)
		{
			mCursorUIPos = pos;
		}

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
		static Vector3 mCursorWorldPos;
		static Vector3 mCursorUIPos;
	};
}
