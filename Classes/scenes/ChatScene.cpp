#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ChatScene.h"
#include "../utils/NodeUtil.h"
#include "json/document.h"
#include "entity/Entity.h"
#include "../core/GameHelper.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* ChatStage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = ChatStage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChatStage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("scene/chat/scene.csb");
	auto size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);
    addChild(rootNode);

	img_back = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_back")));
	img_say = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_say")));
	lb_gold = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(rootNode, std::string("lb_gold")));
	pnl_show = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(rootNode, std::string("pnl_show")));
	lvw_chat = dynamic_cast<cocos2d::ui::ListView*>(NodeUtil::seekFromRootByName(rootNode, std::string("lvw_chat")));
	footer = dynamic_cast<cocos2d::Node*>(NodeUtil::seekFromRootByName(rootNode, std::string("footer")));
	img_arrow = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(footer, std::string("img_arrow")));

	pnl_reply_select = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(rootNode, std::string("pnl_reply_select")));

	// a_list
	lb_reply_0 = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_reply_select, std::string("lb_reply_0")));
	lb_reply_1 = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_reply_select, std::string("lb_reply_1")));
	lb_reply_2 = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_reply_select, std::string("lb_reply_2")));

	// 当前用户
	map<string, string> params;
	params.insert(map<string, string>::value_type("id", "1"));
	vector<UserVo> userVos = GameHelper::getInstance()->getPersistenceHelper()->findAllUserInfoState(params);
	UserInfo userInfo = userVos.at(0).user.info;
	UserInfoState userInfoState = userVos.at(0).userState.info;
	vector<UserRecordState> records = userVos.at(0).userState.records;
	UserRecord currentRecord = userVos.at(0).user.records.at(userInfoState.current_q);

	// set a list value
	lb_reply_0->setText(currentRecord.a_list.at(0));
	lb_reply_1->setText(currentRecord.a_list.at(1));
	lb_reply_2->setText(currentRecord.a_list.at(2));

	for (vector<UserRecordState>::iterator itr = records.begin(); itr != records.end(); itr++) {
		cocos2d::Node* node;
		Size size;
		//q
		{
			std::string question = itr->q;
			std::string name = userInfo.name;
			node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/chat/item/item_you.csb"));
			auto lb_msg = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_msg")));
			auto lb_time = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_time")));
			auto lb_name = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_name")));
			auto img_face = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(node, std::string("img_face")));
			lb_msg->setText(question);
			lb_name->setText(name);
			size = Size(540, 180);

			// add to list
			node->setName("root_node");
			ui::Layout* layout = ui::Layout::create();
			layout->setSize(size);
			layout->setLayoutType(ui::Layout::Type::VERTICAL);
			layout->addChild(node);
			layout->setTouchEnabled(true);
			lvw_chat->pushBackCustomItem(layout);
		}
		if (itr->a != "") {
			// a
			std::string answer = itr->a;
			node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/chat/item/item_me.csb"));
			size = Size(540, 150);
			auto lb_msg = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_msg")));
			lb_msg->setText(answer);

			// add to list
			node->setName("root_node");
			ui::Layout* layout = ui::Layout::create();
			layout->setSize(size);
			layout->setLayoutType(ui::Layout::Type::VERTICAL);
			layout->addChild(node);
			layout->setTouchEnabled(true);
			lvw_chat->pushBackCustomItem(layout);
		}
	}
	// add click listener
	img_back->addClickEventListener([](cocos2d::Ref* pSender){
		Director::getInstance()->popScene();
	});

	img_say->addClickEventListener([=](cocos2d::Ref* pSender){
		toggleReplyPanel();
	});

    return true;
}

void ChatStage::onEnter() {
	Node::onEnter();
}

void ChatStage::onExit() {
	Node::onExit();
}

void ChatStage::toggleReplyPanel() {
	if (reply_panel_state != REPLY_PANEL_STATE::OPEN) { // open
		reply_panel_state = REPLY_PANEL_STATE::OPEN;
		auto pnl_reply_size = pnl_show->getContentSize();
		auto action = MoveBy::create(0.2f, Vec2(0, 300));
		footer->runAction(action);
		pnl_show->runAction(action->clone());
		lvw_chat->runAction(action->clone());

		// change view state
		lb_gold->setVisible(true);
		img_arrow->loadTexture("scene/chat/ui/close.png");
	}
	else { // close
		reply_panel_state = REPLY_PANEL_STATE::CLOSE;
		auto pnl_reply_size = pnl_show->getContentSize();
		auto action = MoveBy::create(0.2f, Vec2(0, -300));
		footer->runAction(action);
		pnl_show->runAction(action->clone());
		lvw_chat->runAction(action->clone());

		// change view state
		lb_gold->setVisible(false);
		img_arrow->loadTexture("scene/chat/ui/open.png");
	}
}

void ChatStage::showTab(SHOW_TAB tab) {

	switch (tab)
	{
	case ChatStage::SHOW_TAB::REPLY:
		
		break;
	case ChatStage::SHOW_TAB::WAIT:
		break;
	default:
		break;
	}
}
