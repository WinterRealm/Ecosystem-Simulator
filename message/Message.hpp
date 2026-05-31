#pragma once
#include <queue>
#include <map>
#include <string>
namespace ES{
	struct Message{
		std::map<std::string,std::string> message;
	};
	class MessageBridge{
		public:
			MessageBridge()=default;
			~MessageBridge()=default;
			void emit(Message msg){
				q.push(msg);
			}
			Message seekEvent(){
				return q.front();
			}
			void next(){
				q.pop();
			}
		private:
			std::queue<Message> q;
	};
}
