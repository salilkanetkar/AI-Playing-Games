Script.ReloadScript( "SCRIPTS/Entities/AI/Characters/Human_x.lua")
Script.ReloadScript( "SCRIPTS/Entities/actor/BasicActor.lua")
Script.ReloadScript( "SCRIPTS/Entities/AI/Shared/BasicAI.lua")

CTFriend_x = {
  Properties = {
    bAdditionalBool = false,
  }
}

--AI.CreateGroupFormation(System.GetEntityIdByName("CounterTerroristFriend1"), System.GetEntityIdByName("CounterTerrorist1"))
--local group_id = AI.GetGroupOf()

--Log(tostring(AI.GetLeader(self.id)))
function CTFriend_x:FollowCounterTerrorist()
	AI.SetRefPointPosition(self.id, System.GetEntityByName('CounterTerrorist1'):GetWorldPos())
	return
end
--[[
function CTFriend_x:OnEnemySeen()
  --AIBase.OnEnemySeen(self);
  local attentionTarget = AI.GetAttentionTargetEntity(self.id);
  if (attentionTarget.Properties.esFaction == "Friend" or attentionTarget.Properties.esFaction == "Medics" or attentionTarget.Properties.esFaction == "CTFriend") then
	Log(tostring("Should not Kill"))
	AI.Signal(SIGNALFILTER_SENDER, 1, "OnFriendSeen", self.id)
  else
	Log(tostring(attentionTarget.Properties.esFaction))
	Log(tostring("Should Kill"))
	AI.Signal(SIGNALFILTER_SENDER, 1, "OnHostileSeen", self.id)
  end
end
--]]
mergef(CTFriend_x,Human_x,1)
CreateActor(CTFriend_x)
CounterTerroristFriend=CreateAI(CTFriend_x)

Script.ReloadScript( "SCRIPTS/AI/Assignments.lua")
InjectAssignmentFunctionality(CounterTerroristFriend)
AddDefendAreaAssignment(CounterTerroristFriend)
AddHoldPositionAssignment(CounterTerroristFriend)
AddCombatMoveAssignment(CounterTerroristFriend)
AddPsychoCombatAllowedAssignment(CounterTerroristFriend)

CounterTerroristFriend:Expose()
