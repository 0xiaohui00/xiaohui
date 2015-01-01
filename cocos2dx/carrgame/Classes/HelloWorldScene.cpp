#include "HelloWorldScene.h"
#include "GameScene.h"
#include  "moreScene.h"
#include  "helpScene.h"
#include "SelectScene.h"
#include "GameScene2.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);   //将图层添加至场景

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();    //获得可视屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();      //绘图的起点

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto StartItem = MenuItemImage::create(   //关闭菜单按钮
		"start.png",
		"start.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));  //回调函数

	StartItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + StartItem->getContentSize().height / 2 +40));

	auto MoreItem = MenuItemImage::create(   //关闭菜单按钮
		"more.png",
		"more.png",
		CC_CALLBACK_1(HelloWorld::menuMoreCallback, this));  //回调函数

	MoreItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 ));

	auto AboutItem = MenuItemImage::create(   //关闭菜单按钮
		"help.png",
		"help.png",
		CC_CALLBACK_1(HelloWorld::menuAboutCallback, this));  //回调函数

	AboutItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - AboutItem->getContentSize().height / 2 - 40 ));

	auto closeItem = MenuItemImage::create(   //关闭菜单按钮
		"exit.png",
		"exit.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));  //回调函数

	closeItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - closeItem->getContentSize().height - 65));     //设置位置

	// create menu, it's an autorelease object StartItem, MoreItem, AboutItem,
	auto menu = Menu::create(StartItem, MoreItem, AboutItem, closeItem, NULL);    //创建一个菜单
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("helloworld.jpg");

	// position the sprite on the center of the screen

	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	// add the sprite as a child to this layer
	this->addChild(sprite,0);

	this->schedule(schedule_selector(HelloWorld::update), 0.5f);

	//对手机返回键的监听 
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定 
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	//添加到事件分发器中 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void HelloWorld::menuStartCallback(Ref* pSender)
{		//退出按钮回调函数

	auto scene = SelectScene::createscene();
	Director::getInstance()->replaceScene(scene);

}

void HelloWorld::menuMoreCallback(Ref* pSender)
{		

	auto scene = moreScene::createscene();
	Director::getInstance()->replaceScene(scene);

}

void HelloWorld::menuAboutCallback(Ref* pSender)
{		
	auto scene = helpScene::createscene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{		//退出按钮回调函数
	
	Director::getInstance()->end();

}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	Director::getInstance()->end();
}


