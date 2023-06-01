//
// 수료 후 취업율 15프로
//
// 출퇴근 기록 어플 근로자의날(법적 유급 휴가)같은 날 근무시 1.5배 임금과 + 하루치 임금을 받아야한다.(2.5배) - 노동청에 신고 못받을시 
//
// 계약서 작성 급하게 하지말자 - > 서류 검토
// ㄴ 기본급 통상임금이 높을수록 좋다. 야근수당이 많다고 좋은게 아님
// 
// 퇴직금 - 최근 3개월의 임금의 평균을 합산해서 받음(DB형)
// ㄴ 최대한 많이받아서 퇴직 
// 
// DC형 퇴직금
// ㄴ 임금의 10%의 액수가 퇴직금 계좌에 들어감
// ㄴ 주식, 펀드 투자 가능
// 
// 연봉 인상 수치에따라 db, dc 전략을 세워야함
// 
// 주식 임금의 10~20%
// ㄴ 해외 주식
// ㄴ 작전주 조심 워렌 버핏도 추천하는 나스닥 s&p500  100대기업 주식 ㅅㅅ(연금)
// 
// 릭제거
// ㄴ 셰이더, 버퍼 할당후 delete 작업 필요
// ㄴ 렌더러 클래스에 release 함수 추가
// ㄴ 메인cpp에 렌더러 클래스 release함수 호출
// 
// 스마트 포인터
// ㄴ 포인터의 단점(가독성, 주소를 접근해서 값변경가능, 메모리 누수 - 직접 해제)
// ㄴ 위같은 c++에서는 메모리 누수로부터 안정성을 보장하기 위해서 스마트 포인터라인 기능을 제공함
// ㄴ 스마트 포인터는 포인터처럼 동작하는 템플릿 클래스 객체이고 사용하지 않는 메모리를 자동으로 해제해준다.
// 
// std::unique_ptr<>
// std::shared_ptr<>
// std::weak_ptr<>
// 
// std::unique_ptr<>
// ㄴ 오직 하나의 객체만 소유 할 수 있도록 만든 스마트 포인터
// ㄴ 어플리케이션 객체 만들때 사용했음
// 
// std::shared_ptr<>
// ㄴ 하나의 특정 객체를 참조하는 스마트 포인터가 총 몇개인지를 체크하는 스마트 포인터
// 
// class sharedPTR
// {
// public:
// static int refercount =0;
// }
// 하나의 객체의 주소를 여러개의 쉐어드 ptr이 각각 가지고 있음
// ㄴ delete시 바로 하나의 객체를 메모리 할당이 아닌 카운트를 세서 0이 될시 메모리 해제
// ㄴ 순환참조처럼 서로를 저장하고있으면 꼬일수도 있어서 이를 보완한게 weak_ptr
// 
//  std::weak_ptr<>
// ㄴ 참조횟수를 기반으로 동작하기때문에 서로가 서로를 가리키는 shared ptr이라면 참조 횟수가 절대 0이 되지 않으므로 메모리가 영원히 해제되지않을수있다.
// 
// comptr -> shared ptr 동작 방식
// 
// 하나의 리소스를 공유하는 오브젝트(총알, 몬스터 등등)들의 메모리 해제 시 원본 리소스가 공유를 하기에 해제되면 안되기에 스마트 포인터 사용
//