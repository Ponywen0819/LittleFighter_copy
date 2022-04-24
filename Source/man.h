#pragma once

#include "Bitmaplib.h"
#include "skills.h"
#include "Area.h"
#include "CStateBar.h"
#include <string>
#include <map>
#include "Frame.h"


namespace game_framework {
	class obj{
	public:
		obj() { Frams = nullptr; _mode = 0; _x = _y = _z = 0.0; }
		obj(std::map<int, Frame> *f) {
			Frams = f;
		}

	protected:
		std::map<int, Frame> *Frams;
		int		_mode;			//現在的模式
		float	_x, _y, _z;		//現在的位置
	};

	class man:public obj{
	public:
		man() {
			charector = 0;
			_Double_Tap_Gap = 30;
			initG = 0;
			time = 0;
			Walk_Ani_num = 5;
			
			commandBuffer = "";

			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			first_att_animation = true;
			_outofctrl = false;
			jumpType = false;
			walk_Ani_dir = true;
			run_Ani_dir = true;
			JumpUp = false;
			JumpDown = false;
			JumpFront = false;
		}
		~man() {

		}
		// 設定初始庫
		void	init(Bitmaplib *l, man *m, int n,CStateBar *state, std::map<int, Frame> *f);		

		// 設定初始位置
		void	setInitPosotion(int x, int y);		

		// 設定指令
		void	setComm(UINT comm);					
		// 取消指令
		void	cComm(UINT comm);					

		void	checkbeenatt(skillsContainer &con);	// 被攻擊偵測
		void	OnMove();							// 改變位置
		void	onShow();							// 顯示

		void setCH(int ch) {						//設定是哪個腳色
			charector = ch;
		}
		
		bool	out() { return inMotion; }
		int		gotMode() { return _mode; }
		int		getx() { return int(_x); }
		int		gety() { return int(_y); }
		int		getz() { return int(_z); }
		int		getNext() { return (*Frams)[_mode]._next; }

	protected:
		int		getNextWalkMotion() {
			if (walk_Ani_dir) {
				if (++Walk_Ani_num == 9) {
					Walk_Ani_num = 7;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			else {
				if (--Walk_Ani_num == 4) {
					Walk_Ani_num = 6;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			return Walk_Ani_num;
		}
		void	adjustPosition(int f_now,int f_next);

		bool	inMotion;							// 是否在特殊動作裡

		virtual void otherCommand(int n);
		virtual void readOtherList();

		vector<std::string> commandList;		// 被讀取的指令列表
		
		bool _outofctrl;					
	
		void setPosotion(int n);


		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

		// 計數器

		void setTimmer(int t) { time = t; }
		void Count() {if (time > 0) time--;}
		bool isTime() { return time == 0; }			

		void backToRandon();			// 回到原始的狀態
		void toMotion(int next);		// 處發動作
		void nextFrame();				// 動作中的下一個Frame
		

		// 指令輸入間隔

		void setCountDwon();					//連點倒數
		void resetCountDown();					//連點倒數歸零
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }

	private:
		float	initG;							// 設定上升速度
		int		Walk_Ani_num;					// 下一個走路動作的號碼
		bool	JumpUp, JumpDown,JumpFront;		// 斜跳

		int		charector;						// 選擇之腳色

		int		_Double_Tap_Gap;				// 連點間隔
		
		int		NumOfMan;						// 在場上的人
		int		time;							// 計數

		bool	jumpType;
		bool	Face_to_Left;					// 面相方向
		bool	_dir[4];						// 方向
		bool	flag[7];						// keyboard input flag
		bool	first_att_animation;			// 是不是出左拳
		bool	Alive;							// 是否活著
		
		
		bool	walk_Ani_dir;					// 走路動作的方向
		bool	run_Ani_dir;					// 跑步動作的方向

		std::string commandBuffer;				// input command buffer
		
		Bitmaplib *	lib;						// 圖片輸出
		CStateBar *	_s;							// 血量條

		man *		mans;						// 在場上的人	
		man *		gotCatch;					// 被抓的人
	};

	class weapon:public obj{
	public:
		weapon() { _mode = 0; }
		
		void init(std::map<int, Frame> *f){
			Frams = f;
			hp = 200;
		}

		void OnMove() {
			if (IsHolding) {
				//獲取man的位置與更新位置
			}
		}
		void OnShow();
	private:
		man*	holding;		//誰再拿他
		bool	IsHolding;		//有被拾取

		int hp;
	};

}
