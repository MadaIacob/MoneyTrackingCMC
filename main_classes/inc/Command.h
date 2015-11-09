#include "MessageHandler.h"

class Command {
	private:
		MessageHandler* ptrMessage;
	public:
		//virtual Command() = 0;
		virtual void parseParams(vector<string> params) = 0;
		virtual void validateParams(vector<string> &params) = 0;
		void setMessageHandler(MessageHandler& message);
		virtual void executeCommand();
		virtual ~Command();

		
	protected:
		void setMessageCode(MessageCodes_E messageCode);
		
}