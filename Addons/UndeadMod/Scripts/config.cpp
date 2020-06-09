/**
 * config.cpp
 *
 * Undead Mod
 * © 2020 DayZ Undead Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class CfgPatches
{
	class UndeadMod_Scripts
	{
		units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]= {"RPC_Scripts", "JM_CF_Scripts", "VPPNotifications", "DZ_Data"};
	};
};

class CfgMods
{	
	class DZ_UndeadMod
	{	
		dir = "UndeadMod/Scripts";
		picture = "";
		action = "";
		appId = 2122259919;
		hideName = 1;
		hidePicture = 1;
		name = "Undead Mod";
		tooltip = "Undead Mod";
		credits = "SigWar & Mateuus";
		author = "Mateuus";
		authorID = "0"; 
		version = "0.1"; 
		extra = 0;
		type = "mod";
					
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"UndeadMod/Scripts/3_Game"};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {"UndeadMod/Scripts/4_World"};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {"UndeadMod/Scripts/5_Mission"};
			};
		}
	};
};

class CfgVehicles
{
	class Container_Base;
	class WoodenCrate: Container_Base
	{
	};
	class UndeadMod_Cama_Kit: WoodenCrate
	{		
		scope = 2;
		displayName = "Cama Spawn Kit";
		descriptionShort = "Cama Spawn Kit";
		model="\UndeadMod\Objetos\cama\sleepingbag_packed.p3d";
		weight = 300;
		itemBehaviour = 2;
		isMeleeWeapon = 0;
		absorbency = 0;
		reversed = 0;
		rotationFlags = 8;
		itemSize[] = {4,7};
		lootCategory = "Materials";
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"UndeadMod\Objetos\cama\data\packed\sleepingbag_packed_CO.paa"};
	};
};