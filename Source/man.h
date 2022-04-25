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
		obj() { 
			Frams = nullptr; 
			_mode = 0; 
			_x = _y = _z = 0.0; 
			beatenCount = 0;
			beatenCount = nullptr;
			beatenList = nullptr;
			numOfBeaten = 0;
			Face_to_Left = true;
			inMotion = false;
			Caught = nullptr;
		}
		obj(const obj& o) {
			Frams = o.Frams; _mode = o._mode; _x = o._x; _y = o._y; _z = o._z; Face_to_Left = o.Face_to_Left;
		}
		~obj() {
			if (beatenCount != nullptr) {
				delete beatenCount;
			}
			if (beatenList != nullptr) {
				delete beatenList;
			}
		}

		obj& operator=(const obj& o) {
			if (this != &o) {
				Frams = o.Frams; 
				_mode = o._mode; 
				_x = o._x; 
				_y = o._y; 
				_z = o._z; 
				Face_to_Left = o.Face_to_Left;
				beatenList = o.beatenList;
				beatenCount = o.beatenCount;

			}
			return *this;
		}

		obj(std::map<int, Frame> *f) {
			Frams = f;
		}

		bool touch(itr i,bool _Face_to_left, double x, double y, double z) {
			// �����@�νd��
			double Lx, Ly, Rx, Ry;
			if (_Face_to_left) {
				Rx = 79 + x - i.getX();
				Lx = Rx - i.getW();
				
				Ly = i.getY() + y;
				Ry = Ly + i.getH();
			}
			else {
				Lx = i.getX() + x;
				Ly = i.getY() + y;
				Rx = Lx + i.getW();
				Ry = Ly + i.getH();
			}
			int n = (*Frams)[_mode]._Num_of_hitbox;

			for (int i = 0; i < n; i++) {
				hitbox hit = *((*Frams)[_mode]._hitbox + i);
				double _Lx, _Ly, _Rx, _Ry;
				if (this->Face_to_Left) {
					_Rx = 79 + _x - hit.getX();
					_Lx = _Rx - hit.getW();

					_Ly = hit.getY() + _y;
					_Ry = _Ly + hit.getH();
				}
				else {
					_Lx = hit.getX() + _x;
					_Ly = hit.getY() + _y;
					_Rx = _Lx + hit.getW();
					_Ry = _Ly + hit.getH();
				}
				double min_x = _Lx > Lx ? _Lx : Lx;
				double min_y = _Ly > Ly ? _Ly : Ly;
				double max_x = _Rx < Rx ? _Rx : Rx;
				double max_y = _Ry < Ry ? _Ry : Ry;
				if (min_x > max_x || min_y > max_y) {
					continue;
				}
				else {
					return true;
				}
			}
			return false;
		}

		void addBeaten(obj *who);

		bool checkBeenBeaten(obj *who);
		void restList();
		void bcount();
		void del(int n);

		bool	inMotion;			// �O�_�b�S��ʧ@��
		std::map<int, Frame> *Frams;
		int		_mode;				// �{�b���Ҧ�
		double	_x, _y, _z;			// �{�b����m
		bool	Face_to_Left;		// ���ۤ�V
		obj*	Caught;				// �Q����H

		obj**	beatenList;			// �Q���쪺�H
		int*	beatenCount;		// �h�[����~�i�H�A���@��
		int		numOfBeaten;		// ���h�֤H�Q����
	};


	class man:public obj{
	public:
		man() {
			charector = 0;
			_Double_Tap_Gap = 30;
			initG = 0;
			time = 0;
			Walk_Ani_num = 5;
			fall = 100;
			commandBuffer = "";

			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			first_att_animation = true;
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

		void	getAllObj(obj** a, int n) {
			all = a;
			numofobj = n;
		}

		void	setInitPosotion(int x, int y);		// �]�w��l��m	

		void	setComm(UINT comm);					// �]�w���O
		void	cComm(UINT comm);					// �������O					

		void	checkbeenatt();						// �Q��������
		void	OnMove();							// ���ܦ�m
		void	onShow();							// ���

		void	setCH(int ch) {						//�]�w�O���Ӹ}��
			charector = ch;
		}

		bool	out() { return inMotion; }
		int		gotMode() { return _mode; }
		int		getx() { return int(_x); }
		int		gety() { return int(_y); }
		int		getz() { return int(_z); }
		int		getNext() { return (*Frams)[_mode]._next; }
		int		getState() { return (*Frams)[_mode]._state; }

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
		

		virtual void otherCommand(int n);
		virtual void readOtherList();

		vector<std::string> commandList;			// �QŪ�������O�C��
		
		void setPosotion(int n);
		void setYstep(double G, double x, double z) {
			_y += G++; initG = G; stepx = x; stepz = z;
		}
		void moveY() {
			if (_y >= 0) { 
				return; 
			}
			_y += initG++;
			initG += 1;
			if (JumpFront) {_x += stepx;}
			if (JumpBack) {_x -= stepx;}
			if (JumpUp) { _z -= stepz; }
			if (JumpDown) { _z += stepz; }
		}

		void checkFlag();
		void checkBuff();
		void specialEvent();
		void readCommand();

		// �p�ƾ�
		void setTimmer(int t) { time = t; }
		void Count() {
			if (fall < 100)fall ++;
			else if (fall < 45) fall = 45;
			if (time > 0) time--;
		}
		bool isTime() { return time == 0; }			

		void backToRandon();						// �^���l�����A
		void toMotion(int next);					// �B�o�ʧ@
		void nextFrame();							// �ʧ@�����U�@��Frame
		

		// ���O��J���j
		void setCountDwon();						//�s�I�˼�
		void resetCountDown();						//�s�I�˼��k�s
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }

	private:
		double	initG;								// �]�w�W�ɳt��
		double	stepx, stepz;						// ���D���ʶZ��
		double	fall;								// �w�t��

		int		Walk_Ani_num;						// �U�@�Ө����ʧ@�����X
		int		charector;							// ��ܤ��}��
		int		_Double_Tap_Gap;					// �s�I���j
		int		NumOfMan;							// �b���W���H
		int		time;								// �p��

		bool	useSupperAtt;						// �i�H�ϥβ׵��u
		bool	JumpUp, JumpDown,JumpFront,JumpBack;			// �׸�
		bool	jumpType;
		bool	_dir[4];							// ��V
		bool	flag[7];							// keyboard input flag
		bool	first_att_animation;				// �O���O�X����
		bool	Alive;								// �O�_����
		bool	walk_Ani_dir;						// �����ʧ@����V
		bool	run_Ani_dir;						// �]�B�ʧ@����V
			
		std::string commandBuffer;					// input command buffer
		
		obj*	beaten;								//

		Bitmaplib *	lib;							// �Ϥ���X
		CStateBar *	_s;								// ��q��
		obj **all;									// ���W�����~�H��
		int numofobj;								// ���W�����~�H���ƶq
		man *		mans;							// �b���W���H	
		man *		gotCatch;						// �Q�쪺�H
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
