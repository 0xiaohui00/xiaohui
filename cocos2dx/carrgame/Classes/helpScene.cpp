#include "helpScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
Scene* helpScene::createscene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	helpScene *layer = helpScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool helpScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// add "HelloWorld" splash screen"
	Sprite* pSprite = Sprite::create("helpscene.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);


	//back
	MenuItemImage *pBack = MenuItemImage::create(
		"back_normal.png",
		"back_selected.png",
		CC_CALLBACK_1(helpScene::btnBack,this));
	pBack->setPosition(visibleSize.width / 2, pBack->getContentSize().height / 2);

	Menu* pBackMenu = Menu::create(pBack, NULL);
	pBackMenu->setPosition(Point::ZERO);
	this->addChild(pBackMenu, 1);

	//���ֻ����ؼ��ļ��� 
	auto listener = EventListenerKeyboard::create();
	//�ͻص������� 
	listener->onKeyReleased = CC_CALLBACK_2(helpScene::onKeyReleased, this);
	//���ӵ��¼��ַ����� 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void helpScene::btnBack(Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}
void helpScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}