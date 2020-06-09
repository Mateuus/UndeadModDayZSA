/**
 * UndeadMod.c
 *
 * Undead Mod
 * © 2020 DayZ Undead Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		if (!UndeadMod.m_Loaded) { UndeadMod.LoadFileData(); }
	}
}