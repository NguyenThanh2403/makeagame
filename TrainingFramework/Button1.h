#pragma once
#include "Sprite2D.h"
class Button1 :	public Sprite2D
{
private:
protected:
public:
	Button1(Models* model, Shaders* shader, Texture* texture);
	Button1(Models* model, Shaders* shader, Vector4 color);
	~Button1();
	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;
};

