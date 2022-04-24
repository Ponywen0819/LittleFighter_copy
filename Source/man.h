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
		int		_mode;			//�{�b���Ҧ�
		float	_x, _y, _z;		//�{�b����m
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
		// �]�w��l�w
		void	init(Bitmaplib *l, man *m, int n,CStateBar *state, std::map<int, Frame> *f);		

		// �]�w��l��m
		void	setInitPosotion(int x, int y);		

		// �]�w���O
		void	setComm(UINT comm);					
		// �������O
		void	cComm(UINT comm);					

		void	checkbeenatt(skillsContainer &con);	// �Q��������
		void	OnMove();							// ���ܦ�m
		void	onShow();							// ���

		void setCH(int ch) {						//�]�w�O���Ӹ}��
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

		bool	inMotion;							// �O�_�b�S��ʧ@��

		virtual void otherCommand(int n);
		virtual void readOtherList();

		vector<std::string> commandList;		// �QŪ�������O�C��
		
		bool _outofctrl;					
	
		void setPosotion(int n);


		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

		// �p�ƾ�

		void setTimmer(int t) { time = t; }
		void Count() {if (time > 0) time--;}
		bool isTime() { return time == 0; }			

		void backToRandon();			// �^���l�����A
		void toMotion(int next);		// �B�o�ʧ@
		void nextFrame();				// �ʧ@�����U�@��Frame
		

		// ���O��J���j

		void setCountDwon();					//�s�I�˼�
		void resetCountDown();					//�s�I�˼��k�s
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }

	private:
		float	initG;							// �]�w�W�ɳt��
		int		Walk_Ani_num;					// �U�@�Ө����ʧ@�����X
		bool	JumpUp, JumpDown,JumpFront;		// �׸�

		int		charector;						// ��ܤ��}��

		int		_Double_Tap_Gap;				// �s�I���j
		
		int		NumOfMan;						// �b���W���H
		int		time;							// �p��

		bool	jumpType;
		bool	Face_to_Left;					// ���ۤ�V
		bool	_dir[4];						// ��V
		bool	flag[7];						// keyboard input flag
		bool	first_att_animation;			// �O���O�X����
		bool	Alive;							// �O�_����
		
		
		bool	walk_Ani_dir;					// �����ʧ@����V
		bool	run_Ani_dir;					// �]�B�ʧ@����V

		std::string commandBuffer;				// input command buffer
		
		Bitmaplib *	lib;						// �Ϥ���X
		CStateBar *	_s;							// ��q��

		man *		mans;						// �b���W���H	
		man *		gotCatch;					// �Q�쪺�H
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
				//���man����m�P��s��m
			}
		}
		void OnShow();
	private:
		man*	holding;		//�֦A���L
		bool	IsHolding;		//���Q�B��

		int hp;
	};

}
