#ifndef __YUEMA_GAME_HELPER_H__
#define __YUEMA_GAME_HELPER_H__
#include "core\db\PersistenceHelper.h"

class GameHelper
{
public:
	static GameHelper* getInstance();
	// 初始化
	void init();
	// 开始游戏
	void start();
	// 保存状态
	void save();
	PersistenceHelper* getPersistenceHelper();
private:
	static GameHelper* m_instance;
	GameHelper() {};
	class Garbo
	{
	public:
		~Garbo() {
			if (GameHelper::m_instance) delete GameHelper::m_instance;
		}
	};
	static Garbo barbo;

	// 复制JSON
	void copy();
	// 解析JSON
	void parse();
	// 初始化数据
	void initData();
};

#endif // __YUEMA_GAME_HELPER_H__
