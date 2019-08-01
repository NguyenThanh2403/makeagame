#pragma once
#include "Sprite3D.h"
class Ball :	public Sprite3D
{
private:
	void			CaculateWorldMatrix();

public:
	Ball(Models* model, Shaders* shader, Camera* camera, Texture* texture);
	Ball(Models* model, Shaders* shader, Camera* camera, Vector4 color);
	~Ball();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;


	void			Set3DPosition(Vector3 pos);
	Vector3			Get3DPosition();
	void			Set3DScale(Vector3 sca);
	Vector3			Get3DScale();
	void			Set3DRotation(Vector3 ros);
	Vector3			Get3DRotation();
};

