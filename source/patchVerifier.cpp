#include "pch.h"
#include "patchVerifier.h"

void patchVerifier::verify() {
	graphicsVerify();
	gameplayVerify();
	arenaVerify();
	storyVerify();
	audioVerify();
	modeVerify();
	bugVerify();
	titleVerify();
}

void patchVerifier::graphicsVerify() {
	if (windowHandler::resizeticked == BST_CHECKED) {
		Window::log_file << "Resized portraits directory found." << std::endl;
		patchProcessor::resizeName = "resized_portraits";
	}
	if (windowHandler::portraitsticked == BST_CHECKED) {
		Window::log_file << "Portrait directory found." << std::endl;
		patchProcessor::portraitsName = "portraits";
	}
	if (windowHandler::roniticked == BST_CHECKED) {
		Window::log_file << "Roni directory found." << std::endl;
		if (!windowHandler::resizeticked == BST_CHECKED) {
			patchProcessor::roniName = "roni_pw\\default";
		}
		else {
			patchProcessor::roniName = "roni_pw\\resized";
		}
	}
	if (windowHandler::cafeticked == BST_CHECKED) {
		Window::log_file << "Emeralda diner fix directory found." << std::endl;
		if (patchProcessor::num == 1) {
			if (!windowHandler::scriptticked == BST_CHECKED) {
				patchProcessor::cafeName = "emeralda_fix\\og_script";
			}
			else {
				patchProcessor::cafeName = "emeralda_fix\\new_script";
			}
		}
	}
}

void patchVerifier::gameplayVerify() {
	monsterFileVerify();
	if (windowHandler::encticked == BST_CHECKED) {
		Window::log_file << "Half encounters directory found." << std::endl;
		// Check if script patches aren't selected to avoid compatibility issues. Otherwise, a merged folder will be used
		if (!windowHandler::scriptticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::encountersName = "encounter_rate_1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::encountersName = "encounter_rate_2";
			}
		}
		else {
			if (patchProcessor::num == 1) {
				patchProcessor::encountersName = "encounterone_script";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::encountersName = "encountertwo_script";
			}
		}
	}
	if (windowHandler::itemspellsticked == BST_CHECKED) {
		Window::log_file << "Rebalanced items/party directory found." << std::endl;
		// Check if the items/script hybrid patch needs to be applied
		if (windowHandler::scriptticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::itemspellsName = "Script_items";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::itemspellsName = "Script_items2";
			}
		}
		else {
			if (patchProcessor::num == 1) {
				patchProcessor::itemspellsName = "items1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::itemspellsName = "items2";
			}
		}
	}
	if (windowHandler::deathblowsticked == BST_CHECKED) {
		Window::log_file << "No Deathblow levels directory found." << std::endl;
		patchProcessor::deathblowName = "exp_data";
	}
	if (windowHandler::capticked == BST_CHECKED) {
		patchProcessor::editExe = true;
	}
}

void patchVerifier::monsterFileVerify() {
	if (windowHandler::monstersticked == BST_CHECKED) {
		Window::log_file << "Rebalanced monsters directory found." << std::endl;
		// Check if items/spells and script patches aren't selected to avoid compatibility issues.
		if (!windowHandler::itemspellsticked == BST_CHECKED && !windowHandler::scriptticked == BST_CHECKED) {
			patchProcessor::monsterName = "Monsters";
		}
		else if (windowHandler::itemspellsticked == BST_CHECKED && !windowHandler::scriptticked == BST_CHECKED) {
			patchProcessor::monsterName = "monsters_items";
		}
		else if (!windowHandler::itemspellsticked == BST_CHECKED && windowHandler::scriptticked == BST_CHECKED) {
			patchProcessor::monsterName = "monsters_script";
		}
		else if (windowHandler::itemspellsticked == BST_CHECKED && windowHandler::scriptticked == BST_CHECKED) {
			patchProcessor::monsterName = "monsters_both";
		}
	}
	if (windowHandler::expticked == BST_CHECKED) {
		Window::log_file << "Experience directory found." << std::endl;
		patchProcessor::expName = "og_monsters";
	}
	if (windowHandler::goldticked == BST_CHECKED) {
		Window::log_file << "Gold directory found." << std::endl;
		patchProcessor::goldName = "og_monsters";
	}
}

void patchVerifier::arenaVerify() {
	if (windowHandler::basicarenaticked == BST_CHECKED) {
		Window::log_file << "Basic arena directory found." << std::endl;
		if (!windowHandler::scriptticked == BST_CHECKED) {
			patchProcessor::arenaName = "filesbasic";
		}
		else {
			patchProcessor::arenaName = "filesbasic_script";
		}
	}
	if (windowHandler::expertarenaticked == BST_CHECKED) {
		Window::log_file << "Expert arena directory found." << std::endl;
		if (!windowHandler::scriptticked == BST_CHECKED) {
			patchProcessor::arenaName = "filesexpert";
		}
		else {
			patchProcessor::arenaName = "filesexpert_script";
		}
	}
}

