class ESClientModule : JMModuleBase {
	private ref array<ref ESClientLocation> m_escapeLocations = new array<ref ESClientLocation>;
	private ref ESConfig m_escapeConfig;
	
	void ESClientModule() {
		RegisterRPC();
	}
	
	override void OnUpdate(float timeslice) {
		foreach (ESClientLocation location : m_escapeLocations) {
			location.OnUpdate(timeslice);
		}
	}
	
	override bool IsServer() {
		return false;
	}		
	
	void RegisterRPC() {
		GetRPCManager().AddRPC("DayZES", "OnServerConfig", this, SingleplayerExecutionType.Client);
	}
	
	private void OnServerConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target) {		
		Param1<ref ESConfig> config;		
		
		if (!ctx.Read(config))
			return;
		
		Print("[ESClientModule] Initializing");
						
		m_escapeConfig = config.param1;	
		
		foreach (ESClientLocation location : m_escapeLocations) {		
			delete location;
		}
		
		m_escapeLocations.Clear();
		
		foreach (ESLocationConfig locationConfig : m_escapeConfig.Locations) {		
			Print("[ESClientModule] Creating location " + locationConfig.id);	
			m_escapeLocations.Insert(new ESClientLocation(locationConfig, this));
		}
	}
}