----------------------------------------------------------------------
-- File    : neural_network.lua
-- Created : 26-Apr-2015
-- By      : Alexandre Trilla <alex@atrilla.net>
--
-- AIMA - Artificial Intelligence, A Maker's Approach
--
-- Copyright (C) 2015 A.I. Maker
----------------------------------------------------------------------
--
-- This file is part of AIMA.
--
-- AIMA is free software: you can redistribute it and/or modify it
-- under the terms of the MIT/X11 License as published by the
-- Massachusetts Institute of Technology. See the MIT/X11 License
-- for more details.
--
-- You should have received a copy of the MIT/X11 License along with
-- this source code distribution of AIMA (see the COPYING file in the
-- root directory). If not, see
-- <http://www.opensource.org/licenses/mit-license>.
----------------------------------------------------------------------

-- Artificial neural network class (multilayer perceptron model).
--
-- Activation function is assumed to be sigmoid.
-- Tikhonov regularisation is set to 1.
Script.ReloadScript( "SCRIPTS/Entities/AI/Characters/gradient_ascent.lua")

ann = {}


-- PRE:
-- IN - size of input layer (number).
-- HID - size of hidden layer (number).
-- OUT - size of output layer (number).
--
-- POST:
-- Returns an instance of an ANN (table).

function ann:new(IN, HID, OUT)
  local newann = {Lin = IN, Lhid = HID, Lout = OUT}
  self.__index = self
  setmetatable(newann, self)
  newann:initw()
  return newann
end


-- POST:
-- Initialises the model (the thetas).

function ann:initw()
  local epsilonIN = math.sqrt(6) / math.sqrt(self.Lin + self.Lhid)
  local epsilonOUT = math.sqrt(6) / math.sqrt(self.Lhid + self.Lout)
  --
  local function initmat(din, dout, value)
    math.randomseed(os.time())
    local mat = {}
    for i = 1, dout do
      local aux = {}
      for j = 1, din do
        table.insert(aux, ((math.random() - 0.5) / 0.5 ) * value)
      end
      table.insert(mat, aux)
    end
    return mat
  end
  --
  self.thetain = initmat(self.Lin + 1, self.Lhid, epsilonIN)
  self.thetaout = initmat(self.Lhid + 1, self.Lout, epsilonOUT)
end


-- PRE:
-- input - feat [1,N] vector (table).
--
-- POST:
-- Returns output [1,K] vector (table).
function ann:predict(input)
  local function matprod(m1, m2)
    local result = {}
    -- init
    for i = 1, #m1 do
      local row = {}
      for j = 1, #m2[1] do
        table.insert(row, 0)
      end
      table.insert(result, row)
    end
    -- multiply
    for i = 1, #m1 do
      for j = 1, #m2[1] do
        local prod = 0
        for k = 1, #m1[1] do
          prod = prod + m1[i][k] * m2[k][j]
        end
        result[i][j] = prod
      end
    end
    return result
  end
  --
  local function sigmoid(x)
    local y = 1 / (1 + math.exp(-x))
    return y
  end
  -- input must be a column [N,1] vector (table).
  -- step 1
  local aIN = {{1}}
  for i = 1, #input do
    table.insert(aIN, {input[i]})
  end
  --print(tostring("In Predict"))
  --print_r(aIN)
  -- step 2
  local zHID = matprod(self.thetain, aIN)
  local aHID = {{1}}
  for i = 1, #zHID do
    table.insert(aHID, {sigmoid(zHID[i][1])})
  end
  -- step 3
  local azOUT = matprod(self.thetaout, aHID)
  for i = 1, #azOUT do
    azOUT[i][1] = sigmoid(azOUT[i][1])
  end
  local flatOUT = {}
  for i = 1, #azOUT do
    table.insert(flatOUT, azOUT[i][1])
  end
  return flatOUT
end



