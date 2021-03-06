#ifndef __REGISTER_SCENE_H__
#define __REGISTER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class RegisterStage : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(RegisterStage);

	// listeners
	void onClick(Ref *pSender);

private:
	// properties
	std::string user_name;
	std::string sex;

	// sprites
	cocos2d::Sprite* character;
	cocos2d::Sprite* radio_girl;
	cocos2d::Sprite* radio_boy;
	cocos2d::Node* tip_yuema;
	cocos2d::ui::Button* btn_yue;
	cocos2d::ui::Button* btn_girl;
	cocos2d::ui::Button* btn_boy;
	cocos2d::ui::EditBox* txt_user_name;

	// show yuema tip
	void showYuemaTip();
	void onGirlClick();
	void onBoyClick();
	void onYueClick();
};

#endif // __REGISTER_SCENE_H__
