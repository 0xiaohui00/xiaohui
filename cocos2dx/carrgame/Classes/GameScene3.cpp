#include "GameScene3.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"
#include "DialogLayer.h"
using namespace CocosDenshion;

#define FIX_POS(_pos, _min, _max) \
if (_pos < _min)        \
	_pos = _min;        \
else if (_pos > _max)   \
	_pos = _max;        \

USING_NS_CC;

GameScene3::GameScene3(void)   //游戏初始化
{
	mSpeed = 3;
	isPlaying = false;
	Score = 0;
	speedLast = 5;
	mSelNum = 0.0f;
}


GameScene3::~GameScene3(void)
{
}

// on "init" 
Scene* GameScene3::createScene()    //在游戏场景中添加一个图层
{
	auto scene = Scene::create();
	auto layer = GameScene3::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene3::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getWinSize();    //当前逻辑屏幕大小
	visibleSize = Director::getInstance()->getVisibleSize();  //可视屏幕
	auto origin = Director::getInstance()->getVisibleOrigin(); //可视起点坐标

	auto pauseItem = MenuItemImage::create(
		"pause.png",
		"pause.png",
		CC_CALLBACK_1(GameScene3::menupauseCallback, this));

	pauseItem->setPosition(Vec2(pauseItem->getContentSize().width / 2 + 5,
		visibleSize.height - pauseItem->getContentSize().height / 2));


	restartsItem = MenuItemImage::create(
		"start.png",
		"start.png",
		CC_CALLBACK_1(GameScene3::menurestartsCallback, this));

	restartsItem->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	auto menu = Menu::create(pauseItem, restartsItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	bg1 = Sprite::create("roadthrees.png");
	bg1->setAnchorPoint(Vec2(0,0));
	bg1->setPosition(Vec2(visibleSize.width / 2 + 23, visibleSize.height / 2));
	this->addChild(bg1, 1);  //设为最底层

	bg2 = Sprite::create("roadthrees.png");
	bg2->setAnchorPoint(Vec2(0, 0));
	bg2->setPosition(Vec2(visibleSize.width / 2+ 23, bg1->getContentSize().height));
	this->addChild(bg2, 1);

	Road = Sprite::create("roadthree.jpg");  //设置公路
	//Road->setAnchorPoint(Vec2(0, 0));
	Road->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /2));
	this->addChild(Road, 0);

	/*pRoad2 = Sprite::create("road.jpg");   //设置公路连接公路2
	pRoad2->setAnchorPoint(Vec2(0, 0));
	pRoad2->setPosition(Vec2(visibleSize.width / 5, pRoad1->getContentSize().height));
	this->addChild(pRoad2, 0);*/

	mainRole = Sprite::create("car.png");    //添加一辆车
	//mainRole->setAnchorPoint(Vec2::ZERO);
	mainRole->setPosition(Vec2(visibleSize.width / 4 *3, 200));
	this->addChild(mainRole, 1);

	this->schedule(schedule_selector(GameScene3::update), 0.01f);
	this->scheduleOnce(schedule_selector(GameScene3::Start), 0.1f);

	srand((int)time(0));
	for (int x = 0; x<10; x++)
	{
		int car = rand() % 4;
		if (car == 0)
		{
			roles[x] = Sprite::create("car1.png");
		}
		else if (car == 1){
			roles[x] = Sprite::create("car2.png");
		}
		else if (car == 2){
			roles[x] = Sprite::create("car3.png");
		}
		else if (car == 3){
			roles[x] = Sprite::create("car1.png");
		}
		else if (car == 4){
			roles[x] = Sprite::create("car1.png");
		}
		else{
			roles[x] = Sprite::create("car1.png");
		}
		//roles[x]->setAnchorPoint(Vec2(0, 0));

		int left = rand() % 300;
		int high = 680 + rand() % 15000;
		roles[x]->setPosition(Vec2((visibleSize.width / 2 +23) + left + 30, high));
		this->addChild(roles[x], 2);
		auto moveby = MoveBy::create(0.4f, Point(5, 0));
		auto action = Sequence::create(moveby, roles[x], NULL);
	}

	mOverLabel = Label::create("Game Over", "Arial", 96);   //游戏结束提示
	mOverLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
	mOverLabel->setVisible(false);
	this->addChild(mOverLabel, 3);

	mScoreLable = Label::create("", "Arial", 24);  //分数显示

	mScoreLable->setPosition(Vec2((visibleSize.width / 2 - Road->getContentSize().width / 2) + mScoreLable->getContentSize().width / 2,
		visibleSize.height - mScoreLable->getContentSize().height - 100));

	this->addChild(mScoreLable, 3);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("start.mp3");  //
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bg.mp3", true);   //背景音乐

	this->schedule(schedule_selector(GameScene3::update), 0.01f);

	Device::setAccelerometerEnabled(false);  //重力感应
	auto accListener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene3::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(accListener, this);

	//对手机返回键的监听 
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定 
	listener->onKeyReleased = CC_CALLBACK_2(GameScene3::onKeyReleased, this);
	//添加到事件分发器中 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
