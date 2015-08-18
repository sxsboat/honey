#ifndef __YUEMA_ENTITY_H__
#define __YUEMA_ENTITY_H__

#include "cocos2d.h"
#include <vector>

// 聊天记录实体类
class RecordEntity
{
public:
};

// 角色信息实体类
class CharcaterInfoEntity
{
public:

	CharcaterInfoEntity(){};

	// 问题列表
	std::vector<std::string> questions;
	
	// 回复列表
	std::vector<std::vector<std::string>> answers;

	// 分值
	std::vector<std::vector<int>> scores;

	std::string name;
	int age;
	std::string job;
	std::string height;
	std::string weight;
	std::string loves;
	std::string constellation;
	std::string hobby;
	std::string talk;
	std::string sound;
	std::string About;
	std::string About_1;
	std::string RoleWin;
	std::string Win;
	std::string RoleOver;
	std::string Over;
};

// 角色列表类
class CharcaterEntity
{
public:
	std::map<int, CharcaterInfoEntity> charcaters;
};

#endif // __YUEMA_ENTITY_H__
