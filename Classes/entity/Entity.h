/*
* int值默认是-1，这样方便将对象作为条件传入
*/
#ifndef __YUEMA_ENTITY_H__
#define __YUEMA_ENTITY_H__

#include <vector>
#include <map>

using namespace std;

// 基本信息状态
struct BaseState
{
	// 总游戏时间
	long playtime = -1L;
	// 金币总数
	int gold = -1;
	// 最后退出时间
	long last_play_time = -1;
	// 短信总数
	int msg_count = -1;
	// 游戏状态 0等待初始化1正常2待升级3升级中99未知错误
	int game_state = -1;
};

// 用户信息状态
struct UserInfoState
{
	// 用户ID
	string id;
	// 攻略状态 0攻略中1成功2失败
	int strategy_state = -1;
	// 攻略总次数
	int strategy_count = -1;
	// 攻略成功次数
	int strategy_success_count = -1;
	// 回复状态 0等待玩家回复1玩家已回复
	int reply_state = -1;
	// 回复时间戳
	long reply_time = -1L;
	// 密友 0否1是
	int chum = -1;
	// 完美攻略 0否1是
	int perfect = -1;
	// 当前题目索引
	int current_q = -1;
	// 当前答题状态 000、001的十进制表示
	int a_list_state = -1;
	// 是否出场 0否1是
	int appear = -1;
};

// 用户聊天记录
struct UserRecordState
{
	// 问题
	string q;
	// 提问时间
	long q_time = -1L;
	// 回复
	string a;
	// 回复时间
	long a_time = -1L;
	// 得分
	int score = -1;
};

// 用户状态
struct UserState
{
	// 用户状态
	UserInfoState info;
	// 聊天记录
	vector<UserRecordState> records;
};

// 游戏状态
struct GameState
{
	// 游戏基本状态
	BaseState base;
	// 人物状态
	map<string, UserState> users;
};

// 游戏配置
struct GameBase
{
	// 游戏名
	string name;
	// 游戏版本
	string version;
	// 人物攻略最低分数
	int good_score = -1;
	// 同时出场人数
	int max_user = -1;
	// 最大短信数量
	int max_msg_count = -1;
	// 最大金币数量
	int max_gold_count = -1;
	// 短信回复频率 单位秒
	int msg_recovery_interval = -1;
	// 首发人物ID
	string first_user_id;
};

// 用户基本信息
struct UserInfo
{
	// 用户ID
	string id;
	// 名字
	string name;
	// 性别
	string sex;
	// 星座
	string constellation;
	// 身高
	string height;
	// 体重
	string weight;
	// 年龄
	int age = -1;
	// 职业
	string career;
	// 类型 0普通1仅聊天
	int type = -1;
	// 签名
	string signature;
	// 个人信息
	string information;
	// 售价
	int price = -1;
	// 攻略成功
	string rolewin;
	// 攻略成功回复
	string win;
	// 攻略失败
	string roleover;
	// 攻略失败回复
	string over;
};

// 用户对话信息
struct UserRecord
{
	// 问题
	string q;
	// 答案列表
	vector<string> a_list;
	// 得分列表
	vector<int> s_list;
};

// 用户信息
struct User
{
	// 用户基本信息
	UserInfo info;
	// 用户对话信息
	vector<UserRecord> records;
};

// 游戏基本信息
struct GameConfig {
	// 基本配置
	GameBase base;
	// 人物状态
	map<string, User> users;
};

// 聚合用户信息
struct UserVo {
	// 用户基本信息
	User user;
	// 用户状态信息
	UserState userState;
};
#endif // __YUEMA_ENTITY_H__
