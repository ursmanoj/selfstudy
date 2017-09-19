class LibAPI {
public:
	static LibAPI& GetInstance() {
		static LibAPI singleObject;
		return singleObject;
	}
	void Display();
};