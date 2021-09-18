class ESServerLocationSpawn {
	private ref ESLocationSpawnConfig m_Config;
	private ref ESServerLocation m_Location;
	private ref ExpansionPartyData m_PartyData;
	
	void ESServerLocationSpawn(ESLocationSpawnConfig config, ESServerLocation location) {
		this.m_Config = config;
		this.m_Location = location;
	}
	
	void SetPartyAndTeleport(ExpansionPartyData party) {
			
	}
}