ann_weapon=
{
  Lhid = 3,
  Lin = 9,
  thetain =  {
                 [1] =  {
                          [1] = -0.37027789901415,
                          [2] = -0.090094664180094,
                          [3] = 0.4688787116792,
                          [4] = -0.13944314290846,
                          [5] = -0.54660463930753,
                          [6] = -0.13099701374425,
                          [7] = -0.171197955869,
                          [8] = 0.16064259496818,
                          [9] = 0.48696289678631,
                          [10] = 0.199429544904
                        },
                 [2] =  {
                          [1] = -0.034490687192959,
                          [2] = 0.44012694000331,
                          [3] = -0.27159784837506,
                          [4] = -0.34027719223241,
                          [5] = 0.35749823364549,
                          [6] = 0.39335012069529,
                          [7] = 0.65869470129471,
                          [8] = 0.14954146588005,
                          [9] = 0.10311599423872,
                          [10] = -0.58048908086303,
                        },
                 [3] = {
                          [1] = 0.22969945693819,
                          [2] = -0.77985913362396,
                          [3] = 0.39601318255061,
                          [4] = -0.37978890251447,
                          [5] = 0.53621361317242,
                          [6] = -0.58652848135003,
                          [7] = -0.46431416125007,
                          [8] = 0.64873618981549,
                          [9] = -0.069968603345083,
                          [10] = 0.33423617922043
                        }
               },
  Lout = 4,
  thetaout = {
                  [1] =  {
                           [1] = 0.44068017663487,
                           [2] = -0.13066521299126,
                           [3] = 0.51676913458272,
                           [4] = -0.26046093487424
                         },
                  [2] =  {
                           [1] = -1.6651235169294,
                           [2] = -0.22661359333928,
                           [3] = -0.2274152908695,
                           [4] = 0.16732897579806
                         },
                  [3] = {
                           [1] = -0.77169063255772,
                           [2] = 0.14488705050435,
                           [3] = -0.064780496664131,
                           [4] = 0.54656324802407
                         },
                  [4] =  {
                           [1] = -1.5967763077659,
                           [2] = -0.50348457911334,
                           [3] = 0.45283663288927,
                           [4] = 0.47049266820813
                         }
                }
}


ann_velocity= {
  Lhid = 3,
  Lin = 9,
  thetain = {
                 [1] =  {
                          [1] = -0.35613345810087,
                          [2] = -0.23667156946413,
                          [3] = 0.33380805291522,
                          [4] = 0.37298930048568,
                          [5] = 0.025343364266012,
                          [6] = 0.18712502056148,
                          [7] = -0.26090558450883,
                          [8] = -0.07404192361961,
                          [9] = 0.19117285099504,
                          [10] = -0.15543868394729
                        },
                 [2] =  {
                          [1] = -0.69064420310194,
                          [2] = 0.4817680272428,
                          [3] = 0.39201081669221,
                          [4] = 0.18706458423963,
                          [5] = 0.011332150553481,
                          [6] = -0.15633514496631,
                          [7] = -0.17846696923624,
                          [8] = 0.044548923605309,
                          [9] = -0.13106107456306,
                          [10] = -0.34729387186899
                        },
                 [3] =  {
                          [1] = 0.064882211520738,
                          [2] = 0.19879110343967,
                          [3] = -0.28491117116917,
                          [4] = 0.097370804992714,
                          [5] = 0.21957023161329,
                          [6] = 0.27520680203216,
                          [7] = -0.27006306455173,
                          [8] = 0.20951560877366,
                          [9] = 0.27950481660291,
                          [10] = 0.27285927966121
                        }
               },
  Lout = 2,
  thetaout =  {
                  [1] = {
                           [1] = -0.53129608697095,
                           [2] = -0.21898225415711,
                           [3] = 0.53422619680071,
                           [4] = 0.60452584304881
                         },
                  [2] =  {
                           [1] = 0.022808933482042,
                           [2] = 0.14216299208923,
                           [3] = -0.41163764655209,
                           [4] = -0.14247783866582
                         }
                }
}




