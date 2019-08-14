#include "Option.h"

Option::Option()
{

}


Option::~Option()
{
}


void Option::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("ioniaa");

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
	texture = ResourceManagers::GetInstance()->GetTexture("Button_q");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(450, 120));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button_w");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(450, 200));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button_e");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(450, 260));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	//repit button
	texture = ResourceManagers::GetInstance()->GetTexture("Button_r");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(450, 320));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);



	//logo
	texture = ResourceManagers::GetInstance()->GetTexture("TD");
	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(Application::screenWidth / 4, Application::screenHeight / 2);
	m_logo->SetSize(150, 300);

	SoundManager::GetInstance()->AddSound("welcome");
	SoundManager::GetInstance()->PlaySound("welcome");


	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("phong");
	auto m_Text_gameName = std::make_shared< Text>(shader, font, "HASAGI", TEXT_COLOR::RED, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 80, 50));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "Use Q to call a Samurai", TEXT_COLOR::BLUE, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(510, 120));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, " Use W to launch darts", TEXT_COLOR::GREEN, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(510, 190));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "Use E to Call a Ninja if HP <50", TEXT_COLOR::RED, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(510, 270));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "Use R to Clear Map after every 20 points", TEXT_COLOR::PURPLE, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(510, 340));
	m_listText.push_back(m_Text_gameName);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arial");
	m_Text_gameName = std::make_shared< Text>(shader, font, "You can move by click left mouse", TEXT_COLOR::YELLOW, 2.0);
	m_Text_gameName->Set2DPosition(Vector2(400, 400));
	m_listText.push_back(m_Text_gameName);

}


void Option::Exit()
{

}


void Option::Pause()
{

}

void Option::Resume()
{

}


void Option::HandleEvents()
{

}

void Option::HandleKeyEvents(int key, bool bIsPressed)
{

}

void Option::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	//if(bIsPressed)
	//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void Option::HandleMouseEvents(int x, int y)
{
}

void Option::Update(float deltaTime)
{

}

void Option::Draw()
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

