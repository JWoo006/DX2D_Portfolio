//
// editor 분리
// grid object editor로 옮기기
// 
// 공유 항목 프로젝트간 참조를 위해 Editor window 참조에 참조 추가
// ㄴ %(AdditionalIncludeDirectories) 부모또는 프로젝트 기본값에 상속 속성 체크
// 
// gui로 분류(네임 스페이스) - gui (그래픽 유저 인터페이스)
// ㄴ gui에서 출력되는 트랜스폼 
//
// 하나의 콜라이더 메쉬(사각형)로 모든 오브젝트에 사용
// ㄴ 오브젝트마다 콜라이더 사각형 메쉬, 쉐이더를 가지고 있기에는 비효율적
// ㄴ 실제 메쉬는 에디터에서 만들고 정보(타입, pos, rotation, scale..)들은 렌더러 클래스에서 보내주기
// ㄴ 렌더러 클래스에 디버그 메쉬를 관리할 벡터와 정보를 push(넘길)함수 추가
// ㄴ 렌더러 클래스 원 mesh 추가
// ㄴ 렌더러 클래스 구조 변경 버텍스, 인덱스 변수
//   
// 디버그 마테리얼 코드
// ㄴ ps,vs 추가
// ㄴ 스프라이트 셰이더 코드 베이스로 초록색으로 출력
// ㄴ 렌더러 - 셰이더 생성, input layout 추가, 마테리얼 추가
// ㄴ topology - 트라이앵글이 아니라 라인(선 LINESTRIP)으로 설정
// ㄴ SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
// ㄴ SetRSState(eRSType::SolidNone); 레스터라이저 - none
// 
// gui에디터
// ㄴ 메쉬, 마테리얼 가져오기
// ㄴ 디버그 오브젝트 rect에 트랜스폼, 메쉬렌더러 컴포넌트 추가
// ㄴ Update, LateUpdate 각 mEditorObjects들의 오브젝트 업데이트 호출
// ㄴ main - application이 돌고나서 에디터 Run호출 + 에디터 초기화 호출 추가
// ㄴ 어플리케이션 렌더 부의 present를 밖으로 빼서 그전에 gui 렌더가 호출되게끔 구현
// ㄴ 그리드를 에디터로 옮기기
// 
//