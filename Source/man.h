#pragma once

#include "Bitmaplib.h"
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
			arestC = 0;
			Alive = true;
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

		// ���~�U�ۦ��ۤv���ʪ��覡
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
		

		//
		// �]�w
		//
		void updateObj(obj** list, int n) {
			all = list;
			numOfObj = n;
		}
		void setmax(int x, int z) {
			maxx = x; maxz = z;
		}



		virtual void hitSomeOne() {}
		//
		// �ʧ@��s�禡
		//
		virtual void backToRandon() {};
		virtual void toMotion(int next) {};
		virtual void nextFrame() {};			

		void init(obj** a,int n) {
			this->all = a;
			numOfObj = n;
			Frams = fl->getFrame(id);
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
			
			if (abs(z - _z) > 12) {
				return true;
			}

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
				//TRACE("%.1f %.1f %.1f %.1f\n", min_x, min_y, max_x, max_y);
				if (min_x > max_x || min_y > max_y) {
					continue;
				}
				else {
					return true;
				}
			}
			return false;
		}

		bool touch(obj * o) {
			if (abs(o->_z - this->_z) > 10) {
				return false;
			}
			//
			// �إߧ�����P�w�ϰ�
			//
			area att;
			att.init(o->_x, o->_y+o->_z, (*(o->Frams))[o->_mode]._i.getX(), (*(o->Frams))[o->_mode]._i.getY(),
				(*(o->Frams))[o->_mode]._i.getW(), (*(o->Frams))[o->_mode]._i.getH(), o->Face_to_Left, o->maxW);
			for (int i = 0; i < (*Frams)[_mode]._Num_of_hitbox; i++) {
				hitbox hit = *((*Frams)[_mode]._hitbox + i);
				area n;
				n.init(_x, _y+_z, hit.getX(), hit.getY(), hit.getW(), hit.getH(), this->Face_to_Left, this->maxW);
				if (n.touch(att)) {
					return true;
				}
			}
			return false;
		}
		//�����n
		void addBeaten(obj *who);
		bool checkBeenBeaten(obj *who);
		void restList();
		void bcount();
		void del(int n);
		

		virtual obj*	usingSkills() {
			return nullptr;
		}


		int	id;						//�N��ۤv�O����
		std::map<int, Frame> *Frams;// �ʧ@��ƪ�
		obj**	all;				// �Ҧ����~���C��
		int		numOfObj;			// �Ҧ����~���Ӽ�

		Bitmaplib*	lib;			// �Ϥ���X
		Framelib*	fl;				// ���F�n�гy
		bool	inMotion;			// �O�_�b�S��ʧ@��
		int		_mode;				// �{�b���Ҧ�
		double	_x, _y, _z;			// �{�b����m
		bool	Face_to_Left;		// ���ۤ�V
		

		obj*	Caught;				// �Q����H
		obj**	beatenList;			// �Q���쪺�H

		int		maxW,maxH;			// �����~�Ϥ��j�p
		int*	beatenCount;		// �h�[����~�i�H�A���@��
		int		numOfBeaten;		// ���h�֤H�Q����
		int		cc;					// ��H�p��
		int		time;				// �p��
		int		arestC;				// �h�[����~�i�H���H
		int		hp;					// ��q
		int		maxx, maxz;			// �a�Ϫ��̤j��
		bool	Alive;				
	};

	class allobj {
	public:
		allobj() {
			num = 0;
			all = nullptr;
		}
		~allobj() {
			delete[] all;
		}

		

		void add(obj *);
		void del(int n);

		obj* getobj(int n);
		int getN() {
			return num;
		}
	private:
		int num;
		obj** all;
	};

	class man:public obj{
	public:
		man():obj() {
			_Double_Tap_Gap = 30;
			initG = 0;
			time = 0;
			Walk_Ani_num = 5;
			fall = 100;
			commandBuffer = "";
			
			for (int i = 0; i < 8; i++)SkillsMotion[i] = -1;
			SkillsMotion[0] = SkillsMotion[1] = 9;
			for (int i = 0; i < 7; i++)	flag[i] = false;
			for (int i = 0; i < 4; i++)	_dir[i] = false;
			first_att_animation = true;
			inSpecialMotion = false;
			walk_Ani_dir = true;
			run_Ani_dir = true;
			JumpUp = false;
			JumpDown = false;
			JumpFront = false;
			skills = nullptr;
			maxW = maxH = 79;
			_y = 79;
			//
			//	�H���򥻰ʧ@�ѼƳ]�w
			//
			wlaking_speed = 4;
			wlaking_speed_z = 2;

			running_speed = 8;
			running_speed_z = 1.3;

			heavy_walking = 3;
			heavy_walking_z = 1.5;

			heavy_running = 5;
			heavy_running_z = 0.8;

			jump_height = -16.3;
			jump_distance = 8;
			jump_distance_z = 3;

			dash_distance = 15;
			dash_distance_z = 3.75;
		}
		man(int ch, Framelib *f, Bitmaplib* b,allobj* al) :man() {
			id = ch;
			lib = b;
			fl = f;
			_a = al;
			switch (ch){
			case 0: {
				SkillsMotion[2] = 235;
				SkillsMotion[3] = 290;
				//SkillsMotion[4] = 266; // �����F
				SkillsMotion[6] = 260;
				break;
			}
			case 1: {
				SkillsMotion[2] = 235;
				SkillsMotion[3] = 245;
				SkillsMotion[4] = 260;
				SkillsMotion[5] = 270;
				break;
			}
			case 2: {
				SkillsMotion[2] = 235;
				SkillsMotion[3] = 255;
				SkillsMotion[4] = 285;
				SkillsMotion[5] = 267;
				break;
			}
			default:
				break;
			}
			Frams = fl->getFrame(id);
		}
		~man() {

		}	

		void	getFl(Framelib* a) {
			fl = a;
		}
		void	setComm(UINT comm);					// �]�w���O
		void	cComm(UINT comm);					// �������O					

		obj*	usingSkills() {
			obj* a = skills;
			skills = nullptr;
			return a;
		}

		void	checkbeenatt();						// �Q��������
		void	checkbeenatt(obj**, int);
		void	OnMove();							// ���ܦ�m
		void	OnShow();							// ���
	protected:

		void getAllObj(obj** a, int n) {
			all = a;
			numOfObj = n;
		}		// ���o�b���W���Ҧ����~

		// ���D�B�z

		void setYstep(double G, double x, double z) {
			_y += G++; initG = G; stepx = x; stepz = z;
		}
		void moveY() {
			if (_y >= maxH) { 
				return; 
			}
			_y += initG++;
			initG += 1;
			if (JumpFront) {_x += stepx;}
			if (JumpBack) {_x -= stepx;}
			if (JumpUp) { _z -= stepz; }
			if (JumpDown) { _z += stepz; }

			if (id == 0) {
				if ((initG == 0) && (_mode == 267)) {
					toMotion(268);
				}
			}
		}
		void adjustPosition(int f_now,int f_next);

		//�ץ�Ĳ�o�B�z
		void checkFlag();
		void checkBuff();
		void specialEvent();

		// ���A��s�B�z
		void backToRandon();						// �^���l�����A
		void toMotion(int next);					// �B�o�ʧ@
		void nextFrame();							// �ʧ@�����U�@��Frame

		// �p�ƾ�
		void setTimmer(int t) { time = t; }
		void Count() {
			if (arestC > 0)arestC--;
			if (fall < 100)fall ++;
			else if (fall < 45) fall = 45;
			if (time > 0) time--;
		}
		bool isTime() { return time == 0; }			

		// ���O��J���j
		void setCountDwon();						//�s�I�˼�
		void resetCountDown();						//�s�I�˼��k�s
		void CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }

		int	 getNextWalkMotion() {
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
	private:
		double	initG;								// �]�w�W�ɳt��
		double	stepx, stepz;						// ���D���ʶZ��
		double	fall;								// �w�t��

		//
		//	�}��򥻳]�w�Ѽ�
		//
		double	wlaking_speed;
		double	wlaking_speed_z;

		double	running_speed;
		double	running_speed_z;

		double	heavy_walking;
		double	heavy_walking_z;

		double	heavy_running;
		double	heavy_running_z;

		double	jump_height;
		double	jump_distance;
		double	jump_distance_z;

		double	dash_distance;
		double	dash_distance_z;

		int		Walk_Ani_num;						// �U�@�Ө����ʧ@�����X
		int		_Double_Tap_Gap;					// �s�I���j
		int		NumOfMan;							// �b���W���H
		int		SkillsMotion[8];					

		bool	inSpecialMotion;					// �b�S��ʧ@��
		bool	useSupperAtt;						// �i�H�ϥβ׵��u
		bool	JumpUp, JumpDown,JumpFront,JumpBack;// �׸�
		bool	_dir[4];							// ��V
		bool	flag[7];							// keyboard input flag
		bool	first_att_animation;				// �O���O�X����
		bool	Alive;								// �O�_����
		bool	walk_Ani_dir;						// �����ʧ@����V
		bool	run_Ani_dir;						// �]�B�ʧ@����V

		
		allobj* _a;									//���W�Ҧ��H
		obj*	skills;								// �X�ޯ�
		std::string commandBuffer;					// input command buffer
	};

	class weapon:public obj{
	public:
		weapon() { _mode = 0; }
		
		void init(std::map<int, Frame> *f,Bitmaplib* b){
			lib = b;
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
		allobj* _a;				//���W�Ҧ��H
		man*	holding;		//�֦A���L
		bool	IsHolding;		//���Q�B��
	};

	class wp :public obj {
	public:
		wp():obj() {
			id = 0;
			hp = 500;
			time = 0;
			skills = nullptr;
		}

		wp(int n,int mode, Framelib *f, Bitmaplib* b):wp(){
			fl = f;
			lib = b;
			id = n;
			_mode = mode;
			switch (id) {
			case 203: {
				maxW = 81;
				maxH = 82;
				break;
			}
			default: {
				maxW = 81;
				maxH = 82;
				break;
			}
			}
			Frams = fl->getFrame(id);
		}
		
		void init( int x, int y,int z,bool fa) {
			_x = x;
			_y = y;
			_z = z;
			Face_to_Left = fa;
			if (Face_to_Left) {
				_x -= (maxW + (*Frams)[_mode]._centerx);
			}
			else {
				_x -= (*Frams)[_mode]._centerx;
			}
				_y += (*Frams)[_mode]._centery;
		}

		obj*	usingSkills() {
			obj* a = skills;
			skills = nullptr;
			return a;
		}


		void hitSomeOne() {
			switch (id) {
			case 203:
			case 209:
			case 210: {
				toMotion(10);
				break;
			}
			default: {
				break;
			}
			}
		}
		void backToRandon();
		void toMotion(int next);
		void nextFrame();

		void OnMove();
		void OnShow();
	private:
		void adjustPosition(int f_now, int f_next);
		// �p�ƾ�
		void setTimmer(int t) { time = t; }
		void Count() {
			if (time > 0) time--;
		}
		bool isTime() { return time <= 0; }

		allobj* a;				//���W�Ҧ��H
		obj*	skills;			// �ߩ񪺧ޯ�
		obj*	owner;			// �֩�		
		int		stand;			// ���򪺮ɶ�
	};

	

	class ObjContainer {
	public:
		ObjContainer() {
			numOfObj = 0;
		}
		~ObjContainer() {
			delete[] all;
		}
		void init(int player1,int player2, Bitmaplib *l, Framelib* f);
		void creatWeapon(int n);

		void KeyUp(UINT nChar);
		void KeyDown(UINT nChar);
		
		void check();

		void OnMove();
		void OnShow();
	private:
		int		state;				// �ϥΪ̿�θ}�⪺�Ϊp
		int		numOfObj;			// ���W�Ҧ����~���ƶq
		obj**	all;				// ���W�Ҧ����~
		allobj  a;					// ���W�Ҧ����~

		man**	mans;				//�H��
		Bitmaplib* lib;				
		Framelib* fl;
		int maxx, maxz;				// �a�Ϫ��̤j��
	};

	
}
