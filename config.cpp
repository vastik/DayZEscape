class CfgPatches
{
	class DayZEscape
	{
		requiredAddons[]=
		{
			"JM_CF_Scripts"
		};
	};
};

class CfgMods
{

	class DayZEscape
	{
		type = "mod";
		inputs = "DayZEscape/scripts/inputs.xml";
		dir = "DayZEscape" ;
		dependencies[] = {"Game", "World", "Mission"};

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"DayZEscape/scripts/3_game"};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {"DayZEscape/scripts/4_world"};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {"DayZEscape/scripts/5_mission"};
			};
		};
	};
};