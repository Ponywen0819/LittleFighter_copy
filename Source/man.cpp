#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "man.h"
#include "skills.h"


#define height 28

namespace game_framework {

	//��l��
	
	man::man() {
		charector = 0;
		_x = _y = _z = 0;
		_mode = 0;
		for (int i = 0; i < 7; i++)	flag[i] = false;
		for (int i = 0; i < 4; i++)	_dir[i] = false;
		jumpAnimationGap = 0;
		attAnimationGap = 0;
		recoverGap = 50;
		_Double_Tap_Gap = 30;
		initG = height;
		commandBuffer = "";
		setJumpCount();
		_outofctrl = false;
		first_att_animation = true;
		stonkcount = 6;
		punch_fall = 2;
		isStonk = false;
	}

	man::man(int x, int y) {
		charector = 0;
		_z = 0;
		_mode = 0;
		_Double_Tap_Gap = 30;
		for (int i = 0; i < 7; i++)	flag[i] = false;
		for (int i = 0; i < 4; i++)	_dir[i] = false;
		jumpAnimationGap = 0;
		initG = height;
		commandBuffer = "";
		setJumpCount();
		_outofctrl = false;
		first_att_animation = true;
		attAnimationGap = 0;
		_x = x;
		_y = y;
		now = nullptr;
	}

	void man::init(Bitmaplib *l) {
		lib = l;
	}

