//
// 파티클 텍스쳐 적용
// ㄴ 정점의 정보없이 uv좌표및 파티클 크기를 구하기위해 지오메트리 셰이더 기능을 사용
// 
// 지오메트리 셰이더 - 정점을 gpu에서 그려줄수있다.
// ㄴ 잔상- 오브젝트로 늘리는게 아닌 본체의 정점정보를 여러개로 늘려서 그리기/\
// ㄴ 정점의 정보를 늘리는것으로 정점에 노멀(방향을)을 추가해 표면에 변화를 줄수도 있다.
// ㄴ 보통 정점 3개로 받아서 복사 및 위치를 이동하는 작업후 PS로 보냄
//
// 포인트 메시 생성주의
//