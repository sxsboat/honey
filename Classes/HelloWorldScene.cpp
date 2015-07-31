#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "NodeUtil.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	// init data
	sex = "girl";
	user_name = UserDefault::getInstance()->getStringForKey("user_name");

	// init layer
    auto rootNode = CSLoader::createNode("scene/register/scene.csb");
	auto size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);
    addChild(rootNode);

	// init sprites
	character = dynamic_cast<Sprite*>(NodeUtil::seekFromRootByName(rootNode, std::string("character")));
	txt_user_name = dynamic_cast<cocos2d::ui::TextField*>(NodeUtil::seekFromRootByName(rootNode, std::string("txt_user_name")));
	radio_girl = dynamic_cast<cocos2d::Sprite*>(NodeUtil::seekFromRootByName(rootNode, std::string("radio_girl")));
	radio_boy = dynamic_cast<cocos2d::Sprite*>(NodeUtil::seekFromRootByName(rootNode, std::string("radio_boy")));
	tip_yuema = dynamic_cast<cocos2d::Node*>(NodeUtil::seekFromRootByName(rootNode, std::string("tip_yuema")));
	btn_yue = dynamic_cast<cocos2d::ui::Button*>(NodeUtil::seekFromRootByName(rootNode, std::string("btn_yue")));
	btn_girl = dynamic_cast<cocos2d::ui::Button*>(NodeUtil::seekFromRootByName(rootNode, std::string("btn_girl")));
	btn_boy = dynamic_cast<cocos2d::ui::Button*>(NodeUtil::seekFromRootByName(rootNode, std::string("btn_boy")));

	// init sprites data
	txt_user_name->setText(user_name);

	// init listeners
	btn_yue->addClickEventListener(CC_CALLBACK_1(HelloWorld::onClick, this));
	btn_girl->addClickEventListener(CC_CALLBACK_1(HelloWorld::onClick, this));
	btn_boy->addClickEventListener(CC_CALLBACK_1(HelloWorld::onClick, this));

    return true;
}

void HelloWorld::showYuemaTip() {
	// cocos studio animation
	auto tip_yuema_action = CSLoader::createTimeline("scene/register/ui/tip_yuema.csb");
	tip_yuema->runAction(tip_yuema_action);
	tip_yuema_action->gotoFrameAndPlay(0, 15, false);
}

void HelloWorld::onGirlClick() {
	showYuemaTip();
	auto texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose_pressed.png");
	radio_girl->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose.png");
	radio_boy->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/image/girl.png");
	character->setTexture(texture);
	sex = "girl";
}

void HelloWorld::onBoyClick() {
	showYuemaTip();
	auto texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose.png");
	radio_girl->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose_pressed.png");
	radio_boy->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/image/boy.png");
	character->setTexture(texture);
	sex = "boy";
}

void HelloWorld::onYueClick() {
	user_name = txt_user_name->getStringValue();
	if (user_name.empty()) {
		showYuemaTip();
	}
	else
	{
		// save user name and sex
		UserDefault::getInstance()->setStringForKey("user_name", user_name);
		UserDefault::getInstance()->setStringForKey("sex", sex);
		auto scene = MainStage::createScene();
		auto transitions = TransitionFade::create(0.5f, scene);
		Director::getInstance()->replaceScene(transitions);
	}
}

void HelloWorld::onClick(Ref *pSender) {
	cocos2d::Node* node = dynamic_cast<cocos2d::Node*> (pSender);
	int tag = node->getTag();
	switch (tag)
	{
		case 4149: // girl
			onGirlClick();
			break;
		case 4148: // boy
			onBoyClick();
			break;
		case 4143: // yue
			onYueClick();
			break;
		default:
			break;
	}
}