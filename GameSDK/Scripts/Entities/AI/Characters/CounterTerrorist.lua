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
    iHostageCount = 0,
    iHostageRescued = 0,
    iMedCount = 0,
    sCurrentHostage = "",
    vectorCurrentHosLoc = {},
	  sCurrentEnemy = "",
    bGroupLeader = false,
    -- vectorTeammates = {},
    -- iEnemiesKilled = 0,
  },
  Group = {
    -- bGroupLeader = false,
    vectorTeammates = {},
    iEnemiesKilled = 0,
  },
  time_elapsed = 0.0,
	player_pos = {},
	player_health = {},
  xml_def_path = "Scripts/Entities/AI/Characters/DataDef.xml",
  xml_data_path = "DataData.xml",
}

function CT_x:OnInit()
  self:Activate(1);
end

function CT_x:OnUpdate(dt)
  if (not System.IsEditing()) then
    self.time_elapsed = self.time_elapsed + dt;
	Log(tostring("hey I am update"))
  end
end

function CT_x:ExecuteTest()
  Log("Game Won!!")
  CryAction.SaveXML(self.xml_def_path, self.xml_data_path, self)
  self.time_elapsed = 0.0
 self.player_pos = {}
 self.player_health = {}
end

function CT_x:Savefile()
  Log(tostring("File updated"))
  CryAction.SaveXML(self.xml_def_path, self.xml_data_path, self)
end
-- function CT_x:OnReset(bGameStart)
-- 	self.time_elapsed = 0.0
-- 	if(not bGameStart) then
-- 		 CryAction.SaveXML(self.xml_def_path, self.xml_data_path, self)
-- 	end
--   self.player_pos = {}
--   self.player_health = {}
--
-- end

function CT_x:CheckHostageRescued()
  if (self.Properties.iHostageCount == self.Properties.iHostageRescued) then
    AI.SetBehaviorVariable(self.id, "AllHostagesRescued", true)
    AI.Signal(0, -1, "GoTo_GameWon", self.id)
    if #self.Group.vectorTeammates > 0 then
      for i = 1, #self.Group.vectorTeammates do
        local entId = System.GetEntityIdByName(self.Group.vectorTeammates[i])
        AI.Signal(0, -1, "GoTo_GameWon", entId)
      end
    end
    Log(tostring("All hostages rescued"))
  else
    Log(tostring("Hostage not rescued yet"))
  end
end

