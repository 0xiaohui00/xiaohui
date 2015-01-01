#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene2 : public cocos2d::Layer
{
public:
	GameScene2(void);
	~GameScene2(void);
	static cocos2d::Scene* createScene();
	virtual bool init();
	

	void menupauseCallback(cocos2d::Ref* pSender);
	
	void menurestartsCallback(cocos2d::Ref* pSender);

	void GotoDialogScene(CCRenderTexture *renderTexture);
	void CreateDialogScene(CCRenderTexture *renderTexture);

	

	void update(float t);
	void updateSel(float t);
	void Start(float t);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
	//void runRight();
	//void runLeft();
	void addTouchEvent();
	void onAcceleration(Acceleration* acc, Event* event);
	CREATE_FUNC(GameScene2);
private:
	Size winSize;
	Size visibleSize;
	EventListenerTouchOneByOne* listener;
	Sprite *Road;
	Sprite *Road2;
	Sprite *bg1;
	Sprite *bg2;
	//Sprite *pRoad2;
	Label *mScoreLable;
	Label *mOverLabel;

	Sprite *mainRole;
	int mSpeed;
	Sprite *roles[10];  //随机汽车数组
	bool isPlaying;
	int Score;
	int speedLast;
	MenuItemImage* pauseItem;
	//MenuItemImage* resumeItem;
	//MenuItemImage* turnItem;
	//MenuItemImage* closeItem;
	MenuItemImage* restartsItem;
	Point LocationPos;

	float mSelNum;
	float count;
};

