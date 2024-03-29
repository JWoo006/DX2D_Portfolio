#include "jwTransform.h"
#include "jwRenderer.h"
#include "jwConstantBuffer.h"
#include "jwCamera.h"

namespace jw
{
	using namespace jw::graphics;
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mWorldPosition(Vector3::Zero)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		// 이동 회전 크기 변경
	}

	void Transform::LateUpdate()
	{
		// 수정된 데이터를 가지고 월드 행렬로 변환
		mWorld = Matrix::Identity; // 단위 행렬

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;
		mWorldPosition = mPosition;
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);

		//mTopLeft = Vector3::TransformNormal(Vector3::TopLeft, rotation);
		//mBottomRight = Vector3::TransformNormal(Vector3::BottomRight, rotation);

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{

	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.mWorld = mWorld;
		trCB.mView = Camera::GetGpuViewMatrix();
		trCB.mProjection = Camera::GetGpuProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
	}

}