function ann:predict_test(input)
  local function matprod(m1, m2)
    local result = {}
    -- init
    for i = 1, #m1 do
      local row = {}
      for j = 1, #m2[1] do
        table.insert(row, 0)
      end
      table.insert(result, row)
    end
    -- multiply
    for i = 1, #m1 do
      for j = 1, #m2[1] do
        local prod = 0
        for k = 1, #m1[1] do
          prod = prod + m1[i][k] * m2[k][j]
        end
        result[i][j] = prod
      end
    end
    return result
  end
  --
  local function sigmoid(x)
    local y = 1 / (1 + math.exp(-x))
    return y
  end
  -- input must be a column [N,1] vector (table).
  -- step 1
  local aIN = {{1}}
  for i = 1, #input do
    table.insert(aIN, {input[i]})
  end
  --print(tostring("In Predict"))
  --print_r(aIN)
  -- step 2
  local zHID = matprod(self.thetain, aIN)
  local aHID = {{1}}
  for i = 1, #zHID do
    table.insert(aHID, {sigmoid(zHID[i][1])})
  end
  -- step 3
  local azOUT = matprod(self.thetaout, aHID)
  for i = 1, #azOUT do
    azOUT[i][1] = sigmoid(azOUT[i][1])
  end
  local flatOUT = {}
  for i = 1, #azOUT do
    table.insert(flatOUT, azOUT[i][1])
  end
  return flatOUT
end

-- PRE:
-- input - feat [1,N] vector (table).
--
-- POST:
-- Returns output [1,K] vector (table).
function ann:predict_weapon(input)
  local function matprod(m1, m2)
    local result = {}
    -- init
    for i = 1, #m1 do
      local row = {}
      for j = 1, #m2[1] do
        table.insert(row, 0)
      end
      table.insert(result, row)
    end
    -- multiply
    for i = 1, #m1 do
      for j = 1, #m2[1] do
        local prod = 0
        for k = 1, #m1[1] do
          prod = prod + m1[i][k] * m2[k][j]
        end
        result[i][j] = prod
      end
    end
    return result
  end
  --
  local function sigmoid(x)
    local y = 1 / (1 + math.exp(-x))
    return y
  end
  -- input must be a column [N,1] vector (table).
  -- step 1
  local aIN = {{1}}
  for i = 1, #input do
    table.insert(aIN, {input[i]})
  end
  --print(tostring("In Predict"))
  --print_r(aIN)
  -- step 2
  local zHID = matprod(ann_weapon.thetain, aIN)
  local aHID = {{1}}
  for i = 1, #zHID do
    table.insert(aHID, {sigmoid(zHID[i][1])})
  end
  -- step 3
  local azOUT = matprod(ann_weapon.thetaout, aHID)
  for i = 1, #azOUT do
    azOUT[i][1] = sigmoid(azOUT[i][1])
  end
  local flatOUT = {}
  for i = 1, #azOUT do
    table.insert(flatOUT, azOUT[i][1])
  end
  return flatOUT
end


function ann:predict_velocity(input)
  local function matprod(m1, m2)
    local result = {}
    -- init
    for i = 1, #m1 do
      local row = {}
      for j = 1, #m2[1] do
        table.insert(row, 0)
      end
      table.insert(result, row)
    end
    -- multiply
    for i = 1, #m1 do
      for j = 1, #m2[1] do
        local prod = 0
        for k = 1, #m1[1] do
          prod = prod + m1[i][k] * m2[k][j]
        end
        result[i][j] = prod
      end
    end
    return result
  end
  --
  local function sigmoid(x)
    local y = 1 / (1 + math.exp(-x))
    return y
  end
  -- input must be a column [N,1] vector (table).
  -- step 1
  local aIN = {{1}}
  for i = 1, #input do
    table.insert(aIN, {input[i]})
  end
  --print(tostring("In Predict"))
  --print_r(aIN)
  -- step 2
  local zHID = matprod(ann_velocity.thetain, aIN)
  local aHID = {{1}}
  for i = 1, #zHID do
    table.insert(aHID, {sigmoid(zHID[i][1])})
  end
  -- step 3
  local azOUT = matprod(ann_velocity.thetaout, aHID)
  for i = 1, #azOUT do
    azOUT[i][1] = sigmoid(azOUT[i][1])
  end
  local flatOUT = {}
  for i = 1, #azOUT do
    table.insert(flatOUT, azOUT[i][1])
  end
  return flatOUT
