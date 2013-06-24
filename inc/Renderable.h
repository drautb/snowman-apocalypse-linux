#pragma once

class Renderable
{
public:
	virtual ~Renderable(void){}

	virtual float Z()const=0;
	virtual void Render()=0;
};

