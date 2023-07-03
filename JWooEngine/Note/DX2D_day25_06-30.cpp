//
// Z축 정렬
// ㄴ 반투명한 물체를 합성할 경우에는 z버퍼쓰기를 끄고
// ㄴ 반투명 모델의 표시위의 z값으로 정렬해서 그린다
// ㄴ 깊이 버퍼 none에서 처리
// ㄴ 정렬을 위해 카메라 클래스에 트랜스폼 z축 비교함수 추가
// ㄴ 앞에 있는 그림의 색과 섞여서 그려야하기 때문에 정렬필요
// ㄴ 좌표계 작은게 앞으로 오는지 큰게 앞으로 오는지 구분해서 구현
// ㄴ 카메라 클래스 렌더러함수부에 z버퍼 on/off함수 추가
// 
// 코드 정리 - 함수화
// 
// 부모 자식 객체간 회전
// ㄴ 부모의 월드 좌표계 기준으로 자식의 트랜스폼이 이동 및 회전되게끔
// ㄴ 부모 있는지 체크 후 자신의 월드 행렬 *= 부모 월드 행렬
// ㄴ 이런 회전이 적용되는곳 -> 애니메이션 구조 - 팔꿈치 회전 -> 팔회전
// 
// 앞으로 남은 것들
// ㄴ 애니메이션, 충돌 처리, 파티클, 라이트(빛 명암), 포스트 프로세싱
// ㄴ imgui 툴 -> 컨텐츠 모두 제작후 시간나면 만들기
// 
// 숙제
// ㄴ 회전에 들어가는 라디안 인자를 degree값으로 변경 (수학.h파일
// ㄴ 화면 구성 
// ㄴ 텍스쳐 bg, UI 씬구성하기
//