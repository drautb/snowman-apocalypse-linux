#pragma once

#include <GL\glfw.h>

void MousePosCallback(int newXPos, int newYPos);
void MouseButtonCallback(int button, int pressed);

class Mouse
{
public:
	const static int		BUTTON_COUNT = 3;

	int						xPos, yPos;
	int						buttons[BUTTON_COUNT];
	bool					buttonLocks[BUTTON_COUNT];

private:
	Mouse(void);

	// Not implemented
	Mouse(Mouse const &other);
	void operator=(Mouse const &rhs);

public:

	/**
	 * Singleton Access
	 */
	static Mouse &GetInstance()
	{
		static Mouse instance;

		return instance;
	}

	/** 
	 * Destructor
	 */
	~Mouse(void);

	bool ButtonIsDown(int button);
	bool ButtonIsHit(int button);
};