	void man::LoadBitmap() {
		
		//���߰ʵe
		
		char *standLf[4] = { ".\\Bitmaps\\temp\\stand\\L\\0.bmp",".\\Bitmaps\\temp\\stand\\L\\1.bmp",".\\Bitmaps\\temp\\stand\\L\\2.bmp",".\\Bitmaps\\temp\\stand\\L\\3.bmp" };
		for (int i = 0; i < 4; i++)	stand[0].AddBitmap(standLf[i], RGB(0, 0, 0));
		char *standRf[4] = { ".\\Bitmaps\\temp\\stand\\R\\0.bmp",".\\Bitmaps\\temp\\stand\\R\\1.bmp",".\\Bitmaps\\temp\\stand\\R\\2.bmp",".\\Bitmaps\\temp\\stand\\R\\3.bmp" };
		for (int i = 0; i < 4; i++)	stand[1].AddBitmap(standRf[i], RGB(0, 0, 0));
		
		//�����ʵe

		char *walkLf[6] = { ".\\Bitmaps\\temp\\walk\\L\\0.bmp",".\\Bitmaps\\temp\\walk\\L\\1.bmp",".\\Bitmaps\\temp\\walk\\L\\2.bmp",".\\Bitmaps\\temp\\walk\\L\\3.bmp",".\\Bitmaps\\temp\\walk\\L\\4.bmp",".\\Bitmaps\\temp\\walk\\L\\5.bmp" };
		for (int i = 0; i < 6; i++)	walk[0].AddBitmap(walkLf[i], RGB(0, 0, 0));
		char *walkRf[6] = { ".\\Bitmaps\\temp\\walk\\R\\0.bmp",".\\Bitmaps\\temp\\walk\\R\\1.bmp",".\\Bitmaps\\temp\\walk\\R\\2.bmp",".\\Bitmaps\\temp\\walk\\R\\3.bmp",".\\Bitmaps\\temp\\walk\\R\\4.bmp",".\\Bitmaps\\temp\\walk\\R\\5.bmp" };
		for (int i = 0; i < 6; i++)	walk[1].AddBitmap(walkRf[i], RGB(0, 0, 0));
		
		//�]�B�ʧ@

		char *runLf[4] = { ".\\Bitmaps\\temp\\run\\L\\0.bmp",".\\Bitmaps\\temp\\run\\L\\1.bmp",".\\Bitmaps\\temp\\run\\L\\2.bmp",".\\Bitmaps\\temp\\run\\L\\3.bmp"};
		for (int i = 0; i < 4; i++)	run[0].AddBitmap(runLf[i], RGB(0, 0, 0));
		char *runRf[4] = { ".\\Bitmaps\\temp\\run\\R\\0.bmp",".\\Bitmaps\\temp\\run\\R\\1.bmp",".\\Bitmaps\\temp\\run\\R\\2.bmp",".\\Bitmaps\\temp\\run\\R\\3.bmp" };
		for (int i = 0; i < 4; i++)	run[1].AddBitmap(runRf[i], RGB(0, 0, 0));

		//���D�ۤU�ʧ@

		squat[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\0.bmp",RGB(0, 0, 0));
		squat[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\0.bmp", RGB(0, 0, 0));
		
		//���D�w�ưʧ@

		readyJump[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\1.bmp", RGB(0, 0, 0));
		readyJump[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\1.bmp", RGB(0, 0, 0));

		//�p���ʧ@

		littleJump[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\2.bmp", RGB(0, 0, 0));
		littleJump[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\2.bmp", RGB(0, 0, 0));

		//�j�����k�ʧ@

		bigJumpR[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\6.bmp", RGB(0, 0, 0));
		bigJumpR[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\3.bmp", RGB(0, 0, 0));

		//�j�������ʧ@

		bigJumpL[0].LoadBitmap(".\\Bitmaps\\temp\\jump\\L\\3.bmp", RGB(0, 0, 0));
		bigJumpL[1].LoadBitmap(".\\Bitmaps\\temp\\jump\\R\\4.bmp", RGB(0, 0, 0));
		
		//�����ʵe

		char *attL[4] = { ".\\Bitmaps\\temp\\att\\L\\0.bmp",".\\Bitmaps\\temp\\att\\L\\1.bmp",".\\Bitmaps\\temp\\att\\L\\2.bmp",".\\Bitmaps\\temp\\att\\L\\3.bmp" };
		for (int i = 0; i < 4; i++) att[0][i].LoadBitmap(attL[i], RGB(0, 0, 0));
		char *attR[4] = { ".\\Bitmaps\\temp\\att\\R\\0.bmp",".\\Bitmaps\\temp\\att\\R\\1.bmp",".\\Bitmaps\\temp\\att\\R\\2.bmp",".\\Bitmaps\\temp\\att\\R\\3.bmp" };
		for (int i = 0; i < 4; i++) att[1][i].LoadBitmap(attR[i], RGB(0, 0, 0));
		
		//�ħ�ʧ@
		char *bigattL[3] = { ".\\Bitmaps\\temp\\bigatt\\L\\0.bmp",".\\Bitmaps\\temp\\bigatt\\L\\1.bmp",".\\Bitmaps\\temp\\bigatt\\L\\2.bmp"};
		for (int i = 0; i < 3; i++) bigatt[0][i].LoadBitmap(bigattL[i], RGB(0, 0, 0));
		char *bigattR[3] = { ".\\Bitmaps\\temp\\bigatt\\R\\0.bmp",".\\Bitmaps\\temp\\bigatt\\R\\1.bmp",".\\Bitmaps\\temp\\bigatt\\R\\2.bmp"};
		for (int i = 0; i < 3; i++) bigatt[1][i].LoadBitmap(bigattR[i], RGB(0, 0, 0));

		//��ʧ@

		char *kickL[2] = { ".\\Bitmaps\\temp\\kick\\L\\0.bmp",".\\Bitmaps\\temp\\kick\\L\\1.bmp"};
		for (int i = 0; i < 2; i++) kick[0][i].LoadBitmap(kickL[i], RGB(0, 0, 0));
		char *kickR[2] = { ".\\Bitmaps\\temp\\kick\\R\\0.bmp",".\\Bitmaps\\temp\\kick\\R\\1.bmp"};
		for (int i = 0; i < 2; i++) kick[1][i].LoadBitmap(kickR[i], RGB(0, 0, 0));

		// ����ʧ@

		char *flykickL[2] = { ".\\Bitmaps\\temp\\kick\\L\\2.bmp",".\\Bitmaps\\temp\\kick\\L\\3.bmp" };
		for (int i = 0; i < 2; i++) flykick[0][i].LoadBitmap(flykickL[i], RGB(0, 0, 0));
		char *flykickR[2] = { ".\\Bitmaps\\temp\\kick\\R\\2.bmp",".\\Bitmaps\\temp\\kick\\R\\3.bmp" };
		for (int i = 0; i < 2; i++) flykick[1][i].LoadBitmap(flykickR[i], RGB(0, 0, 0));

		//Ū���ӧO�}��ޯ��

		readCommand();
	}

	void man::readCommand() {
		commandList.push_back("11");
		commandList.push_back("22");
		readOtherList();
	}

	void man::readOtherList() {

	}

	void man::setInitPosotion(int x, int y) {
		_x = x;
		_y = y;
	}
	
	//�o�O�d���l���O�ޱ���func

	void man::otherCommand(int n) {

	}

	//��J�B�z

	void man::setComm(UINT comm) {
		flag[comm - 1] = true;
		if (comm == 2) {
			flag[0] = false;
			commandBuffer += '2';
		}

		if (comm == 1) {
			flag[1] = false;
			commandBuffer += '1';
		}

		if (comm == 3) {
			flag[3] = false;
			commandBuffer += '3';
		}

		if (comm == 4) {
			flag[2] = false;
			commandBuffer += '4';
		}

		if (comm == 5) {
			commandBuffer += '5';
		}

        if (comm == 6) {
			commandBuffer += '6';
		}

		if (comm == 7) {
			commandBuffer += '7';
		}
		
		if (_mode <  100) {
			if (comm == 1 && Face_to_Left == false)	Face_to_Left = true;
			else if (comm == 2 && Face_to_Left)	Face_to_Left = false;
		}
	}

	void man::cComm(UINT comm) {
		flag[comm - 1] = false;
	}

	// �̾ڿ�J���ܪ��A

	void man::setPosotion(int n) {
		if (_dir[0]) _x -= n;
		if (_dir[1]) _x += n;
		if (_dir[2]) _y -= 1;
		if (_dir[3]) _y += 1;
	}

	void man::checkFlag() {
		//TRACE("%d", _outofctrl);
		if (_outofctrl) {
			return;
		}

		if (flag[0]) {
			if ((!Face_to_Left) && (_mode == 100)) {
				_mode = 0;
			}
			else if(_mode!=100) {
				Face_to_Left = true;
				_dir[0] = true;
				_dir[1] = false;
			}
		}

		if (flag[1]) {
			if ((Face_to_Left) && (_mode == 100)) {
				_mode = 0;
			}
			else if (_mode != 100) {
				Face_to_Left = false;
				_dir[0] = false;
				_dir[1] = true;
			}
		}

		if (!(flag[0] || flag[1])) {
			if(_mode !=100)
				_dir[0] = _dir[1] = false;
		}
		
		if (flag[2]) {
			_dir[2] = true;
			_dir[3] = false;
		}

		if (flag[3]) {
			_dir[2] = false;
			_dir[3] = true;
		}

		if (!(flag[3] || flag[2])) {
			_dir[3] = _dir[2] = false;
		}

		if (flag[4]) {
			flag[4] = false;
			if (_mode == 100) {
				if(Face_to_Left) _mode = 94;
				else _mode = 93;
			}
			else {
				_mode = 90;
			}
			_outofctrl = true;
		}
		
		if (flag[5]) {
			flag[5] = false;
			if (_mode == 100) {
				_mode = 103;
				_outofctrl = true;
				_dir[2] = _dir[3] = false;
				setattCount();
			}
			else{
				_mode = 101;
				_outofctrl = true;
				first_att_animation = !first_att_animation;
				setattCount();
			}
		}

		if (_mode < 90) {
			for (int i = 0; i < 4; i++) {
				if (flag[i]) {
					_mode = 1;
					break;
				}
				else {
					_mode = 0;
					_dir[i] = false;
				}
			}
		}
	}

	void man::checkBuff() {
		if (_outofctrl) return;

		if (_Double_Tap_Gap <= 0) {
			setCountDwon();
			commandBuffer = "";
		}
		else{
			int index = 0;
			std::vector<std::string>::iterator i;
			for (i = commandList.begin(); i != commandList.end(); ++i) {
				if (*i == commandBuffer) break;
				index++;
			}
			if (index != commandList.size()) {
				commandBuffer = "";
				if (index == 0 || index == 1) {
					_mode = 100;
				}
				else{
					otherCommand(index);
				}
			}
		}

	}

	void man::specialEvent() {
		if (!_outofctrl) return;
		//TRACE("%d %d \n", flag[4], flag[5]);
		if (flag[5]) {
			if (_mode == 92) {
				setattCount();
				_mode = 106;
			}
			else if (_mode == 93 ) {
				setattCount();
				_mode = 108;
			}
			else if (_mode == 94) {
				setattCount();
				_mode = 109;
			}
		}
	}

	void man::checkbeenatt(skillsContainer &con) {
		int j = 0;
		while(j < con.getnum()) {
			if (con.getskills(j)->getowner() == this) {
				j++; continue;
			}
			int x = con.getskills(j)->getx() - _x;
			int y = con.getskills(j)->gety() - _y;
			int z = con.getskills(j)->getz();
			int w = con.getskills(j)->getw();
			int h = con.getskills(j)->geth();
			bool touch=false;
			int point_x[4] = {x,x+w,x,x+w};
			int point_y[4] = {y,y,y+h,y+h};
			for (int i = 0; i < 4; i++) {
				if (abs(z - _z) > 10) 	break;
				if (point_x[i] < 0 || point_y[i] < 0) {
					continue;
				}
				else if(point_x[i] > 79 || point_y[i] > 79){
					continue;
				}
				else{
					touch = true;
					break;
				}
			}
			if (touch) {
				recoverGap = 40;
				Skills* temp = con.getskills(j);
				stonkcount -= temp->getdizzy();					// �p��Q���쪺�w�t��
																// �p��Q���쪺�ˮ`
				//TRACE("stonk count %d\n", stonkcount);
				_outofctrl = true;
				int mid = x + (w / 2);
				setbeattenCount(5);
				if (stonkcount > 3) {
					if (mid <= 40) {
						_mode = 112;				// �Q���Ĥ@�U��	
					}
					else {
						_mode = 114;				// �Q���Ĥ@�U�k
					}
				}
				else if (stonkcount > 0) {
					if (mid <= 40) {
						_mode = 116;				// �Q���ĤG�U��	
					}
					else {
						_mode = 118;				// �Q���ĤG�U�k
					}
				}
				else if(stonkcount ==0){
					_mode = 115;						// �w�t
					setdizzyCount(100);
					isStonk = true;
				}
				else{
					if ( mid <= 40 ) {
						_mode = 200;				// ������
					}
					else{
						_mode = 200;				// �����k
					}
				}
				con.dleteSkills(j);

			}		
			j++;
		}
	}

	Skills* man::usingSkill(){
		return now;
	}

	//�H�����A��s

	void man::OnMove() {
		TRACE("dizzy %d  %d \n", stonkcount, recoverGap);
		//�˼�
		now = nullptr;
		if(_Double_Tap_Gap>=0) _Double_Tap_Gap--;
		JumpCount();
		attCount();
		beattenCount();
		recoverCount();
		dizzyCount();

		//�d�ݫ���P��J���O
		checkFlag();
		checkBuff();
		specialEvent();
	

		switch (_mode){
		case 1:
			setPosotion(1);
			break;
		case 90:
			if (JumpCountisZero()) {
				_mode = 91; setJumpCount();
			}
			break;
		case 91:
			if (JumpCountisZero()) {
				_mode = 92; 
			}
			break;
		case 92:
			setPosotion(2);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 93:
		case 94:
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 100:						//�Ĩ�ʧ@
			setPosotion(2);
			break;

		case 101:
			if (attCountisZero()) {		// �ǳƧ���
				_mode = 102;
				setattCount();
				punch *temp = new punch(_x, _y, _z, Face_to_Left, first_att_animation, lib, (void*)this);
				temp->setdizzy(punch_fall);
				now = temp;
			}
			break;
		case 102:						
			if (attCountisZero()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 103:
			setPosotion(2);
			if (attCountisZero()) {
				_mode = 104;
				setattCount();
			}
			break;
		case 104:
			setPosotion(2);
			if (attCountisZero()) {
				_mode = 105;
				setattCount();
			}
			break;
		case 105:
			setPosotion(2);
			if (attCountisZero()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 106:
			if (attCountisZero()) {
				_mode = 107;
				setattCount();
			}
			setPosotion(2);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 107:
			if (attCountisZero()) {
				_mode = 92;
			}
			setPosotion(2);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;

		// ����

		case 108:
			if (attCountisZero()) {
				_mode = 110;
				setattCount();
			}
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 109:
			if (attCountisZero()) {
				_mode = 111;
				setattCount();
			}
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 110:
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 111:								
			setPosotion(4);
			if (jumping()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;

		// �������

		case 112:						// �Q���Ĥ@�U��-1
			setInitPosotion(_x + 1, _y);
			if (beattenCountisZero()) {
				setbeattenCount(10);
				_mode = 115;
			}
			break;
		case 114:						// �Q���Ĥ@�U�k-1
			setInitPosotion(_x - 1, _y);
			if (beattenCountisZero()) {
				setbeattenCount(10);
				_mode = 115;
			}
			break;
		case 115:						// �Q���Ĥ@�U�k-2
			if (beattenCountisZero()) {
				if (isStonk) {
					_mode = 120;
					setbeattenCount(10);
				}
				else{
					_mode = 0;
					_outofctrl = false;
				}
				
			}
			break;
		case 116:						// �Q���ĤG�U��-1
			setInitPosotion(_x + 1, _y);
			if (beattenCountisZero()) {
				setbeattenCount(10);
				_mode = 117;
			}
			break;
		case 117:						// �Q���ĤG�U��-2
			if (beattenCountisZero()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;

		case 118:						// �Q���ĤG�U�k-1
			setInitPosotion(_x - 1, _y);
			if (beattenCountisZero()) {
				setbeattenCount(10);
				_mode = 119;
			}
			break;
		case 119:						// �Q���ĤG�U�k-2
			if (beattenCountisZero()) {
				_mode = 0;
				_outofctrl = false;
			}
			break;
		case 120:						// �w�t
			if (beattenCountisZero()) {
				setbeattenCount(10);
				_mode = 115;
			}
			break;
		case 121:						// ������

			break;
		case 122:						// �����k
			
			break;
		default:
			break;
		}
	}
	
	//�H�����

	void man::onShow() {
		int index;
		if (Face_to_Left) index = 0;
		else index = 1;
		switch (_mode){
		case 0:
			stand[index].OnMove();
			stand[index].SetTopLeft(_x, _y);
			stand[index].OnShow();
			break;
		case 1:
			walk[index].OnMove();
			walk[index].SetTopLeft(_x, _y);
			walk[index].OnShow();
			break;
		case 90:									//���D�ۤU
			squat[index].SetTopLeft(_x, _y);
			squat[index].ShowBitmap();
			break;
		case 91:									//���D�ǳ�
			readyJump[index].SetTopLeft(_x, _y);
			readyJump[index].ShowBitmap();
			break;
		case 92:									//���D�p��
			littleJump[index].SetTopLeft(_x, _y + _z);
			littleJump[index].ShowBitmap();
			break;
		case 93:									//���D�j�����k
			bigJumpR[index].SetTopLeft(_x, _y + _z);
			bigJumpR[index].ShowBitmap();
			break;
		case 94:									//���D�j������
			bigJumpL[index].SetTopLeft(_x, _y + _z);
			bigJumpL[index].ShowBitmap();
			break;
		case 100:									//�b�]
			run[index].OnMove();
			run[index].SetTopLeft(_x, _y);
			run[index].OnShow();
			break;
		case 101:									//�����ʧ@�w��
			if (first_att_animation) {
				att[index][0].SetTopLeft(_x,_y+_z);
				att[index][0].ShowBitmap();
			}
			else {
				att[index][2].SetTopLeft(_x, _y + _z);
				att[index][2].ShowBitmap();
			}
			break;
		case 102:									//�����ʧ@
			if (first_att_animation) {
				att[index][1].SetTopLeft(_x, _y + _z);
				att[index][1].ShowBitmap();
			}
			else {
				att[index][3].SetTopLeft(_x, _y + _z);
				att[index][3].ShowBitmap();
			}
			break;
		case 103:									//�ħ�ǳưʧ@
			bigatt[index][0].SetTopLeft(_x, _y + _z);
			bigatt[index][0].ShowBitmap();
			break;
		case 104:									//�ħ�ʧ@
			bigatt[index][1].SetTopLeft(_x, _y + _z);
			bigatt[index][1].ShowBitmap();
			break;
		case 105:									//�ħ�end�ʧ@
			bigatt[index][2].SetTopLeft(_x, _y + _z);
			bigatt[index][2].ShowBitmap();
			break;
		case 106:
			kick[index][0].SetTopLeft(_x, _y + _z);
			kick[index][0].ShowBitmap();
			break;
		case 107:
			kick[index][1].SetTopLeft(_x, _y + _z);
			kick[index][1].ShowBitmap();
			break;
		case 108:
		case 109:
			flykick[index][0].SetTopLeft(_x, _y + _z);
			flykick[index][0].ShowBitmap();
			break;
		case 110:
		case 111:
			flykick[index][1].SetTopLeft(_x, _y + _z);
			flykick[index][1].ShowBitmap();

		// ����ˮ`�ʧ@

		case 112:
		case 114:
			lib->setbeatenTopLeft(0,Face_to_Left,0,_x,_y+_z);
			lib->showBeaten(0, Face_to_Left, 0);
			break;
		case 115:
			lib->setbeatenTopLeft(0, Face_to_Left, 1, _x, _y + _z);
			lib->showBeaten(0, Face_to_Left, 1);
			break;
		case 116:
			lib->setbeatenTopLeft(2, Face_to_Left, 0, _x, _y + _z);
			lib->showBeaten(2, Face_to_Left, 0);
			break;
		case 117:
			lib->setbeatenTopLeft(2, Face_to_Left, 1, _x, _y + _z);
			lib->showBeaten(2, Face_to_Left, 1);
			break;
		case 118:
			lib->setbeatenTopLeft(1, Face_to_Left, 0, _x, _y + _z);
			lib->showBeaten(1, Face_to_Left, 0);
			break;
		case 119:
			lib->setbeatenTopLeft(1, Face_to_Left, 1, _x, _y + _z);
			lib->showBeaten(1, Face_to_Left, 1);
			break;
		case 120:
			lib->setbeatenTopLeft(3, Face_to_Left, 0, _x, _y + _z);
			lib->showBeaten(3, Face_to_Left, 0);
			break;
		case 121:
		case 122:

		default:
			break;
		}	
	}

	//�B�z���O��J�ɶ����j

	void man::setCountDwon() {
		_Double_Tap_Gap = 75;
	}

	void man::resetCountDown() {
		_Double_Tap_Gap = -1;
	}

	//�B�z���D�ʧ@�P�y��

	bool man::jumping() {
		//TRACE("%d %d %d %d\n", _dir[0], _dir[1], _dir[2], _dir[3]);
		_z -= int(initG / 5);
		--initG;
		if (initG == -height - 1) {
			initG = height;
			return true;
		}
		return false;
	}

	void man::setJumpCount() {
		jumpAnimationGap = 6;
	}

	void man::JumpCount() {
		if (jumpAnimationGap > 0) jumpAnimationGap--;
	}

	bool man::JumpCountisZero() {
		return jumpAnimationGap == 0;
	}

	// �B�z�����ʧ@

	void man::setattCount() {
		attAnimationGap = 15;
	}

	bool man::attCountisZero() {
		return attAnimationGap == 0;
	}

	void man::attCount() {
		if (attAnimationGap > 0) attAnimationGap--;

	}

	// �B�z�w�t�ʧ@

	void man::setbeattenCount(int t=10) {
		beatenMotionGap = t;
	}
	void man::beattenCount() {
		if (beatenMotionGap > 0)beatenMotionGap--;
	}
	bool man::beattenCountisZero() {
		return beatenMotionGap == 0;
	}

	void man::setdizzyCount(int t) {
		dizzyGap = t;
	}
	void man::dizzyCount() {
		if (dizzyGap > 0)dizzyGap--;
		else{
			isStonk = false;
		}
	}
	bool man::dizzyCountisZero() {
		return dizzyGap == 0;
	}


	void man::recoverCount() {
		if (stonkcount < 0) stonkcount = 6;
		if (recoverGap == 0) {
			recoverGap = 40;
			stonkcount = 6;
		}
		else{
			recoverGap--;
		}
	}
}