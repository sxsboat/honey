/*
* intֵĬ����-1���������㽫������Ϊ��������
*/
#ifndef __YUEMA_ENTITY_H__
#define __YUEMA_ENTITY_H__

#include <vector>
#include <map>

using namespace std;

// ������Ϣ״̬
struct BaseState
{
	// ����Ϸʱ��
	long playtime = -1L;
	// �������
	int gold = -1;
	// ����˳�ʱ��
	long last_play_time = -1;
	// ��������
	int msg_count = -1;
	// ��Ϸ״̬ 0�ȴ���ʼ��1����2������3������99δ֪����
	int game_state = -1;
};

// �û���Ϣ״̬
struct UserInfoState
{
	// �û�ID
	string id;
	// ����״̬ 0������1�ɹ�2ʧ��
	int strategy_state = -1;
	// �����ܴ���
	int strategy_count = -1;
	// ���Գɹ�����
	int strategy_success_count = -1;
	// �ظ�״̬ 0�ȴ���һظ�1����ѻظ�
	int reply_state = -1;
	// �ظ�ʱ���
	long reply_time = -1L;
	// ���� 0��1��
	int chum = -1;
	// �������� 0��1��
	int perfect = -1;
	// ��ǰ��Ŀ����
	int current_q = -1;
	// ��ǰ����״̬ 000��001��ʮ���Ʊ�ʾ
	int a_list_state = -1;
	// �Ƿ���� 0��1��
	int appear = -1;
};

// �û������¼
struct UserRecordState
{
	// ����
	string q;
	// ����ʱ��
	long q_time = -1L;
	// �ظ�
	string a;
	// �ظ�ʱ��
	long a_time = -1L;
	// �÷�
	int score = -1;
};

// �û�״̬
struct UserState
{
	// �û�״̬
	UserInfoState info;
	// �����¼
	vector<UserRecordState> records;
};

// ��Ϸ״̬
struct GameState
{
	// ��Ϸ����״̬
	BaseState base;
	// ����״̬
	map<string, UserState> users;
};

// ��Ϸ����
struct GameBase
{
	// ��Ϸ��
	string name;
	// ��Ϸ�汾
	string version;
	// ���﹥����ͷ���
	int good_score = -1;
	// ͬʱ��������
	int max_user = -1;
	// ����������
	int max_msg_count = -1;
	// ���������
	int max_gold_count = -1;
	// ���Żظ�Ƶ�� ��λ��
	int msg_recovery_interval = -1;
	// �׷�����ID
	string first_user_id;
};

// �û�������Ϣ
struct UserInfo
{
	// �û�ID
	string id;
	// ����
	string name;
	// �Ա�
	string sex;
	// ����
	string constellation;
	// ���
	string height;
	// ����
	string weight;
	// ����
	int age = -1;
	// ְҵ
	string career;
	// ���� 0��ͨ1������
	int type = -1;
	// ǩ��
	string signature;
	// ������Ϣ
	string information;
	// �ۼ�
	int price = -1;
	// ���Գɹ�
	string rolewin;
	// ���Գɹ��ظ�
	string win;
	// ����ʧ��
	string roleover;
	// ����ʧ�ܻظ�
	string over;
};

// �û��Ի���Ϣ
struct UserRecord
{
	// ����
	string q;
	// ���б�
	vector<string> a_list;
	// �÷��б�
	vector<int> s_list;
};

// �û���Ϣ
struct User
{
	// �û�������Ϣ
	UserInfo info;
	// �û��Ի���Ϣ
	vector<UserRecord> records;
};

// ��Ϸ������Ϣ
struct GameConfig {
	// ��������
	GameBase base;
	// ����״̬
	map<string, User> users;
};

// �ۺ��û���Ϣ
struct UserVo {
	// �û�������Ϣ
	User user;
	// �û�״̬��Ϣ
	UserState userState;
};
#endif // __YUEMA_ENTITY_H__
