#include "pch.h"
#include "windowPainter.h"

void windowPainter::createWindows(Window* win) {
	pWin = win;
	graphicWindows();
	gameplayWindows();
	arenaWindows();
	storyWindows();
	audioWindows();
	modeWindows();
}

void windowPainter::graphicWindows() {
	// Create graphic patch windows
	pWin->resize = CreateWindow(L"BUTTON", L"Face fixes (resize)", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::graphicsx), (int)(Window::winY * 0.30), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->portraits = CreateWindow(L"BUTTON", L"Face fixes (normal)", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::graphicsx), (int)(Window::winY * 0.36), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->flashes = CreateWindow(L"BUTTON", L"No battle flashes", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::graphicsx), (int)(Window::winY * 0.42), 100, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->roni = CreateWindow(L"BUTTON", L"PW Roni", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::graphicsx), (int)(Window::winY * 0.48), 100, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->cafe = CreateWindow(L"BUTTON", L"Emeralda cafe fix", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::graphicsx), (int)(Window::winY * 0.54), 100, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	// Put in window list
	Window::windList.emplace_back(Window::resize);
	Window::windList.emplace_back(Window::portraits);
	Window::windList.emplace_back(Window::flashes);
	Window::windList.emplace_back(Window::roni);
	Window::windList.emplace_back(Window::cafe);
}

void windowPainter::gameplayWindows() {
	// Create gameplay patch windows
	pWin->encounters = CreateWindow(L"BUTTON", L"1/2 encounters", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.30), 90, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->experience = CreateWindow(L"BUTTON", L"Modify exp", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.36), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->expList = CreateWindow(L"BUTTON", L"Modifier", WS_CHILD | WS_VISIBLE | BS_SPLITBUTTON, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.42), 110, 25, Window::winHwnd, (HMENU)9004, Window::winInst, NULL);
	pWin->gold = CreateWindow(L"BUTTON", L"Modify gold", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.48), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->goldList = CreateWindow(L"BUTTON", L"Modifier", WS_CHILD | WS_VISIBLE | BS_SPLITBUTTON, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.54), 110, 25, Window::winHwnd, (HMENU)9005, Window::winInst, NULL);
	pWin->monsters = CreateWindow(L"BUTTON", L"Rebalanced enemies", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.60), 120, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->itemspells = CreateWindow(L"BUTTON", L"Rebalanced party/items", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.66), 160, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->deathblows = CreateWindow(L"BUTTON", L"No Deathblow levels", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.72), 160, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->cap = CreateWindow(L"BUTTON", L"No damage cap", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::gameplayx), (int)(Window::winY * 0.78), 160, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	// Put in window list
	Window::windList.emplace_back(Window::encounters);
	Window::windList.emplace_back(Window::experience);
	Window::windList.emplace_back(Window::expList);
	Window::windList.emplace_back(Window::gold);
	Window::windList.emplace_back(Window::goldList);
	Window::windList.emplace_back(Window::itemspells);
	Window::windList.emplace_back(Window::monsters);
	Window::windList.emplace_back(Window::deathblows);
	Window::windList.emplace_back(Window::cap);
	// Put in gameplay window list
	Window::gameplayWindList.emplace_back(Window::encounters);
	Window::gameplayWindList.emplace_back(Window::experience);
	Window::gameplayWindList.emplace_back(Window::gold);
	Window::gameplayWindList.emplace_back(Window::itemspells);
	Window::gameplayWindList.emplace_back(Window::monsters);
	Window::gameplayWindList.emplace_back(Window::deathblows);
	Window::gameplayWindList.emplace_back(Window::cap);
}

