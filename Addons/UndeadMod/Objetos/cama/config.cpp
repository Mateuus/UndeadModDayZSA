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
	class DZ_Base_Cama
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgVehicles
{
	class Container_Base;
	class Base_Cama: Container_Base
	{
		scope = 2;
		displayName = "Cama Spawn";
		descriptionShort = "Cama Spawn";
		model="\UndeadMod\Objetos\cama\sleepingbag.p3d";
		weight = 2000;
		physLayer = "item_large";
		itemSize[] = {8,4};
		itemsCargoSize[]={10,10};
		carveNavmesh = 0;
		canBeDigged=0;
		bounding="BSphere";
		overrideDrawArea="3.0";
		placement="ForceSlopeOnTerrain";
		rotationFlags = 1;
		itemBehaviour = 2;
		storageCategory = 1;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"UndeadMod\Objetos\cama\data\unpacked\sleepingbag_CO.paa"};
	};
	class UndeadMod_Cama_Holo: Container_Base
	{
		scope = 0;
		displayName = "Spawn Cama HOLO";
		model="\UndeadMod\Objetos\cama\sleepingbag.p3d";
	};
};