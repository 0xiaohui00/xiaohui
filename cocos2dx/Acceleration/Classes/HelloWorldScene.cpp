#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
 
	auto label = Label::create("luoyonghui","Courier",30);
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(label);
	Sprite *s = Sprite::create("car1.png");
	s->setAnchorPoint(Point(0, 0));
	s->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(s);
	
	Device::setAccelerometerEnabled(true);
	//auto listener = EventListenerTouchOneByOne::create();
	auto listener = EventListenerAcceleration::create([s](Acceleration *acc, Event *event){
		if (acc->x <= -0.1)
		{
			//s->runAction(RepeatForever::create(MoveBy::create(0.1, Point(-3, 0))));
			s->runAction(MoveBy::create(0.1, Point(-5, 0)));
			log("LEFT");
		}
		else if (acc->x >= 0.1)
		{
			//s->runAction(RepeatForever::create(MoveBy::create(0.1, Point(3, 0))));
			s->runAction(MoveBy::create(0.1, Point(5, 0)));
			log("RIGHT");
		}
		else if (acc->y <= -0.1)
		{
			//s->runAction(RepeatForever::create(MoveBy::create(0.1, Point(0, -3))));
			s->runAction(MoveBy::create(0.1, Point(0, -5)));
			log("DOWN");
		}
		else if (acc->y >= 0.1)
		{
			//s->runAction(RepeatForever::create(MoveBy::create(0.1, Point(0, 3))));
			s->runAction(MoveBy::create(0.1, Point(0, 5)));
			log("UP");
		}
	});
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, s);
	
    return true;
};

/*void HelloWorld::onEnter(){
	Layer::onEnter();
	addEdages();
}

void HelloWorld::addEdages(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edageShape = Node::create();
	edageShape->setPhysicsBody(body);
	edageShape->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(edageShape);
}*/
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
