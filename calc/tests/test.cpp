#define BOOST_TEST_MODULE calcTest
//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//msvc9.0 generuje smieci dla biblioteki boost::thread
#pragma warning(disable:4244)
//msvc9.0 generuje smieci dla biblioteki boost::unit_test_framework
#pragma warning(disable:4275)
//msvc generuje niepotrzebne ostrzezenie o zalaczaniu flagi /EHa
#pragma warning(disable:4535)
#endif

#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <map>
#include <utility>

#include "../src/Tsp/City.hpp"
#include "../src/Tsp/Route.hpp"
#include "../src/Tsp/Tsp.hpp"
#include "../src/Tsp/TspException.hpp"
#include "../src/Tsp/TspGraph.hpp"
#include "../src/Tsp/TspQueue.hpp"
#include "../src/Tsp/TspManager.hpp"

using namespace calc;

// tests if City's attributes are correct
void testCity(const City &city, const City::CityId id,
			  const City::Coord x, const City::Coord y)
{
	BOOST_CHECK_EQUAL( city.getId(), id );
	BOOST_CHECK_EQUAL( city.getX(), x );
	BOOST_CHECK_EQUAL( city.getY(), y );
}

// function that calculates summary length of the given route specified
// by city_ids in vector res.
Distance calcRouteLength(const Tsp::PResult &res,
					   std::map<City::CityId, City * > &cities)
{
	Distance length = 0.0;

	for (unsigned i = 0; i < res->size() - 1; ++i)
	{
		length += cities[(*res)[i]]->distance(*cities[(*res)[i + 1]]);
	}

	return length;
}

// tells TspManager to solve Tsp created from the given PRoute,
// checks its attributes after executing algorithm
void threadF(PRoute pRoute)
{
	PTsp pTsp(new Tsp(pRoute));
	TspManager::getInstance().solve(pTsp);
	
	// waits for Tsp to be solved and then checks if result is good
	// (checks Ids of cities in the route and Tsp's state)
	boost::this_thread::sleep(boost::posix_time::millisec(100));
	BOOST_CHECK_EQUAL( pTsp->getState(), Tsp::SOLVED );
	BOOST_CHECK( (pTsp->getResult()[0] == 0) || (pTsp->getResult()[0] == 1) );
	BOOST_CHECK( (pTsp->getResult()[1] == 0) || (pTsp->getResult()[1] == 1) );
	BOOST_CHECK_NE( pTsp->getResult()[0], pTsp->getResult()[1] );
}

// Tests City class
BOOST_AUTO_TEST_CASE( cityTest )
{
	City city1(0, 1, 2);

	// checks if city1 is correctly constructed
	BOOST_CHECK_EQUAL( city1.getId(), 0 );
	BOOST_CHECK_EQUAL( city1.getX(), 1 );
	BOOST_CHECK_EQUAL( city1.getY(), 2 );

	// checks if distance method returns correct value and
	// if it is commutative(c1.dist(c2) == c2.dist(c1))
	City city2(1, 4, 6);
	BOOST_CHECK_CLOSE( city1.distance(city2), 5, 0.1 );
	BOOST_CHECK_CLOSE( city1.distance(city2), city2.distance(city1), 0.1 );
}

// Tests Route class
BOOST_AUTO_TEST_CASE( routeTest )
{
	Route route;

	// checks size of empty route
	unsigned emptyRouteSize = route.getCities().size();
	BOOST_CHECK_EQUAL( emptyRouteSize, 0 );
	BOOST_CHECK_EQUAL( emptyRouteSize, route.getCitiesIds().size() );

	// checks size of route with one city
	City city1(0, 1, 2);
	route.addCity(city1);
	unsigned routeSize = route.getCities().size();
	BOOST_REQUIRE_EQUAL( routeSize, 1 );
	BOOST_CHECK_EQUAL( routeSize, route.getCitiesIds().size() );
	BOOST_CHECK_EQUAL( route.getCitiesIds()[0], 0);
	
	// checks if added City is unchanged
	BOOST_CHECK_EQUAL( route.getCities()[0].getId(), 0 );
	BOOST_CHECK_EQUAL( route.getCities()[0].getX(), 1 );
	BOOST_CHECK_EQUAL( route.getCities()[0].getY(), 2 );

	// checks size of list with two cities, therir paramteres
	// and if they are in proper order
	City city2(1, 2, 3);
	route.addCity(city2);
	routeSize = route.getCities().size();
	BOOST_REQUIRE_EQUAL( routeSize, 2 );
	BOOST_CHECK_EQUAL( routeSize, route.getCitiesIds().size() );
	BOOST_CHECK_EQUAL( route.getCitiesIds()[0], 0);
	BOOST_CHECK_EQUAL( route.getCitiesIds()[1], 1);

	BOOST_CHECK_EQUAL( route.getCities()[0].getId(), 0 );
	BOOST_CHECK_EQUAL( route.getCities()[0].getX(), 1 );
	BOOST_CHECK_EQUAL( route.getCities()[0].getY(), 2 );

	BOOST_CHECK_EQUAL( route.getCities()[1].getId(), 1 );
	BOOST_CHECK_EQUAL( route.getCities()[1].getX(), 2 );
	BOOST_CHECK_EQUAL( route.getCities()[1].getY(), 3 );
}