-- Initialize the data file with the list of all the hostages to be rescued
-- and the list of all the medics (to find the nearest medic in case of )
function CT_x:InitHostageLoc()
  local entities = System.GetEntitiesByClass("Hostage")
  local mEntities = System.GetEntitiesByClass("Medic")

  Data ={
    LocationTable = {
      HostagesLoc = {},
      MedicLoc = {}
    }
  }
  -- Initialize the list of all the teammates
  local team = System.GetEntitiesByClass("CounterTerrorist")
  if (next(team) ~= nil) then
    local numTeam = table.getn(team)
    for i = 1, numTeam do
      if (team[i]:GetName() ~= self:GetName()) then
        self.Group.vectorTeammates[#self.Group.vectorTeammates + 1] = team[i]:GetName()
      end
    end
  end

  if (next(mEntities) ~= nil) then
    local mNum = table.getn(mEntities)
    self.Properties.iMedCount = mNum
    for i = 1, mNum do
      mtmp = {
        MIndex=i,
        MName = tostring(mEntities[i]:GetName()),
        MLoc = mEntities[i]:GetWorldPos()
      }
      table.insert(Data.LocationTable.MedicLoc, mtmp)
    end
  end

  if next(entities) ~= nil then
    local n = table.getn(entities)
    self.Properties.iHostageCount = n
    self.Properties.iHostageRescued = 0
    for i = 1, self.Properties.iHostageCount do
      tmp = {
        HIndex=i,
        HName=tostring(entities[i]:GetName()),
        HLoc = entities[i]:GetWorldPos()
      }
      table.insert(Data.LocationTable.HostagesLoc, tmp)
    end

  Log(tostring("Locations initialized"))
  CryAction.SaveXML("Scripts/Entities/AI/Characters/LocationsDef.xml", "D:/Amazon/Lumberyard/dev/GameSDK/Scripts/Entities/AI/Characters/LocationsData.xml", Data)
  -- AI.Signal(0,-1,"OnHostageInit",self.id)
  -- return true
  -- if self.Properties.iHostageCount > 0 then
    AI.SetBehaviorVariable(self.id, "LocationsInitialized", true)
    return true
  end
end


-- Find the nearest hostage based on the importance of the hostage
-- The group leader will lead and his teammates are supposed to follow him covering
-- from two different angles
function CT_x:FindNearestHostage()
  if (self.Properties.bGroupLeader == true) then
    local Data = CryAction.LoadXML("Scripts/Entities/AI/Characters/LocationsDef.xml", "D:/Amazon/Lumberyard/dev/GameSDK/Scripts/Entities/AI/Characters/LocationsData.xml")
    -- local HostLoc = {}
    local myPos = self:GetWorldPos()
    local DistTable = {}
    local shortestDist = 0
    for i = 1, self.Properties.iHostageCount do
      local tempPos = Data.LocationTable.HostagesLoc[i].HLoc
      -- table.insert(HostLoc, Data.LocationTable.HostagesLoc[i].HLoc)
      local tmpDist = DistanceVectors(myPos, tempPos)
      local entity = System.GetEntityByName(Data.LocationTable.HostagesLoc[i].HName)
      if shortestDist == 0 then
        if entity.Properties.bRescued == false then
          shortestDist = tmpDist
          sCurrentHostage = Data.LocationTable.HostagesLoc[i].HName
          vectorCurrentHosLoc = Data.LocationTable.HostagesLoc[i].HLoc
          table.insert(DistTable, tmpDist)
        end
      else
        if tmpDist < shortestDist then
          if entity.Properties.bRescued == false then
            shortestDist = tmpDist
            sCurrentHostage = Data.LocationTable.HostagesLoc[i].HName
            vectorCurrentHosLoc = Data.LocationTable.HostagesLoc[i].HLoc
            table.insert(DistTable, tmpDist)
          end
        end
      end
    end
    if next(DistTable) == nil then
      self.Properties.iHostageRescued = self.Properties.iHostageCount
      AI.Signal(0, -1, "GoTo_Idle", self.id)
    else
      AI.SetRefPointPosition(self.id, vectorCurrentHosLoc)
      if shortestDist <= 15 then
        AI.Signal(0, -1, "GoTo_WalkToHostage", self.id)
      end
    end
    Log(sCurrentHostage)
    Log(Vec2Str(vectorCurrentHosLoc))
    Log(tostring(shortestDist))

  else
    -- local followPos = {x=0, y=0, z=0}
    -- for i=1, #vectorTeammates do
    --   if vectorTeammates[i].Properties.bGroupLeader == true then
    --     local lead = vectorTeammates[i]
    --     local leadPos = System.GetEntityByName(lead):GetWorldPos()
    -- end
    -- AI.SetRefPointPosition(self.id, leadPos)
    AI.Signal(0, -1, "GoTo_FollowLeader", self.id)
  end
end

-- If the counter terrorist entity is not a leader, it will realize that it has to follow
-- the leader and the RefPoint is set to be the leader.
function CT_x:FindFormationPos()
  local leadPos = {}
  local pos1 = {}
  for i=1, #self.Group.vectorTeammates do
    local ent = System.GetEntityByName(self.Group.vectorTeammates[i])
    if ent.Properties.bGroupLeader == true then
      local lead = self.Group.vectorTeammates[i]
      leadPos = System.GetEntityByName(lead):GetWorldPos()
    else
      pos1 = System.GetEntityByName(self.Group.vectorTeammates[i]):GetWorldPos()
    end
  end
  if #self.Group.vectorTeammates <= 2 then
    AI.SetRefPointPosition(self.id, leadPos)
  else
    -- local pos1 = System.GetEntityByName(vectorTeammates[1]:GetWorldPos())
    -- local pos2 = System.GetEntityByName(vectorTeammates[2]:GetWorldPos())
    if (DistanceVectors(self:GetWorldPos(), leadPos) > 5) then
      AI.SetRefPointPosition(self.id, leadPos)
    else
      AI.SetRefPointPosition(self.id, pos1)
    end
  end
end

function CT_x:ReleaseHostage()
  local currentEnt = System.GetEntityByName(sCurrentHostage)
  local entId = System.GetEntityIdByName(sCurrentHostage)
  currentEnt.Properties.bRescued = true
  self.Properties.iHostageRescued = self.Properties.iHostageRescued + 1
  currentEnt.Properties.sRescuerName = self:GetName()
  AI.Signal(0, -1, "WalkWithMe", entId)
end

function CT_x:OnEnemySeen()
  --AIBase.OnEnemySeen(self);
  local attentionTarget = AI.GetAttentionTargetEntity(self.id);
  local targetFaction = attentionTarget.Properties.esFaction
  self.Properties.sCurrentEnemy = attentionTarget:GetName()
  if (targetFaction == "Friend" or targetFaction == "Medics" or targetFaction == "Hostage" or targetFaction == "Players") then
	Log(tostring("Should not Kill"))
	AI.Signal(SIGNALFILTER_SENDER, 1, "OnFriendSeen", self.id)
  else
	Log(tostring(attentionTarget.Properties.esFaction))
	Log(tostring("Should Kill"))
	AI.Signal(SIGNALFILTER_SENDER, 1, "OnHostileSeen", self.id)
  end
end

-- Function to let the teammates throw nades for damage and then go for open combat
function CT_x:OnSuspectedSoundHeard()
  
end


function CT_x:FindIfEnemyDead()
  if(self.Properties.sCurrentEnemy ~= "") then
    local enemy = System.GetEntityByName(self.Properties.sCurrentEnemy)
    -- Log(self.Properties.sCurrentEnemy)
    if (enemy:IsDead()) then
      self.Properties.sCurrentEnemy = ""
      AI.Signal(0, -1, "GoTo_GoToHostage", self.id)
    end
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
  -- local locData = CryEngine.LoadXML("Scripts/Entities/AI/Characters/LocationsDef.xml", "D:/Amazon/Lumberyard/dev/GameSDK/Scripts/Entities/AI/Characters/LocationsData.xml")
  Log(tostring("finding hostage location"))
  -- if(hostageNumber == 4) then
	-- AI.Signal(SIGNALFILTER_SENDER, 1, "AllHostagesRescued", self.id)
	-- return
  -- end
  -- Log(tostring("FindingHostageDude"));
  -- Log(tostring(hostageNumber));
  -- dummy = dummyPlayer..tostring(hostageNumber);
  -- Log(tostring(dummy));
  -- AI.SetRefPointPosition(System.GetEntityIdByName('CounterTerrorist1'), System.GetEntityByName(dummy):GetWorldPos())
  -- --Log(tostring("Incremented Value"));
  -- --Log(tostring(hostageNumber));
  -- AI.Signal(SIGNALFILTER_SENDER, 1, "OnFindingHostage", self.id)
  -- hostageNumber = hostageNumber + 1;
end

function CT_x:CheckAIHealth()
	if (self:IsDead()) then
		Log(tostring("If Part"));
		Log(tostring(self:IsDead()));
		AI.Signal(SIGNALFILTER_SENDER, 1, "GoToGameOver", self.id)
	else
    -- Log(tostring("Not Dead yet..."))
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

----------------------
-- FlowEvents
----------------------
function CT_x:On_Position(sender, params)
	--Log(tostring(params));
  self.player_pos[#self.player_pos+1] = {pos = params };
end

function CT_x:On_Health(sender, params)
  --Log(tostring(params));
  local CtHealth = self.actor:GetHealth()
  -- Log(tostring(CtHealth))
  self.player_health[#self.player_health+1] = { h = CtHealth };
end

function CT_x:On_Dead(sender, params)
  Log("From flowgraph " .. tostring(params))
  CryAction.SaveXML(self.xml_def_path, self.xml_data_path, self)
end

CounterTerrorist.FlowEvents = {
  Inputs = {
    Position = { CT_x.On_Position, "Vec3" },
	  Health = {CT_x.On_Health, "int"},
    Dead = {CT_x.On_Dead, "int"}
  },
  Outputs = {},
}
