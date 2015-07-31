#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "NodeUtil.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainStage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainStage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainStage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("scene/main/scene.csb");
	auto size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);
    addChild(rootNode);
	_rootNode = rootNode;

	// find view
	lvw_talk = dynamic_cast<cocos2d::ui::ListView*>(NodeUtil::seekFromRootByName(_rootNode, std::string("lvw_talk")));
	pnl_keep = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(_rootNode, std::string("pnl_keep")));
	pnl_find = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(_rootNode, std::string("pnl_find")));
	pnl_setting = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(_rootNode, std::string("pnl_setting")));
	// tab
	img_talk = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_talk")));
	img_keep = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_keep")));
	img_find = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_find")));
	img_setting = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_setting")));
	// keep listview
	lvw_keep = dynamic_cast<cocos2d::ui::ListView*>(NodeUtil::seekFromRootByName(_rootNode, std::string("lvw_keep")));

	//auto button = ui::Button::create();
	//button->loadTextureNormal("scene/register/ui/yuema.png");
	//lvw_talk->setItemModel(button);
	// init data
	for (int i = 0; i < 3; i++) {
		auto node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/main/talk/item/item_msg.csb"));
		ui::Layout* layout = ui::Layout::create();
		layout->setSize(node->getContentSize());
		layout->setLayoutType(ui::Layout::Type::VERTICAL);
		layout->addChild(node);
		layout->setTouchEnabled(true);
		lvw_talk->pushBackCustomItem(layout);
		//lvw_talk->pushBackDefaultItem();
	}

	for (int i = 0; i < 5; i++) {
		auto node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/main/keep/item/item_keep.csb"));
		ui::Layout* layout = ui::Layout::create();
		layout->setSize(node->getContentSize());
		layout->setLayoutType(ui::Layout::Type::VERTICAL);
		layout->addChild(node);
		layout->setTouchEnabled(true);
		lvw_keep->pushBackCustomItem(layout);
	}

	// init listeners
	img_talk->addClickEventListener(CC_CALLBACK_1(MainStage::onClick, this));
	img_keep->addClickEventListener(CC_CALLBACK_1(MainStage::onClick, this));
	img_find->addClickEventListener(CC_CALLBACK_1(MainStage::onClick, this));
	img_setting->addClickEventListener(CC_CALLBACK_1(MainStage::onClick, this));
	lvw_talk->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MainStage::onItemClick, this));

	showTab(TALK);
    return true;
}

void MainStage::onClick(cocos2d::Ref *pSender) {
	TAB tab_index;
	cocos2d::Node* node = dynamic_cast<cocos2d::Node*> (pSender);
	int tag = node->getTag();
	switch (tag)
	{
	case 19: // talk
		tab_index = TALK;
		break;
	case 21: // keep
		tab_index = KEEP;
		break;
	case 22: // find
		tab_index = FIND;
		break;
	case 23: // setting
		tab_index = SETTING;
		break;
	default:
		break;
	}
	showTab(tab_index);
}

void MainStage::showTab(TAB tab) {
	// return if click current tab
	if (current_tab == tab) return;
	// hide current tab
	Node* node = getTab(current_tab);
	if (node) node->setVisible(false);
	// reset all tab bg
	img_talk->loadTexture("scene/main/ui/common/talk_off.png");
	img_keep->loadTexture("scene/main/ui/common/keep_off.png");
	img_find->loadTexture("scene/main/ui/common/find_off.png");
	img_setting->loadTexture("scene/main/ui/common/setting_off.png");
	switch (tab)
	{
	case TALK:
		showTalkTab();
		break;
	case KEEP:
		showKeepTab();
		break;
	case FIND:
		showFindTab();
		break;
	case SETTING:
		showSettingTab();
		break;
	default:
		break;
	}
	// set current now
	current_tab = tab;
}

void MainStage::showTalkTab() {
	lvw_talk->setVisible(true);
	img_talk->loadTexture("scene/main/ui/common/talk_on.png");
}

void MainStage::showKeepTab() {
	pnl_keep->setVisible(true);
	img_keep->loadTexture("scene/main/ui/common/keep_on.png");
}

void MainStage::showFindTab() {
	pnl_find->setVisible(true);
	img_find->loadTexture("scene/main/ui/common/find_on.png");
}

void MainStage::showSettingTab() {
	pnl_setting->setVisible(true);
	img_setting->loadTexture("scene/main/ui/common/setting_on.png");
}

cocos2d::Node* MainStage::getTab(TAB tab) {
	cocos2d::Node* node;
	current_tab = tab;
	switch (current_tab)
	{
	case TALK:
		node = lvw_talk;
		break;
	case KEEP:
		node = pnl_keep;
		break;
	case FIND:
		node = pnl_find;
		break;
	case SETTING:
		node = pnl_setting;
		break;
	default:
		node = nullptr;
		break;
	}
	return node;
}

void MainStage::onItemClick(cocos2d::Ref* pSender, cocos2d::ui::ListView::EventType eventType) {
	auto list = dynamic_cast<ui::ListView*>(pSender);
	switch (eventType) {
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
			log("------item click start, index:%d------", list->getCurSelectedIndex());
			break;
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
			log("------item click end------index:%d", list->getCurSelectedIndex());
			break;
		default:
			log("------item click default------");
			break;
	}
}