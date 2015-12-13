#include "PersistenceHelper.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/encodedstream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/pointer.h"
#include "../../utils/Util.h"
#include "../../entity/Entity.h"

using namespace rapidjson;

// instance
PersistenceHelper* PersistenceHelper::m_instance = nullptr;

PersistenceHelper::~PersistenceHelper() {
	if (gameState != nullptr) {
		delete gameState;
		gameState = nullptr;
	}
	if (gameConfig != nullptr) {
		delete gameConfig;
		gameConfig = nullptr;
	}
}

PersistenceHelper* PersistenceHelper::getInstance() {
	if (m_instance == nullptr) {
		m_instance = new PersistenceHelper();
	}
	return m_instance;
}

// 解析JSON
void PersistenceHelper::parse() {
	FILE* fp;
	// 块级作用域
	{
		// parse game config
		fp = fopen(m_configFile.c_str(), "r");
		char buffer[256];
		FileReadStream bis(fp, buffer, sizeof(buffer));
		EncodedInputStream<UTF8<>, FileReadStream> eis(bis);
		configDoc.ParseStream<0, UTF8<>>(eis);
		fclose(fp);
		// start parse config
		gameConfig = new GameConfig();
		// parse [/base]
		GameBase gameBase;
		gameBase.name = GetValueByPointer(configDoc, "/base/name")->GetString();
		gameBase.version = GetValueByPointer(configDoc, "/base/version")->GetString();
		gameBase.good_score = GetValueByPointer(configDoc, "/base/good_score")->GetInt();
		gameBase.max_user = GetValueByPointer(configDoc, "/base/max_user")->GetInt();
		gameBase.max_msg_count = GetValueByPointer(configDoc, "/base/max_msg_count")->GetInt();
		gameBase.max_gold_count = GetValueByPointer(configDoc, "/base/max_gold_count")->GetInt();
		gameBase.msg_recovery_interval = GetValueByPointer(configDoc, "/base/msg_recovery_interval")->GetInt();
		gameBase.first_user_id = GetValueByPointer(configDoc, "/base/first_user_id")->GetString();
		// put base
		gameConfig->base = gameBase;
		// parse [/users]
		Value* usersValue = GetValueByPointer(configDoc, "/users");
		for (Value::ConstMemberIterator itr = usersValue->MemberBegin(); itr != usersValue->MemberEnd(); ++itr) {
			UserInfo info;
			vector<UserRecord> records;
			User user;
			string id = itr->name.GetString();
			for (Value::ConstMemberIterator itr2 = itr->value.MemberBegin(); itr2 != itr->value.MemberEnd(); ++itr2) {
				string key = itr2->name.GetString();
				// parse [/users/:id/info]
				if (key == "info") {
					info.id = id;
					info.name = GetValueByPointer(itr2->value, "/name")->GetString();
					info.sex = GetValueByPointer(itr2->value, "/sex")->GetString();
					info.constellation = GetValueByPointer(itr2->value, "/constellation")->GetString();
					info.height = GetValueByPointer(itr2->value, "/height")->GetString();
					info.weight = GetValueByPointer(itr2->value, "/weight")->GetString();
					info.age = GetValueByPointer(itr2->value, "/age")->GetInt();
					info.career = GetValueByPointer(itr2->value, "/career")->GetString();
					info.type = GetValueByPointer(itr2->value, "/type")->GetInt();
					info.signature = GetValueByPointer(itr2->value, "/signature")->GetString();
					info.information = GetValueByPointer(itr2->value, "/information")->GetString();
					info.price = GetValueByPointer(itr2->value, "/price")->GetInt();
					info.rolewin = GetValueByPointer(itr2->value, "/rolewin")->GetString();
					info.win = GetValueByPointer(itr2->value, "/win")->GetString();
					info.roleover = GetValueByPointer(itr2->value, "/roleover")->GetString();
					info.over = GetValueByPointer(itr2->value, "/over")->GetString();
				}
				else if (key == "records"){ // parse [/users/:id/records]
					for (int i = 0; i < 10; i++) {
						UserRecord record;
						int index = (i + 1) * 10;
						// q
						record.q = GetValueByPointer(itr2->value, JsonUtils::getPoint("/%i", index))->GetString();
						vector<string> a_list;
						vector<int> s_list;
						// a
						a_list.push_back(GetValueByPointer(itr2->value, JsonUtils::getPoint("/%i", index + 1))->GetString());
						a_list.push_back(GetValueByPointer(itr2->value, JsonUtils::getPoint("/%i", index + 2))->GetString());
						a_list.push_back(GetValueByPointer(itr2->value, JsonUtils::getPoint("/%i", index + 3))->GetString());
						// s
						s_list.push_back(GetValueByPointer(itr2->value, JsonUtils::getPoint("/%i", index + 4))->GetInt());
						s_list.push_back(GetValueByPointer(itr2->value, JsonUtils::getPoint("/%i", index + 5))->GetInt());
						s_list.push_back(GetValueByPointer(itr2->value, JsonUtils::getPoint("/%i", index + 6))->GetInt());
						record.a_list = a_list;
						record.s_list = s_list;
						records.push_back(record);
					}
				}
			}
			user.info = info;
			user.records = records;
			// put user
			gameConfig->users.insert(map<string, User>::value_type(id, user));
		}
	}
	 //块级作用域
	{
		// parse game state
		fp = fopen(m_stateFile.c_str(), "r");
		char buffer[256];
		FileReadStream bis(fp, buffer, sizeof(buffer));
		EncodedInputStream<UTF8<>, FileReadStream> eis(bis);
		stateDoc.ParseStream<0, UTF8<>>(eis);
		fclose(fp);
		// start parse state
		gameState = new GameState();
		// parse [/base]
		BaseState baseState;
		baseState.playtime = GetValueByPointer(stateDoc, "/base/playtime")->GetInt64();
		baseState.gold = GetValueByPointer(stateDoc, "/base/gold")->GetInt();
		baseState.last_play_time = GetValueByPointer(stateDoc, "/base/last_play_time")->GetInt64();
		baseState.msg_count = GetValueByPointer(stateDoc, "/base/msg_count")->GetInt();
		baseState.game_state = GetValueByPointer(stateDoc, "/base/game_state")->GetInt();
		// put base
		gameState->base = baseState;
		// parse [/users]
		Value* usersValue = GetValueByPointer(stateDoc, "/users");
		for (Value::ConstMemberIterator itr = usersValue->MemberBegin(); itr != usersValue->MemberEnd(); ++itr) {
			UserInfoState info;
			vector<UserRecordState> records;
			UserState user;
			string id = itr->name.GetString();
			for (Value::ConstMemberIterator itr2 = itr->value.MemberBegin(); itr2 != itr->value.MemberEnd(); ++itr2) {
				string key = itr2->name.GetString();
				// parse [/users/:id/info]
				if (key == "info") {
					info.id = id;
					info.strategy_state = GetValueByPointer(itr2->value, "/strategy_state")->GetInt();
					info.strategy_count = GetValueByPointer(itr2->value, "/strategy_count")->GetInt();
					info.strategy_success_count = GetValueByPointer(itr2->value, "/strategy_success_count")->GetInt();
					info.reply_state = GetValueByPointer(itr2->value, "/reply_state")->GetInt();
					info.reply_time = GetValueByPointer(itr2->value, "/reply_time")->GetInt64();
					info.chum = GetValueByPointer(itr2->value, "/chum")->GetInt();
					info.perfect = GetValueByPointer(itr2->value, "/perfect")->GetInt();
					info.current_q = GetValueByPointer(itr2->value, "/current_q")->GetInt();
					info.a_list_state = GetValueByPointer(itr2->value, "/a_list_state")->GetInt();
					info.appear = GetValueByPointer(itr2->value, "/appear")->GetInt();
				}
				else if (key == "records"){ // parse [/users/:id/records]
					for (Value::ConstValueIterator itr3 = itr2->value.Begin(); itr3 != itr2->value.End(); ++itr3) {
						UserRecordState record;
						record.q = GetValueByPointer(*itr3, "/q")->GetString();
						record.q_time = GetValueByPointer(*itr3, "/q_time")->GetInt64();
						record.a = GetValueByPointer(*itr3, "/a")->GetString();
						record.a_time = GetValueByPointer(*itr3, "/a_time")->GetInt64();
						record.score = GetValueByPointer(*itr3, "/score")->GetInt();
						records.push_back(record);
					}
				}
			}
			user.info = info;
			user.records = records;
			// put user
			gameState->users.insert(map<string, UserState>::value_type(id, user));
		}
	}
}

