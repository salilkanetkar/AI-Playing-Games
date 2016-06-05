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
    if #self.Group.vectorTeammates-1 > 0 then
      for i = 1, #self.Group.vectorTeammates do
        local entId = System.GetEntityIdByName(self.Group.vectorTeammates[i])
        AI.Signal(0, -1, "GoTo_GameWon", entId)
      end
    end
    Log(self:GetName() .. tostring(" All hostages rescued"))
  else
    Log(self:GetName() .. tostring(" Hostage not rescued yet"))
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
  -- local team = System.GetEntitiesByClass("CounterTerrorist")
  -- if (next(team) ~= nil) then
  --   local numTeam = table.getn(team)
  --   for i = 1, numTeam do
  --     if (team[i]:GetName() ~= self:GetName()) then
  --       self.Group.vectorTeammates[#self.Group.vectorTeammates + 1] = team[i]:GetName()
  --     end
  --   end
  -- end
  self.Group.vectorTeammates[#self.Group.vectorTeammates+1] = self:GetName()
  Log(tostring(#self.Group.vectorTeammates))

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
    Log(self:GetName() .. " I'm leader ")
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
    AI.Signal(0, -1, "GoTo_FollowLeader", self.id)
    Log ("I'm not leader " .. self:GetName())
  end
end

-- If the counter terrorist entity is not a leader, it will realize that it has to follow
-- the leader and the RefPoint is set to be the leader.
function CT_x:FindFormationPos()
  local lead = ""
  for i=1, #self.Group.vectorTeammates do
    local ent = System.GetEntityByName(self.Group.vectorTeammates[i])
    if ent.Properties.bGroupLeader == true then
      Log ("My leader is " .. ent:GetName())
      lead = ent:GetName()
    end
  end
  -- Log(self:GetName() .. " is finding formation leader and got " .. lead)
  local leadPos = System.GetEntityByName(lead):GetWorldPos()
  AI.SetRefPointPosition(self.id, leadPos)
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
  for i = 1, #self.Group.vectorTeammates do
    if self.Group.vectorTeammates[i] ~= self:GetName() then
      local ent = System.GetEntityIdByName(self.Group.vectorTeammates[i])
      System.GetEntityByName(self.Group.vectorTeammates[i]).Properties.sCurrentEnemy = attentionTarget:GetName()
      AI.SetAttentiontarget(ent, System.GetEntityIdByName(AI.GetAttentionTargetOf(self.id)))
      AI.Signal(0, -1, "OnHostileSeen", ent)
    end
  end
end


function CT_x:OnEnemyDamage(sender, data)
  AI.SetAttentiontarget(self.id, data.id)
  Log(AI.GetAttentionTargetEntity(self.id):GetName())
  AI.Signal(0, -1, "OnHostileSeen", self.id)
  Log("Getting attacked")
  if #self.Group.vectorTeammates > 0 then
    for i = 1, #self.Group.vectorTeammates do
      AI.SetAttentiontarget(System.GetEntityIdByName(self.Group.vectorTeammates[i]), data.id)
      AI.Signal(0, -1, "OnHostileSeen", System.GetEntityIdByName(self.Group.vectorTeammates[i]))
    end
  end
end

function CT_x:CheckToNade()
  if self.Properties.bGroupLeader == false then
    local enemiesList = System.GetEntitiesByClass("Human")
    local enemyNearCount = 0
    Log("Hello... checking whether to nade")
    if #enemiesList > 0 then
      for i = 1, #enemiesList do
        local dist = DistanceVectors(self:GetWorldPos(), enemiesList[i]:GetWorldPos())
        if dist <= 20 then
          enemyNearCount = enemyNearCount + 1
        end
      end
    end
    -- if enemyNearCount > (#self.Group.vectorTeammates + 1) then
    --   local prob = math.random()
    --   if prob > 0.5 then
        AI.ThrowGrenade(entity.id, AI_RGT_FRAG_GRENADE, AI_REG_ATTENTIONTARGET)
      -- end
    -- end
  end
end


function CT_x:FindIfEnemyDead()
  local enemyTarget = AI.GetAttentionTargetEntity(self.id)
  if enemyTarget ~= nil then
    if enemyTarget:IsDead() == true then
      AI.Signal(0, -1, "GoTo_GoToHostage", self.id)
    end
  else
    AI.Signal(0, -1, "GoTo_GoToHostage", self.id)
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
  if (self:IsDead()) then
    local myIndex = 0
    local numTeam = #self.Group.vectorTeammates
    for i = 1,  numTeam do
      if self.Group.vectorTeammates[i] == self:GetName() then
        myIndex = i
      end
    end
    table.remove(self.Group.vectorTeammates, myIndex)
    numTeam = numTeam - 1
    if (self.Properties.bGroupLeader == true) then
      self.Properties.bGroupLeader = false
      if (numTeam > 0) then
        local randEnt = math.random(1, numTeam)
        local ent = System.GetEntityByName(self.Group.vectorTeammates[randEnt])
        ent.Properties.bGroupLeader = true
        Log("New Leader is " .. self.Group.vectorTeammates[randEnt])
        Log(tostring(ent.Properties.bGroupLeader) .. " I'm the leader ")
        Log(tostring(#self.Group.vectorTeammates) .. " Size of the group")
      end
    end
    Log("From flowgraph " .. tostring(params))
    CryAction.SaveXML(self.xml_def_path, self.xml_data_path, self)
  else
    local mytarget = AI.GetAttentionTargetEntity(self.id)
    AI.SetAttentiontarget(self.id, mytarget.id)
    AI.Signal(0, -1, "OnHostileSeen", self.id)
  end
end

CounterTerrorist.FlowEvents = {
  Inputs = {
    Position = { CT_x.On_Position, "Vec3" },
	  Health = {CT_x.On_Health, "int"},
    Dead = {CT_x.On_Dead, "int"}
  },
  Outputs = {},
}
