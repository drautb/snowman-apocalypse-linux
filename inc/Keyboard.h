#pragma once

#include <GLFW/glfw3.h>

void KeyboardCallback(GLFWwindow* window, int, int, int, int);

class Keyboard
{
public:
	/**
	 * Class Constants
	 */
	const static int KEY_COUNT		= 256;

	/**
	 * Other Members
	 */
	int keys[KEY_COUNT];

	bool keyLocks[KEY_COUNT];

private:
	/**
	 * Constructor
	 */
	Keyboard(void);

	// Not implemented
	Keyboard(Keyboard const &other);
	void operator=(Keyboard const &rhs);

public:
	/**
	 * Singleton Access
	 */
	static Keyboard &GetInstance()
	{
		static Keyboard instance;

		return instance;
	}

	/** 
	 * Destructor
	 */
	~Keyboard(void);

	/**
	 * Other Methods
	 */
	bool KeyIsDown(char key);

	bool KeyIsDown(int key);

	bool KeyIsHit(char key);

	bool KeyIsHit(int key);
};




