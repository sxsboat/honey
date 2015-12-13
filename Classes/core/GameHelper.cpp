#include "GameHelper.h"
#include "cocostudio/CocoStudio.h"
#include "../utils/Util.h"

GameHelper* GameHelper::m_instance = nullptr;
GameHelper* GameHelper::getInstance() {
	if (m_instance == nullptr) {
		m_instance = new GameHelper();
	}
	return m_instance;
}

void GameHelper::init() {
	copy();
	parse();
	initData();
}

void GameHelper::copy() {
	FileUtils* fileUtils = FileUtils::getInstance();
	string writablePath = fileUtils->getWritablePath();
	string writableConfigFile = string(writablePath).append("data/config.json");
	string writableStateFile = string(writablePath).append("data/state.json");
	if (!fileUtils->isDirectoryExist(string(writablePath).append("data"))) {
		fileUtils->createDirectory(string(writablePath).append("data"));
	}
	// 文件不存在则copy
	if (!fileUtils->isFileExist(writableConfigFile)) {
		string fileStr = fileUtils->getStringFromFile("data/config.json");
		MeFileUtils::writeStringToFile(fileStr, writableConfigFile);
		
	}
	if (!fileUtils->isFileExist(writableStateFile)) {
		string fileStr = fileUtils->getStringFromFile("data/state.json");
		MeFileUtils::writeStringToFile(fileStr, writableStateFile);
	}
	PersistenceHelper::getInstance()->setFilePaths(writableConfigFile, writableStateFile);
}

// 解析JSON
void GameHelper::parse() {
	PersistenceHelper::getInstance()->parse();
}

// 初始化数据
void GameHelper::initData() {
	GameConfig* gameConfig = GameHelper::getInstance()->getPersistenceHelper()->getGameConfig();
	GameState* gameState = GameHelper::getInstance()->getPersistenceHelper()->getGameState();
	// 初始化游戏
	BaseState baseState = gameState->base;
	if (baseState.game_state == 0) {
		string id = gameConfig->base.first_user_id;
		map<string, string> params;
		params.insert(map<string, string>::value_type("id", id));
		vector<UserVo> userVos = GameHelper::getInstance()->getPersistenceHelper()->findAllUserInfoState(params);
		UserVo userVo = userVos.at(0);
		// 插入用户基本信息
		UserInfoState userInfoState;
		userInfoState.id = id;
		GameHelper::getInstance()->getPersistenceHelper()->insertUserInfoState(userInfoState);
		// 插入聊天信息
		UserRecordState userRecordState;
		userRecordState.q = userVo.user.records.at(0).q;
		userRecordState.q_time = DateUtils::currentTimestamp();
		userInfoState.current_q = 0;
		GameHelper::getInstance()->getPersistenceHelper()->insertUserRecordState(userInfoState, userRecordState);
		baseState.game_state = 1;
		GameHelper::getInstance()->getPersistenceHelper()->saveBaseState(baseState);
	}
}

// 开始游戏
void GameHelper::start() {
	for (int i = 1; i < 5; i++) {
		map<string, string> params;
		params.insert(map<string, string>::value_type("id", "1"));
		vector<UserVo> userVos = GameHelper::getInstance()->getPersistenceHelper()->findAllUserInfoState(params);
		UserInfoState userInfoState = userVos.at(0).userState.info;
		userInfoState.current_q = i;
		UserRecordState userRecordState;
		userRecordState.q = userVos.at(0).user.records.at(i).q;
		userRecordState.q_time = DateUtils::currentTimestamp();
		userRecordState.a = userVos.at(0).user.records.at(i).a_list.at(0);
		userRecordState.a_time = DateUtils::currentTimestamp();
		userRecordState.score = userVos.at(0).user.records.at(i).s_list.at(0);
		GameHelper::getInstance()->getPersistenceHelper()->insertUserRecordState(userInfoState, userRecordState);
	}
	
}

// 保存状态
void GameHelper::save() {
	PersistenceHelper::getInstance()->save();
}

PersistenceHelper* GameHelper::getPersistenceHelper() {
	return PersistenceHelper::getInstance();
}