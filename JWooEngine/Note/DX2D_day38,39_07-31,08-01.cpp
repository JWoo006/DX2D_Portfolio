//
// compute shader로 렌더
// 
// 
// 파티클
// ㄴ 파티클VS 코드 추가 - VSIn으로 Position
// ㄴ 파티클 100개를 그리려면 기존의 drawindex함수를 100번 호출해야함 - 비효율적
// ㄴ uint Instance : SV_InstanceID
// ㄴ 100개의 파티클은 100개의 월드행렬이 필요하고 이는 cpu가 처리하기 때문에 위치값만 넣어주고
// ㄴ 구조화 버퍼로 파티클 정보 보내기(배열로 보내서 gpu가 처리)
// ㄴ - pos, direction, end time, time, speed, active(조건)
// ㄴ 파티클은 같은 마테리얼을 사용
// ㄴ 그래픽 디바이스 - drawindexedinstanced함수 추가
// ㄴ 인스터싱으로 메쉬 100개를 한꺼번에 그려줄때 셰이더에서 구분해줄때 Instance : SV_InstanceID로구분
// ㄴ Instance가 인덱스 기능을 함
// ㄴ 파티클 PS 코드 추가
//
// 파티클 시스템 컴포넌트
// ㄴ 유니티 파티클 시스템 컴포넌트 예제
// ㄴ 속성 - 사이즈, 스피드, 개수, 중력 등등 조절 이가능
// ㄴ 파티클도 보여야 하기 때문에 렌더러 참조 및 상속받아서 구현
// ㄴ 파티클 마다 구조화 버퍼가 필요 - 구조화 버퍼 포인터 변수 추가
// ㄴ Count, StartSize, EndSize, StartColor, EndColor, LifeTime
// ㄴ 렌더러 - 파티클 셰이더 추가, 마테리얼 추가
// ㄴ 파티클 시스템 컴포넌트 생성자에서 메쉬 및 마테리얼 설정
// ㄴ 파티클 갯수만큼 반복문돌림 - 파티클 포지션 정함
// ㄴ 버퍼 추가 - 파티클 정보, 타입, 개수 넣어서 넘김
// ㄴ 렌더 구현
// 
// 카메라 z값 비교조건 변경
//