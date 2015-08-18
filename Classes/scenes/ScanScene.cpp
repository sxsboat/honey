#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ScanScene.h"
#include "../utils/NodeUtil.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* ScanStage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = ScanStage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ScanStage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("scene/scan/scene.csb");
	auto size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);
    addChild(rootNode);

	img_back = dynamic_cast<cocos2d::ui::ImageView*>(NodeUtil::seekFromRootByName(rootNode, std::string("img_back")));
	lb_time = dynamic_cast<cocos2d::ui::Text*>(NodeUtil::seekFromRootByName(rootNode, std::string("lb_time")));
	spr_light = dynamic_cast<cocos2d::Sprite*>(NodeUtil::seekFromRootByName(rootNode, std::string("spr_light")));
	// add click listener
	img_back->addClickEventListener([](cocos2d::Ref* pSender){
		Director::getInstance()->popScene();
	});
    return true;
}

void ScanStage::update(float dt) {
	lb_time->setText(StringUtils::format("%f", dt));
}

void ScanStage::onEnter() {
	Node::onEnter();
	auto action = RotateBy::create(10.0f, 360.0f);
	spr_light->runAction(RepeatForever::create(action));
	scheduleUpdate();
}

void ScanStage::onExit() {
	Node::onExit();
}