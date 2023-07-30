//
// 8월 1일 까지 스컬기준 플레이어 로직 제작
// ㄴ 공격 , 장비 장착, 몬스터 피격
// 
// 같이 접근하는 데이터가 있을경우 하나의 동작을 할때 기다려주는 작업 - 동기화, 멀티 스레드
// 
// 뷰 
// ㄴ 지금 엔진은 셰이더 리소스 뷰만 사용중임
// ㄴ 렌더타겟뷰, 깊이버퍼 뷰, Unordered Acesses View(순서가 지정되지않은 엑세스 리소스 뷰
// ㄴ 텍스쳐 클래스에 위 뷰 변수생성 및 create함수(뷰를 보여줄 영역) 추가
// ㄴ 텍스쳐 안에 뷰들을 설정하는 구조로 변경
// 
// computeshader
// ㄴ CS(컴포팅 셰이더) 코드 추가
// ㄴ 스레드 개수를 3차원으로 구현 xyz
// ㄴ rwtexture  이론 - gpu에서 계산?
// 
// // 실제 그래픽카드 하드웨어 객체
//Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

//  dx11에서 직접적으로 디바이스객체 접근하지않고
// 이객체를 이용하여 명령을 내린다.
//Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

// 최종적으로 그려질 텍스처(도화지)
//Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

// 렌더타겟에 직접접근하지 않고 렌더타겟뷰를 통해서 접근한다.
//Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

// 깊이버퍼
//Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

// 깊이버퍼에 접근할수 있는 뷰
//Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

// 더블버퍼링 작업을 진행해주는 swapChain
//Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
//