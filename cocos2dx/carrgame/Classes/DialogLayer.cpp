#include "DialogLayer.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
DialogLayer::DialogLayer()
{
}

DialogLayer::~DialogLayer()
{
}
bool DialogLayer::init()
{
	bool bRet = false;

	do {
		CC_BREAK_IF(!LayerColor::initWithColor(Color4B(0, 0, 0, 125)));
		this->initDialog();
		bRet = true;
	} while (0);
	return bRet;
}

void DialogLayer::initDialog()
{
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*LabelTTF *label = LabelTTF::create("What you Want?", "", 64);
	label->setPosition(winSize.width / 2, winSize.height / 2 + 150);
	this->addChild(label);*/
	auto sprite = Sprite::create("pausebg.jpg");
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
	this->addChild(sprite);

	auto resumeItem = MenuItemImage::create(
	"restart.png",
	"restart.png",
	CC_CALLBACK_1(DialogLayer::cancelMenuItemCallback, this));
	resumeItem->setPosition(Vec2(resumeItem->getContentSize().width / 2, visibleSize.height / 2 + resumeItem->getContentSize().height /2 + 5));
	//restartItem->setVisible(false);

	auto turnItem = MenuItemImage::create(
	"turn.png",
	"turn.png",
	CC_CALLBACK_1(DialogLayer::returnMenuItemCallback, this));
	turnItem->setPosition(Vec2(turnItem->getContentSize().width / 2, visibleSize.height / 2 ));
	//turnItem->setVisible(false);

	auto closeItem = MenuItemImage::create(
	"close.png",
	"close.png",
	CC_CALLBACK_1(DialogLayer::okMenuItemCallback, this));
	closeItem->setPosition(Vec2(closeItem->getContentSize().width / 2, visibleSize.height / 2 - closeItem->getContentSize().height /2 -5));
	//closeItem->setVisible(false);

	/*MenuItemFont *cancelMenuItem = MenuItemFont::create("Resume Game",
		CC_CALLBACK_1(DialogLayer::cancelMenuItemCallback, this));
	cancelMenuItem->setPosition(winSize.width / 2, winSize.height / 2 );

	MenuItemFont *restartMenuItem = MenuItemFont::create("Restart Game",
		CC_CALLBACK_1(DialogLayer::restartMenuItemCallback, this));
	restartMenuItem->setPosition(winSize.width / 2, winSize.height / 2 - 50);

	MenuItemFont *returnMenuItem = MenuItemFont::create("Return Menu",
		CC_CALLBACK_1(DialogLayer::returnMenuItemCallback, this));
	returnMenuItem->setPosition(winSize.width / 2, winSize.height / 2 - 100);

	MenuItemFont *okMenuItem = MenuItemFont::create("Exit Game",
		CC_CALLBACK_1(DialogLayer::okMenuItemCallback, this));
	okMenuItem->setPosition(winSize.width / 2, winSize.height / 2 - 150);
	*/
	

	auto menu = Menu::create(resumeItem, turnItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	
}


void DialogLayer::okMenuItemCallback(Ref *pSender)
{
	// 点击确定就退出（拷贝的原有方法）
	Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void DialogLayer::cancelMenuItemCallback(Ref *pSender)
{
	Director::getInstance()->resume();
	Device::setAccelerometerEnabled(true);
	this->removeFromParentAndCleanup(false);
}

void DialogLayer::restartMenuItemCallback(Ref *pSender) 
{
	this->scheduleOnce(schedule_selector(GameScene::Start), 0.01f);
}

void DialogLayer::returnMenuItemCallback(Ref *pSender)
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}