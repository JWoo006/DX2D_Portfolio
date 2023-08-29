#include "jwParticleSystem.h"
#include "jwTime.h"
#include "jwMesh.h"
#include "jwMaterial.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwGameObject.h"

#include <random>

namespace jw
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
		, mTime(0.0f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		mCS = Resources::Find<ParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector4::Zero;
			//pos.x += rand() % 20;
			//pos.y += rand() % 10;

			//int sign = rand() % 2;
			//if (sign == 0)
			//	pos.x *= -1.0f;
			//sign = rand() % 2;
			//if (sign == 0)
			//	pos.y *= -1.0f;

			
			std::random_device rd; // 시드 생성기
			std::mt19937 gen(rd()); // 메르센 트위스터 엔진을 시드로 초기화
			std::uniform_real_distribution<double> dis(0.5, 1.0); // 0.5에서 1.0 사이의 균일한 분포

			double randomValue = dis(gen); // 랜덤한 실수 값 생성


			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);
			float a = cosf((float)i * (XM_2PI / (float)1000));
			float b = sinf((float)i * (XM_2PI / 100.f));
			particles[i].direction = Vector4(1.f, 1.f, 0.0f, 1.0f);
			
			particles[i].position = pos;
			particles[i].speed = randomValue;
			particles[i].active = 0;
		}

		mBuffer = new graphics::StructedBuffer();
		mBuffer->Create(sizeof(Particle), 1000, eViewType::UAV, particles);

		mSharedBuffer = new graphics::StructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);

	}
	ParticleSystem::~ParticleSystem()
	{
		delete mSharedBuffer;
		delete mBuffer;
	}
	void ParticleSystem::Initialize()
	{
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::LateUpdate()
	{
		float AliveTime = 1.0f / 12.0f; // 파티클 생성 주기
		mTime += Time::DeltaTime();

		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 1;
			mSharedBuffer->SetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			mSharedBuffer->SetData(&shareData, 1);
		}


		mCS->SetParticleBuffer(mBuffer);
		mCS->SetSharedBuffer(mSharedBuffer);
		mCS->OnExcute();
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 14);
		mBuffer->BindSRV(eShaderStage::GS, 14);
		mBuffer->BindSRV(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);

		mBuffer->Clear();
	}
}