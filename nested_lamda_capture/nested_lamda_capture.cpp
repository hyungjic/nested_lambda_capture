// nested_lamda_capture.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <functional>
#include <iostream>

using namespace std;
class Server
{
public:
	void Start(const function<void()>& cb)
	{
		cb();
	}
};
class Client
{
public:
	Client(Server* server)
		: m_server(server) {}

	void Start()
	{
		cout << "server: " << m_server << endl;

		m_server->Start([&]()
		{
			Read([&]()
			{
				cout << "read callback" << endl;
				cout << "val: " << ++val << endl;

				int var = 100;

				Write([&]()
				{
					cout << "write callback" << endl;
					cout << "val: " << ++val << endl;
					cout << "var: " << ++var << endl;
					cout << "server: " << m_server << endl;
				});
			});
		});
	}

	void Read(const function<void()>& cb)
	{
		cb();
	}

	void Write(const function<void()>& cb)
	{
		cb();
	}

	int val = 1;
	Server* m_server;
};


int main()
{
	Server server;
	Client client(&server);

	client.Start();
	cout << "val: " << ++client.val << endl;

	return 0;
}

