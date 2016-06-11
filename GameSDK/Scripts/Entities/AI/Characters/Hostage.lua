----------------------------------------------------------------------------------------------------
--
-- All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
-- its licensors.
--
-- For complete copyright and license terms please see the LICENSE at the root of this
-- distribution (the "License"). All use of this software is governed by the License,
-- or, if provided, by the license below or the license accompanying this file. Do not
-- remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--
-- Original file Copyright Crytek GMBH or its affiliates, used under license.
--
----------------------------------------------------------------------------------------------------
Script.ReloadScript( "SCRIPTS/Entities/AI/Characters/Human_x.lua")
Script.ReloadScript( "SCRIPTS/Entities/actor/BasicActor.lua")
Script.ReloadScript( "SCRIPTS/Entities/AI/Shared/BasicAI.lua")

Hostage_x = {
  Properties = {
    bAdditionalBool = false,
    bRescued = false,
    vectorAIPoint = {x=0,y=0,z=0},
    sRescuerName = "",
  }
}

-- function Hostage_x:OnEnemySeen()
--   AIBase.OnEnemySeen(self);
--   Log("Hostage seeing enemy")
--
--   local attentionTarget = AI.GetAttentionTargetEntity(self.id);
--
--   if (attentionTarget.Properties.esFaction == "Players" or attentionTarget.Properties.esFaction == "Friend") then
--     if (bRescued == true) then
--       AI.SetRefPointPosition(self.id, attentionTarget:GetWorldPos())
--       AI.Signal(SIGNALFILTER_SENDER, 1, "WalkWithMe", self.id)
--     end
--   end
-- end

-- function Hostage_x:OnEnemySeen()
--   if self.Properties.bRescued == false then
--     local attentionTarget = AI.GetAttentionTargetEntity(self.id)
--     if attentionTarget.Properties.esFaction == "Players" then
--       local CT = System.GetEntitiesByClass("CounterTerrorist")
--       if #CT > 0 then
--         for i = 1, #CT do
--           CT[i].Properties.iHostageRescued = CT[i].Properties.iHostageRescued + 1
--           Log("From hostage incrementing rescued " .. tostring(CT[i].Properties.iHostageRescued))
--         end
--         self.Properties.bRescued = true
--         self.Properties.sRescuerName = attentionTarget:GetName()
--         AI.Signal(0, -1, "WalkWithPlayer", self.id)
--       end
--     end
--   end
-- end

function Hostage_x:GetRescuerPos()
  -- Log("Getting the position of leader")
  local CTs = System.GetEntitiesByClass("CounterTerrorist")
  if #CTs > 0 then
    for i = 1, #CTs do
      if CTs[i].Properties.bGroupLeader == true then
        -- Log(tostring(CTs[i]:GetName()))
        AI.SetRefPointPosition(self.id, CTs[i]:GetWorldPos())
      end
    end
    -- local RescuerPosition = System.GetEntityByName(self.Properties.sRescuerName):GetWorldPos()
    -- AI.SetRefPointPosition(self.id, RescuerPosition)
  else
    AI.Signal(0, -1, "GoTo_Idle", self.id)
  end
end

mergef(Hostage_x,Human_x,1)

CreateActor(Hostage_x)
Hostage=CreateAI(Hostage_x)

Script.ReloadScript( "SCRIPTS/AI/Assignments.lua")
InjectAssignmentFunctionality(Hostage)
AddDefendAreaAssignment(Hostage)
AddHoldPositionAssignment(Hostage)
AddCombatMoveAssignment(Hostage)
AddPsychoCombatAllowedAssignment(Hostage)

Hostage:Expose()
