#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
class helpScene : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createscene();
	//Btn2 back to home
	void btnBack(Ref* pSender);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
	CREATE_FUNC(helpScene);
};

#endif // __HELLOWORLD_SCENE_H__