// 保存JSON
void PersistenceHelper::save() {
	FILE* fp;
	fp = fopen(m_stateFile.c_str(), "w");
	char buffer[256];
	FileWriteStream bos(fp, buffer, sizeof(buffer));
	typedef EncodedOutputStream<UTF8<>, FileWriteStream> OutputStream;
	OutputStream eos(bos, false);
	PrettyWriter<OutputStream, UTF8<>, UTF8<>> writer(eos);
	stateDoc.Accept(writer);
	fclose(fp);
}

// 获取游戏运行状态
GameState* PersistenceHelper::getGameState() {
	return gameState;
}

// 获取游戏配置信息
GameConfig* PersistenceHelper::getGameConfig() {
	return gameConfig;
}

// 新增用户信息
void PersistenceHelper::insertUserInfoState(const UserInfoState userInfoState) {
	string id = userInfoState.id;
	// 首次插入必须先初始化对象
	UserState userState;
	userState.info = userInfoState;
	gameState->users.insert(map<string, UserState>::value_type(id, userState));
	// 创建用户节点
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s", id.c_str()), Value(kObjectType));
	// 创建信息节点
	Value info(kObjectType);
	info.AddMember("strategy_state", Value(kNumberType).SetInt(userInfoState.strategy_state), stateDoc.GetAllocator());
	info.AddMember("strategy_count", Value(kNumberType).SetInt(userInfoState.strategy_count), stateDoc.GetAllocator());
	info.AddMember("strategy_success_count", Value(kNumberType).SetInt(userInfoState.strategy_success_count), stateDoc.GetAllocator());
	info.AddMember("reply_state", Value(kNumberType).SetInt(userInfoState.reply_state), stateDoc.GetAllocator());
	info.AddMember("reply_time", Value(kNumberType).SetInt64(userInfoState.reply_time), stateDoc.GetAllocator());
	info.AddMember("chum", Value(kNumberType).SetInt(userInfoState.chum), stateDoc.GetAllocator());
	info.AddMember("perfect", Value(kNumberType).SetInt(userInfoState.perfect), stateDoc.GetAllocator());
	info.AddMember("current_q", Value(kNumberType).SetInt(userInfoState.current_q), stateDoc.GetAllocator());
	info.AddMember("a_list_state", Value(kNumberType).SetInt(userInfoState.a_list_state), stateDoc.GetAllocator());
	info.AddMember("appear", Value(kNumberType).SetInt(userInfoState.appear), stateDoc.GetAllocator());
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info", id.c_str()), info, stateDoc.GetAllocator());
	// 创建聊天记录节点
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/records", id.c_str()), Value(kArrayType), stateDoc.GetAllocator());
	save();
}