void windowPainter::arenaWindows() {
	// Create arena patch windows
	pWin->normalarena = CreateWindow(L"BUTTON", L"Normal", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, (int)(Window::winX * pWin->arenax), (int)(Window::winY * 0.30), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->basicarena = CreateWindow(L"BUTTON", L"Basic mode", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, (int)(Window::winX * pWin->arenax), (int)(Window::winY * 0.36), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->expertarena = CreateWindow(L"BUTTON", L"Expert mode", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, (int)(Window::winX * pWin->arenax), (int)(Window::winY * 0.42), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	// Put in window list
	Window::windList.emplace_back(Window::normalarena);
	Window::windList.emplace_back(Window::basicarena);
	Window::windList.emplace_back(Window::expertarena);
	// Put in gameplay window list
	Window::gameplayWindList.emplace_back(Window::basicarena);
	Window::gameplayWindList.emplace_back(Window::expertarena);
}

void windowPainter::storyWindows() {
	// Create story patch windows
	pWin->script = CreateWindow(L"BUTTON", L"Script/name changes", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::storyx), (int)(Window::winY * 0.30), 120, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->fasttext = CreateWindow(L"BUTTON", L"Fast text", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::storyx), (int)(Window::winY * 0.36), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->instant = CreateWindow(L"BUTTON", L"Instant text", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::storyx), (int)(Window::winY * 0.42), 110, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	// Put in window list
	Window::windList.emplace_back(Window::fasttext);
	Window::windList.emplace_back(Window::script);
	Window::windList.emplace_back(Window::instant);
}

void windowPainter::audioWindows() {
	// Create audio patch windows
	pWin->fmvs = CreateWindow(L"BUTTON", L"FMV undub", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::audiox), (int)(Window::winY * 0.30), 100, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->voice = CreateWindow(L"BUTTON", L"Battle undub", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::audiox), (int)(Window::winY * 0.36), 90, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->music = CreateWindow(L"BUTTON", L"Music changes", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::audiox), (int)(Window::winY * 0.42), 90, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	// Put in window list
	Window::windList.emplace_back(Window::fmvs);
	Window::windList.emplace_back(Window::voice);
	Window::windList.emplace_back(Window::music);
}

void windowPainter::modeWindows() {
	// Create mode patch windows
	pWin->storyMode = CreateWindow(L"BUTTON", L"Story mode", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::smx), (int)(Window::winY * 0.30), 85, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->jpnControls = CreateWindow(L"BUTTON", L"JPN controls", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::smx), (int)(Window::winY * 0.36), 85, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	pWin->bugFix = CreateWindow(L"BUTTON", L"Bug fix only", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, (int)(Window::winX * Window::smx), (int)(Window::winY * 0.42), 85, 25, Window::winHwnd, (HMENU)9002, Window::winInst, NULL);
	// Put in window list
	Window::windList.emplace_back(Window::storyMode);
	Window::windList.emplace_back(Window::jpnControls);
	Window::windList.emplace_back(Window::bugFix);
}

void windowPainter::initialiseFont() {
	Window::log_file << "Applying font to windows." << std::endl;
	// Apply font to paths
	for (int i = 0; i < Window::pathList.size(); i++) {
		SendMessage(Window::pathList[i], WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), NULL);
	}
	// Apply font to buttons
	for (int i = 0; i < Window::buttonList.size(); i++) {
		SendMessage(Window::buttonList[i], WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), NULL);
	}
	// Apply font to each window in windList
	for (int i = 0; i < Window::windList.size(); i++) {
		SendMessage(Window::windList[i], WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), NULL);
	}

}

void windowPainter::paint() {
	PAINTSTRUCT ps;
	Window::log_file << "Begin drawing window." << std::endl;
	hdc = BeginPaint(Window::winHwnd, &ps);
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SetBkMode(hdc, TRANSPARENT);
	Window::log_file << "Set font." << std::endl;
	SelectObject(hdc, hFont);
	Window::log_file << "Draw window." << std::endl;
	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
	GetClientRect(Window::winHwnd, &rcWindow);
	RECT rc1, rc2;
	rc1, rc2 = rcWindow;
	rc1.top = Window::winY * 0.02;
	rc1.left = Window::winX / 50;
	rc1.right = Window::winX - (rc1.left * 2);
	rc1.bottom = Window::winY * 0.21;
	rc2.top = Window::winY * 0.24;
	rc2.left = rc1.left;
	rc2.right = rc1.right;
	rc2.bottom = Window::winY * 0.85;
	Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
	Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);
	Window::log_file << "Draw upper rectangle." << std::endl;
	FillRect(hdc, &rc1, (HBRUSH)(COLOR_WINDOW));
	Window::log_file << "Draw lower rectangle." << std::endl;
	FillRect(hdc, &rc2, (HBRUSH)(COLOR_WINDOW));
	FrameRect(hdc, &rc1, CreateSolidBrush(RGB(220, 220, 220)));
	FrameRect(hdc, &rc2, CreateSolidBrush(RGB(220, 220, 220)));
	drawText();
	EndPaint(Window::winHwnd, &ps);
}

