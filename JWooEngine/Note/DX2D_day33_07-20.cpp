//
// 컨텐츠 제작이 우선순위
// ㄴ 게임의 느낌 - 애니메이션 배경 오브젝트위치 bgm 
// ㄴ 모작이 아니라 원본처럼
//
// Animation* animation = FindAnimation(name);
//if (nullptr != animation)
//return;
//
//UINT width = 0;
//UINT height = 0;
//UINT fileCount = 0;
//
//std::filesystem::path fs(path);
//std::vector<std::shared_ptr<Texture>> textures = {};
//for (const auto& p : std::filesystem::recursive_directory_iterator(path))
//{
//	std::wstring fileName = p.path().filename();
//	std::wstring fullName = p.path().wstring();
//
//	const std::wstring ext = p.path().extension();
//
//	std::shared_ptr<Texture> tex = Resources::Load<Texture>(fileName, fullName);
//
//	textures.push_back(tex);
//
//	fileCount++;
//}
//
//textures[0]->CreateTex(path, mImageAtlas);
//Create(name, mImageAtlas, leftTop, size, fileCount);
//
//mAnimations.insert(std::make_pair(name, animation));
//
//Events* events = FindEvents(name);
//if (events != nullptr)
//return;
//
//events = new Events();
//mEvents.insert(std::make_pair(name, events));
// 
// 
// 애니메이터
// ㄴ update - 조건문으로 애니메이션 루프 설정 추가
// ㄴ find animation 함수 추가
// ㄴ create 애니메이션 함수 - 예외조건 및 애니메이션 create함수 호출
// ㄴ 상수 버퍼로 보내기위해 binds함수 추가
// ㄴ 애니메이션 클래스에 스프라이트 정보 상수버퍼에 바인딩
// ㄴ 씬에 텍스쳐 로드하고 애니메이터로 애니메이션 생성
// ㄴ PS에서 아틀라스 이미지 사이즈와 UV좌표변환
// ㄴ mesh renderer에 애니메이터 바인드
// ㄴ 비율 좌표계를 고려해서 셰이더에 정보보내기
// ㄴ 셰이더 코드에서 rect비율과 좌우상하 맞춰서 자르기 추가
// ㄴ 애니메이션 타입 
// 
//