// 删除用户信息
void PersistenceHelper::deleteUserInfoState(const UserInfoState userInfoState) {
	string id = userInfoState.id;
	gameState->users.erase(id);
	EraseValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s", id.c_str()));
	save();
}

// 保存用户信息
void PersistenceHelper::saveUserInfoState(const UserInfoState userInfoState) {
	string id = userInfoState.id;
	gameState->users.find(id)->second.info = userInfoState;
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/strategy_state", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.strategy_state));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/strategy_count", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.strategy_count));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/strategy_success_count", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.strategy_success_count));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/reply_state", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.reply_state));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/reply_time", id.c_str()), 
		Value(kNumberType).SetInt64(userInfoState.reply_time));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/chum", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.chum));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/perfect", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.perfect));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/current_q", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.current_q));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/a_list_state", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.a_list_state));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/info/appear", id.c_str()), 
		Value(kNumberType).SetInt(userInfoState.appear));
	save();
}

// 查询用户信息
UserInfoState PersistenceHelper::findUserInfoState(const UserInfoState params){
	return gameState->users.find(params.id)->second.info;
}

// 查询所有用户信息
vector<UserVo> PersistenceHelper::findAllUserInfoState(map<string, string> params) {
	// 检查是否有ID过滤条件
	map<string, string>::iterator id_filter = params.find("id");
	map<string, string>::iterator reply_state_filter = params.find("reply_state");
	vector<UserVo> userVos;
	map<string, User> usersConfig = gameConfig->users;
	map<string, UserState> usersState = gameState->users;
	for (map<string, User>::iterator itr = usersConfig.begin(); itr != usersConfig.end(); itr++) {
		UserVo userVo;
		map<string, UserState>::iterator itr2 = usersState.find(itr->first);
		if (itr2 != usersState.end()) {
			userVo.userState = itr2->second;
		}
		userVo.user = itr->second;
		// ID过滤符合条件才加入队列
		if (id_filter != params.end()) {
			if (id_filter->second == itr->first) userVos.push_back(userVo);
		}
		else {
			userVos.push_back(userVo);
		}
	}
	return userVos;
}

