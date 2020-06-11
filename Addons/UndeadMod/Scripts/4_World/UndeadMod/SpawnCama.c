/**
 * SpawnCama.c
 *
 * Undead Mod
 * © 2020 DayZ Undead Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

modded class ItemBase extends InventoryItem
{
	protected Object UndeadMod_Cama_Kit_Init;
	
	
	override void OnPlacementComplete( Man player )
	{
		super.OnPlacementComplete(player);
		string ObjType = GetType();
		
		if (ObjType == "UndeadMod_Cama_Kit") {		
			PlayerBase player_base = PlayerBase.Cast(player);
			PlayerIdentity PlayerID = player_base.GetIdentity();
			vector position = player_base.GetLocalProjectionPosition();
			vector orientation = player_base.GetLocalProjectionOrientation();
			vector DefaultCamaPos = Vector(0,0,0);
			vector CamaPos = Vector(0,0,0);
			CamaPos = UndeadMod.GetCamaPos(PlayerID,DefaultCamaPos);
		
			if(CamaPos != DefaultCamaPos){
				ref array<Object> nearest_objects = new array<Object>;
				Object toBeDeleted;
				toBeDeleted = NULL;
				
				GetGame().GetObjectsAtPosition3D(CamaPos, 0.9, nearest_objects, NULL);
				
				for (int i = 0; i < nearest_objects.Count(); ++i) {
					if(nearest_objects.Get(i).IsKindOf("Base_Cama")) {
						toBeDeleted = nearest_objects.Get(i);
						GetGame().ObjectDelete(toBeDeleted);
						NotificationSystem.SendNotificationToPlayerIdentityExtended(PlayerID, 4, "Undead Mod", "Sua cama na posição "+CamaPos.ToString(false)+" foi deletada.");
						UndeadMessage.ServerLog("[UNDEAD MOD] Cama Deletada em: "+CamaPos.ToString(false));	
					}
				}
				
				UndeadMod_Cama_Kit_Init = GetGame().CreateObject("Base_Cama", player_base.GetLocalProjectionPosition(), false);
				UndeadMod_Cama_Kit_Init.SetPosition(position);
				UndeadMod_Cama_Kit_Init.SetOrientation(orientation);
					
				UndeadMod.Insert(PlayerID, position);
				UndeadMod.SaveFileData();
				
				NotificationSystem.SendNotificationToPlayerIdentityExtended(PlayerID, 4, "Undead Mod", "Nova Cama Adicionada.");
			}else{
				UndeadMod_Cama_Kit_Init = GetGame().CreateObject("Base_Cama", player_base.GetLocalProjectionPosition(), false);
				UndeadMod_Cama_Kit_Init.SetPosition(position);
				UndeadMod_Cama_Kit_Init.SetOrientation(orientation);
					
				UndeadMod.Insert(PlayerID, position);
				UndeadMod.SaveFileData();
				
				NotificationSystem.SendNotificationToPlayerIdentityExtended(PlayerID, 4, "Undead Mod", "Nova Cama Adicionada.");
			}
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (this.GetType() == "Base_Cama") {
			foreach(string player_id, vector CamaPos: UndeadMod.ServerCamaData)
			{
				string CPosition = this.GetPosition().ToString(false);
				string OldCPosition =  CamaPos.ToString(false);
				
				if (CPosition == OldCPosition){
					UndeadMod.ServerCamaData.Remove(player_id);
					UndeadMod.SaveFileData();
					UndeadMessage.ServerLog("[UNDEAD MOD] Cama Deletada em: "+CamaPos);	
				}
			}
		}
	}
}

class UndeadMod
{
	static bool m_Loaded = false;
	static ref map<string,vector> ServerCamaData = new map<string,vector>;
	
	static void LoadFileData()
	{
	
		string line_content;
		FileHandle LoadFile = OpenFile("$profile:UndeadMod/SpawnCama/Camas.txt", FileMode.READ);


		if ( LoadFile == 0 ) {
			UndeadMessage.ServerLog("[UNDEAD MOD] FOUND NO CAMAS FILE!" );
			return;
		} else {
			while ( FGets( LoadFile,  line_content ) > 0 )
			{
				array<string> strings = new array<string>;
				line_content.Split("|", strings);
						
				string player_id =  strings.Get(1);
				float vector_x 	 = 	strings.Get(2).ToFloat();
				float vector_y   = 	strings.Get(3).ToFloat();
				float vector_z   = 	strings.Get(4).ToFloat();

				vector CamaPos = Vector(vector_x, vector_y, vector_z);
				ServerCamaData.Insert(player_id, CamaPos);
			}
			
			UndeadMessage.ServerLog("[UNDEAD MOD] LOADED FILE DATA!" );
			CloseFile(LoadFile);
			m_Loaded = true;
		}
	}
	
	static void SaveFileData()
	{
		FileHandle SaveFile = OpenFile("$profile:UndeadMod/SpawnCama/Camas.txt", FileMode.WRITE);		
		if (SaveFile != 0) {
			int i = 0;			
			foreach(string player_id, vector CamaPos: UndeadMod.ServerCamaData)
			{
				i++;
				array<string> s_vector = new array<string>;
				string CamaPosString = CamaPos.ToString(false);
				CamaPosString.Split(" ", s_vector);
				
				float vector_x 	 = 	s_vector.Get(0).ToFloat();
				float vector_y   = 	s_vector.Get(1).ToFloat();
				float vector_z   = 	s_vector.Get(2).ToFloat();
					
				string attach = i.ToString() + "|" + player_id + "|" + vector_x + "|" +vector_y+ "|" +vector_z;
				FPrintln(SaveFile, attach );
			}
			CloseFile(SaveFile);
		}
		UndeadMessage.ServerLog("[UNDEAD MOD] SAVE FILE DATA!" );
	}
	
	static void Insert(PlayerIdentity player_id, vector CamaPos)
	{
		Remove(player_id.GetId());
		ServerCamaData.Insert(player_id.GetId(), CamaPos);
		
		string player_name = player_id.GetName();
		UndeadMessage.ServerLog("[UNDEAD MOD] O jogador "+player_name+" adicionou uma cama na posição: "+CamaPos);
	}
	
	static void Remove(string playerID)
	{
		foreach(string player_id, vector CamaPos: UndeadMod.ServerCamaData)
		{
			if ( player_id == playerID ) {
				UndeadMod.ServerCamaData.Remove(player_id);
				UndeadMessage.ServerLog("[UNDEAD MOD] Cama Deletada em: "+CamaPos);	
			}	
		}
	}
	
	static void DeleteServerCama (vector cama)
	{
		foreach(string player_id, vector CamaPos: UndeadMod.ServerCamaData)
		{
			string CPosition = cama.ToString(false);
			string OldCPosition = CamaPos.ToString(false);
			if (CPosition == OldCPosition){
				UndeadMod.ServerCamaData.Remove(player_id);
				UndeadMod.SaveFileData();
				UndeadMessage.ServerLog("[UNDEAD MOD] Cama Deletada em: "+CamaPos);	
			}
		}
	}
	
	static vector GetCamaPos(PlayerIdentity playerID, vector SenderCamaPos)
	{
		foreach(string player_id, vector CamaPos: UndeadMod.ServerCamaData)
		{
			if(player_id == playerID.GetId())
			{
				SenderCamaPos = CamaPos;
				break;
			}
		}
		return SenderCamaPos;
	}
}