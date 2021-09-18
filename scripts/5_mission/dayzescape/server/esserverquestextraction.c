class ESServerQuestExtraction : ESQuest {	
	private static ref ESQuestExtractionConfig m_StaticConfig;	
	private ref array<ref ESServerQuestExtractionZone> m_Zones;
	private ref ESQuestExtractionLocationConfig m_Config;
	private ref ESServerLocation m_Location;	
	
	void ESServerQuestExtraction(ESServerLocation location) {
		this.m_Location = location;
		this.m_Zones = new array<ref ESServerQuestExtractionZone>;
		
		if (!m_StaticConfig) {
			JsonFileLoader<ESQuestExtractionConfig>.JsonLoadFile("$profile:DayZEscape\\Quests\\ESQuestExtraction.json", m_StaticConfig);				
			if (!m_StaticConfig)
				Error("Quests\\EscapeQuestExtraction.json is not present!");
		}
		
		foreach (ESQuestExtractionLocationConfig locationConfig : m_StaticConfig.Locations) {
			if (locationConfig.id == m_Location.GetId()) {
				this.m_Config = locationConfig;
				
				foreach (ESQuestExtractionLocationExtractionConfig zone : m_Config.Extractions) {
					m_Zones.Insert(new ESServerQuestExtractionZone(zone, this));	  				
				}
				
				break;
			}
		}				
	}
	
	void OnClientExtractionStateUpdate(ESQuestExtractionStateChangedEvent ev) {
		foreach (ESServerQuestExtractionZone zone : m_Zones) {
			if (zone.GetId() == ev.Zone) {
				zone.OnClientExtractionStateUpdate(ev);
			}	
		}		
	}
	
	static ESQuestExtractionConfig GetStaticConfig() {
		return ESServerQuestExtraction.m_StaticConfig;
	}
}

modded class ESServerLocation {
	override private ESQuest CreateQuest(string type) {
		if (type == "ESQuestExtraction") 
			return new ESServerQuestExtraction(this);
		else
			return super.CreateQuest(type);
	}
}