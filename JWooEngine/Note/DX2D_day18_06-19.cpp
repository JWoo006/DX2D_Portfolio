//
// 샘플링
// ㄴ 샘플러를 통해서 실제 이미지 크기와 화면에 보여줄 픽셀 크기가 
//    다르기때문에 보간 작업을 하는 작업
// ㄴ 디폴트로 비등방성 필터링으로 적용됨
// ㄴ 2d 도트 게임은 계단현상 방지를 위해 픽셀 데이터 그대로 샘플링
// 
// 샘플러 종류
// ㄴ msaa, fxaa 샘플링 알고리즘
// ㄴ 안티에일리어싱 종류와 차이 한번식 읽어보기
// 
// 샘플러 enumclass 추가
// ㄴ Point - 아무것도 하지않고 해당 픽셀 그대로 가져오기(2d 도트 최적화)
// ㄴ Anisotropic - 비등방성 필터링
// 
// 픽셀 셰이더에 포인터 , 비등방성 샘플러 스테이트 추가 후 샘플러에 넣기
// 
// 다렉 클래스에 CreateSampler, 바인드 샘플러 함수 추가
// ㄴ 렌더러 클래스에서 샘플러 구현 - desc추가, createsampler, 바인드 샘플러 호출
// ㄴ U, V, W 옵션을 조절해서 텍스쳐 어드레싱 모드를 적용할수 있음
//  
// 마테리얼
// ㄴ 오브젝트에 보면 메쉬 렌더러, 메테리얼을 가지고있다.
// ㄴ 마테리얼안에는 셰이더와 텍스쳐를 가지고 있으며 이를 총 합쳐서 지칭하는게 마테리얼이다
// ㄴ 셰이더를 마테리얼안에 들어가게끔 작업
// ㄴ 마테리얼, 렌더패스(불칸에서는 다른용어로 말함)
// ㄴ 마테리얼 클래스 추가 및 메쉬 렌더러가 셰이더 클래스를 가진 마테리얼 클래스를 가지게끔 구현
// 
// 상수버퍼 배열로 전환
// 전역화된 텍스쳐, 셰이더를 마테리얼 클래스에 넣어서 관리 및 호출
// 
// 오디오 컴포넌트
// ㄴ 유니티 - 오디오 클립, 오디오 리스너, 오디오 소스
//