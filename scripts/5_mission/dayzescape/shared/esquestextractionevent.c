class ESQuestExtractionStateChangedEvent : ESQuestEvent {	
	string Zone;
	bool State;
	[NonSerialized()]
	PlayerIdentity Player;
}