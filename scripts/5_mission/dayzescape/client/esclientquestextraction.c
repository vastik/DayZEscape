class ESClientQuestExtraction : ESQuest {	
	private ESClientLocation m_location;
	private ref ESQuestExtractionLocationConfig m_config;	
	private ref array<ref ESClientQuestExtractionZone> m_zones = new array<ref ESClientQuestExtractionZone>;
	
	void ESClientQuestExtraction(ESClientLocation location) {
		this.m_location = location;		
	}

	void OnServerConfig(ESQuestExtractionConfig data) {
		foreach (ESQuestExtractionLocationConfig config : data.Locations) {
			if (config.id == m_location.GetId()) {
				this.m_config = config;
				
				foreach (ESQuestExtractionLocationExtractionConfig zone : m_config.Extractions) {
					m_zones.Insert(new ESClientQuestExtractionZone(zone, this));	  				
				}	
				
				break;
			}
		}
	}	
	
	override void OnUpdate(float dt) {
		foreach (ESClientQuestExtractionZone zone : m_zones) {
			zone.OnUpdate();			
		}
	}
	
	ESClientLocation GetLocation() {
		return this.m_location;
	}
}

modded class ESClientLocation {
	override private ESQuest CreateQuest(string type) {
		if (type == "ESQuestExtraction") 
			return new ESClientQuestExtraction(this);
		else
			return super.CreateQuest(type);
	}
}