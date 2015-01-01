#include "cocos2d.h"
#include "HelloWorldScene.h"
class welcome : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createscene();
	//Btn2 back to home
	//void update(float t);
	Size visibleSize;
	Sprite *sprite;
	CREATE_FUNC(welcome);
};

