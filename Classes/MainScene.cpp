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

	// find view
	lvw_talk = dynamic_cast<cocos2d::ui::ListView*>(NodeUtil::seekFromRootByName(rootNode, std::string("lvw_talk")));
	pnl_keep = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(rootNode, std::string("pnl_keep")));
	pnl_find = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(rootNode, std::string("pnl_find")));
	pnl_setting = dynamic_cast<cocos2d::ui::Layout*>(NodeUtil::seekFromRootByName(rootNode, std::string("pnl_setting")));
	// tab
	img_talk = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_talk")));
	img_keep = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_keep")));
	img_find = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_find")));
	img_setting = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_setting")));

	// keep listview
	lvw_keep = dynamic_cast<cocos2d::ui::ListView*>(NodeUtil::seekFromRootByName(rootNode, std::string("lvw_keep")));
	pvw_find = dynamic_cast<cocos2d::ui::PageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("pvw_find")));

	// find tab
	lb_gift = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_find, std::string("lb_gift")));
	lb_buy_diamond = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_find, std::string("lb_buy_diamond")));
	lb_msg = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_find, std::string("lb_msg")));
	lb_free_diamond = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(pnl_find, std::string("lb_free_diamond")));

	//auto button = ui::Button::create();
	//button->loadTextureNormal("scene/register/ui/yuema.png");
	//lvw_talk->setItemModel(button);
	// init data
	for (int i = 0; i < 3; i++) {
		auto node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/main/talk/item/item_msg.csb"));
		node->setName("root_node");
		ui::Layout* layout = ui::Layout::create();
		layout->setSize(node->getContentSize());
		layout->setLayoutType(ui::Layout::Type::VERTICAL);
		layout->addChild(node);
		layout->setTouchEnabled(true);
		// add click listener
		layout->addClickEventListener([](cocos2d::Ref* pSender){
			log("----------item clicked---------");
		});
		// add touch listener
		layout->addTouchEventListener([](cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType event){
			auto layout = dynamic_cast<ui::Layout*>(pSender);
			auto node = layout->getChildByName("root_node");
			auto layout_bg = dynamic_cast<ui::Layout*>(node->getChildByName("pnl_item_bg"));
			Vec2 start;
			Vec2 moved;
			float x;
			float y;
			switch (event)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				layout_bg->setBackGroundColor(Color3B(233, 233, 233));
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				start = layout->getTouchBeganPosition();
				moved = layout->getTouchMovePosition();
				x = moved.x - start.x;
				y = moved.y - start.y;
				if (fabs(x) > 50 || fabs(y) > 50) {
					layout_bg->setBackGroundColor(Color3B(255, 255, 255));
				}
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				layout_bg->setBackGroundColor(Color3B(255, 255, 255));
				break;
			default:
				break;
			}
		});
		lvw_talk->pushBackCustomItem(layout);
		//lvw_talk->pushBackDefaultItem();
	}

	// init keep listview
	for (int i = 0; i < 5; i++) {
		auto node = dynamic_cast<cocos2d::Node*>(CSLoader::createNode("scene/main/keep/item/item_keep.csb"));
		node->setName("root_node");
		ui::Layout* layout = ui::Layout::create();
		layout->setSize(node->getContentSize());
		layout->setLayoutType(ui::Layout::Type::VERTICAL);
		layout->addChild(node);
		layout->setTouchEnabled(true);
		// add click listener
		layout->addClickEventListener([](cocos2d::Ref* pSender){
			log("----------item clicked---------");
		});
		// add touch listener
		layout->addTouchEventListener([](cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType event){
			auto layout = dynamic_cast<ui::Layout*>(pSender);
			auto node = layout->getChildByName("root_node");
			auto layout_bg = dynamic_cast<ui::Layout*>(node->getChildByName("pnl_item_bg"));
			Vec2 start;
			Vec2 moved;
			float x;
			float y;
			switch (event)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				layout_bg->setBackGroundColor(Color3B(233, 233, 233));
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				start = layout->getTouchBeganPosition();
				moved = layout->getTouchMovePosition();
				x = moved.x - start.x;
				y = moved.y - start.y;
				if (fabs(x) > 50 || fabs(y) > 50) {
					layout_bg->setBackGroundColor(Color3B(255, 255, 255));
				}
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				layout_bg->setBackGroundColor(Color3B(255, 255, 255));
				break;
			default:
				break;
			}
		});
		lvw_keep->pushBackCustomItem(layout);
	}

	// init find pageview
	pvw_find->removeAllPages();
	pvw_find->addEventListener([](Ref *pSender, ui::PageView::EventType type){
		auto pageview = dynamic_cast<ui::PageView*>(pSender);
		switch (type) {
		case ui::PageView::EventType::TURNING:
			
			break;
		default:
			break;
		}
	});
	for (int i = 0; i < 4; i++) {
		auto layout = ui::Layout::create();
		Size size = pvw_find->getContentSize();
		layout->setContentSize(size);
		
		// init listview
		auto listview = ui::ListView::create();
		listview->setPropagateTouchEvents(false);
		//listview->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(MainStage::onScroll, this));
		for (int j = 0; j < i+2; j++) {
			ui::ImageView* image = nullptr;
			if (j % 2 == 0) {
				image = ui::ImageView::create("scene/main/find/ui/diamond.png");
			}
			else {
				image = ui::ImageView::create("scene/main/find/ui/all_girl.png");
			}
			image->setSwallowTouches(true);
			listview->setBounceEnabled(true);
			listview->setItemsMargin(10.0f);
			listview->setContentSize(size);
			// add click listener
			image->addClickEventListener([](cocos2d::Ref* pSender){
				auto image = dynamic_cast<ui::ImageView*>(pSender);
				log("----------item clicked---------");
			});
			// add touch listener
			image->addTouchEventListener([](cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType event){
				auto image = dynamic_cast<ui::ImageView*>(pSender);
				Vec2 start;
				Vec2 moved;
				float x;
				float y;
				switch (event)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
					image->setScale(1.0f);
					break;
				case cocos2d::ui::Widget::TouchEventType::MOVED:
					start = image->getTouchBeganPosition();
					moved = image->getTouchMovePosition();
					x = moved.x - start.x;
					y = moved.y - start.y;
					if (fabs(x) > 50 || fabs(y) > 50) {
						image->setScale(0.95f);
					}
					break;
				case cocos2d::ui::Widget::TouchEventType::ENDED:
				case cocos2d::ui::Widget::TouchEventType::CANCELED:
					image->setScale(0.95f);
					break;
				default:
					break;
				}
			});
			image->setTouchEnabled(true);
			image->setScale(0.95f);
			listview->pushBackCustomItem(image);
		}

		layout->addChild(listview);
		pvw_find->insertPage(layout, i);
	}

	// init listeners
	img_talk->addClickEventListener(CC_CALLBACK_1(MainStage::onTabClick, this));
	img_keep->addClickEventListener(CC_CALLBACK_1(MainStage::onTabClick, this));
	img_find->addClickEventListener(CC_CALLBACK_1(MainStage::onTabClick, this));
	img_setting->addClickEventListener(CC_CALLBACK_1(MainStage::onTabClick, this));
	// init find tab listener
	lb_gift->addClickEventListener(CC_CALLBACK_1(MainStage::onFindTabClick, this));
	lb_buy_diamond->addClickEventListener(CC_CALLBACK_1(MainStage::onFindTabClick, this));
	lb_msg->addClickEventListener(CC_CALLBACK_1(MainStage::onFindTabClick, this));
	lb_free_diamond->addClickEventListener(CC_CALLBACK_1(MainStage::onFindTabClick, this));

	lvw_talk->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MainStage::onItemClick, this));

	showTab(TAB::TALK);
    return true;
}

