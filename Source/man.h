#pragma once

#include "Bitmaplib.h"
#include "Area.h"
#include "CStateBar.h"
#include <string>
#include <map>
#include "Frame.h"

#define MaxHp 500
#define MaxMp 500

namespace game_framework {
	class obj{
	public:
		obj() { 
			_mode = 0; 
			arestC = 0;
			beatenCount = 0;
			numOfBeaten = 0;
			_x = _y = _z = 0.0; 
			Frams = nullptr; 
			beatenList = nullptr;
			beatenCount = nullptr;
			Caught = nullptr;
			Alive = true;
			Face_to_Left = true;
			stop = false;
			inMotion = false;
			hit = holdinglt = holdingheavy = false;

			maxx = map_pos = upbond = underbond = 0;
		}
		obj(const obj& o) {
			Frams = o.Frams; _mode = o._mode; _x = o._x; _y = o._y; _z = o._z; Face_to_Left = o.Face_to_Left;
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
		
		~obj() {
			if (beatenCount != nullptr) {
				delete beatenCount;
			}
			if (beatenList != nullptr) {
				delete beatenList;
			}
		}
		
		void del(int n);
		void OnShow();
		void bcount();
		void restList();
		void showShadow();
		void setArest(int n);
		void addBeaten(obj *who);
		void mapSetting(int* data) {
			maxx = data[0]; 
			map_pos = data[1]; 
			upbond = data[2]; 
			underbond = data[3];
			mapdata = data;
		}

		int  getArest();
		
		bool touch(obj * o) {
			if (o->id == 213 || o->id == 215) {
				if (abs(o->_z - this->_z) > 40) {
					return false;
				}
			}
			else {
				if (abs(o->_z - this->_z) > 10) {
					return false;
				}
			}
			//
			// �إߧ�����P�w�ϰ�
			//
			area att;
			att.init(o->_x, o->_y, (*(o->Frams))[o->_mode]._i.getX(), (*(o->Frams))[o->_mode]._i.getY(),
				(*(o->Frams))[o->_mode]._i.getW(), (*(o->Frams))[o->_mode]._i.getH(), o->Face_to_Left, o->maxW);
			for (int i = 0; i < (*Frams)[_mode]._Num_of_hitbox; i++) {
				hitbox hit = *((*Frams)[_mode]._hitbox + i);
				area n;
				n.init(_x, _y, hit.getX(), hit.getY(), hit.getW(), hit.getH(), this->Face_to_Left, this->maxW);
				if (n.touch(att)) {
					return true;
				}
			}
			return false;
		}
		bool checkBeenBeaten(obj *who);

		Frame getNoFrame() { return (*Frams)[_mode]; }
		

		virtual void OnMove() = 0;
		virtual void setdir(bool f) {}
		virtual void nextFrame() {};
		virtual void backToRandon() {};
		virtual void toMotion(int next) {};
		virtual void holdingSth(obj* thing) {}
		virtual void hitSomeOne(obj* other) {}
		virtual void setYstep(double G, double x, double z) {}

		bool isAlive() { return Alive; }
		
		virtual obj* getOwner() { return this; }
		virtual obj* usingSkills() { return nullptr; }



		std::map<int, Frame> *Frams;// �ʧ@��ƪ�
		
		obj*	Caught;				// �Q����H
		obj**	beatenList;			// �Q���쪺�H

		int		id;					// �N��ۤv�O����
		int		_mode;				// �{�b���Ҧ�
		int		numOfBeaten;		// ���h�֤H�Q����
		int		cc;					// ��H�p��
		int		time;				// �p��
		int		arestC;				// �h�[����~�i�H���H
		int		hp;					// ��q
		int		kind;				// �����~������
		int		maxW,maxH;			// �����~�Ϥ��j�p
		int		maxx, map_pos;		// �a�Ϫ��̤j��
		int		upbond, underbond;	// �a�Ϫ��W�U�ɽu 
		
		int*	beatenCount;		// �h�[����~�i�H�A���@��
		int*	mapdata;			//�a�Ϫ���� �e�� �{�b����m �W�� �U��
		
		bool	Face_to_Left;		// ���ۤ�V
		bool	inMotion;			// �O�_�b�S��ʧ@��
		bool	Alive;	
		bool	stop;	
		bool	hit;
		bool	holdinglt;
		bool	holdingheavy;
		
		double	_x, _y, _z;			// �{�b����m
	};

	class allobj {
	public:
		allobj() {
			num = 0;
			all = s = nullptr;
		}
		~allobj() {
			for (int i = 0; i < num; i++)
				delete *(all + i);
			delete all;
		}