void GameScene3::Start(float t)
{
	//开始按钮事件
	addTouchEvent();
	isPlaying = true;
	mOverLabel->setVisible(false);
	//pauseItem->setVisible(true);
	restartsItem->setVisible(false);
	Device::setAccelerometerEnabled(true);
	for (int i = 0; i<10; i++)
	{
		int car = rand() % 4;
		this->removeChild(roles[i]);
		if (car == 0)
		{
			roles[i] = Sprite::create("car1.png");
		}
		else if (car == 1){
			roles[i] = Sprite::create("car2.png");
		}
		else if (car == 2){
			roles[i] = Sprite::create("car3.png");
		}
		else if (car == 3){
			roles[i] = Sprite::create("car1.png");
		}
		else if (car == 4){
			roles[i] = Sprite::create("car1.png");
		}
		else{
			roles[i] = Sprite::create("car1.png");
		}
		//roles[i]->setAnchorPoint(Vec2(0, 0));

		int left = rand() % 300;
		int high = 680 + rand() % 15000;
		roles[i]->setPosition(Vec2((visibleSize.width / 2 +23) + left + 30, high));
		this->addChild(roles[i], 2);
		auto moveby = MoveBy::create(0.4f, Point(5, 0));
		auto action = Sequence::create(moveby, roles[i], NULL);
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("car_sound.mp3");  //开始游戏音效
}
void GameScene3::menupauseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->pause();
	Device::setAccelerometerEnabled(false);
	auto *dialogLayer = DialogLayer::create();
	this->addChild(dialogLayer);
}


void GameScene3::menurestartsCallback(cocos2d::Ref* pSender)
{
	this->scheduleOnce(schedule_selector(GameScene3::Start), 0.01f);
}

