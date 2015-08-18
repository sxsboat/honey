#ifndef __YUEMA_ENTITY_H__
#define __YUEMA_ENTITY_H__

#include "cocos2d.h"
#include <vector>

// �����¼ʵ����
class RecordEntity
{
public:
};

// ��ɫ��Ϣʵ����
class CharcaterInfoEntity
{
public:

	CharcaterInfoEntity(){};

	// �����б�
	std::vector<std::string> questions;
	
	// �ظ��б�
	std::vector<std::vector<std::string>> answers;

	// ��ֵ
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

// ��ɫ�б���
class CharcaterEntity
{
public:
	std::map<int, CharcaterInfoEntity> charcaters;
};

#endif // __YUEMA_ENTITY_H__
