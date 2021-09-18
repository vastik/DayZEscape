class ESClientQuestExtractionZone {
	private ref ESQuestExtractionLocationExtractionConfig m_config;
	private ESClientQuestExtraction m_quest;
	private bool m_clientIsInZone = false;			
	
	void ESClientQuestExtractionZone(ESQuestExtractionLocationExtractionConfig config, ESClientQuestExtraction quest) {
		this.m_config = config;		
		this.m_quest = quest;	
	}	

	string GetId() {
		return m_config.id;
	}	

	void OnUpdate() {
		vector player = GetGame().GetPlayer().GetPosition();
		vector zone = m_config.Point;
		
		player[1] = 0;
		
		float distance = vector.Distance(player, zone);
		
		bool inZone = distance <= m_config.Radius;
		
		if (inZone != m_clientIsInZone) {
			m_clientIsInZone = inZone;			
			
			ESQuestExtractionStateChangedEvent ev = new ESQuestExtractionStateChangedEvent;
			ev.Location = m_quest.GetLocation().GetId();			
			ev.Zone = m_config.id;
			ev.State = m_clientIsInZone;						
					
			GetRPCManager().SendRPC("DayZES", "OnClientQuestExtractionStateChanged", new Param1<ESQuestExtractionStateChangedEvent>(ev));
		}
	}
}