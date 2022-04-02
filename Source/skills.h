#pragma once

#include "Bitmaplib.h"
#include "Area.h"

namespace game_framework {
	class Skills {
	public:
		Skills();
		Skills(const Skills &out);
		Skills(int w,int h,void *owner);
		void initPostion(int x, int y, int w, int h) {
			_x = x; _y = y;
			Area.init(_x, _y, w, h);
		}
		virtual void LoadBitmap();
		virtual void onMove();
		virtual void onShow();
		bool touch(const area &other) {
			return Area.touch(other);
		}
		
		void	last() {
			LastTime--;
		}

		//setter
		void	setPostion(int x, int y, int z) {
			_x = x; _y = y; _z = z;
			Area.setPosetion(_x, _y);
		}
		void	setDanmage(int danmage) {
			_danmage = danmage;
		}
		void	setdizzy(int dizzy) {
			_dizzy = dizzy;
		}
		void	setcost(int cost) {
			_cost = cost;
		}
		void	setLastTime(int t) {
			LastTime = t;
		}
		void	setDir(bool f) {
				FaceToLeft = f;
		}

		//getter
		int		getx() {
			return _x;
		}
		int		gety() {
			return _y;
		}
		int		getz() {
			return _z;
		}
		int		getDanmage() {
			return _danmage;
		}
		int		getdizzy() {
			return _dizzy;
		}
		int		getcost() {
			return _cost;
		}
		int		getLastTime() {
			return LastTime;
		}
		int		getw() {
			return _w;
		}
		int		geth() {
			return _h;
		}
		bool	getDir() {
			return FaceToLeft;
		}
		void*	getowner() {
			return _owner;
		}

	protected:
		int		_dizzy;				// �w�t����
		int		_x, _y, _z;			// �_�l��m
		int		_w, _h;				// �e��
		int		_danmage;			// �ˮ`
		int		_cost;				// �ӶO
		int		LastTime;			// ����ɶ�
		void*	_owner;
		bool	FaceToLeft;
		area	Area;				// �ޯ�@�νd��
	};

	class punch :public Skills {
	public:
		punch();
		punch(int x, int y, int z,bool FacetoLeft,bool LeftPunch, Bitmaplib *l,void *owner);
		void init(bool f);
		void onMove();
		void addBitmap(int i);
		void onShow();
	private:
		bool _FacetoLeft;
		bool _LeftPunch;
		PAnimation _ani;			// �ޯ�ʵe
		Bitmaplib *lib;
	};

	class skillsContainer {
	public:
		skillsContainer();
		~skillsContainer();

		void addSkills(Skills *new_skill);
		void dleteSkills(int n);
		void onMove();
		void onShow();
		void check();
		int getnum() {
			return numOfSkills;
		}
		Skills* getskills(int n);
	private:
		int numOfSkills;
		std::vector<Skills*> skills;
	};

}

