#pragma once

#include "Bitmaplib.h"

namespace game_framework {
	class Skills {
	public:
		Skills();
		Skills(const Skills &out);
		Skills(int w,int h,void *owner);
		virtual void LoadBitmap();
		virtual void onMove();
		virtual void onShow();
		void last();
		
		//setter
		void setXY(int x,int y,int z);
		void setDanmage(int danmage);
		void setdizzy(int dizzy);
		void setcost(int cost);
		void setLastTime(int t);
		void setDir(bool f) {
			FaceToLeft = f;
		}
		//getter
		int	 getx();
		int  gety();
		int	 getz();
		int  getDanmage();
		int  getdizzy();
		int  getcost();
		int  getLastTime();
		int	 getw() {
			return _w;
		}
		int geth() {
			return _h;
		}
		bool getDir() {
			return FaceToLeft;
		}
		
		void *  getowner();
	private:
		int _dizzy;				// �w�t����
		int _x, _y, _z;			// �_�l��m
		int _w, _h;				// �e��
		int _danmage;			// �ˮ`
		int _cost;				// �ӶO
		int LastTime;			// ����ɶ�
		void * _owner;
		bool FaceToLeft;
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

