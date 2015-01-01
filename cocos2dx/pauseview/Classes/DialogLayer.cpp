#include "DialogLayer.h"
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

	LabelTTF *label = LabelTTF::create("Are u sure exit?", "", 64);
	label->setPosition(winSize.width / 2, winSize.height / 2 + 50);
	this->addChild(label);

	MenuItemFont *okMenuItem = MenuItemFont::create("OK", 
		CC_CALLBACK_1(DialogLayer::okMenuItemCallback,this));
	okMenuItem->setPosition(winSize.width / 2 , winSize.height / 2 - 50);

	MenuItemFont *cancelMenuItem = MenuItemFont::create("Cancel", 
		CC_CALLBACK_1(DialogLayer::cancelMenuItemCallback,this));
	cancelMenuItem->setPosition(winSize.width / 2 , winSize.height / 2 - 100);

	m_pMenu = Menu::create(okMenuItem, cancelMenuItem, NULL);
	m_pMenu->setPosition(CCPointZero);
	this->addChild(m_pMenu);
}


void DialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
{
	// 点击确定就退出（拷贝的原有方法）
	Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void DialogLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
	Director::getInstance()->resume();
	this->removeFromParentAndCleanup(false);
}
