from django.db import models
from math import sqrt



class City(models.Model):
    """Describes one city"""       
    name = models.CharField(max_length = 50, unique=True)
    xpos = models.PositiveIntegerField()
    ypos = models.PositiveIntegerField()
    

    class Meta:
        #the posinates of the city must be uniqe (we do not alow two cities in
        #one place)    
        unique_together = ('xpos', 'ypos')
    
    def __unicode__(self):
        return self.name + '(' + str(self.xpos) + ',' + str(self.ypos) + ')'
        
    def getInfo(self):
        return {'id': self.id, 'name': self.name, 'xpos': self.xpos, 'ypos': self.ypos}



class Route(models.Model):  
    """describes list of the cities, which have to be visited by traveler"""    
    name        = models.CharField(max_length = 50, unique=True, null=False)
    
    #one list can have multiple cities and every city can by included
    #in many lists.
    cities      = models.ManyToManyField(City, through='Membership')
    homeCity    = models.ForeignKey(City, related_name = 'home_city', null=True)
    next        = models.PositiveIntegerField(default=0)    
    
    
    def __unicode__(self):
        return self.name

        
    def addCity(self, city):
        """add previously created city to the list
        
        If list was empty this city is automaticaly set as first city
        (start point for traveler)
        """

        m = Membership.objects.create(route=self, city=city, order=self.next)
        m.save()        
        self.next += 1

        if self.homeCity is None:
            self.homeCity = city

       
            
    def delCity(self, city):
        """remove city from the list"""
        
        if self.homeCity.pk == city.pk:
            self.homeCity = None  
            
        Membership.objects.get(route=self, city=city).delete() 
                          
        if not self.empty():
            self.homeCity = self.getCities()[0]

        
    def getCities(self):
        """get all cities belonging to this city list"""
        cities = []
        for c in Membership.objects.filter(route=self).order_by('order'):
            cities.append(c.city)

        return cities
        
        
    @property
    def home(self):
        """start point for traveler
        
        if you set this to a city not included in this list yet, it will be added
        """
        return self.homeCity
        
       
        
    @home.setter
    def home(self, city):
        if self.home is not None:
            Membership.objects.filter(city__id=self.home.id).update(order=self.next)            
            self.next += 1            
        if city not in self.getCities():
            self.addCity(city)
        self.homeCity = city
        Membership.objects.filter(city__id=city.id).update(order=0)
        
        
    def getInfo(self):
        """returns basic information about the list"""
        return {'id': self.id, 'name': self.name, 'count': self.cities.count(), 'length': self.getLength()}
        
        
    def getCitiesInfo(self):
        """returns information about cities included in the list"""
        info = []
        for c in self.getCities():
            if c.pk == self.home.pk:
                pos = 'home'
            else:
                pos = 'middle'
                
            cityInfo = c.getInfo()
            cityInfo['position'] = pos
            
            info.append(cityInfo)
        #print 'current length: ', self.getLength()                        
        return info
        
    def getLength(self):
        if self.cities.count() < 2:
            return 0
        length = 0
        print self.getCities(), (self.getCities()[:-1], self.getCities()[1:])
        for c1,c2 in zip(self.getCities()[:-1], self.getCities()[1:]):
            length += self.citiesDistance(c1,c2)
        return length
            
    def citiesDistance(self, city1, city2):
        return sqrt((city2.xpos - city1.xpos)**2 + (city2.ypos - city1.ypos)**2)
        
    def empty(self):
        """checks if list is empty"""
        return self.cities.count() == 0   
        
        
class Membership(models.Model):
    route = models.ForeignKey(Route)
    city = models.ForeignKey(City)
    order = models.PositiveIntegerField()
    
    class Meta:
        unique_together = ('route', 'city')    
    
    def __unicode__(self):
        return str(self.city) + ' in ' + str(self.route) + ' (' + str(self.order) + ')'
             

