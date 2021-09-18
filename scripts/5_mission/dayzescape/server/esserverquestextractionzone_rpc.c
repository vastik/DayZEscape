modded class ESServerModule {	
	override void RegisterRPC() {
		super.RegisterRPC();		
		GetRPCManager().AddRPC("DayZES", "OnClientQuestExtractionStateChanged", this, SingleplayerExecutionType.Server);		
	}
	
	private void OnClientQuestExtractionStateChanged(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {		
		Param1<ref ESQuestExtractionStateChangedEvent> params;
		ctx.Read(params);		
		
		ESQuestExtractionStateChangedEvent data = params.param1;		
		data.Player = sender;
		
		JsonSerializer js = new JsonSerializer;		
		string jsout;
		js.WriteToString(data, false, jsout);
		
		Print("ESQuestExtractionStateChangedEvent " + jsout);
		
		foreach (ESServerLocation location : m_escapeLocations) {
			location.OnClientQuestExtractionStateChanged(data);
		}
	}
}

modded class ESServerLocation {
	void OnClientQuestExtractionStateChanged(ESQuestExtractionStateChangedEvent data) {
		if (data.Location != m_config.id) 
			return;
		
		foreach (ESQuest quest : m_quests) {
			ESServerQuestExtraction extractionQuest = ESServerQuestExtraction.Cast(quest);
			if (extractionQuest) {
				extractionQuest.OnClientExtractionStateUpdate(data);
			}
		}
	}
}