#ifndef __CHAT_SCENE_H__
#define __CHAT_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ChatStage : public cocos2d::Layer
{
public:

	enum class REPLY_PANEL_STATE {
		NONE = -1,
		OPEN,
		CLOSE
	};

	enum class SHOW_TAB {
		NONE = -1,
		REPLY,
		WAIT
	};

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(ChatStage);

	void onEnter() override;
	void onExit() override;

private:

	REPLY_PANEL_STATE reply_panel_state = REPLY_PANEL_STATE::NONE;
	SHOW_TAB current_show_tab = SHOW_TAB::NONE;

	cocos2d::ui::ImageView* img_back;
	cocos2d::ui::ImageView* img_say;
	cocos2d::ui::Text* lb_gold;
	cocos2d::ui::Layout* pnl_show;
	cocos2d::ui::ImageView* img_arrow;

	// a_list
	cocos2d::ui::Text* lb_reply_0;
	cocos2d::ui::Text* lb_reply_1;
	cocos2d::ui::Text* lb_reply_2;

	// footer show panel
	cocos2d::ui::Layout* pnl_reply_select;

	//footer
	cocos2d::Node* footer;

	// listview 
	cocos2d::ui::ListView* lvw_chat;

	// toggle reply state
	void toggleReplyPanel();

	void showTab(SHOW_TAB tab);
};

#endif // __CHAT_SCENE_H__
