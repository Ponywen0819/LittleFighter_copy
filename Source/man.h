#pragma once

#include "Bitmaplib.h"
#include "skills.h"
#include "Area.h"
#include "CStateBar.h"
#include <string>
#include <map>
#include "Frame.h"

#define TEST true

namespace game_framework {

	#define height 28
	#define MAN_DIZZY 903
	class obj{
	public:
		obj() { Frams = nullptr; }
		obj(std::map<int, Frame> *f) {
			Frams = f;
		}

	protected:
		std::map<int, Frame> *Frams;
		int		_mode;			//�{�b���Ҧ�

		int		_x, _y, _z;		//�{�b����m
	};

	class man:public obj{
	public:
		man() {
			Body.init(_x+25, _y+15, 25, 64);
			charector = 0;
			_x = _y = _z = 0;
			_mode = 0;
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
		void init(Bitmaplib *l, man *m, int n,CStateBar *state, std::map<int, Frame> *f);		// �]�w��l�w
		void setInitPosotion(int x, int y);			// �]�w��l��m
		
		void LoadBitmap();							// ���J�ϧ�

		void setComm(UINT comm);					// �]�w���O
		void cComm(UINT comm);						// �������O

		void OnMove();								// ���ܦ�m
		void onShow();								// ���

		void checkbeenatt(skillsContainer &con);	// �Q��������
		
		bool	NearBy(const man &other);				// �b����
		bool	FaceTo(const man &other);
		bool	out() { return inMotion; }
		int		gotMode() { return _mode; }
		int		getx() { return _x; }
		int		gety() { return _y; }
		int		getz() { return _z; }
		int		getNext() { return (*Frams)[_mode]._next; }

	protected:
		int getNextWalkMotion() {
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
		void adjustPosition(int f_now,int f_next);

		bool inMotion;							// �O�_�b�S��ʧ@��

		area itr;								// �����P�w�d��

		int * extra(std::string &line, std::string *tar,int number);
		virtual void otherCommand(int n);
		virtual void readOtherList();
		vector<std::string> commandList;		// �QŪ�������O�C��
		int _mode;								// �ثe�ʧ@
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

		// Ū��Frame���
		void loadFrame();				

		void backToRandon();			// �^���l�����A
		void toMotion(int next);		// �B�o�ʧ@
		void nextFrame();				// �ʧ@�����U�@��Frame
		

		// ���O��J���j

		void setCountDwon();					//�s�I�˼�
		void resetCountDown();					//�s�I�˼��k�s
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }

	private:
		bool	rising;							// �b�W���٬O�U��
		int		initG;							// �]�w�W�ɳt��
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
		bool	first_att_animation;
		bool	Alive;							// �O�_����
		
		
		bool	walk_Ani_dir;					// �����ʧ@����V
		bool	run_Ani_dir;					// �]�B�ʧ@����V

		area	Body;							// ����HitBox

		std::string commandBuffer;				// input command buffer

		Skills*		now;						// �{�b���ۦ�
		
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
