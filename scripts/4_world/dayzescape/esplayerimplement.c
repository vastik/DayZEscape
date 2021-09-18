modded class DayZPlayerImplement
{	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{	
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
				
		UAInput localInput = GetUApi().GetInputByName("UAEFDToggleTimer");

		if (!localInput.LocalDoubleClick())
			return;		
		
		GetRPCManager().SendRPC("DayZES", "OnTimerRequest");
	}	
}