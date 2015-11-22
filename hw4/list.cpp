void listAll(const Class* c, string path)  // two-parameter overload
{
	if (path == "")
	{
		cout << path + c->name() << endl;
		path += c->name() + "=>";
	}

	vector<Class*>::const_iterator it = c->subclasses().begin();
	while (it != c->subclasses().end())
	{
		cout << path + (*it)->name() << endl;
		listAll(*it, path + (*it)->name() + "=>");
		it++;
	}

	return;
}