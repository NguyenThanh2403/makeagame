#include "Gameover.h"

Gameover::Gameover()
{

}


Gameover::~Gameover()
{
}


void Gameover::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Noxus");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Back");
	auto button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 150));
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//resume button
	texture = ResourceManagers::GetInstance()->GetTexture("Repit");
	 button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 300));
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);
	/*/repit button
	texture = ResourceManagers::GetInstance()->GetTexture("fb");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 120));
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
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("tw");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(500, 330));
	button->SetSize(50, 50);
	m_listButton.push_back(button);*/


	//logo
	texture = ResourceManagers::GetInstance()->GetTexture("TD");
	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(Application::screenWidth / 4, Application::screenHeight / 2);
	m_logo->SetSize(150, 300);
	SoundManager::GetInstance()->PauseSound("joke");

	SoundManager::GetInstance()->AddSound("defeat");
	SoundManager::GetInstance()->PlaySound("defeat");


	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("phong");
	auto m_Text_gameName = std::make_shared< Text>(shader, font, "GAMEOVER!", TEXT_COLOR::RED, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 80, 50));
	m_listText.push_back(m_Text_gameName);
	/*/title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "FB.com/gflkun", TEXT_COLOR::BLUE, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 120));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "0385496699", TEXT_COLOR::GREEN, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 190));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "ins.com/nguyenthanh", TEXT_COLOR::RED, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 270));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "tw.com/nguyenthanh", TEXT_COLOR::PURPLE, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(560, 340));
	m_listText.push_back(m_Text_gameName);*/
}


void Gameover::Exit()
{

}


void Gameover::Pause()
{

}

void Gameover::Resume()
{

}


void Gameover::HandleEvents()
{

}

void Gameover::HandleKeyEvents(int key, bool bIsPressed)
{

}

void Gameover::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	//if(bIsPressed)
	//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void Gameover::HandleMouseEvents(int x, int y)
{
}

void Gameover::Update(float deltaTime)
{

}

void Gameover :: Draw()
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

