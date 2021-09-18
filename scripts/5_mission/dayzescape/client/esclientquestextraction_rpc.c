modded class ESClientModule {	
	override void RegisterRPC() {
		super.RegisterRPC();	
		GetRPCManager().AddRPC("DayZES", "OnServerQuestExtractionConfig", this, SingleplayerExecutionType.Client);		
	}
	
	private void OnServerQuestExtractionConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {		
		Param1<ref ESQuestExtractionConfig> params;
		ctx.Read(params);		
		
		ESQuestExtractionConfig config = params.param1;		
		
		foreach (ESClientLocation location : m_escapeLocations) {
			location.OnServerQuestExtractionConfig(config);
		}
	}
}

modded class ESClientLocation {
	void OnServerQuestExtractionConfig(ESQuestExtractionConfig config) {
		foreach (ESQuest quest : m_quests) {
			ESClientQuestExtraction client = ESClientQuestExtraction.Cast(quest);
			if (client) {
				client.OnServerConfig(config);
			}
		}
	}
}