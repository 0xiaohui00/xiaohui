#include "SelectScene.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene3.h"

USING_NS_CC;
Scene* SelectScene::createscene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	SelectScene *layer = SelectScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SelectScene::init()
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
	/*Sprite* pSprite = Sprite::create("help.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);*/
	Sprite *roadbg = Sprite::create("roadground.jpg");
	roadbg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(roadbg, 0);

	Sprite *sprite1 = Sprite::create("road11.png");
	sprite1->setPosition(visibleSize.width  / 4, visibleSize.height / 4 * 3);
	addChild(sprite1,2);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [](Touch *t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->
			getLocation())){
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener1, sprite1);

	Sprite *sprite2 = Sprite::create("road22.png");
	sprite2->setPosition(visibleSize.width / 4 * 3 - 20, visibleSize.height / 4 * 3);
	addChild(sprite2,2);
	
	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [](Touch *t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->
			getLocation())){
			auto scene = GameScene2::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener2, sprite2);

	Sprite *sprite3 = Sprite::create("road3.png");
	sprite3->setPosition(visibleSize.width / 4 , visibleSize.height / 4 + 100);
	addChild(sprite3, 2);

	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = [](Touch *t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->
			getLocation())){
			auto scene = GameScene3::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener3, sprite3);

	Sprite *road4 = Sprite::create("road4.png");
	road4->setPosition(visibleSize.width / 4 * -20, visibleSize.height / 4 + 100);
	addChild(road4, 1);
	//对手机返回键的监听 
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定 
	listener->onKeyReleased = CC_CALLBACK_2(SelectScene::onKeyReleased, this);
	//添加到事件分发器中 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void SelectScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}