class ESServerLocation {
	private bool m_isActive = false;
	private ref ESLocationConfig m_config;
	private ref array<ref ESQuest> m_quests;	
	private ref ESServerModule m_module;
		
	void ESServerLocation(ESLocationConfig locationConfig, ESServerModule module) {
		this.m_config = locationConfig;				
		this.m_quests = new array<ref ESQuest>();	
		this.m_module = module;
		
		foreach (string type : m_config.Quests) {
			ESQuest quest = CreateQuest(type);		
			if (!quest)	Error("Quest not found " + type);									
			m_quests.Insert(quest);		
		}
	}
	
	void OnQuestEvent(ESQuestEvent data) {
	}
	
	private ESQuest CreateQuest(string type) {
		return null;	
	}
	
	string GetId() {
		return m_config.id;
	}
}