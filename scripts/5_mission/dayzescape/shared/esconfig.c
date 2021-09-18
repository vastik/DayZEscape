class ESLocationSpawnConfig {
	string id;	
	vector Point; 	
}

class ESLocationQuestConfig {
	string id;
	string Type;
}

class ESLocationConfig {
	ref array<ref ESLocationSpawnConfig> Spawns;
	ref array<string> Quests;
	string Name;
	string id;
	int MinPlayers;
}

class ESConfig {	
	ref array<ref ESLocationConfig> Locations;
}