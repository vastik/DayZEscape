modded class ESServerModule {
	override void OnInvokeConnect(PlayerBase player, PlayerIdentity identity) {
		super.OnInvokeConnect(player, identity);		
		
		ESQuestExtractionConfig config = ESServerQuestExtraction.GetStaticConfig();
		if (!config) return;
		
		GetRPCManager().SendRPC("DayZES", "OnServerQuestExtractionConfig", new Param1<ESQuestExtractionConfig>(config), true, identity);
	}
}