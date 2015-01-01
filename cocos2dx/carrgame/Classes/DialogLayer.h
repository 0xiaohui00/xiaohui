#include "cocos2d.h"

USING_NS_CC;

class DialogLayer : public LayerColor
{
	Menu *m_pMenu;
	bool m_bTouchedMenu;
public:
	DialogLayer();
	~DialogLayer();

	virtual bool init();
	// 初始化对话框内容
	void initDialog();

	CREATE_FUNC(DialogLayer);

	void okMenuItemCallback(Ref *pSender);
	void cancelMenuItemCallback(Ref *pSender);
	void returnMenuItemCallback(Ref *pSender);
	void restartMenuItemCallback(Ref *pSender);


};