		void init();

		void reset() {
			for (int i = 0; i < num; i++)
				delete *(all + i);
			delete all;

			num = 0;
			all = s = nullptr;
		}

		void add(obj *);
		void del(int n);

		obj* getSortObj(int n);

		void so();
		
		obj* getobj(int n);

		obj** getall() { return all; }

		int getN() { return num; }
	private:
		int num;
		obj** all;
		obj** s;
	};

	class man :public obj {
	public:
		man() :obj() {
			_Double_Tap_Gap = 30;
			initG = 0;
			time = 0;
			Walk_Ani_num = 5;
			fall = 100;
			mp = 500;
			HpRecover = 500;
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
			cantBeTouch = false;
			maxW = maxH = 79;
			_y = 79;
			cantBrTouchCount = 0;
			stepx = stepz = 0;

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

			hp = HpRecover= 500;
			kind = 0;

			mpGap = hpGap = 0;
			Alive = true;

			total_hpcost = total_mpcost = total_damage = 0;
		}
		man(int ch,allobj* al) :man() {
			id = ch;
			_a = al;
			switch (ch) {
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
			Frams = Framelib::Instance()->getFrame(id);
		}
		~man() {

		}
		void	setComm(UINT comm);					// �]�w���O
		void	cComm(UINT comm);					// �������O					
		void	checkbeenatt();						// �Q��������
		void	OnMove();							// ���ܦ�m
		void	holdingSth(obj* thing) { holding = thing; }
		void	setHP(){ hp = 0; }
		void	setplayer(int p, CStateBar* b){
			player = p;
			bar = b;
		}
		// ���D�B�z
		void	setYstep(double G, double x, double z) {
			initG = G; stepx = x; stepz = z; jumping = true;
		}
		void	moveY() {
			_y -= initG;
		
			if (JumpFront) {_x += stepx;}
			if (JumpBack) {_x -= stepx;}
			if (JumpUp) { _z -= stepz; }
			if (JumpDown) { _z += stepz; }

			if (_y <= (*Frams)[_mode]._centery) {
				_y = maxH;
				stepx = stepz = initG = 0;
				JumpFront = JumpBack = JumpUp = JumpDown = false;
			}
			else{
				initG += 2;
			}

			if (id == 0) {
				if ((initG == 0) && (_mode == 267)) {
					toMotion(268);
				}
			}
		}
		// �վ��m
		void	adjustPosition(int f_now,int f_next);
		void	hitSomeOne(obj *thoer) { 
			total_damage += (*Frams)[_mode]._i.getInjury();
			who = thoer; 
			stop = true;
		}
		//�ץ�Ĳ�o�B�z
		void	checkFlag();
		void	checkBuff();
		void	specialEvent();
		// ���A��s�B�z
		void	backToRandon();						// �^���l�����A
		void	toMotion(int next);					// �B�o�ʧ@
		void	nextFrame();						// �ʧ@�����U�@��Frame
		// �p�ƾ�
		void	setTimmer(int t) { time = t; }
		void	Count() {
			// ��q�^�_����
			if (HpRecover > hp && --hpGap <= 0 && hp <MaxHp && hp > 0) {
				hp++;
				hpGap = 12;

			}

			// �]�O�^�_����
			if (--mpGap <= 0 && mp < MaxMp) {
				if (hp > 400) {
					if (id == 2) {
						mp += 3;
					}
					else {
						mp++;
					}
				}
				else if (hp > 300) {
					if (id == 2) {
						mp += 4;
					}
					else {
						mp+=2;
					}
				}
				else if (hp > 200) {
					if (id == 2) {
						mp += 4;
					}
					else {
						mp+=3;
					}
				}
				else if (hp > 100) {
					if (id == 2) {
						mp += 5;
					}
					else {
						mp+=4;
					}
				}
				else {
					mp += 5;
				}
				mpGap = 3;
			}
			
			if (cantBrTouchCount > 0) { cantBrTouchCount--;}
			if (cantBrTouchCount == 0) cantBeTouch = false;
			if (arestC > 0)arestC--;

			// �w�t��
			if (fall < 100)fall ++;
			else if (fall < 45) fall = 45;
			
			
			if (time > 0) time--;
		}
		// ���O��J���j
		void	setCountDwon();						//�s�I�˼�
		void	resetCountDown();					//�s�I�˼��k�s
		void	CountDown() { if (_Double_Tap_Gap > 0)_Double_Tap_Gap--; }
		void	thw_obj();
		void	injuredMotion(bool f) {
			if (fall < 35) {			// ����
				if (f != this->Face_to_Left) {
					toMotion(180);
				}
				else {
					toMotion(186);
				}
				time = (*Frams)[_mode]._wait;
				fall = 100;
			}
			else if (fall < 55) {		// �w�t
				toMotion(226);
			}
			else if (fall < 60) {		// �Q����ĤG�U
				if (f != this->Face_to_Left) {
					toMotion(222);
				}
				else {
					toMotion(224);
				}
			}
			else {						// �Q����Ĥ@�U
				toMotion(220);
			}

		}
		void	hurt(int d);
		
		bool	isTime() { return time == 0; }			
		
		int		getX() { return int(_x); }
		int		getZ() { return int(_z); }
		int		getID() { return id; }
		int		getHP() {
			if (hp > 0)
				return hp;
			else
				return 0;
		}
		int		getTotalHpCost() { return total_hpcost; }
		int		getTotalMpCost() { return total_mpcost; }
		int		getTotalDamage() { return total_damage; }
		int		getNextWalkMotion() {
			if (walk_Ani_dir) {
				if (++Walk_Ani_num >= 9) {
					Walk_Ani_num = 7;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			else {
				if (--Walk_Ani_num <= 4) {
					Walk_Ani_num = 6;
					walk_Ani_dir = !walk_Ani_dir;
				}
			}
			return Walk_Ani_num;
		}

		obj*	usingSkills() {
			obj* a = skills;
			skills = nullptr;
			return a;
		}
	private:
		double	initG;								// �]�w�W�ɳt��
		double	stepx, stepz;						// ���D���ʶZ��
		double	fall;								// �w�t��
		double	defend;								//���m��

		//	�}��򥻳]�w�Ѽ�
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

		int		mp;									// �]�O
		int		HpRecover;					
		int		player;					
		int		Walk_Ani_num;						// �U�@�Ө����ʧ@�����X
		int		_Double_Tap_Gap;					// �s�I���j
		int		NumOfMan;							// �b���W���H
		int		SkillsMotion[8];					
		int		cantBrTouchCount;				
		int		hpGap, mpGap;						//��q�P�]�O��_
		int		total_hpcost, total_mpcost,total_damage;			// ��q�P�]�O�`���ӷl

		//
		// �p�ɬ���
		//


		bool	inSpecialMotion;					// �b�S��ʧ@��
		bool	useSupperAtt;						// �i�H�ϥβ׵��u
		bool	JumpUp, JumpDown,JumpFront,JumpBack;// �׸�
		bool	_dir[4];							// ��V
		bool	flag[7];							// keyboard input flag
		bool	first_att_animation;				// �O���O�X����
		bool	walk_Ani_dir;						// �����ʧ@����V
		bool	run_Ani_dir;						// �]�B�ʧ@����V
		bool	jumping;							// ���b���D
		bool	cantBeTouch;						

		obj*	holding;			
		obj*	who;								// �Q��������
		obj*	skills;								// �X�ޯ�
		allobj* _a;				//���W�Ҧ��H
		CStateBar*	bar;
		std::string commandBuffer;					// input command buffer
	};

	class weapon:public obj{
	public:
		weapon() { 
			_mode = 0; 
			JumpFront, JumpBack, JumpUp, JumpDown, jumping = false;
			stepx, stepz, initG = 0;
			throwing = false;

			kind = 2;
		}
		
		weapon(int n, int mode, obj* ow,allobj * all) :weapon() {
			id = n;
			_mode = mode;
			switch (id){
			case 10: {
				maxH = maxW = 48;
				break;
			}
			case 11: {
				maxH = maxW = 58;
				break;
			}
			case 12: {
				maxH = maxW = 69;
				break;
			}
			case 201: {
				maxH = maxW = 48;
			}
			default:
				break;
			}
			Frams = Framelib::Instance()->getFrame(id);
			holding = ow;

			_a = all;

			stepx = stepz = initG = 0;
			JumpFront = JumpBack = JumpUp = JumpDown = false;
		}

		void checkbeenatt();
		void init(int x, int y, int z, bool fa) {
			_x = x;
			_y = y;
			_z = z;
			Face_to_Left = fa;
			if (fa) {
				_x = x - (maxW - (*Frams)[_mode]._centerx);
			}
			else {
				_x -= (*Frams)[_mode]._centerx;
			}
			_y += (*Frams)[_mode]._centery;
		}
		void hitSomeOne(obj *thoer);
		void backToRandon();
		void toMotion(int next);
		void nextFrame();
		void OnMove();
		void setYstep(double G, double x, double z) {
			initG = G; stepx = x; stepz = z; jumping = true;
		}
		void setdir(bool f) {
			if (!f) JumpFront = true;
			else JumpBack = true;
			throwing = true;
		}
		void holdingSth(obj* thing) { holding = thing; }
	
	private:
		void moveY() {
			int st = (*Frams)[_mode]._state;
			if ( st == 1002) {
				_y-=2;
				if (Face_to_Left) _x -= stepx;
				else _x += stepx;
			}
			else {
				_y -= initG;
				if (JumpFront) { _x += stepx; }
				if (JumpBack) { _x -= stepx; }
				if (JumpUp) { _z -= stepz; }
				if (JumpDown) { _z += stepz; }
			}
			
			if (_y <= (*Frams)[_mode]._centery) {
				stepx = stepz = initG = 0;
				JumpFront = JumpBack = JumpUp = JumpDown = false;
			}
			else {
				initG += 2;
			}

			if (id == 0) {
				if ((initG == 0) && (_mode == 267)) {
					toMotion(268);
				}
			}
		}
		void adjustPosition(int f_now, int f_next) {
			if (!Face_to_Left) _x = _x + (*Frams)[f_now]._centerx - (*Frams)[f_next]._centerx;
			else _x = _x - (*Frams)[f_now]._centerx + (*Frams)[f_next]._centerx;
		}
		// �p�ƾ�
		void setTimmer(int t) { time = t; }
		void Count() {
			if (arestC > 0)arestC--;
			if (time > 0) time--;
		}
		
		bool isTime() { return time <= 0; }

		obj* getOwner() {
			return holding;
		}
		

		bool	IsHolding;		//���Q�B��
		bool	throwing;		
		bool	JumpFront, JumpBack, JumpUp, JumpDown, jumping;

		double	stepx, stepz, initG;
		
		obj*	holding;		//�֦A���L
		allobj* _a;				//���W�Ҧ��H
	};

	class wp :public obj {
	public:
		wp():obj() {
			id = 0;
			hp = 500;
			time = 0;
			skills = nullptr;
			
			kind = 1;
		
		}

		wp(int n,int mode,obj* ow, allobj * all):wp(){
			id = n;
			owner = ow;
			this->_a = all;
			switch (id) {
			case 203: {
				maxW = 81;
				maxH = 82;
				break;
			}
			case 209: {
				maxW = 81;
				maxH = 82;
				break;
			}
			case 210: {
				maxW = 81;
				maxH = 82;
				break;
			}
			case 211: {
				maxW = 35;
				maxH = 49;
				break;
			}
			case 212: {
				maxW = 59;
				maxH = 63;
				break;
			}
			case 213: {
				maxW =159;
				maxH = 159;
				break;
			}
			case 214: {
				maxW = 109;
				maxH = 109;
				break;
			}
			case 215: {
				maxW = 159;
				maxH = 159;
				break;
			}
			default: {
				maxW = 81;
				maxH = 82;
				break;
			}
			}
			Frams = Framelib::Instance()->getFrame(id);
			_mode = mode;
			setTimmer((*Frams)[_mode]._wait);
		}
		
		~wp() {
			if (skills != nullptr) {
				delete skills;
			}
		}

		void init( int x, int y,int z,bool fa) {
			_x = x;
			_y = y;
			_z = z;
			Face_to_Left = fa;
			if (fa) {
				_x = x - (maxW - (*Frams)[_mode]._centerx);
			}
			else {
				_x -= (*Frams)[_mode]._centerx;
			}
				_y += (*Frams)[_mode]._centery;
		}
		void hitSomeOne(obj *thoer);
		void backToRandon();
		void toMotion(int next);
		void nextFrame();
		void OnMove();

		obj* usingSkills() {
			obj* a = skills;
			skills = nullptr;
			return a;
		}
		obj* getOwner() {
			return owner;
		}
	private:
		void adjustPosition(int f_now, int f_next);
		void setTimmer(int t) { time = t; }
		void Count() {
			if (arestC > 0)arestC--;
			if (time > 0) time--;
		}
		
		bool isTime() { return time <= 0; }

		int		stand;			// ���򪺮ɶ�
		allobj* _a;				//���W�Ҧ��H
		obj*	skills;			// �ߩ񪺧ޯ�
		obj*	owner;			// �֩�		
	};

	class  AI{
	public:
		AI() {
			n = numOfTarget = 0;
			self = Target = nullptr;
			commandFinish = nullptr;
			commandState = nullptr;
			commandType = _x = _z = nullptr;
		}

		~AI() {
			if (self != nullptr)
				delete self;
			if (Target != nullptr)
				//delete Target;
			if(commandType != nullptr)
				delete commandType;
			if (commandFinish != nullptr)
				delete commandFinish;
			if (commandState != nullptr)
				delete commandState;
		}
		void add(man* newone);	// �гy�q��
		void check();			// �ˬd���F�S
		void del(int n);		// �R�����q��
		void del(obj* shit);
		void reset() {
			if (self != nullptr)
				delete self;
			if (commandType != nullptr)
				delete commandType;
			if (commandFinish != nullptr)
				delete commandFinish;
			if (commandState != nullptr)
				delete commandState;

			n = numOfTarget = 0;
			self = nullptr;
			commandFinish = nullptr;
			commandState = nullptr;
			commandType = _x = _z = nullptr;
		}
		void updateEnemy(int n,man** mans);
		void OnMove();

		int  getTotalHP();
		int getComnum() { return n; }
	private:
		int		n;				// �q�����ƶq	
		int		numOfTarget;	// �ؼЪ��ƶq
		
		int*	commandType;		// �����Ӻ���
		int*	commandState;		
		int*	_x;				//�Ω�����q�����O����
		int*	_z;		
		
		bool*	commandFinish;		//���O����
		
		man**	self;			// �q�����H
		man**	Target;			// �����ؼ�
	};

	class ObjContainer {
	public:
		ObjContainer() {
			mans = nullptr;
			com = new AI();
		}
		~ObjContainer() {
			if(mans != nullptr)
				delete mans;
			delete com;
		}
		
		void initOfinit(int player1, int player2) {
			bar.init(player1, player2);
		}
		void init(int player1,int player2);
		void load() {
			bar.LoadBitmap();
		}
		void reset() {
			if (mans != nullptr)
				delete mans;
			mans = nullptr;
			a.reset();
			com->reset();
		}
		void check();
		void OnMove();
		void OnShow();
		void KeyUp(UINT nChar);
		void KeyDown(UINT nChar);
		void mapSetting(int* data);
		void creatWeapon(int n,int x,int z);
		void creatEnemy(int type, int x, int y);

		int	 getState() { return state; }
		int  getX() {
			if (mans == nullptr) return 0;
			if (state == 0) {
				if (!mans[0]->isAlive()) {
					return int(mans[0]->_x);
				}
				else if (!mans[1]->isAlive()) {
					return int(mans[0]->_x);
				}
				else {
					return int(mans[0]->_x + mans[1]->_x) / 2;
				}
			}
			else if (state == 3) {
				return 0;
			}
			else{
				return int(mans[0]->_x);
			}
		}
		int  getEnemyHP();
		int	 getHP();

		bool end();

		std::string getendInfo() {
			if (mans == nullptr) return std::string("");
			
			std::string temp = "";
			temp+= std::to_string(state);
			temp += ",";
			if (state == 0) {
				if ((mans[0]->getHP() > 0) || (mans[1]->getHP() > 0)) {
					temp += '1';
				}
				else {
					temp += '0';
				}
				temp += ',';

				for (int i = 0; i < 2; i++) {
					temp += std::to_string(mans[i]->getID());
					temp += ",";
					temp += std::to_string(mans[i]->getTotalDamage());
					temp += ",";
					temp += std::to_string(mans[i]->getTotalHpCost());
					temp += ",";
					temp += std::to_string(mans[i]->getTotalMpCost());
					temp += ",";
					temp += std::to_string(mans[i]->isAlive());
					temp += ",";
				}
			}
			else {
				if (mans[0]->getHP() >0) {
					temp += '1';
				}
				else {
					temp += '0';
				}
				temp += ',';
				temp+= std::to_string(mans[0]->getID());
				temp += ",";
				temp += std::to_string(mans[0]->getTotalDamage());
				temp += ",";
				temp += std::to_string(mans[0]->getTotalHpCost());
				temp += ",";
				temp += std::to_string(mans[0]->getTotalMpCost());
				temp += ",";
				temp += std::to_string(mans[0]->isAlive());
				temp += ",";
			}
			return temp;
		}
	private:
		int		state;				// �ϥΪ̿�θ}�⪺�Ϊp
		int*	map_data;			// �a�Ϫ��]�w��
		AI*		com;				// �q��
		man**	mans;				// �H��
		allobj  a;					// ���W�Ҧ����~
		CStateBar bar;				// ���A��		
	};

	
}
