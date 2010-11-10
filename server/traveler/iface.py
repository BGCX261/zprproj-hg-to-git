from models import City, CityList

def addCity(name, x, y):
    city = City(name = name, xcoord = x, ycoord = y)
    city.save()
    return city.id
    
def addCityList(name):
    cityList = CityList(name = name)
    cityList.save()
    return cityList.id
    
def addCityToList(city_id, list_id):
    city = City.objects.get(id = city_id)
    cityList = CityList.objects.get(id = list_id)
    cityList.addCity(city)
    
def delCity(city_id):
    City.objects.get(id = city_id).delete()

def delCityList(list_id):
    CityList.objects.get(id = list_id).delete()

def delCityFromList(city_id, list_id):
    city = Cities.objects.get(id = city_id)
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
    cities = []
    cityList = CityList.objects.get(id = list_id)
    for c in cityList.getCities():
        cities.append(c.getInfo())
    return cities

def setFirstCity(list_id, city_id)
    city = Cities.objects.get(id = city_id)
    CityList.objects.get(id = list_id).first = city
    
def setLastCity(list_id, city_id)
    city = Cities.objects.get(id = city_id)
    CityList.objects.get(id = list_id).last = city