// 新增聊天记录
void PersistenceHelper::insertUserRecordState(const UserInfoState userInfoState, const UserRecordState userRecordState) {
	string id = userInfoState.id;
	gameState->users.find(id)->second.info = userInfoState;
	gameState->users.find(id)->second.records.push_back(userRecordState);
	// save user info
	saveUserInfoState(userInfoState);
	Value record(kObjectType);
	Value q;
	q.SetString(userRecordState.q.c_str(), userRecordState.q.length(), stateDoc.GetAllocator());
	Value a;
	a.SetString(userRecordState.a.c_str(), userRecordState.a.length(), stateDoc.GetAllocator());
	record.AddMember("q", q, stateDoc.GetAllocator());
	record.AddMember("q_time", Value(kNumberType).SetInt64(userRecordState.q_time), stateDoc.GetAllocator());
	record.AddMember("a", a, stateDoc.GetAllocator());
	record.AddMember("a_time", Value(kNumberType).SetInt64(userRecordState.a_time), stateDoc.GetAllocator());
	record.AddMember("score", Value(kNumberType).SetInt(userRecordState.score), stateDoc.GetAllocator());
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/records/-", id.c_str()), record, stateDoc.GetAllocator());
	save();
}

// 修改聊天记录
void PersistenceHelper::saveUserRecordState(const UserInfoState userInfoState, const UserRecordState userRecordState) {
	string id = userInfoState.id;
	int current_q = userInfoState.current_q;
	gameState->users.find(id)->second.info = userInfoState;
	gameState->users.find(id)->second.records.at(current_q) = userRecordState;
	// save user info
	saveUserInfoState(userInfoState);
	Value record(kObjectType);
	Value q;
	q.SetString(userRecordState.q.c_str(), userRecordState.q.length(), stateDoc.GetAllocator());
	Value a;
	a.SetString(userRecordState.a.c_str(), userRecordState.a.length(), stateDoc.GetAllocator());
	record.AddMember("q", q, stateDoc.GetAllocator());
	record.AddMember("q_time", Value(kNumberType).SetInt64(userRecordState.q_time), stateDoc.GetAllocator());
	record.AddMember("a", a, stateDoc.GetAllocator());
	record.AddMember("a_time", Value(kNumberType).SetInt64(userRecordState.a_time), stateDoc.GetAllocator());
	record.AddMember("score", Value(kNumberType).SetInt(userRecordState.score), stateDoc.GetAllocator());
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/records/%i", id.c_str(), current_q), record, stateDoc.GetAllocator());
	save();
}

// 查询聊天记录
vector<UserRecordState> PersistenceHelper::findUserRecordState(const UserInfoState params) {
	string id = params.id;
	return gameState->users.find(id)->second.records;
}

// 清空聊天记录
void PersistenceHelper::cleanUserRecordState(const UserInfoState params) {
	string id = params.id;
	gameState->users.find(id)->second.records.empty();
	EraseValueByPointer(stateDoc, JsonUtils::getPoint("/users/%s/records", id.c_str()));
	save();
}

// 保存游戏信息
void PersistenceHelper::saveBaseState(const BaseState baseState) {
	gameState->base = baseState;
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/base/playtime"), Value(kNumberType).SetInt64(baseState.playtime));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/base/gold"), Value(kNumberType).SetInt(baseState.gold));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/base/last_play_time"), Value(kNumberType).SetInt64(baseState.last_play_time));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/base/msg_count"), Value(kNumberType).SetInt(baseState.msg_count));
	SetValueByPointer(stateDoc, JsonUtils::getPoint("/base/game_state"), Value(kNumberType).SetInt(baseState.game_state));
	save();
}

// 保证JSON节点存在
void PersistenceHelper::ensureNodeExist(char ch[]) {
}

// 设置配置文件、状态文件路径
void PersistenceHelper::setFilePaths(string configFile, string stateFile) {
	m_configFile = configFile;
	m_stateFile = stateFile;
}