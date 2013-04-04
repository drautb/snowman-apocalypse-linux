#pragma once

class Object
{
public:

	static int				nextId;

private:

	int						id;

public:

	Object(void);
	~Object(void);

	int Id()const{return id;}
};

