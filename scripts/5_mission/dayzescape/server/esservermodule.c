class ESServerModule : JMModuleBase {
	private bool m_isGameActive = false;
	private ref ESConfig m_escapeConfig;
	private ref array<ref ESServerLocation> m_escapeLocations;
	
	override bool IsClient() {
		return false;
	}
	
	override void OnMissionLoaded() {
		m_escapeLocations = new array<ref ESServerLocation>;
		
		Print("[ESServerModule] Initializing");
						
		m_escapeConfig = new ESConfig;
		JsonFileLoader<ESConfig>.JsonLoadFile("$profile:DayZEscape\\Globals.json", m_escapeConfig);		
		
		if (!m_escapeConfig) {
			Error("[DayZEscape] Globals.json is not present!");				
			return;
		}
		
		RegisterRPC();

		foreach (ESLocationConfig locationConfig : m_escapeConfig.Locations) {		
			Print("[ESServerModule] Creating location " + locationConfig.id);	
			m_escapeLocations.Insert(new ESServerLocation(locationConfig, this));
		}					
	}
	
	void RegisterRPC() {
				
	}
	
	override void OnInvokeConnect( PlayerBase player, PlayerIdentity identity) {
		GetRPCManager().SendRPC("DayZES", "OnServerConfig", new Param1<ref ESConfig>(m_escapeConfig));
	}
}