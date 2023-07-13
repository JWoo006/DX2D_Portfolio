//
// collision manager
// collider2d 클래스
// ㄴ OnEnter, stay, exit 상태 추가
// ㄴ collidernumber와 ID추가
// 
// entity 속성 클래스
// ㄴ  collider id 
// 
// gameobject
// ㄴ getcomponents 템플릿 - const 레퍼런스 타입으로 변경
// ㄴ  ㄴ 스크립트도 돌면서 있으면 가져오기
//
// 그래픽디바이스 dx11
// ㄴ DXGI_SWAP_EFFECT_FLIP_DISCARD - > dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
// 
// 스프라이트PS
// ㄴ if ( color.a <= 0.0f) discard;
// 
// collision manager
// ㄴ 행(가로 row)열(column 세로) 레이어 마스크 생성
// ㄴ 현재 씬의 모든 오브젝트들을 왼쪽 오른쪽에 두어 충돌 체크 - 왼쪽 오른쪽이 같거나 없을시 continue 예외 처리
//