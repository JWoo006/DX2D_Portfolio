//
// ������ ������ �켱����
// �� ������ ���� - �ִϸ��̼� ��� ������Ʈ��ġ bgm 
// �� ������ �ƴ϶� ����ó��
//
// Animation* animation = FindAnimation(name);
//if (nullptr != animation)
//return;
//
//UINT width = 0;
//UINT height = 0;
//UINT fileCount = 0;
//
//std::filesystem::path fs(path);
//std::vector<std::shared_ptr<Texture>> textures = {};
//for (const auto& p : std::filesystem::recursive_directory_iterator(path))
//{
//	std::wstring fileName = p.path().filename();
//	std::wstring fullName = p.path().wstring();
//
//	const std::wstring ext = p.path().extension();
//
//	std::shared_ptr<Texture> tex = Resources::Load<Texture>(fileName, fullName);
//
//	textures.push_back(tex);
//
//	fileCount++;
//}
//
//textures[0]->CreateTex(path, mImageAtlas);
//Create(name, mImageAtlas, leftTop, size, fileCount);
//
//mAnimations.insert(std::make_pair(name, animation));
//
//Events* events = FindEvents(name);
//if (events != nullptr)
//return;
//
//events = new Events();
//mEvents.insert(std::make_pair(name, events));
// 
// 
// �ִϸ�����
// �� update - ���ǹ����� �ִϸ��̼� ���� ���� �߰�
// �� find animation �Լ� �߰�
// �� create �ִϸ��̼� �Լ� - �������� �� �ִϸ��̼� create�Լ� ȣ��
// �� ��� ���۷� ���������� binds�Լ� �߰�
// �� �ִϸ��̼� Ŭ������ ��������Ʈ ���� ������ۿ� ���ε�
// �� ���� �ؽ��� �ε��ϰ� �ִϸ����ͷ� �ִϸ��̼� ����
// �� PS���� ��Ʋ�� �̹��� ������� UV��ǥ��ȯ
// �� mesh renderer�� �ִϸ����� ���ε�
// �� ���� ��ǥ�踦 ����ؼ� ���̴��� ����������
// �� ���̴� �ڵ忡�� rect������ �¿���� ���缭 �ڸ��� �߰�
// �� �ִϸ��̼� Ÿ�� 
// 
//