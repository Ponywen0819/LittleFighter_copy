/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "man.h"
#include "skills.h"
#include "Bitmaplib.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit(){
	ShowInitProgress(0);
	
	menu.LoadBitmap();
}

void CGameStateInit::OnBeginState(){
	chose = 0;
	windows = 0;			//0���}�l����,1���﨤�e��
	checkin_1 = 0;
	checkin_2 = 0;
	player1_index = 0;
	player2_index = 0;
	lock_1 = -1;
	lock_2 = -1;
	CountDown = FALSE;
	start = FALSE;
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_UP = 0x26;	// keyboard�W�b�Y
	const char KEY_DOWN = 0x28;	// keyboard�U�b�Y
	const char KEY_SPACE = ' '; // keyboard�ť�
	const char KEY_S = 0x53;	// keyboard S
	const char KEY_A = 0x41;	// keyboard A
	const char KEY_D = 0x44; // keyboard D
	const char KEY_K = 75; // keyboard D
	const char KEY_LEFT = 37; // keyboard D
	const char KEY_RIGHT = 39; // keyboard D

	if (windows == 0) {
		if (nChar == KEY_UP && chose == 1) {
			chose = 0;
		}
		if (nChar == KEY_DOWN && chose == 0) {
			chose = 1;
		}
		if (nChar == KEY_SPACE && chose == 0) {
			windows = 1;
		}
		if (nChar == KEY_SPACE && chose == 1) {
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
		}
	}


	else if (windows == 1 && CountDown == FALSE) {
		if (nChar == KEY_S && checkin_1 == 0) {
			checkin_1 = 1;
		}
		if (nChar == KEY_K && checkin_2 == 0) {
			checkin_2 = 1;
		}

		if (checkin_1 == 1 && lock_1 < 1) {
			if (nChar == KEY_A) {
				player1_index--;
			}
			if (nChar == KEY_D) {
				player1_index++;
			}
			if (nChar == KEY_S) {
				lock_1++;
			}
			menu.cal_1(player1_index);
		}

		if (checkin_2 == 1 && lock_2 < 1) {
			if (nChar == KEY_LEFT) {
				player2_index--;
			}
			if (nChar == KEY_RIGHT) {
				player2_index++;
			}
			if (nChar == KEY_K) {
				lock_2++;
			}
			menu.cal_2(player2_index);
		}
		//TRACE("%d", lock_1);
		if ((lock_1 == 1 && lock_2 == 1) || (lock_1 == 1 && lock_2 == -1) || (lock_1 == -1 && lock_2 == 1)) {
			CountDown = TRUE;
		}

	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point){  //�ƹ��B�z
	//GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{

	if (windows == 0) {
		menu.OnShowMenu(1);
		chose == 0 ? menu.OnShowSelect(0) : menu.OnShowSelect(1);
	}
	else if (windows == 1) {
		menu.OnShowMenu(2);
		if (checkin_1 == 1) {
			menu.OnShowChar1(menu.Get_player1());
		}
		if (checkin_2 == 1) {
			menu.OnShowChar2(menu.Get_player2());
		}
	
		if (CountDown) {
			start = menu.OnShowCountDown(lock_2);
			if (checkin_1 == 1) {
				menu.OnShowChar1(menu.Get_player1());
			}
			if (checkin_2 == 1) {
				menu.OnShowChar2(menu.Get_player2());
			}
			if (start) {
				GotoGameState(GAME_STATE_RUN);
			}
		}
		
	}

	
	
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// ���ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160����16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28)
{
	ball = new CBall [NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnBeginState(){
	man1.setInitPosotion(200, 200);
	man2.setInitPosotion(150, 200);
}	

void CGameStateRun::OnMove(){
	skills.check();
	man1.checkbeenatt(skills);
	man2.checkbeenatt(skills);
	man1.OnMove();
	man2.OnMove();
	skills.addSkills(man1.usingSkill());
	skills.addSkills(man2.usingSkill());
	skills.onMove();

}

void CGameStateRun::OnInit(){
	//
	ShowInitProgress(33);	
	lib.LoadBitmap();

	ShowInitProgress(50);
	man1.LoadBitmap();
	man1.init(&lib);

	ShowInitProgress(75);
	man2.LoadBitmap();
	man2.init(&lib);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25;	// keyboard���b�Y
	const char KEY_UP    = 0x26;	// keyboard�W�b�Y
	const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
	const char KEY_DOWN  = 0x28;	// keyboard�U�b�Y
	const char KEY_SPACE = 0x20;	// keyboard�ť���
	const char KEY_Z = 90;			// keyboard Z

	if (nChar == KEY_LEFT) {
		man1.setComm(1);
	}
	else if (nChar == KEY_RIGHT) {
		man1.setComm(2);
	}
	else if (nChar == KEY_UP) {
		man1.setComm(3);
	}
	else if (nChar == KEY_DOWN) {
		man1.setComm(4);
	}
	else if (nChar == KEY_SPACE) {
		man1.setComm(5);
	}
	else if (nChar == KEY_Z) {
		man1.setComm(6);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
	const char KEY_LEFT = 0x25;	// keyboard���b�Y
	const char KEY_UP = 0x26;	// keyboard�W�b�Y
	const char KEY_RIGHT = 0x27;	// keyboard�k�b�Y
	const char KEY_DOWN = 0x28;	// keyboard�U�b�Y
	const char KEY_SPACE = 0x20;	// keyboard�ť���
	const char KEY_Z = 90;			// keyboard Z

	if (nChar == KEY_LEFT) {
		man1.cComm(1);
	}
	else if (nChar == KEY_RIGHT) {
		man1.cComm(2);
	}
	else if (nChar == KEY_UP) {
		man1.cComm(3);
	}
	else if (nChar == KEY_DOWN) {
		man1.cComm(4);
	}
	else if (nChar == KEY_SPACE) {
		man1.cComm(5);
	}
	else if (nChar == KEY_Z) {
		man1.cComm(6);
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow(){ 
	man1.onShow();
	man2.onShow();
	skills.onShow();
}

}