end




-- PRE:
-- feat - list of example feature vectors (table).
-- targ - list of target value vectors (table).
--
-- POST:
-- Fits the neural network params to the given data.
-- Returns training error (number).

function ann:train(feat, targ)
  --require("gradient_ascent")

  local function saveThetas()
    local thetas = {}
    -- theta in
    for i = 1, self.Lhid do
      for j = 1, (self.Lin + 1) do
        table.insert(thetas, self.thetain[i][j])
      end
    end
    -- theta out
    for i = 1, self.Lout do
      for j = 1, (self.Lhid + 1) do
        table.insert(thetas, self.thetaout[i][j])
      end
    end
    return thetas
  end
  local function loadThetas(thetas)
    -- theta in
    local index = 1
    for i = 1, self.Lhid do
      for j = 1, (self.Lin + 1) do
        self.thetain[i][j] = thetas[index]
        index = index + 1
      end
    end
    -- theta out
    for i = 1, self.Lout do
      for j = 1, (self.Lhid + 1) do
        self.thetaout[i][j] = thetas[index]
        index = index + 1
      end
    end
  end
  local function cost(thetas)
    local sqerr, pr
    local J = 0
    loadThetas(thetas)
    for m = 1, #feat do
      pr = self:predict(feat[m])
      sqerr = 0
      for k = 1, #pr do
        sqerr = sqerr + math.pow(targ[m][k] - pr[k], 2)
      end
      J = J + sqerr
    end
    J = J / #feat
    -- Regularisation
    local R = 0
    for i = 1, #self.thetain do
      for j = 2, #self.thetain[1] do
        R = R + math.pow(self.thetain[i][j], 2)
      end
    end
    for i = 1, #self.thetaout do
      for j = 2, #self.thetaout[1] do
        R = R + math.pow(self.thetaout[i][j], 2)
      end
    end
    R = R * (0.01 / (self.Lin*self.Lhid + self.Lhid*self.Lout))
    return -(J + R)
  end
  -- flatten thetas
  local flatTheta = saveThetas()
  gradient_ascent(cost, flatTheta, 1)
  -- deflat theta, restore model
  trerr = cost(flatTheta)
  loadThetas(flatTheta)
  -- return training err
  return trerr
end


function print_r ( t )  
    local print_r_cache={}
    local function sub_print_r(t,indent)
        if (print_r_cache[tostring(t)]) then
            print(indent.."*"..tostring(t))
        else
            print_r_cache[tostring(t)]=true
            if (type(t)=="table") then
                for pos,val in pairs(t) do
                    if (type(val)=="table") then
                        print(indent.."["..pos.."] => "..tostring(t).." {")
                        sub_print_r(val,indent..string.rep(" ",string.len(pos)+8))
                        print(indent..string.rep(" ",string.len(pos)+6).."}")
                    elseif (type(val)=="string") then
                        print(indent.."["..pos..'] => "'..val..'"')
                    else
                        print(indent.."["..pos.."] => "..tostring(val))
                    end
                end
            else
                print(indent..tostring(t))
            end
        end
    end
    if (type(t)=="table") then
        print(tostring(t).." {")
        sub_print_r(t,"  ")
        print("}")
    else
        sub_print_r(t,"  ")
    end
    print()
end

