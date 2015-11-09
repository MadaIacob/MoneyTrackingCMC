
class MessageHandler {
	private:
		MessageCodes_E messageCode;
	
	public:
		MessageHandler() : messageCode(NO_ERROR){}
		void setMessageCode(MessageCodes_E messageCode);
		bool isSetMessageCode();
		void printMessage(vector<string> parameters);
		MessageCodes_E getMessageCode();
		
};

