#pragma once

#include "Bitmaplib.h"
#include "skills.h"

namespace game_framework {

	class man{
	public:
		man();
		man(int x, int y);
		void init(Bitmaplib *l);
		void LoadBitmap();							// ���J�ϧ�
		void setComm(UINT comm);					// �]�w���O
		void cComm(UINT comm);						// �������O
		void setInitPosotion(int x,int y);			// �]�w��l��m
		void OnMove();								// ���ܦ�m
		void onShow();								// ���
		void checkbeenatt(skillsContainer &con);	// �Q��������
		Skills* usingSkill();						// �b�������L�ϥΩۦ�
	protected:
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

		// �B�z�w�t�p��

		void setdizzyCount(int t);
		void dizzyCount();
		bool dizzyCountisZero();
		// �����ʧ@

		bool fly();

		// ���O��J���j

		void setCountDwon();					//�s�I�˼�
		void resetCountDown();					//�s�I�˼��k�s

	private:
		int body_x, body_y, body_w, body_h;
		int charector;							//��ܤ��}��
		int _x, _y,_z;							//�H����m
		bool flag[7];							//keyboard input flag
		std::string commandBuffer;				//input command buffer
		int _Double_Tap_Gap;					//�s�I���j
		bool Face_to_Left;						//���ۤ�V
		bool _dir[4];							//��V
		int jumpAnimationGap;					
		int jumpMotionStand;					//���D�ʧ@�ɶ�
		bool is_jumping;						//�O�_�b���D
		int initG;								//�]�w�W�ɳt��
		bool first_att_animation;
		int attAnimationGap;
		int beatenMotionGap;
		
		CAnimation stand[2];					// �����ʧ@
		CAnimation walk[2];						// �����ʧ@
		CAnimation run[2];						// �]���ʧ@
		CMovingBitmap squat[2];					// �ۤU�ʧ@
		CMovingBitmap readyJump[2];				// �ǳƸ��ʧ@
		CMovingBitmap littleJump[2];			// ��a���ʧ@
		CMovingBitmap bigJumpR[2];				// �Ĩ���ʧ@
		CMovingBitmap bigJumpL[2];				// �Ĩ���ʧ@
		CMovingBitmap kick[2][2];				// ��ʧ@
		CMovingBitmap flykick[2][2];			// ����
		CMovingBitmap att[2][4];				//�����ʧ@
		CMovingBitmap bigatt[2][3];				//�ħ�ʧ@
		Skills* now;							//�{�b���ۦ�
		Bitmaplib *lib;
		
		int punch_fall;
		bool isStonk;
		int dizzyGap;
	};
}
