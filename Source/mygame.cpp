/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
#include "Bitmaplib.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////
int player1 = -1, player2 = -1,v = 1 , chose_stage = 0;//test
boolean a = FALSE;

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g){
	
}

void CGameStateInit::OnInit(){
	TRACE("\n\n\n\n\n\nshit\n\n\n\n\n\\n");
	ShowInitProgress(0);
	CAudio::Instance()->Load(AUDIO_CHOOSE, "Sounds\\choose.wav");	
	CAudio::Instance()->Load(AUDIO_CHAR, "Sounds\\char.wav");	
	CAudio::Instance()->Load(AUDIO_MAIN, "Sounds\\main.wav");
	
	menu.LoadBitmap();

	
}

void CGameStateInit::OnBeginState(){
	
	chose = 0;
	windows = 0;			//0為開始結束,1為選角畫面
	how = 0;
	checkin_1 = 0;
	checkin_2 = 0;
	player1_index = 0;
	player2_index = 0;
	lock_1 = -1;
	lock_2 = -1;
	CountDown = FALSE;
	start = FALSE;
	stage = FALSE;
	main = TRUE;
	chose_stage = 0;
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
	const char KEY_UP = 0x26;	// keyboard上箭頭
	const char KEY_DOWN = 0x28;	// keyboard下箭頭
	const char KEY_SPACE = 0x20; // keyboard空白
	const char KEY_S = 0x53;	// keyboard S
	const char KEY_A = 0x41;	// keyboard A
	const char KEY_D = 0x44; // keyboard D
	const char KEY_K = 75; // keyboard D
	const char KEY_LEFT = 37; // keyboard D
	const char KEY_RIGHT = 39; // keyboard D
	const char KEY_J = 74;
	const char KEY_L = 76;
	const char KEY_TAB = 9;


	// TRACE("button key  %d\n", nChar);
	if (main) {
		CAudio::Instance()->Play(AUDIO_MAIN, true);
		main = FALSE;
	}
	if (windows == 0) {
		if (nChar == KEY_UP && chose == 1) {
			chose = 0;
		}
		else if (nChar == KEY_UP && chose == 2) {
			chose = 1;
		}
		if (nChar == KEY_DOWN && chose == 0) {
			chose = 1;
		}
		else if (nChar == KEY_DOWN && chose == 1) {
			chose = 2;
		}
		if (nChar == KEY_SPACE && chose == 0) {
			CAudio::Instance()->Play(AUDIO_CHOOSE);
			windows = 1;
		}
		if (nChar == KEY_SPACE && chose == 1) {
			CAudio::Instance()->Play(AUDIO_CHOOSE);
			windows = 2;
		}
		else if (nChar == KEY_SPACE && chose == 2) {
			CAudio::Instance()->Play(AUDIO_CHOOSE);
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
		}
	}

	else if (windows == 1 && stage == FALSE) {
		if (nChar == KEY_RIGHT && chose_stage == 0) {
			CAudio::Instance()->Play(AUDIO_CHAR);
			chose_stage = 1;
		}
		else if (nChar == KEY_RIGHT && chose_stage == 1) {
			CAudio::Instance()->Play(AUDIO_CHAR);
			chose_stage = 2;
		}
		else if (nChar == KEY_LEFT && chose_stage ==1) {
			CAudio::Instance()->Play(AUDIO_CHAR);
			chose_stage = 0;
		}
		else if (nChar == KEY_LEFT && chose_stage == 2) {
			CAudio::Instance()->Play(AUDIO_CHAR);
			chose_stage = 1;
		}
		if (nChar == KEY_SPACE) {
			CAudio::Instance()->Play(AUDIO_CHOOSE);
			stage = TRUE;
		}
	}


	else if (windows == 1 && CountDown == FALSE && stage == TRUE) {
		if (nChar == KEY_S && checkin_1 == 0) {
			CAudio::Instance()->Play(AUDIO_CHAR);
			checkin_1 = 1;
			player1 = 0;
		}
		if (nChar == KEY_K && checkin_2 == 0) {
			CAudio::Instance()->Play(AUDIO_CHAR);
			checkin_2 = 1;
			player2 = 0;
		}

		if (checkin_1 == 1 && lock_1 < 1) {
			if (nChar == KEY_A) {
				player1_index--;
			}
			if (nChar == KEY_D) {
				player1_index++;
			}
			if (nChar == KEY_S) {
				CAudio::Instance()->Play(AUDIO_CHAR);
				lock_1++;
			}
			player1 = menu.Get_player1(player1_index);
		}
		if (checkin_2 == 1 && lock_2 < 1) {
			if (nChar == KEY_J) {
				player2_index--;
			}
			if (nChar == KEY_L) {
				player2_index++;
			}
			if (nChar == KEY_K) {
				CAudio::Instance()->Play(AUDIO_CHAR);
				lock_2++;
			}
			player2 = menu.Get_player2(player2_index);
		}

		if ((lock_1 == 1 && lock_2 == 1) || (lock_1 == 1 && lock_2 == -1) || (lock_1 == -1 && lock_2 == 1)) {
			CountDown = TRUE;
		}

	}

	else if (windows == 2) {
		if (how == 0) {
			CAudio::Instance()->Play(AUDIO_CHOOSE);
			how = 1;
		}
		else if (how == 1) {
			CAudio::Instance()->Play(AUDIO_CHOOSE);
			windows = 0;
			how = 0;
		}
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point){  //滑鼠處理
	//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	checkin_1 = 0;
	lock_1 = -1;
}

void CGameStateInit::OnShow(){
	if (windows == 0) {
		menu.OnShowMenu(1);
		if (chose == 0) {
			menu.OnShowSelect(0);
		}
		else if (chose == 1) {
			menu.OnShowSelect(1);
		}
		else if (chose == 2) {
			menu.OnShowSelect(2);
		}
		
	}
	else if (windows == 1) {
		if (!stage) {
			menu.OnShowStage(chose_stage);
		}
		else {
			menu.OnShowMenu(2);
			if (checkin_1 == 1) {
				menu.OnShowChar1(player1);
			}
			if (checkin_2 == 1) {
				menu.OnShowChar2(player2);
			}
			menu.OnShowCharLock(lock_1, lock_2);
			if (CountDown) {
				start = menu.OnShowCountDown(lock_1, lock_2);
				if (start) {
					CAudio::Instance()->Stop(AUDIO_MAIN);
					GotoGameState(GAME_STATE_RUN);
				}
			}
		}
	}

	else if (windows == 2) {
		how == 0 ? menu.OnShowMenu(3) : menu.OnShowMenu(4);
	}
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g){
}

void CGameStateOver::OnMove(){
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
	
}

void CGameStateOver::OnBeginState(){
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit(){
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow(){
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g){
	
}

CGameStateRun::~CGameStateRun(){
	TRACE("RRRRRRRRRRRRR");
}

void CGameStateRun::OnBeginState(){
	stage.init(chose_stage + 1, &allobj, player1, player2);
	allobj.reset();
	allobj.initOfinit(player1, player2);

}	

void CGameStateRun::OnMove(){
	allobj.OnMove();
	stage.check(allobj.getEnemyHP());
	
	if (stage.overgame()) {
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit() {

	allobj.load(&Blib, &Flib);

	ShowInitProgress(33);
	Blib.LoadBitmap();

	ShowInitProgress(65);
	Flib.init();

	std::string path = "";
	for (int i = 1; i < 103; i++) {
		path = "music\\"+std::to_string(i)+".wav";
		CAudio::Instance()->Load(i+5, (char *)path.c_str());	// 載入編號1的聲音lake.mp3
	}

	stage.load();
	allobj.mapSetting(stage.getdata());
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	allobj.KeyDown(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){	
	//haha
	//Hie
	//豬威比ＮＩＣＩ
	//SIMPLELIFE超柔抽取衛生紙
	//臣女喜歡忠貞之鳥
	allobj.KeyUp(nChar);
}

// 處理滑鼠的動作
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  {
}

// 處理滑鼠的動作
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	{
	
}

// 處理滑鼠的動作
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

// 處理滑鼠的動作
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  {
	GotoGameState(GAME_STATE_OVER);
}

// 處理滑鼠的動作
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	{
	GotoGameState(GAME_STATE_OVER);
}

// 顯示
void CGameStateRun::OnShow() {
	stage.OnShow(allobj.getX());
	allobj.OnShow();	
}
}