#include "welcome.h"
#include "HelloWorldScene.h"

USING_NS_CC;
Scene* welcome::createscene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	welcome *layer = welcome::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool welcome::init()
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
	Sprite* pSprite = Sprite::create("welcomebg.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 ));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->
			getLocation())){
			auto scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listener, pSprite);

	sprite = Sprite::create("scar.png");
	sprite->setPosition(Vec2(visibleSize.width / 4,visibleSize.height / 2 -37));
	addChild(sprite,0);
	//sprite->runAction(MoveBy::create(4, Point(visibleSize.width / 2, 0)));
	sprite->runAction(MoveBy::create(3, Point(visibleSize.width / 2, 0)));
	//this->schedule(schedule_selector(welcome::update), 0.01f);
	return true;
}