// Tests Tsp class
BOOST_AUTO_TEST_CASE( tspTest )
{
	boost::shared_ptr<Route> pEmptyRoute(new Route());
	//BOOST_CHECK_THROW( Tsp(pEmptyRoute), TspBadRouteException );

	boost::shared_ptr<Route> pRoute(new Route());

	City city1(0, 1, 2);
	City city2(1, 20, 30);
	City city3(2, 2, 2);

	pRoute->addCity(city1);
	pRoute->addCity(city2);
	pRoute->addCity(city3);
	
	std::map<City::CityId, City * > citiesMap;
	citiesMap.insert( std::pair<City::CityId, City * >(0, &city1) );
	citiesMap.insert( std::pair<City::CityId, City * >(1, &city2) );
	citiesMap.insert( std::pair<City::CityId, City * >(2, &city3) );

	// checks parameters of tsp after construction
	Tsp tsp(pRoute);
	BOOST_CHECK_EQUAL( tsp.getState(), Tsp::NONE );

	// check if QUEUED state can be set properly
	tsp.setQueued();
	BOOST_CHECK_EQUAL( tsp.getState(), Tsp::QUEUED );

	// check if solve does not change not NONE state
	tsp.solve();
	BOOST_CHECK_EQUAL( tsp.getState(), Tsp::QUEUED );

	Tsp tsp2(pRoute);
	tsp2.solve();

	// checks state of tsp after solving,
	BOOST_REQUIRE_EQUAL( tsp2.getState(), Tsp::SOLVED );
	BOOST_REQUIRE_EQUAL( tsp2.getResult().size(), 3 );

	Distance goodRouteLength = city1.distance(city3) + city3.distance(city2);
	const City &stCity = *citiesMap[tsp2.getResult()[0]];
	const City &ndCity = *citiesMap[tsp2.getResult()[1]];
	const City &rdCity = *citiesMap[tsp2.getResult()[2]];
	Distance computedLength = stCity.distance(ndCity) + ndCity.distance(rdCity);

	// checks if algorithm solved a simple problem correctly
	BOOST_CHECK_CLOSE( goodRouteLength, computedLength, 0.1 );
}

// Tests TspGraph class
BOOST_AUTO_TEST_CASE( tspGraphTest )
{
	// creates three routes consisting of the same cities
	// order of adding cities to a route was different for each route

	City city1(0, 0, 0);
	City city2(1, 0, 1);
	City city3(2, 0, 2);
	City city4(3, 0, 3);

	std::map<City::CityId, City * > cities;
	cities.insert( std::pair<City::CityId, City * >(0, &city1) );
	cities.insert( std::pair<City::CityId, City * >(1, &city2) );
	cities.insert( std::pair<City::CityId, City * >(2, &city3) );
	cities.insert( std::pair<City::CityId, City * >(3, &city4) );

	Route route1;
	route1.addCity(city1);
	route1.addCity(city2);
	route1.addCity(city3);
	route1.addCity(city4);

	Route route2;
	route2.addCity(city4);
	route2.addCity(city3);
	route2.addCity(city2);
	route2.addCity(city1);

	Route route3;
	route3.addCity(city1);
	route3.addCity(city3);
	route3.addCity(city2);
	route3.addCity(city4);

	TspGraph graph1(route1.getCities());
	TspGraph graph2(route2.getCities());
	TspGraph graph3(route3.getCities());

	// checks if length of each result-route is almost the same(close enough)
	// as length of optimal result-route

	Distance route1Length = calcRouteLength(graph1.optimizeRoute(), cities);
	Distance route2Length = calcRouteLength(graph2.optimizeRoute(), cities);
	Distance route3Length = calcRouteLength(graph3.optimizeRoute(), cities);

	BOOST_CHECK_CLOSE(route1Length, 3.0, 0.1);
	BOOST_CHECK_CLOSE(route1Length, route2Length, 0.1);
	BOOST_CHECK_CLOSE(route1Length, route3Length, 0.1);
}

// tests TspManger and TspQueue
BOOST_AUTO_TEST_CASE( tspManagerQueue )
{
	TspQueue queue;
	
	City city1(0, 0, 0);
	City city2(1, 0, 1);

	PRoute route1(new Route());
	route1->addCity(city1);
	route1->addCity(city2);

	// tests only TspQueue, checks if Ids assigned to Tsps
	// and its state are correct
	for (int i = 0; i < 3; ++i)
	{
		PTsp tmpTsp(new Tsp(route1));
		queue.push(tmpTsp);
		BOOST_CHECK_EQUAL( tmpTsp->getState(), Tsp::QUEUED );
	}

	// tests if Tsp's state after poping hasn't changed
	// since putting it inside the queue
	for (int i = 0; i < 3; ++i)
	{
		PTsp tmpTsp(queue.pop());
		BOOST_CHECK_EQUAL( tmpTsp->getState(), Tsp::QUEUED );
	}

	// tests correctness of cooperation of TspManager and TspQueue
	// with many threads
	const int MAX_THREADS = 1;
	boost::thread_group threadGroup;
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		// this part is incorrect
		//threadGroup.create_thread(boost::bind(&threadF, route1));
	}
	threadGroup.join_all();

	int i = 1;
	++i;
}
