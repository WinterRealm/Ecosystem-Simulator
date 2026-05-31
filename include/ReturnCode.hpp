#pragma once
enum class ReturnCode:int{
	//前缀0表示正常，1表示不正常 
	OK=0x00000000,
	QUIT=0x00000001,
	FILE_NOT_FOUND=0x10000001,
	FAILED=0x10000010
};
constexpr int rcToInt(ReturnCode rc){
	return static_cast<int>(rc);
}
