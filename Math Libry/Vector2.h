#pragma once
namespace Mathclasses 
{
	
	
	struct Vector2 
	{

	union
	{

		struct { float x; float y; };
		
		
	};
		float data[2];
		/// <summary>
		/// de
		/// </summary>
		Vector2() : x(0), y(0) { }
	};
}
	
