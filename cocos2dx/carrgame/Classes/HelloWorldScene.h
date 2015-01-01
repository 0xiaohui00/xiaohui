#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	//HelloWorld();
	//~HelloWorld();
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuMoreCallback(cocos2d::Ref* pSender);
	void menuAboutCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
