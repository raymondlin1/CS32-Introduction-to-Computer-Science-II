void listAll(const Class* c, string path)  // two-parameter overload
{
	if (c == nullptr)
		return;

	string temp = path + c->name();
	cout << temp << endl;

	const vector<Class*> v = c->subclasses();
	vector<Class*>::const_iterator it = v.begin();
	while (it != v.end())
	{
		if ((*it) == nullptr)
		{
			cout << endl;
		}
		else
		{

			listAll((*it), temp + "=>");
		}

		it++;
	}
}