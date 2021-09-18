modded class ExpansionPartyModule {
	
	ref map<int, ref ExpansionPartyData> GetServerParties() {
		return this.m_Parties;
	}	
}