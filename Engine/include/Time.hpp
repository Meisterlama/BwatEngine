#ifndef TIME_HPP
#define TIME_HPP

namespace BwatEngine
{
	class Time
	{
	public:
		static double deltaTime;

		static void Update();
		static void Reset();

	private:
	    static double lastFrame;
	};

}

#endif 