void windowPainter::drawText() {
	// Set font
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SelectObject(hdc, hFont);
	// Create text
	swprintf_s(cd1text, 256, L"CD1 File:");
	swprintf_s(cd2text, 256, L"CD2 File:");
	swprintf_s(graphicstext, 256, L"Graphics:      ");
	swprintf_s(gameplaytext, 256, L"Gameplay:  ");
	swprintf_s(arenatext, 256, L"Arena:  ");
	swprintf_s(storytext, 256, L"Story:    ");
	swprintf_s(audiotext, 256, L"Audio:    ");
	swprintf_s(modestext, 256, L"Modes:    ");
	// Output text
	TextOut(hdc, Window::winX * 0.0325, Window::winY * 0.03, cd1text, wcslen(cd1text));
	TextOut(hdc, Window::winX * 0.0325, Window::winY * 0.09, cd2text, wcslen(cd2text));
	TextOut(hdc, Window::winX * Window::graphicsx, Window::winY * 0.26, graphicstext, wcslen(graphicstext));
	TextOut(hdc, Window::winX * Window::gameplayx, Window::winY * 0.26, gameplaytext, wcslen(gameplaytext));
	TextOut(hdc, Window::winX * Window::arenax, Window::winY * 0.26, arenatext, wcslen(arenatext));
	TextOut(hdc, Window::winX * Window::storyx, Window::winY * 0.26, storytext, wcslen(storytext));
	TextOut(hdc, Window::winX * Window::audiox, Window::winY * 0.26, audiotext, wcslen(audiotext));
	TextOut(hdc, Window::winX * Window::smx, Window::winY * 0.26, modestext, wcslen(modestext));
}

void windowPainter::drawDropdown(std::string option) {
	// Set drop down menu window text
	if (option == "normal") {
		if (Window::dropDown->hdr.hwndFrom == GetDlgItem(Window::winHwnd, 9004)) {
			SetWindowText(Window::expList, L"1x");
			Window::expModifier = option;
		}
		if (Window::dropDown->hdr.hwndFrom == GetDlgItem(Window::winHwnd, 9005)) {
			SetWindowText(Window::goldList, L"1x");
			Window::goldModifier = option;
		}
	}
	if (option == "half") {
		if (Window::dropDown->hdr.hwndFrom == GetDlgItem(Window::winHwnd, 9004)) {
			SetWindowText(Window::expList, L"1.5x");
			Window::expModifier = option;
		}
		if (Window::dropDown->hdr.hwndFrom == GetDlgItem(Window::winHwnd, 9005)) {
			SetWindowText(Window::goldList, L"1.5x");
			Window::goldModifier = option;
		}
	}
	if (option == "double") {
		if (Window::dropDown->hdr.hwndFrom == GetDlgItem(Window::winHwnd, 9004)) {
			SetWindowText(Window::expList, L"2x");
			Window::expModifier = option;
		}
		if (Window::dropDown->hdr.hwndFrom == GetDlgItem(Window::winHwnd, 9005)) {
			SetWindowText(Window::goldList, L"2x");
			Window::goldModifier = option;
		}
	}
	if (option == "reset") {
		SetWindowText(Window::expList, L"Modifier");
		Window::expModifier = "";
		SetWindowText(Window::goldList, L"Modifier");
		Window::goldModifier = "";
	}
}