void GameScene3::update(float t)
{

	if (!isPlaying)
	{	//判断是否在游戏
		return;
	}
	bg1->setPosition(Vec2(bg1->getPosition().x, bg1->getPosition().y - mSpeed));
	bg2->setPosition(Vec2(bg2->getPosition().x, bg2->getPosition().y - mSpeed));
	Score += (mSpeed * 10);

	String* scoreStr = String::createWithFormat("Score:%d", Score);  //分数显示
	mScoreLable->setString(scoreStr->getCString());

	mSpeed = 10 + 2 * (Score / 50000);   //速度控制
	if (speedLast != mSpeed)
	{
		speedLast = mSpeed;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hurry.mp3");
	}

	for (int i = 0; i<10; i++)
	{		//随机添加障碍车
		roles[i]->setPosition(Vec2(roles[i]->getPosition().x, roles[i]->getPosition().y - mSpeed + 2));
		if (roles[i]->getPosition().y + roles[i]->getContentSize().height<0)
		{
			int left = rand() % 300;
			int high = 1280 + rand() % 8000;
			roles[i]->setPosition(Vec2(left + 30 + visibleSize.width / 2 , high));
			for (int j = 0; j<10; j++)
			{
				if (abs(roles[i]->getPosition().y - roles[j]->getPosition().y)<200 && abs(roles[i]->getPosition().x - roles[j]->getPosition().x)<100)
				{
					if (i != j)
					{
						roles[i]->setPosition(Vec2(roles[i]->getPosition().x, roles[i]->getPosition().y + 260));
						j = 0;
					}
				}
			}
		}
	}


	if (bg1->getPosition().y + bg1->getContentSize().height<640)
	{
		bg1->setPosition(Vec2(bg1->getPosition().x, bg2->getPosition().y + bg2->getContentSize().height));
	}
	if (bg2->getPosition().y + bg2->getContentSize().height<640)
	{
		bg2->setPosition(Vec2(bg2->getPosition().x, bg1->getPosition().y + bg1->getContentSize().height));
	}

	for (int j = 0; j<10; j++)
	{	//检测是碰撞
		if (mainRole->getBoundingBox().intersectsRect(roles[j]->getBoundingBox()))  //检测碰撞函数
		{

			mOverLabel->setVisible(true);
			Device::setAccelerometerEnabled(false);
			_eventDispatcher->removeEventListener(listener);
			//this->unschedule(schedule_selector(GameScene::updateSel));
			isPlaying = false;
			//pauseItem->setVisible(false);
			restartsItem->setVisible(true);
			if (mainRole->getPosition().x > roles[j]->getPosition().x){
				mainRole->runAction(Spawn::create(
					MoveBy::create(1, Point(1280, mainRole->getPosition().y + 100)),
					RotateBy::create(1, 3600), NULL));
			}
			else {
				mainRole->runAction(Spawn::create(
					MoveBy::create(1, Point(0, mainRole->getPosition().y + 100)),
					RotateBy::create(1, 3600), NULL));
			}

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.mp3");
			Score = 0;
		}
	}
}
bool GameScene3::onTouchBegan(Touch *touch, Event *event)
{
	bg1->setPosition(Vec2(bg1->getPosition().x, bg1->getPosition().y - mSpeed * 5));
	bg2->setPosition(Vec2(bg2->getPosition().x, bg2->getPosition().y - mSpeed * 5));
	//Score += (mSpeed * 10);

	this->schedule(schedule_selector(GameScene3::updateSel), 1);//自定义调度器
	return true;
}

void GameScene3::onTouchMoved(Touch *touch, Event * event)
{
	bg1->setPosition(Vec2(bg1->getPosition().x, bg1->getPosition().y - mSpeed * 5));
	bg2->setPosition(Vec2(bg2->getPosition().x, bg2->getPosition().y - mSpeed * 5));
	//Score += (mSpeed * 10);

	this->schedule(schedule_selector(GameScene3::updateSel), 1);//自定义调度器
}
void GameScene3::onTouchEnded(Touch *touch, Event * event)
{			//停用调度器
	this->unschedule(schedule_selector(GameScene3::updateSel));
}



void GameScene3::updateSel(float t)
{
	speedLast = speedLast + 100;
}

void GameScene3::addTouchEvent()
{	//添加触摸监听事件
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene3::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene3::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene3::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mainRole);
}
void GameScene3::onAcceleration(Acceleration* acc, Event* event)
{	//重力感应监听事件
	Director* pDir = Director::getInstance();
	if (mainRole == NULL) {
		return;
	}
	Size pSpriteSize = mainRole->getContentSize();
	Point ptNow = mainRole->getPosition();
	Point ptTemp = pDir->convertToUI(ptNow);

	ptTemp.x += acc->x * 20.1f;
	ptTemp.y -= acc->y * 20.81f;
	Point ptNext = pDir->convertToGL(ptTemp);

	FIX_POS(ptNext.x, (visibleSize.width / 2 +23 + mainRole->getContentSize().width - 10),
		(visibleSize.width - 30 - mainRole->getContentSize().width));
	FIX_POS(ptNext.y, 200, 200);

	mainRole->setPosition(ptNext);

}
void GameScene3::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}                                                             