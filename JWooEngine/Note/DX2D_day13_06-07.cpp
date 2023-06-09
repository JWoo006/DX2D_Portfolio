//
// 인풋 레이아웃 구조화 구현
// 렌더러의 레이아웃 셰이더 클래스 변수로 보냄
//
// 모든 버퍼를 클래스화하지는 않지만 상수 버퍼는 자주사용하니 예외
// 상수 버퍼(gpu와 cpu간 작은 데이터들을 옮길때 사용하는 버퍼
// 구조화 버퍼( 큰 데이터 (배열)들을 옮길때 사용
// 그래픽스 헤더에 전처리기 이전시키고 그때그때 입력받는 버퍼 구조체 추가
// GpuBuffer를 상속받는 상수버퍼 클래스 추가
// ㄴ 상수 버퍼의 기능인 데이터 세팅함수와 바인드 시켜줄 함수 추가
// ㄴ 클래스 구조 수정
// 
// 게임 엔진 클래스 추가할 차례
// ㄴ 오브젝트(+컴포넌트), 레이어, 씬
// 컴포넌트 기반, ecs 컴포넌트 시스템
// ㄴ 기존의 컴포넌트 기반 설계는 new로 할당해서 메모리가 떨어져 있지만
// ㄴ ecs는 메모리를 붙여서 설계하는 시스템
// ㄴ 기존에는 불규칙적으로 메모리에 할당되어 수행작업에 필요한 다음 메모리 주소를 찾는 연산이 필요하지만
// ㄴ ecs는 메모리가 연속적으로 이어져있어 찾는 연산 수행속도에서 이점이 있다.
// 
// 컴포넌트
// ㄴ enum class 트랜스폼 파티클 메쉬 스크립트 등등 추가
// ㄴ 업데이트 3개로 분할해서 돌림
// 
//