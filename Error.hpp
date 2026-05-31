#pragma once
#include <cstddef>
namespace ES{
		enum ErrorCode{
			RunTimeError=0,//通用运行时
			NotFound=1,//未找到
			MemoryError=2,//内存错误
			IOError=3,//输入输出、磁盘存储错误
			SystemError=4,//系统错误（越位，阻止，宕机等）
			WebError=5//网络错误
		};
}
