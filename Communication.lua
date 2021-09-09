

--Comm by id
bCommRet,strReadData = VpScript_ReadDataByCommId(2,5.0)
if bCommRet == true then 
    VpScript_MessageBox(strReadData)
    VpScript_SendDataByCommId(2,'hi China')
else
    VpScript_MessageBox('Read Data Empty')
end

--[[
--Comm by name
bCommRet,strReadData = VpScript_ReadDataByCommName('S2',5.0)
if bCommRet == true then 
    VpScript_MessageBox(strReadData)
    VpScript_SendDataByCommName('S2','hi China')
else
    VpScript_MessageBox('Read Data Empty')
end
--]]