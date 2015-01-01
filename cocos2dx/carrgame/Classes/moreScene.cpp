#include "moreScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
Scene* moreScene::createscene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	moreScene *layer = moreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool moreScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	// add "HelloWorld" splash screen"
	Sprite* pSprite = Sprite::create("morescene.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);


	//back
	MenuItemImage *pBack = MenuItemImage::create(
		"back_normal.png",
		"back_selected.png",
		CC_CALLBACK_1(moreScene::btnBack,this));
	pBack->setPosition(visibleSize.width  / 2, pBack->getContentSize().height / 2);

    Menu* pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(Point::ZERO);
	this->addChild(pBackMenu, 1);
	//对手机返回键的监听 
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定 
	listener->onKeyReleased = CC_CALLBACK_2(moreScene::onKeyReleased, this);
	//添加到事件分发器中 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void moreScene::btnBack(Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void moreScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}