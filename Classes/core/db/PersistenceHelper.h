#ifndef __YUEMA_PERSISTENCE_HELPER_H__
#define __YUEMA_PERSISTENCE_HELPER_H__
#include "rapidjson\document.h"
#include "..\..\entity\Entity.h"

using namespace rapidjson;

class PersistenceHelper
{
public:
	~PersistenceHelper();
	static PersistenceHelper* getInstance();
	// 解析JSON
	void parse();
	// 保存JSON
	void save();
	// 获取游戏运行状态
	GameState* getGameState();
	// 获取游戏配置信息
	GameConfig* getGameConfig();
	// 新增用户信息
	void insertUserInfoState(const UserInfoState userInfoState);
	// 删除用户信息
	void deleteUserInfoState(const UserInfoState userInfoState);
	// 保存用户信息
	void saveUserInfoState(const UserInfoState userInfoState);
	// 查询用户信息
	UserInfoState findUserInfoState(const UserInfoState params);
	// 查询所有用户信息
	vector<UserVo> findAllUserInfoState(map<string, string> params);
	// 新增聊天记录
	void insertUserRecordState(const UserInfoState userInfoState, const UserRecordState userRecordState);
	// 保存聊天记录
	void saveUserRecordState(const UserInfoState userInfoState, const UserRecordState userRecordState);
	// 查询聊天记录
	vector<UserRecordState> findUserRecordState(const UserInfoState params);
	// 清空聊天记录
	void cleanUserRecordState(const UserInfoState params);
	// 保存游戏信息
	void saveBaseState(const BaseState baseState);
	// 设置配置文件、状态文件路径
	void setFilePaths(string configFile, string stateFile);
private:
	static PersistenceHelper* m_instance;
	PersistenceHelper() {};
	class Garbo
	{
	public:
		~Garbo() {
			if (PersistenceHelper::m_instance) delete PersistenceHelper::m_instance;
		}
	};
	static Garbo barbo;
	string m_configFile;
	string m_stateFile;
	Document configDoc;
	Document stateDoc;
	GameState* gameState;
	GameConfig* gameConfig;
	// 保证JSON节点存在
	void ensureNodeExist(char ch[]);
};

#endif // __YUEMA_PERSISTENCE_HELPER_H__
