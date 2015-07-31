#include "NodeUtil.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

Node* NodeUtil::seekFromRootByName(cocos2d::Node* root, std::string name) {
	if (!root) return nullptr;
	if (root->getName() == name) return root;
	const auto& children = root->getChildren();
	for (auto& child : children) {
		Node* p_node = dynamic_cast<Node*>(child);
		if (p_node) {
			Node* node = seekFromRootByName(p_node, name);
			if (node) return node;
		}
	}
	return nullptr;
}


