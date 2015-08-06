#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ChatScene.h"
#include "NodeUtil.h"

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
	// add click listener
	img_back->addClickEventListener([](cocos2d::Ref* pSender){
		Director::getInstance()->popScene();
	});

    return true;
}
