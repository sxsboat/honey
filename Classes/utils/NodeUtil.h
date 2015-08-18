#ifndef __NODE_UTIL_H__
#define __NODE_UTIL_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class NodeUtil
{
public:
	// seek node by name
	static cocos2d::Node* seekFromRootByName(cocos2d::Node* root, std::string name);
};
#endif // __NODE_UTIL_H__
