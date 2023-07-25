//
// Light 빛 컴포넌트
// ㄴ Light 클래스 추가
// ㄴ LightAttribute 구조체 추가
// ㄴ 타입, 반지름(raidus, 각도(angle, 패딩(pad(int)), 색(color), pos, direction,
// ㄴ 빛의 타입 - directional(태양- 전역), point(전구 , spot(원뿔), 
// ㄴ 2d - 유니티 urp 그래픽 렌더 파이프라인
// ㄴ 빛 정보를 상수버퍼에 넘기기에는 상수버퍼 용량 제한이 있어 구조체 버퍼로 보냄
// ㄴ late update에서 attribution 속성 추가
// 
// StructuredBuffer 구조화 버퍼
// ㄴ 보낼 데이터의 크기, 배열의 크기를 보내기위한 변수 추가
// ㄴ gpu에서 읽기위한 srv추가
// ㄴ stride 갯수
// ㄴ cerate, set, bind함수 추가
// ㄴ 상수버퍼와 차이점 알아보기
// ㄴ desc - srv, 구조화 버퍼 타입 설정
// ㄴ 뷰 desc 추가
// ㄴ setdata의 입력된 stride(데이터 갯수)가 기존의 stride보다 크면 사이즈 조정 추가
// 
// 렌더러 클래스
// ㄴ 라이트 버퍼 넘겨주기
// 
// 
//