#include "RegisterScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "../utils/NodeUtil.h"
#include "../utils/Util.h"
#include "../core/GameHelper.h"

USING_NS_CC;

using namespace cocostudio::timeline;
Scene* RegisterStage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = RegisterStage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RegisterStage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	GameHelper::getInstance()->init();
	GameHelper::getInstance()->start();

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
	radio_girl = dynamic_cast<cocos2d::Sprite*>(NodeUtil::seekFromRootByName(rootNode, std::string("radio_girl")));
	radio_boy = dynamic_cast<cocos2d::Sprite*>(NodeUtil::seekFromRootByName(rootNode, std::string("radio_boy")));
	tip_yuema = dynamic_cast<cocos2d::Node*>(NodeUtil::seekFromRootByName(rootNode, std::string("tip_yuema")));
	btn_yue = dynamic_cast<cocos2d::ui::Button*>(NodeUtil::seekFromRootByName(rootNode, std::string("btn_yue")));
	btn_girl = dynamic_cast<cocos2d::ui::Button*>(NodeUtil::seekFromRootByName(rootNode, std::string("btn_girl")));
	btn_boy = dynamic_cast<cocos2d::ui::Button*>(NodeUtil::seekFromRootByName(rootNode, std::string("btn_boy")));

	auto tfd_user_name = dynamic_cast<cocos2d::ui::TextField*>(NodeUtil::seekFromRootByName(rootNode, std::string("txt_user_name")));
	auto layer_register = dynamic_cast<cocos2d::Node*>(NodeUtil::seekFromRootByName(rootNode, std::string("layer_register")));
	auto txt_user_name_position = tfd_user_name->getPosition();
	auto txt_user_name_size = tfd_user_name->getContentSize();
	txt_user_name = ui::EditBox::create(txt_user_name_size, ui::Scale9Sprite::create());
	txt_user_name->setPosition(txt_user_name_position);
	txt_user_name->setFontSize(36);
	txt_user_name->setFontColor(Color4B(0,0,0, 255));
	txt_user_name->setMaxLength(8);
	layer_register->addChild(txt_user_name);

	// init sprites data
	txt_user_name->setText(user_name.c_str());

	// init listeners
	btn_yue->addClickEventListener(CC_CALLBACK_1(RegisterStage::onClick, this));
	btn_girl->addClickEventListener(CC_CALLBACK_1(RegisterStage::onClick, this));
	btn_boy->addClickEventListener(CC_CALLBACK_1(RegisterStage::onClick, this));

    return true;
}

void RegisterStage::showYuemaTip() {
	// cocos studio animation
	auto tip_yuema_action = CSLoader::createTimeline("scene/register/ui/tip_yuema.csb");
	tip_yuema->runAction(tip_yuema_action);
	tip_yuema_action->gotoFrameAndPlay(0, 15, false);
}

void RegisterStage::onGirlClick() {
	showYuemaTip();
	auto texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose_pressed.png");
	radio_girl->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose.png");
	radio_boy->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/image/girl.png");
	character->setTexture(texture);
	sex = "girl";
}

void RegisterStage::onBoyClick() {
	showYuemaTip();
	auto texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose.png");
	radio_girl->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/ui/btn_choose_pressed.png");
	radio_boy->setTexture(texture);
	texture = Director::getInstance()->getTextureCache()->addImage("scene/register/image/boy.png");
	character->setTexture(texture);
	sex = "boy";
}

void RegisterStage::onYueClick() {
	user_name = txt_user_name->getText();
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

void RegisterStage::onClick(Ref *pSender) {
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