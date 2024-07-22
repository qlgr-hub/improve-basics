-- variable = 1
-- print(variable)
-- print(type(variable))

-- variable = "1"
-- print(variable)
-- print(type(variable))

-- variable = variable + 1
-- print(variable)
-- print(type(variable))

-- variable = "name"
-- variable = variable + 1

-- local variable = "name"

-- function ChangeName()
--     local variable = "age"
-- end

-- print(variable)
-- ChangeName()
-- print(variable)

-- function GetValue()
--     local variable = "age"
-- end

-- local value = GetValue()
-- print(value)
-- value = value + 1

-- function GetValue()
--     return "age"
-- end

-- local value = GetValue()
-- print(value)

-- function GetValues()
--     return "name", "age"
-- end

-- local name, age = GetValues()
-- print(name)
-- print(age)


-- newTable = {}

-- newTable["value"] = 3.14

-- newTable[3.14] = "value"

-- keyTable = {}
-- newTable[keyTable] = "VALID"

-- print(newTable["value"])
-- print(newTable[3.14])
-- print(newTable[keyTable])

-- newTable = {}

-- newTable["nilValue1"] = 1
-- newTable["nilValue2"] = 2

-- print(newTable["nilValue1"])
-- print(newTable["nilValue2"])

-- newTable["nilValue1"] = nil

-- print(newTable["nilValue1"])
-- print(newTable["nilValue2"])

-- newTable = {}

-- table.insert(newTable, "first")
-- table.insert(newTable, "second")
-- table.insert(newTable, "third")
-- print(newTable[2])

-- print(newTable[2])

-- table.insert(newTable, 2, "fourth")

-- print(newTable[2])

-- table.remove(newTable, 1)

-- print(newTable[1])
-- print(newTable[2])
-- print(newTable[3])
-- print(newTable[4])

-- newTable = {}

-- table.insert(newTable, "first")
-- table.insert(newTable, "second")
-- table.insert(newTable, "third")

-- print(#newTable)

-- newTable[9] = "fourth"
-- print(newTable[9])

-- print(#newTable)

-- value1 = 1
-- value2 = 2

-- if value1 == value2 then
--     print("Are equal")
-- elseif value1 ~= value2 then
--     print("Not equal")
-- else
--     print("Should't be here!")
-- end

-- value1 = 2
-- while value1 do
--     print("We got here! " .. value1)
--     value1 = value1 - 1
--     if value1 == -1 then
--         value1 = nil
--     end
-- end

-- value1 = 2
-- while value1 do
--     print("We got here! " .. value1)
--     value1 = value1 - 1
--     if value1 == -1 then
--         break
--     end
-- end

-- value1 = 2
-- while value1>= 0 do
--     print("We got here! " .. value1)
--     value1 = value1 - 1
-- end

-- for i=0, 10, 2 do
--     print(i)
-- end

newTable = {}
newTable["first"] = 1
newTable["second"] = 2
newTable["third"] = 3

for key, value in pairs(newTable) do
    print(key .. ": " .. value)
end

newTable = {}

table.insert(newTable, "first")
table.insert(newTable, "second")
table.insert(newTable, "third")

for index, value in ipairs(newTable) do
    print(index .. ": " .. value)
end