void MainStage::onTabClick(cocos2d::Ref *pSender) {
	TAB tab_index = TAB::NONE;
	cocos2d::Node* node = dynamic_cast<cocos2d::Node*> (pSender);
	int tag = node->getTag();
	switch (tag)
	{
	case 19: // talk
		tab_index = TAB::TALK;
		break;
	case 21: // keep
		tab_index = TAB::KEEP;
		break;
	case 22: // find
		tab_index = TAB::FIND;
		break;
	case 23: // setting
		tab_index = TAB::SETTING;
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
	case TAB::TALK:
		showTalkTab();
		break;
	case TAB::KEEP:
		showKeepTab();
		break;
	case TAB::FIND:
		showFindTab();
		break;
	case TAB::SETTING:
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
	case TAB::TALK:
		node = lvw_talk;
		break;
	case TAB::KEEP:
		node = pnl_keep;
		break;
	case TAB::FIND:
		node = pnl_find;
		break;
	case TAB::SETTING:
		node = pnl_setting;
		break;
	default:
		node = nullptr;
		break;
	}
	return node;
}

void MainStage::onFindTabClick(cocos2d::Ref *pSender) {
	FIND_TAB tab_index = FIND_TAB::NONE;
	cocos2d::Node* node = dynamic_cast<cocos2d::Node*> (pSender);
	int tag = node->getTag();
	switch (tag)
	{
	case 193: // gift
		tab_index = FIND_TAB::GIFT;
		break;
	case 194: // buy_diamond
		tab_index = FIND_TAB::BUY_DIAMOND;
		break;
	case 195: // msg
		tab_index = FIND_TAB::MSG;
		break;
	case 196: // free_diamond
		tab_index = FIND_TAB::FREE_DIAMOND;
		break;
	default:
		break;
	}
	showFindTab(tab_index);
}

void MainStage::showFindTab(FIND_TAB tab) {
	// return if click current find tab
	if (current_find_tab == tab) return;
	// reset all find tab bg
	lb_gift->setTextColor(Color4B(101, 176, 101, 255));
	lb_buy_diamond->setTextColor(Color4B(101, 176, 101, 255));
	lb_msg->setTextColor(Color4B(101, 176, 101, 255));
	lb_free_diamond->setTextColor(Color4B(101, 176, 101, 255));
	switch (tab)
	{
	case FIND_TAB::GIFT:
		lb_gift->setTextColor(Color4B(255, 255, 255, 255));
		pvw_find->scrollToPage((int)FIND_TAB::GIFT);
		break;
	case FIND_TAB::BUY_DIAMOND:
		lb_buy_diamond->setTextColor(Color4B(255, 255, 255, 255));
		pvw_find->scrollToPage((int)FIND_TAB::BUY_DIAMOND);
		break;
	case FIND_TAB::MSG:
		lb_msg->setTextColor(Color4B(255, 255, 255, 255));
		pvw_find->scrollToPage((int)FIND_TAB::MSG);
		break;
	case FIND_TAB::FREE_DIAMOND:
		lb_free_diamond->setTextColor(Color4B(255, 255, 255, 255));
		pvw_find->scrollToPage((int)FIND_TAB::FREE_DIAMOND);
		break;
	default:
		break;
	}
	// set current find now
	current_find_tab = tab;
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

void MainStage::onScroll(Ref* pSender, ui::ScrollView::EventType type)
{
	
}