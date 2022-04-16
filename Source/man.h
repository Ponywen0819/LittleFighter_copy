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
	class man{
	public:
		man() {
			Body.init(_x+25, _y+15, 25, 64);
			charector = 0;
			_x = _y = _z = 0;
			_mode = 0;
			jumpAnimationGap = 0;
			attAnimationGap = 0;
			recoverGap = 50;
			_Double_Tap_Gap = 30;
			stonkcount = 6;
			punch_fall = 2;
			initG = height;
			time = 0;
			
			commandBuffer = "";
			setJumpCount();

			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			first_att_animation = true;
			_outofctrl = false;
			_isDizzy = false;
			jumpType = false;
			walk_Ani_dir = true;
			run_Ani_dir = true;
		}
		man(int x, int y);
		~man() {

		}
		void init(Bitmaplib *l, man *m, int n,CStateBar *state);		// �]�w��l�w
		void setInitPosotion(int x, int y);			// �]�w��l��m
		void LoadBitmap();							// ���J�ϧ�

		void setComm(UINT comm);					// �]�w���O
		void cComm(UINT comm);						// �������O

		void OnMove();								// ���ܦ�m
		void onShow();								// ���

		void checkbeenatt(skillsContainer &con);	// �Q��������
		Skills* usingSkill();						// ���L�ϥΩۦ�
		bool NearBy(const man &other);				// �b����
		bool FaceTo(const man &other);
		bool out() { return _outofctrl; }
		bool isDizzy() { return _isDizzy; }
		bool iscatch() { return _catching; }
		bool gotc() { return _Catch; }
		int gotMode() { return _mode; }
		int getx() { return _x; }
		int gety() { return _y; }
		int getz() { return _z; }
		int getNext() { return all[_mode]._next; }

	protected:
		bool inMotion;			// �O�_�b�S��ʧ@��


		int * extra(std::string &line, std::string *tar,int number);
		virtual void otherCommand(int n);
		virtual void readOtherList();
		vector<std::string> commandList;		// �QŪ�������O�C��
		int _mode;								// �ثe�ʧ@
		bool _outofctrl;					
	
		void setPosotion(int n);
		void caculateZ(int f, int x, int y, int z);
		void setZ();


		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

		void setDizzyCount() { dizzyCount = MAN_DIZZY; }

		// �p�ƾ�

		void setTimmer(int t) { time = t; }
		void Count() {if (time > 0) time--;}
		bool isTime() { return time == 0; }

		// Ū��Frame���
		void loadFrame();				

		void backToRandon();			// �^���l�����A
		void toMotion(int next);				// �B�o�ʧ@
		void nextFrame();				// �ʧ@�����U�@��Frame
		
		// �����ʧ@�p��

		void attCount();
		bool attCountisZero();
		void setattCount();

		// �w�t��_�p��

		void recoverCount();
		int recoverGap;							// ��_�p��
		int stonkcount;							// �w�t����

		// ���D�p��

		void setJumpCount();
		void JumpCount();
		bool JumpCountisZero();
		bool jumping();

		// �@����˰ʧ@�p��

		void setbeattenCount(int t);
		void beattenCount();
		bool beattenCountisZero();

		// �����ʧ@

		// ���O��J���j

		void setCountDwon();					//�s�I�˼�
		void resetCountDown();					//�s�I�˼��k�s

	private:

		int		charector;						// ��ܤ��}��
		int		_x, _y,_z;						// �H����m
		// �N�� �e�� �Ѧa �W�U
		int		_Double_Tap_Gap;				// �s�I���j
		int		jumpAnimationGap;					
		int		jumpMotionStand;				// ���D�ʧ@�ɶ�
		int		initG;							// �]�w�W�ɳt��
		int		attAnimationGap;
		int		beatenMotionGap;
		int		punch_fall;
		int		dizzyGap;
		int		NumOfMan;						// �b���W���H
		int		time;							// �p��
		int		tempf;							//
		int		dizzyCount;						//

		float	a1, a2, a3,a4,a5;						// ���u��{��
		float	tempx, tempy;
		float	FrameCount;						// ���u�諰�Ѽ�

		bool	jumpType;
		bool	Face_to_Left;					// ���ۤ�V
		bool	_dir[4];						// ��V
		bool	first_att_animation;
		bool	is_jumping;						// �O�_�b���D
		bool	flag[7];						// keyboard input flag
		bool	Alive;							// �O�_����
		bool	Fset;							// �O�_�n�p��諰
		bool	_catching;						// ���O�H
		bool	_Catch;							// �Q������A
		bool	_isDizzy;						// �w�t���A
		bool	_untouch;						// �L�Ī��A
		bool	walk_Ani_dir;					// �����ʧ@����V
		bool	run_Ani_dir;					// �]�B�ʧ@����V

		area	Body;							// ����HitBox

		std::string commandBuffer;				// input command buffer
		
		CAnimation stand[2];					// �����ʧ@
		CAnimation walk[2];						// �����ʧ@
		CAnimation run[2];						// �]���ʧ@
		
		CMovingBitmap test;
		CMovingBitmap squat[2];					// �ۤU�ʧ@
		CMovingBitmap readyJump[2];				// �ǳƸ��ʧ@
		CMovingBitmap littleJump[2];			// ��a���ʧ@
		CMovingBitmap bigJumpR[2];				// �Ĩ���ʧ@
		CMovingBitmap bigJumpL[2];				// �Ĩ���ʧ@
		CMovingBitmap kick[2][2];				// ��ʧ@
		CMovingBitmap flykick[2][2];			// ����
		CMovingBitmap att[2][4];				// �����ʧ@
		CMovingBitmap bigatt[2][3];				// �ħ�ʧ@

		Skills*		now;						// �{�b���ۦ�
		
		Bitmaplib *	lib;						// �Ϥ���X

		CStateBar *	_s;							// ��q��

		man *		mans;						// �b���W���H	
		man *		gotCatch;					// �Q�쪺�H
		
		std::map<int, Frame> all;
	};
}
