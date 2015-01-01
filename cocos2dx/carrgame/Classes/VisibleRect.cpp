#include "VisibleRect.h"

USING_NS_CC;

Rect VisibleRect::s_visibleRect;

void VisibleRect::changeInit()
{    //自适应屏幕
	
	// 实际应用时分辨率的变化
	s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

Rect VisibleRect::getVisibleRect()
{
	changeInit();
	return s_visibleRect;
}

Vec2 VisibleRect::left()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

Vec2 VisibleRect::right()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

Vec2 VisibleRect::top()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y + s_visibleRect.size.height);
}

Vec2 VisibleRect::bottom()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y);
}

Vec2 VisibleRect::center()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

Vec2 VisibleRect::leftTop()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y + s_visibleRect.size.height);
}

Vec2 VisibleRect::rightTop()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y + s_visibleRect.size.height);
}

Vec2 VisibleRect::leftBottom()
{
	changeInit();
	return s_visibleRect.origin;
}

Vec2 VisibleRect::rightBottom()
{
	changeInit();
	return Vec2(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y);
}
