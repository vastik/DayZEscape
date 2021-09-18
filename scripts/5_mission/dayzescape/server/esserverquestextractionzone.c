typedef map<string, ref Timer> ESPlayerTimers;
typedef map<string, ref PlayerIdentity> ESPlayerIdentity;

static const int ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_ENTER = 0;
static const int ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_LEAVE = 1;
static const int ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_EXIT = 2;

class ESServerQuestExtractionZone {
	private ref ESQuestExtractionLocationExtractionConfig m_config;
	private ref ESServerQuestExtraction m_quest;	
	private ref ESPlayerTimers m_playersTimers = new ESPlayerTimers;
	private ref ESPlayerIdentity m_playersIdentity = new ESPlayerIdentity;
	
	void ESServerQuestExtractionZone(ESQuestExtractionLocationExtractionConfig config, ESServerQuestExtraction quest) {
		this.m_config = config;		
		this.m_quest = quest;
	}
	
	string GetId() {
		return m_config.id;
	}

	void OnClientExtractionStateUpdate(ESQuestExtractionStateChangedEvent data) {
		string playerId = data.Player.GetId();
		
		if (data.State) {
			if (m_playersTimers.Contains(playerId)) {
				Print("[ESQuestExtractionZone] Player  " + playerId + " already in zone!");
				return;
			}
			
			Timer timer = new Timer;
			timer.Run(m_config.Time, this, "OnPlayerExitTimer", new Param1<string>(playerId));
			m_playersTimers.Insert(playerId, timer);
			m_playersIdentity.Insert(playerId, data.Player);

			SendNotification(ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_ENTER, data.Player);
												
			Print("[ESQuestExtractionZone] Player " + playerId + " started extraction");				
		} else {
			if (!m_playersTimers.Contains(playerId)) {
				Print("[ESQuestExtractionZone] Player  " + playerId + " not in zone!");
				return;
			}					
			
			Timer playerTimer = m_playersTimers.Get(playerId);
			playerTimer.Stop();
			
			m_playersTimers.Remove(playerId);
			m_playersIdentity.Remove(playerId);			
			
			SendNotification(ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_LEAVE, data.Player);
		}
	}
	
	private void OnPlayerExitTimer(string playerId) {
		if (!m_playersTimers.Contains(playerId)) {
			Print("[ESQuestExtractionZone.OnPlayerExitTimer] Player  " + playerId + " not in zone!");
			return;
		}		
		
		PlayerIdentity playerIdentity = m_playersIdentity.Get(playerId);
		
		SendNotification(ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_EXIT, playerIdentity); 
		
		Print("[ESQuestExtractionZone] Player " + playerId + " extracted at " + m_config.id);
		
		m_playersTimers.Remove(playerId);
		m_playersIdentity.Remove(playerId);	
	}	
	
	private void SendNotification(int state, PlayerIdentity identity) {
		StringLocaliser title = new StringLocaliser("DE_EXTRACTION_" + state + "_TITLE");		
		StringLocaliser message = new StringLocaliser("DE_EXTRACTION_" + state + "_MESSAGE", m_config.Time.ToString());
		
		string icon = "set:ccgui_enforce image: HudEnter";
		int color = 0;
		
		if (state == ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_ENTER) 
		  color = ARGB(0, 38, 221, 38);
		else if (state == ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_LEAVE)
		  color = ARGB(0, 221, 38, 38);
		else if (state == ESCAPE_QUEST_EXTRACTION_PLAYER_STATE_EXIT)
		  color = ARGB(0, 38, 221, 38);
		
		NotificationSystem.Create(title, message, icon, color, 3, identity);				
	}
}