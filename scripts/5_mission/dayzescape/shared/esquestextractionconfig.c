class ESQuestExtractionConfig {
	ref array<ref ESQuestExtractionLocationConfig> Locations;
}

class ESQuestExtractionLocationConfig {
	string id;
	int Time;
	ref array<ref ESQuestExtractionLocationSpawnConfig> Spawns;
	ref array<ref ESQuestExtractionLocationExtractionConfig> Extractions;	
}

class ESQuestExtractionLocationSpawnConfig {
	string Start;
	ref array<string> Extractions;
}

class ESQuestExtractionLocationExtractionConfig {
	string id;
	string Name;
	int Time;
	int Radius;
	vector Point;
}