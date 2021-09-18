class ESClientLocation {	
	private ref ESLocationConfig m_config;	
	private ref ESClientModule m_module;
	private ref array<ref ESQuest> m_quests;
		
	void ESClientLocation(ESLocationConfig config, ESClientModule module) {		
		this.m_config = config;				
		this.m_quests = new array<ref ESQuest>();	
		this.m_module = module;
		
		foreach (string type : m_config.Quests) {
			ESQuest quest = CreateQuest(type);		
			
			if (!quest) {
				Error("Quest not found " + type);											
				continue;
			}
			
			m_quests.Insert(quest);		
		}				
	}
	
	void OnUpdate(float dt) {
		foreach (ESQuest quest : m_quests) {
			quest.OnUpdate(dt);
		}
	}
	
	string GetId() {
		return this.m_config.id;
	}
	
	private ESQuest CreateQuest(string type) {
		return null;	
	}
}