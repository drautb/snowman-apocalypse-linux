#include <list>
#include <algorithm>

#include "RenderManager.h"
#include "Renderable.h"

using namespace std;

bool sortPredicate(const Renderable *lhs, const Renderable *rhs)
{
	return lhs->Z() < rhs->Z();
}

RenderManager::RenderManager(void)
{
	objectsToRender.clear();
}

RenderManager::~RenderManager(void)
{

}

RenderManager *RenderManager::GetInstance()
{
	static RenderManager instance;

	return &instance;
}

void RenderManager::RegisterObject(Renderable *obj)
{
	objectsToRender.push_back(obj);
}

void RenderManager::RenderAll()
{
	//objectsToRender.sort(&RenderManager::sortPredicate);
	sort(objectsToRender.begin(), objectsToRender.end(), sortPredicate);

	for (vector<Renderable*>::const_iterator iter = objectsToRender.begin();
		iter != objectsToRender.end(); ++iter)
	{
		(*iter)->Render();
	}
}