void patchVerifier::storyVerify() {
	if (windowHandler::fastticked == BST_CHECKED) {
		if (windowHandler::scriptticked == BST_CHECKED) {
			Window::log_file << "Retranslated fast text directory found." << std::endl;
			if (patchProcessor::num == 1) {
				patchProcessor::fastName = "text_cd1";
			}
			if (patchProcessor::num == 2) {
				// Disc 2 will use the same patch regardless of whether the script patch has been applied as it has no cutscenes with auto-advance
				patchProcessor::fastName = "text_cd2";
			}
		}
		else {
			Window::log_file << "Fast text directory found." << std::endl;
			if (patchProcessor::num == 1) {
				patchProcessor::fastName = "text_old1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::fastName = "text_cd2";
			}
		}
		patchProcessor::editExe = true;
	}
	if (windowHandler::scriptticked == BST_CHECKED) {
		Window::log_file << "Retranslated script directory found." << std::endl;
		// Check if items/spells and script hybrid won't be applied
		if (!windowHandler::itemspellsticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::scriptName = "script1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::scriptName = "script2";
			}
		}
	}
	if (windowHandler::instantticked == BST_CHECKED) {
		if (windowHandler::scriptticked == BST_CHECKED) {
			Window::log_file << "Retranslated instant text directory found." << std::endl;
			if (patchProcessor::num == 1) {
				patchProcessor::fastName = "text_cd1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::fastName = "text_cd2";
			}
		}
		patchProcessor::editExe = true;
	}
}

void patchVerifier::audioVerify() {
	if (windowHandler::fmvticked == BST_CHECKED) {
		// Access directory for patches if FMVs has been ticked
		Window::log_file << "Check if 'patches' directory exists." << std::endl;
		std::filesystem::current_path(Window::home);
		if (std::filesystem::exists(patchPath)) {
			std::filesystem::current_path(patchPath);
			Window::log_file << "'patches' directory is valid." << std::endl;
			patchPathValid = true;
			Window::log_file << "FMV patch file found." << std::endl;
			if (patchProcessor::num == 1) {
				patchProcessor::fmvPatch = "cd1_fmvs.xdelta";
				patchProcessor::fmvName = "fmv1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::fmvPatch = "cd2_fmvs.xdelta";
				patchProcessor::fmvName = "fmv2";
			}
		}
		std::filesystem::current_path(Window::home);
		std::filesystem::current_path(patchProcessor::gamefilePath);
	}
	if (windowHandler::voiceticked == BST_CHECKED) {
		Window::log_file << "Undub in-game voice directory found." << std::endl;
		patchProcessor::voiceName = "voice";
	}
	if (windowHandler::musicticked == BST_CHECKED) {
		Window::log_file << "Music change directory found." << std::endl;
		if (!windowHandler::scriptticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::musicName = "music_1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::musicName = "music_2";
			}
		}
	}
}

void patchVerifier::modeVerify() {
	if (windowHandler::storymodeticked == BST_CHECKED) {
		Window::log_file << "Story mode directory found." << std::endl;
		if (!windowHandler::scriptticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::storyModeName = "storyfiles_cd1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::storyModeName = "storyfiles_cd2";
			}
		}
		else {
			if (patchProcessor::num == 1) {
				patchProcessor::storyModeName = "storyfiles_script_cd1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::storyModeName = "storyfiles_script_cd2";
			}
		}
	}
	if (windowHandler::jpnticked == BST_CHECKED) {
		Window::log_file << "Japanese control directory found." << std::endl;
		if (!windowHandler::itemspellsticked == BST_CHECKED && !windowHandler::scriptticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::jpnName = "control_files_1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::jpnName = "control_files_2";
			}
		}
		if (!windowHandler::scriptticked == BST_CHECKED && windowHandler::itemspellsticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::jpnName = "jpn_items_1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::jpnName = "jpn_items_2";
			}
		}
		if (windowHandler::scriptticked == BST_CHECKED) {
			if (patchProcessor::num == 1) {
				patchProcessor::jpnName = "jpn_script_1";
			}
			if (patchProcessor::num == 2) {
				patchProcessor::jpnName = "jpn_script_2";
			}
		}
		patchProcessor::editExe = true;
	}
}

void patchVerifier::bugVerify() {
	// Bug patch is not applied with items/spells and script as they already have it applied.
	if (!windowHandler::itemspellsticked == BST_CHECKED) {
		Window::log_file << "Bug fix directory found." << std::endl;
		if (patchProcessor::num == 1) {
			patchProcessor::bugName = "bug_fix1";
		}
		if (patchProcessor::num == 2) {
			patchProcessor::bugName = "bug_fix2";
		}
	}
}

void patchVerifier::titleVerify() {
	Window::log_file << "Title screen directory found." << std::endl;
	patchProcessor::titleName = "title_screen";
}
