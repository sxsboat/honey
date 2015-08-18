#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainStage : public cocos2d::Layer
{
public:

	enum class TAB {
		NONE = -1,
		TALK,
		KEEP,
		FIND,
		SETTING
	};

	enum class FIND_TAB {
		NONE = -1,
		GIFT,
		BUY_DIAMOND,
		MSG,
		FREE_DIAMOND
	};

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(MainStage);

private:
	cocos2d::Node* _rootNode;
	// current tab is none
	TAB current_tab;
	FIND_TAB current_find_tab;

	// listview
	cocos2d::ui::ListView* lvw_talk;
	cocos2d::ui::ListView* lvw_keep;

	// pageview
	cocos2d::ui::PageView* pvw_find;

	// panels
	cocos2d::ui::Layout* pnl_keep;
	cocos2d::ui::Layout* pnl_find;
	cocos2d::ui::Layout* pnl_setting;

	// tab
	cocos2d::ui::ImageView* img_talk;
	cocos2d::ui::ImageView* img_keep;
	cocos2d::ui::ImageView* img_find;
	cocos2d::ui::ImageView* img_setting;

	cocos2d::ui::Text* lb_gift;
	cocos2d::ui::Text* lb_buy_diamond;
	cocos2d::ui::Text* lb_msg;
	cocos2d::ui::Text* lb_free_diamond;

	// setting
	cocos2d::ui::Button* btn_ok;

	// show tab by tab index
	void showTab(TAB tab);
	void showTalkTab();
	void showKeepTab();
	void showFindTab();
	void showSettingTab();

	void showFindTab(FIND_TAB tab);

	// listeners
	void onItemClick(cocos2d::Ref* pSender, cocos2d::ui::ListView::EventType eventType);
	void onScroll(cocos2d::Ref* pSender, cocos2d::ui::ScrollView::EventType eventType);
	void onTabClick(cocos2d::Ref* pSender);
	void onFindTabClick(cocos2d::Ref* pSender);
	Node* getTab(TAB tab);

};

#endif // __MAIN_SCENE_H__
