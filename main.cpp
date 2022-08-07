#include <windows.h>
#include <fstream>
#include "SimConnect.h"
#include <iostream>
#include <C:\Users\Ozzy\source\repos\Project1\json.hpp>



using json = nlohmann::json;
int quit = 0;
HANDLE hSimConnect = NULL;

enum DATA_DEFINE_ID {
	DEFINITION_1,
};

enum DATA_REQUEST_ID {
	REQUEST_1,
};

struct SimResponse {
	double altitude;
	double heading;
	double speed;
	double degree_latitude;
	double degree_longitude;
	double Pitch;
	double Bank;
	double fuel_total_quantity;
};

void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
	switch (pData->dwID)
	{

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST_1:

			SimResponse* pS = (SimResponse*)&pObjData->dwData;


			std::cout

				<< "\r Altitude: " << pS->altitude
				<< "\n Heading: " << pS->heading
				<< "\n Speed (knots): " << pS->speed
				<< "\n Latitude: " << pS->degree_latitude
				<< "\n Longitude: " << pS->degree_longitude
				<< "\n Pitch: " << pS->Pitch
				<< "\n Bank: " << pS->Bank
				<< "\n Fuel: " << pS->fuel_total_quantity

				<< std::flush;
				 

			break;
		}
		break;
	}
	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;
		break;
	}

	default:
		break;
	}
}

bool initSimEvents() {
	HRESULT hr;

	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Client Event Demo", NULL, 0, NULL, 0))) {
		std::cout << "Connected to Microsoft Flight Sim 2020!" << std::endl;	
		
		//Handle data
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Indicated Altitude", "feet");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "HEADING INDICATOR", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Airspeed Indicated", "knots");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "PLANE LATITUDE", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "PLANE LONGITUDE", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "PLANE PITCH DEGREES", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "PLANE BANK DEGREES", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "FUEL TOTAL QUANTITY", "Gallons");

		//Request data every second
		hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);

		// Process incoming SimConnect Server messages
		while (quit == 0) {
			// Continuously call SimConnect_CallDispatch until quit - MyDispatchProc1 will handle simulation events
			SimConnect_CallDispatch(hSimConnect, MyDispatchProc1, NULL);
			Sleep(1);
		}

		//Close handle when done
		hr = SimConnect_Close(hSimConnect);
		return true;

	}

	else {
		std::cout << "Failed to connect, make sure your flight sim is running" << std::endl;
		return false;
	}
}

int main() {

	class SimResponse;
	static double altitude;
	static double heading;
	static double speed;
	static double degree_latitude;
	static double degree_longitude;
	static double Pitch;
	static double Bank;
	static double fuel_total_quantity;

	json j;
	j["Altitude"] = altitude;
	j["Heading"] = heading;
	j["Speed"] = speed;
	j["Lat"] = degree_latitude;
	j["Long"] = degree_longitude;
	j["Pitch"] = Pitch;
	j["Bank"] = Bank;
	j["Fuel"] = fuel_total_quantity;
	std::ofstream file("data.json");
	file << j;


	initSimEvents();
	std::cin.get();
	return 0; 
}
