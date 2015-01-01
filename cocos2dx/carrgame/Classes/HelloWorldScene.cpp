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
	scene->addChild(layer);   //��ͼ�����������

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

	Size visibleSize = Director::getInstance()->getVisibleSize();    //��ÿ�����Ļ��С
	Vec2 origin = Director::getInstance()->getVisibleOrigin();      //��ͼ�����

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto StartItem = MenuItemImage::create(   //�رղ˵���ť
		"start.png",
		"start.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));  //�ص�����

	StartItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + StartItem->getContentSize().height / 2 +40));

	auto MoreItem = MenuItemImage::create(   //�رղ˵���ť
		"more.png",
		"more.png",
		CC_CALLBACK_1(HelloWorld::menuMoreCallback, this));  //�ص�����

	MoreItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 ));

	auto AboutItem = MenuItemImage::create(   //�رղ˵���ť
		"help.png",
		"help.png",
		CC_CALLBACK_1(HelloWorld::menuAboutCallback, this));  //�ص�����

	AboutItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - AboutItem->getContentSize().height / 2 - 40 ));

	auto closeItem = MenuItemImage::create(   //�رղ˵���ť
		"exit.png",
		"exit.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));  //�ص�����

	closeItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - closeItem->getContentSize().height - 65));     //����λ��

	// create menu, it's an autorelease object StartItem, MoreItem, AboutItem,
	auto menu = Menu::create(StartItem, MoreItem, AboutItem, closeItem, NULL);    //����һ���˵�
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("helloworld.jpg");

	// position the sprite on the center of the screen

	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	// add the sprite as a child to this layer
	this->addChild(sprite,0);

	this->schedule(schedule_selector(HelloWorld::update), 0.5f);

	//���ֻ����ؼ��ļ��� 
	auto listener = EventListenerKeyboard::create();
	//�ͻص������� 
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	//��ӵ��¼��ַ����� 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void HelloWorld::menuStartCallback(Ref* pSender)
{		//�˳���ť�ص�����

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
{		//�˳���ť�ص�����
	
	Director::getInstance()->end();

}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	Director::getInstance()->end();
}


