from models import City, CityList
from calc import Tsp, TspManager, TspState
from tsps import Tsps

def addCity(name, x, y):
    city = City(name = name, xcoord = x, ycoord = y)
    city.save()
    return city.id
    
def addCityList(name):
    cityList = CityList(name = name)
    cityList.save()
    return cityList.id
    
def addCityToList(list_id, city_id):
    city = City.objects.get(id = city_id)
    cityList = CityList.objects.get(id = list_id)
    cityList.addCity(city)
    cityList.save()
    
def delCity(city_id):
    City.objects.get(id = city_id).delete()

def delCityList(list_id):
    CityList.objects.get(id = list_id).delete()

def delCityFromList(city_id, list_id):
    city = City.objects.get(id = city_id)
    cityList = CityList.objects.get(id = list_id)
    cityList.delCity(city)
    
def getCities():
    cities = []
    for c in City.objects.all():
        cities.append(c.getInfo())
    return cities
    
def getCitiesLists():
    lists = []
    for cl in CityList.objects.all():
        lists.append(cl.getInfo())
    return lists

def getCitiesInList(list_id):
    cityList = CityList.objects.get(id = list_id)
    return cityList.getCitiesInfo()

def setHomeCity(list_id, city_id):
    city = City.objects.get(id = city_id)
    cityList = CityList.objects.get(id = list_id)
    cityList.home = city
    cityList.save()
    
def tspSolve(list_id):
    city_list = CityList.objects.get(id=list_id)
    tsp = Tsp(city_list)
    tsp.listId = city_list.id
    
    tsp_id = TspManager().solve(tsp)
    Tsps().addTsp(tsp)
    return tsp_id
    
def tspState(tsp_id):
    tsp = Tsps().getTsp(tsp_id)
    return str(tsp.getState())

def tspResult(tsp_id):
    tsp = Tsps().getTsp(tsp_id)
    if tsp.getState() == TspState.SOLVED:
        city_list = CityList.objects.get(id = tsp.listId)
        city_list.cities.clear()
        
        result = tsp.getResult()
        for i in result:
            city_list.addCity(City.objects.get(id=i))
        city_list.save()
        Tsps().delTsp(tsp_id)
        
    return result

