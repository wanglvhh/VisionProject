--[[
--Int全局变量接口
bRunRet,nValue = VpScript_GetIntGobalViarentById(1)
if bRunRet == true then
    strMessage = string.format('IntValue = %d', nValue)
    VpScript_MessageBox(strMessage)
else
    VpScript_MessageBox('IntValue GetFail')
end

VpScript_SetIntGobalViarentById(1,123456)

bRunRet2,nValue2 = VpScript_GetIntGobalViarentByName('nCount')
if bRunRet2 == true then
    strMessage2 = string.format('IntValue = %d', nValue2)
    VpScript_MessageBox(strMessage2)
else
    VpScript_MessageBox('IntValue GetFail')
end

VpScript_SetIntGobalViarentByName('nCount',1031)

bRunRet3,nValue3 = VpScript_GetIntGobalViarentByName('nCount')
if bRunRet3 == true then
    strMessage3 = string.format('IntValue = %d', nValue3)
    VpScript_MessageBox(strMessage3)
else
    VpScript_MessageBox('IntValue GetFail')
end

--]]

--[[
--Double全局变量接口
bRunRet,dbValue = VpScript_GetDoubleGobalViarentById(2)
if bRunRet == true then
    strMessage = string.format('DoubleValue = %.5f', dbValue)
    VpScript_MessageBox(strMessage)
else
    VpScript_MessageBox('DoubleValue GetFail')
end

VpScript_SetDoubleGobalViarentById(2,0.12)

bRunRet2,dbValue2 = VpScript_GetDoubleGobalViarentByName('dbOffset')
if bRunRet2 == true then
    strMessage2 = string.format('DoubleValue =  %.5f', dbValue2)
    VpScript_MessageBox(strMessage2)
else
    VpScript_MessageBox('DoubleValue GetFail')
end

VpScript_SetDoubleGobalViarentByName('dbOffset',-10.31)

bRunRet3,dbValue3 = VpScript_GetDoubleGobalViarentByName('dbOffset')
if bRunRet3 == true then
    strMessage3 = string.format('DoubleValue =  %.5f', dbValue3)
    VpScript_MessageBox(strMessage3)
else
    VpScript_MessageBox('DoubleValue GetFail')
end

--]]


--[[
--String全局变量接口
bRunRet,strValue = VpScript_GetStringGobalViarentById(3)
if bRunRet == true then 
    VpScript_MessageBox(strValue)
else
    VpScript_MessageBox('StringValue GetFail')
end

VpScript_SetStringGobalViarentById(3,'T{Glue,1}E')

bRunRet2,strValue2 = VpScript_GetStringGobalViarentByName('strTouchValue')
if bRunRet2 == true then 
    VpScript_MessageBox(strValue2)
else
    VpScript_MessageBox('StringValue GetFail')
end

VpScript_SetStringGobalViarentByName('strTouchValue','T{Glue,2}E')

bRunRet3,strValue3 = VpScript_GetStringGobalViarentByName('strTouchValue')
if bRunRet3 == true then 
    VpScript_MessageBox(strValue3)
else
    VpScript_MessageBox('StringValue GetFail')
end

--]]

--[[
--bool全局变量接口
bRunRet,bValue = VpScript_GetBoolGobalViarentById(4)
if bRunRet == true then  
    VpScript_MessageBox(tostring(bValue))
else
    VpScript_MessageBox('BoolValue GetFail')
end

VpScript_SetBoolGobalViarentById(4,true)

bRunRet2,bValue2 = VpScript_GetBoolGobalViarentByName('bRunStatus')
if bRunRet2 == true then 
    VpScript_MessageBox(tostring(bValue2))
else
    VpScript_MessageBox('BoolValue GetFail')
end

VpScript_SetBoolGobalViarentByName('bRunStatus',false)

bRunRet3,bValue3 = VpScript_GetBoolGobalViarentByName('bRunStatus')
if bRunRet3 == true then 
    VpScript_MessageBox(tostring(bValue3))
else
    VpScript_MessageBox('BoolValue GetFail')
end
--]]


--[[
--Matrix全局变量接口
bRunRet,strValue = VpScript_GetMatrixGobalViarentById(0)
if bRunRet == true then  
    VpScript_MessageBox(strValue)
else
    VpScript_MessageBox('MatrixValue GetFail')
end

VpScript_SetMatrixGobalViarentById(0,'0.1,-0.1,-0.1,2.0,2.0,0.2')

bRunRet2,strValue2 = VpScript_GetMatrixGobalViarentByName('hPixelToMotion')
if bRunRet2 == true then 
    VpScript_MessageBox(strValue2)
else
    VpScript_MessageBox('MatrixValue GetFail')
end

VpScript_SetMatrixGobalViarentByName('hPixelToMotion','0.3,-0.3,-0.3,2.0,2.0,0.2')

bRunRet3,strValue3 = VpScript_GetMatrixGobalViarentByName('hPixelToMotion')
if bRunRet3 == true then 
    VpScript_MessageBox(strValue3)
else
    VpScript_MessageBox('MatrixValue GetFail')
end
--]]

--[[
--2DPos全局变量接口
bRunRet,strValue = VpScript_Get2DPosGobalViarentById(5)
if bRunRet == true then  
    VpScript_MessageBox(strValue)
else
    VpScript_MessageBox('2DPosValue GetFail')
end

VpScript_Set2DPosGobalViarentById(5,'0.1,0.1')

bRunRet2,strValue2 = VpScript_Get2DPosGobalViarentByName('point2d')
if bRunRet2 == true then 
    VpScript_MessageBox(strValue2)
else
    VpScript_MessageBox('2DPosValue GetFail')
end

VpScript_Set2DPosGobalViarentByName('point2d','0.3,-0.3')

bRunRet3,strValue3 = VpScript_Get2DPosGobalViarentByName('point2d')
if bRunRet3 == true then 
    VpScript_MessageBox(strValue3)
else
    VpScript_MessageBox('2DPosValue GetFail')
end
--]]

--[[
--3DPos全局变量接口
bRunRet,strValue = VpScript_Get3DPosGobalViarentById(6)
if bRunRet == true then  
    VpScript_MessageBox(strValue)
else
    VpScript_MessageBox('3DPosValue GetFail')
end

VpScript_Set3DPosGobalViarentById(6,'0.1,0.1,0.1')

bRunRet2,strValue2 = VpScript_Get3DPosGobalViarentByName('point3D')
if bRunRet2 == true then 
    VpScript_MessageBox(strValue2)
else
    VpScript_MessageBox('3DPosValue GetFail')
end

VpScript_Set3DPosGobalViarentByName('point3D','0.3,0.3,0.3')

bRunRet3,strValue3 = VpScript_Get3DPosGobalViarentByName('point3D')
if bRunRet3 == true then 
    VpScript_MessageBox(strValue3)
else
    VpScript_MessageBox('3DPosValue GetFail')
end
--]]