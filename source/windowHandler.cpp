#include "pch.h"
#include "windowHandler.h"

void windowHandler::checkGraphics() {
	resizeticked = SendMessage(Window::resize, BM_GETCHECK, NULL, NULL);
	if (resizeticked == BST_CHECKED) {
		if (portraitsticked == BST_CHECKED) {
			SendMessage(Window::portraits, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		if (bugticked == BST_CHECKED) {
			SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
	portraitsticked = SendMessage(Window::portraits, BM_GETCHECK, NULL, NULL);
	if (portraitsticked == BST_CHECKED) {
		if (resizeticked) {
			SendMessage(Window::resize, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		if (bugticked == BST_CHECKED) {
			SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
	flashesticked = SendMessage(Window::flashes, BM_GETCHECK, NULL, NULL);
	if (flashesticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	roniticked = SendMessage(Window::roni, BM_GETCHECK, NULL, NULL);
	if (roniticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	cafeticked = SendMessage(Window::cafe, BM_GETCHECK, NULL, NULL);
	if (cafeticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
}

void windowHandler::checkGameplay() {
	encticked = SendMessage(Window::encounters, BM_GETCHECK, NULL, NULL);
	if (encticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	expticked = SendMessage(Window::experience, BM_GETCHECK, NULL, NULL);
	if (expticked == BST_CHECKED) {
		EnableWindow(Window::expList, true);
		if (bugticked == BST_CHECKED) {
			SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
	else {
		EnableWindow(Window::expList, false);
	}
	goldticked = SendMessage(Window::gold, BM_GETCHECK, NULL, NULL);
	if (goldticked == BST_CHECKED) {
		EnableWindow(Window::goldList, true);
		if (bugticked == BST_CHECKED) {
			SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
	else {
		EnableWindow(Window::goldList, false);
	}
	itemspellsticked = SendMessage(Window::itemspells, BM_GETCHECK, NULL, NULL);
	if (itemspellsticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	monstersticked = SendMessage(Window::monsters, BM_GETCHECK, NULL, NULL);
	if (monstersticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	deathblowsticked = SendMessage(Window::deathblows, BM_GETCHECK, NULL, NULL);
	if (deathblowsticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	capticked = SendMessage(Window::cap, BM_GETCHECK, NULL, NULL);
	if (capticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
}

void windowHandler::checkArena() {
	normalarenaticked = SendMessage(Window::normalarena, BM_GETCHECK, NULL, NULL);
	basicarenaticked = SendMessage(Window::basicarena, BM_GETCHECK, NULL, NULL);
	if (basicarenaticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	expertarenaticked = SendMessage(Window::expertarena, BM_GETCHECK, NULL, NULL);
	if (expertarenaticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	for (int i = 0; i < Window::gameplayWindList.size(); i++) {
		LRESULT boxticked = SendMessage(Window::gameplayWindList[i], BM_GETCHECK, NULL, NULL);
		if (boxticked == BST_CHECKED && storymodeticked == BST_CHECKED) {
			LRESULT smuntick = SendMessage(Window::storyMode, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
}

void windowHandler::checkStory() {
	scriptticked = SendMessage(Window::script, BM_GETCHECK, NULL, NULL);
	if (scriptticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	fastticked = SendMessage(Window::fasttext, BM_GETCHECK, NULL, NULL);
	if (fastticked == BST_CHECKED) {
		if (instantticked == BST_CHECKED) {
			SendMessage(Window::instant, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		if (bugticked == BST_CHECKED) {
			SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
	instantticked = SendMessage(Window::instant, BM_GETCHECK, NULL, NULL);
	if (instantticked == BST_CHECKED) {
		if (fastticked == BST_CHECKED) {
			SendMessage(Window::fasttext, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		if (bugticked == BST_CHECKED) {
			SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
}

void windowHandler::checkAudio() {
	fmvticked = SendMessage(Window::fmvs, BM_GETCHECK, NULL, NULL);
	if (fmvticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	voiceticked = SendMessage(Window::voice, BM_GETCHECK, NULL, NULL);
	if (voiceticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	musicticked = SendMessage(Window::music, BM_GETCHECK, NULL, NULL);
	if (musicticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
}

void windowHandler::checkModes() {
	storymodeticked = SendMessage(Window::storyMode, BM_GETCHECK, NULL, NULL);
	if (storymodeticked == BST_CHECKED) {
		for (int i = 0; i < Window::gameplayWindList.size(); i++) {
			LRESULT boxticked = SendMessage(Window::gameplayWindList[i], BM_GETCHECK, NULL, NULL);
			if (boxticked == BST_CHECKED) {
				boxticked = SendMessage(Window::gameplayWindList[i], BM_SETCHECK, BST_UNCHECKED, NULL);
			}
		}
		if (bugticked == BST_CHECKED) {
			SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
	jpnticked = SendMessage(Window::jpnControls, BM_GETCHECK, NULL, NULL);
	if (jpnticked == BST_CHECKED && bugticked == BST_CHECKED) {
		SendMessage(Window::bugFix, BM_SETCHECK, BST_UNCHECKED, NULL);
	}
	bugticked = SendMessage(Window::bugFix, BM_GETCHECK, NULL, NULL);
	if (bugticked == BST_CHECKED) {
		for (int i = 0; i < Window::windList.size(); i++) {
			LRESULT boxticked = SendMessage(Window::windList[i], BM_GETCHECK, NULL, NULL);
			if (Window::windList[i] != Window::normalarena && Window::windList[i] != Window::bugFix) {
				if (boxticked == BST_CHECKED) {
					boxticked = SendMessage(Window::windList[i], BM_SETCHECK, BST_UNCHECKED, NULL);
				}
			}
		}
	}
	metricticked = SendMessage(Window::metric, BM_GETCHECK, NULL, NULL);
	if (metricticked == BST_CHECKED) {
		SendMessage(Window::metric, BM_SETCHECK, BST_CHECKED, NULL);
	}
}