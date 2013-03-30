/**
 * Useful utilities for 455
 */

#include <stack>

#include <Eigen/Core>

#define SAFE_DELETE(o)			if (o != NULL) { delete o; o = NULL; }
#define KEY_DOWN(k)				Keyboard::GetInstance().KeyIsDown(k)
#define KEY_HIT(k)				Keyboard::GetInstance().KeyIsHit(k)