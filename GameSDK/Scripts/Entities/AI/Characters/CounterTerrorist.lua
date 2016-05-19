Script.ReloadScript( "SCRIPTS/Entities/AI/Characters/Human_x.lua")
Script.ReloadScript( "SCRIPTS/Entities/actor/BasicActor.lua")
Script.ReloadScript( "SCRIPTS/Entities/AI/Shared/BasicAI.lua")

--hostagePositionTable = CryAction.LoadXML(HostageDataDefinition,HostageData);
hostageNumber =  1;
dummyPlayer = "DummyPlayer"
--refPointMedic = System.GetEntityByName('Medic1'):GetWorldPos()

CT_x = {
  Properties = {
    bAdditionalBool = false,
    bHostageFound = false,
  }
}

function CT_x:OnEnemySeen()
  --AIBase.OnEnemySeen(self);
  local attentionTarget = AI.GetAttentionTargetEntity(self.id);
  if (attentionTarget.Properties.esFaction == "Friend" or attentionTarget.Properties.esFaction == "Medics") then
	Log(tostring("Should not Kill"))
	AI.Signal(SIGNALFILTER_SENDER, 1, "OnFriendSeen", self.id)
  else
	Log(tostring(attentionTarget.Properties.esFaction))
	Log(tostring("Should Kill"))
	AI.Signal(SIGNALFILTER_SENDER, 1, "OnHostileSeen", self.id)
  end
end


function CT_x:GetHostageLocation()
  Log(tostring("Get hostage location called"))
  local hostageId = System.GetEntityIdByName("DummyPlayer1");
  local ent = System.GetEntityByName("DummyPlayer1");
  if (ent ~= nil) then
    local EntityPos = ent:GetWorldPos();
    Log(tostring(EntityPos.x)); Log(tostring(EntityPos.y));Log(tostring(EntityPos.z));
  else
    Log("Entity not found");
  end
  AI.SetRefPointPosition(hostageId, EntityPos)
end

function CT_x:GetMedicLocation()
	if(self.actor:GetHealth() < 500) then
		--tempHostageNumber = hostageNumber
		Log(tostring("Get Medic Location"))
		--Log(tostring("Before"))
		--Log(tostring(hostageNumber))
		--Log(tostring("After"))
		--Log(tostring(hostageNumber))
		AI.SetRefPointPosition(System.GetEntityIdByName('CounterTerrorist1'), System.GetEntityByName('Medic1'):GetWorldPos())
		AI.Signal(SIGNALFILTER_SENDER, 1, "OnFindingMedic", self.id)
		--if(hostageNumber > 1) then
		--	hostageNumber = hostageNumber - 1;
		--end	
	else
		Log(tostring("No Medic Location"))
		--hostageNumber = hostageNumber + 1
	end
	return
end
--[[
function CT_x:reduceHostageNumber()
	if(hostageNumber > 1) then
		hostageNumber = hostageNumber - 1
	end	
	Log(tostring("In reduceHostageNumber"))
	Log(tostring(hostageNumber))
	return
end
--]]
function CT_x:OnFindHostage()
  if(hostageNumber == 4) then
	AI.Signal(SIGNALFILTER_SENDER, 1, "AllHostagesRescued", self.id)
	return
  end
  Log(tostring("FindingHostageDude"));
  Log(tostring(hostageNumber));
  dummy = dummyPlayer..tostring(hostageNumber);
  Log(tostring(dummy));
  AI.SetRefPointPosition(System.GetEntityIdByName('CounterTerrorist1'), System.GetEntityByName(dummy):GetWorldPos())
  --Log(tostring("Incremented Value"));
  --Log(tostring(hostageNumber));
  AI.Signal(SIGNALFILTER_SENDER, 1, "OnFindingHostage", self.id)
  hostageNumber = hostageNumber + 1;
end

function CT_x:CheckAIHealth()
	if (self:IsDead()) then
		Log(tostring("If Part"));
		Log(tostring(self:IsDead()));
		AI.Signal(SIGNALFILTER_SENDER, 1, "GoToGameOver", self.id)
	else
		return
	end	
end	

--mergef(CT_x,Human_x_CounterTerrorist,1)
mergef(CT_x,Human_x,1)
CreateActor(CT_x)
CounterTerrorist=CreateAI(CT_x)

Script.ReloadScript( "SCRIPTS/AI/Assignments.lua")
InjectAssignmentFunctionality(CounterTerrorist)
AddDefendAreaAssignment(CounterTerrorist)
AddHoldPositionAssignment(CounterTerrorist)
AddCombatMoveAssignment(CounterTerrorist)
AddPsychoCombatAllowedAssignment(CounterTerrorist)

CounterTerrorist:Expose()
