#include <iostream>
#include <memory>
#include <string>

using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;

struct connection{
	string ip;
	int port;
	connection(string i, int p) : ip(i), port(p){}
};

struct destination{
	string ip;
	int port;
	destination(string i, int p) : ip(i), port(p){}
};

connection connect(destination* pDest){
	shared_ptr<connection> pConn(new connection(pDest->ip, pDest->port));
	cout << "creating connection( " << pConn.use_count() << " )" << endl; 
	return *pConn;
} 

void disconnect(connection pConn){
	cout << "connection close( " << pConn.ip << ": " << pConn.port << ")" << endl;
}

void end_connection(connection* pConn){
	disconnect(*pConn);
}

void f(destination &d){
	connection conn = connect(&d);
	shared_ptr<connection> p(&conn, end_connection);
	cout << "connecting now ( " << p.use_count() << " )" << endl;
}

int main(){
	destination dest("220.181.110.110", 12345);
	f(dest);

	return 0;
}
