#include "Credit.h"


Credit::Credit()
{
	
}


Credit::~Credit()
{
}


void Credit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Cre");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Back");
	auto button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(925, 30));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("fb");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 360));
	button->SetSize(50, 50);
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("dt");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 190));
	button->SetSize(50, 50);
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("ins");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 260));
	button->SetSize(50, 50);
	m_listButton.push_back(button);/*
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("tw");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 330));
	button->SetSize(50, 50);
	m_listButton.push_back(button);*/


	//logo
	texture = ResourceManagers::GetInstance()->GetTexture("loft");
	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(Application::screenWidth / 4, Application::screenHeight / 2);
	m_logo->SetSize(300, 200);
	
	SoundManager::GetInstance()->AddSound("music");
	SoundManager::GetInstance()->PlaySound("music");

	
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("phong");
	auto m_Text_gameName = std::make_shared< Text>(shader, font, "HASAGI", TEXT_COLOR::RED, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 80, 50));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	 font = ResourceManagers::GetInstance()->GetFont("phong");
	m_Text_gameName = std::make_shared< Text>(shader, font, "FB.com/gflkun", TEXT_COLOR::BLUE, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 360));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("phong");
	m_Text_gameName = std::make_shared< Text>(shader, font, "Nguyen Van Cuong", TEXT_COLOR::GREEN, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 190));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("phong");
	m_Text_gameName = std::make_shared< Text>(shader, font, "Makebyme: Nguyen Thanh", TEXT_COLOR::RED, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 270));
	m_listText.push_back(m_Text_gameName);/*
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "tw.com/nguyenthanh", TEXT_COLOR::PURPLE, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 340));
	m_listText.push_back(m_Text_gameName);*/
}


void Credit::Exit()
{

}


void Credit::Pause()
{

}

void Credit::Resume()
{

}


void Credit::HandleEvents()
{

}

void Credit::HandleKeyEvents(int key, bool bIsPressed)
{

}

void Credit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	//if(bIsPressed)
	//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void Credit::HandleMouseEvents(int x, int y)
{
}

void Credit::Update(float deltaTime)
{
	
}

void Credit::Draw()
{
	m_BackGround->Draw();
	m_logo->Draw();
	//m_Text_gameName->Draw();
	//butoon

	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}

}
