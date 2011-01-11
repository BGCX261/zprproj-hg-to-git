from models import City, Route
from calc import Tsp, TspManager, TspState
from tsps import Tsps

def addCity(name, x, y):
    print name
    city = City(name = name, xpos = x, ypos = y)
    city.save()
    return city.id
    
def addRoute(name):
    print name
    route = Route(name = name)
    route.save()
    return route.id
    
def addCityToRoute(route_id, city_id):
    city = City.objects.get(id = city_id)
    route = Route.objects.get(id = route_id)
    route.addCity(city)
    route.save()
    
def delCity(city_id):
    City.objects.get(id = city_id).delete()

def delRoute(route_id):
    Route.objects.get(id = route_id).delete()

def delCityFromRoute(city_id, route_id):
    city = City.objects.get(id = city_id)
    route = Route.objects.get(id = route_id)
    route.delCity(city)
    
def getCities():
    cities = []
    for c in City.objects.all():
        cities.append(c.getInfo())
    return cities
    
def getRoutes():
    routes = []
    for r in Route.objects.all():
        routes.append(r.getInfo())
    return routes

def getCitiesInRoute(route_id):
    route = Route.objects.get(id = route_id)
    return route.getCitiesInfo()

def setHomeCity(route_id, city_id):
    city = City.objects.get(id = city_id)
    route = Route.objects.get(id = route_id)
    route.home = city
    route.save()
    
def tspSolve(route_id):
    route = Route.objects.get(id=route_id)
    tsp = Tsp(route)
    tsp.routeId = route.id
    
    TspManager().solve(tsp)
    Tsps().addTsp(tsp)
    
def tspState(route_id):
    tsp = Tsps().getTsp(route_id)
    return str(tsp.getState())

def tspResult(route_id):
    tsp = Tsps().getTsp(route_id)
    if tsp.getState() == TspState.SOLVED:
        route = Route.objects.get(id = route_id)
        route.cities.clear() 
        route.home = None       
        result = tsp.getResult()
        for i in result:
            route.addCity(City.objects.get(id=i))
        route.save()
        Tsps().delTsp(route_id)
        
    return result

