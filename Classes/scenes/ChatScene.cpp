#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ChatScene.h"
#include "../utils/NodeUtil.h"
#include "json/document.h"
#include "entity/Entity.h"

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

	// init data
	FileUtils* fileUtils = FileUtils::getInstance();
	rapidjson::Document info;
	info.Parse<0>(fileUtils->getStringFromFile("data/girls_info.json").c_str());

	CharcaterEntity charcaterEntity = CharcaterEntity();

	for (int i = 0; i < 25; i++) {
		CharcaterInfoEntity infoEntity = CharcaterInfoEntity();
		// 基本信息
		infoEntity.name = info[rapidjson::SizeType(i)]["name"].GetString();
		infoEntity.age = info[rapidjson::SizeType(i)]["age"].GetInt();
		infoEntity.job = info[rapidjson::SizeType(i)]["job"].GetString();
		infoEntity.height = info[rapidjson::SizeType(i)]["height"].GetString();
		infoEntity.weight = info[rapidjson::SizeType(i)]["weight"].GetString();
		infoEntity.loves = info[rapidjson::SizeType(i)]["loves"].GetString();
		infoEntity.constellation = info[rapidjson::SizeType(i)]["constellation"].GetString();
		infoEntity.hobby = info[rapidjson::SizeType(i)]["hobby"].GetString();
		infoEntity.talk = info[rapidjson::SizeType(i)]["talk"].GetString();
		infoEntity.sound = info[rapidjson::SizeType(i)]["sound"].GetString();
		infoEntity.About = info[rapidjson::SizeType(i)]["About"].GetString();
		infoEntity.About_1 = info[rapidjson::SizeType(i)]["About_1"].GetString();
		infoEntity.RoleWin = info[rapidjson::SizeType(i)]["RoleWin"].GetString();
		infoEntity.Win = info[rapidjson::SizeType(i)]["Win"].GetString();
		infoEntity.RoleOver = info[rapidjson::SizeType(i)]["RoleOver"].GetString();
		infoEntity.Over = info[rapidjson::SizeType(i)]["Over"].GetString();

		// 问题列表
		std::vector<std::string> questions;
		// 回复列表
		std::vector<std::vector<std::string>> answers;
		// 分值
		std::vector<std::vector<int>> scores;

		for (int j = 0; j < 10; j++) {
			int index = (j + 1) * 10;

			// 问题
			std::string question = info[rapidjson::SizeType(i)][StringUtils::format("%i", index).c_str()].GetString();
			questions.push_back(question);

			// 答案
			std::vector<std::string> splite_answer;
			std::string splite_answer_1 = info[rapidjson::SizeType(i)][StringUtils::format("%i", index + 1).c_str()].GetString();
			std::string splite_answer_2 = info[rapidjson::SizeType(i)][StringUtils::format("%i", index + 2).c_str()].GetString();
			std::string splite_answer_3 = info[rapidjson::SizeType(i)][StringUtils::format("%i", index + 3).c_str()].GetString();
			splite_answer.push_back(splite_answer_1);
			splite_answer.push_back(splite_answer_2);
			splite_answer.push_back(splite_answer_3);
			answers.push_back(splite_answer);

			// 分数
			std::vector<int> splite_score;
			int splite_score_1 = info[rapidjson::SizeType(i)][StringUtils::format("%i", index + 4).c_str()].GetInt();
			int splite_score_2 = info[rapidjson::SizeType(i)][StringUtils::format("%i", index + 5).c_str()].GetInt();
			int splite_score_3 = info[rapidjson::SizeType(i)][StringUtils::format("%i", index + 6).c_str()].GetInt();
			splite_score.push_back(splite_score_1);
			splite_score.push_back(splite_score_2);
			splite_score.push_back(splite_score_3);
			scores.push_back(splite_score);
		}

		// add character info
		infoEntity.questions = questions;
		infoEntity.answers = answers;
		infoEntity.scores = scores;
		charcaterEntity.charcaters.insert(std::pair<int, CharcaterInfoEntity>(i, infoEntity));
	}

	for (int i = 0; i < 25; i++) {
		std::map<int, CharcaterInfoEntity>::iterator it = charcaterEntity.charcaters.find(i);
		if (it != charcaterEntity.charcaters.end()) {
			CharcaterInfoEntity info = it->second;
		}
	}

	img_back = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_back")));
	img_say = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_say")));
	lb_gold = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(rootNode, std::string("lb_gold")));
	pnl_show = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(rootNode, std::string("pnl_show")));
	lvw_chat = dynamic_cast<cocos2d::ui::ListView*>(NodeUtil::seekFromRootByName(rootNode, std::string("lvw_chat")));
	footer = dynamic_cast<cocos2d::Node*>(NodeUtil::seekFromRootByName(rootNode, std::string("footer")));
	img_arrow = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(footer, std::string("img_arrow")));

	pnl_reply_select = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(rootNode, std::string("pnl_reply_select")));


	CharcaterInfoEntity charcater_info = charcaterEntity.charcaters.at(0);

	for (int i = 0; i < 10; i++) {
		cocos2d::Node* node;
		Size size;
		if (i % 2 == 0) {
			std::string question = charcater_info.questions.at(i);
			std::string name = charcater_info.name;
			node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/chat/item/item_you.csb"));
			auto lb_msg = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_msg")));
			auto lb_time = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_time")));
			auto lb_name = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_name")));
			auto img_face = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(node, std::string("img_face")));
			lb_msg->setText(question);
			lb_name->setText(name);
			size = Size(540, 180);
			
		}
		else {
			std::string answer = charcater_info.answers.at(i).at(0);
			node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/chat/item/item_me.csb"));
			size = Size(540, 150);
			auto lb_msg = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(node, std::string("lb_msg")));
			lb_msg->setText(answer);
		}
		node->setName("root_node");
		ui::Layout* layout = ui::Layout::create();
		layout->setSize(size);
		layout->setLayoutType(ui::Layout::Type::VERTICAL);
		layout->addChild(node);
		layout->setTouchEnabled(true);
		lvw_chat->pushBackCustomItem(layout);
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
	cocos2d::ui::Text* lb_reply_0;
	cocos2d::ui::Text* lb_reply_1;
	cocos2d::ui::Text* lb_reply_2;

	switch (tab)
	{
	case ChatStage::SHOW_TAB::REPLY:
		lb_reply_0 = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_reply_select, std::string("lb_reply_0")));
		lb_reply_1 = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_reply_select, std::string("lb_reply_1")));
		lb_reply_2 = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_reply_select, std::string("lb_reply_2")));
		break;
	case ChatStage::SHOW_TAB::WAIT:
		break;
	default:
		break;
	}
}