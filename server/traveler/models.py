from django.db import models



class City(models.Model):
    """Describes one city"""       
    name = models.CharField(max_length = 50, unique=True)
    xcoord = models.PositiveIntegerField()
    ycoord = models.PositiveIntegerField()
    

    class Meta:
        #the coordinates of the city must be uniqe (we do not alow two cities in
        #one place)    
        unique_together = ('xcoord', 'ycoord')
    
    def __unicode__(self):
        return self.name + '(' + str(self.xcoord) + ',' + str(self.ycoord) + ')'
        
    def getInfo(self):
        return {'name': self.name, 'x': self.xcoord, 'y': self.ycoord}



class CityList(models.Model):  
    """describes list of the cities, which have to be visited by traveler"""    
    name        = models.CharField(max_length = 50, unique=True)
    
    #one list can have multiple cities and every city can by included
    #in many lists.
    cities      = models.ManyToManyField(City)
    homeCity    = models.ForeignKey(City, related_name = 'home', null=True)
    
    
    def __unicode__(self):
        return self.name

        
    def addCity(self, city):
        """add previously created city to the list
        
        If list was empty this city is automaticaly set as first city
        (start point for traveler)
        """
        self.cities.add(city)
        if self.homeCity is None:
            self.homeCity = city
       
            
    def delCity(self, city):
        """remove city from the list"""
        self.cities.remove(city)
        
        """
        if self.homeCity == city and self.empty():
            self.homeCity = None
        elif self.homeCity == city and not self.empty():
            self.homeCity = self.getCities()[0]

        #Code below doesn't work. There is a proposed solution above.
        """
        if self.homeCity is None and not self.empty():
            self.homeCity = getCities()[0]
            

        
    def getCities(self):
        """get all cities belonging to this city list"""     
        return self.cities.all()
        
        
    @property
    def home(self):
        """start point for traveler
        
        if you set this to a city not included in this list yet, it will be added
        """
        return self.homeCity
        
       
        
    @home.setter
    def home(self, city):
        if city not in self.getCities():
            self.addCity(city)
        self.homeCity = city
        
        
    def getInfo(self):
        """returns basic information about the list"""
        return {'name': self.name, 'count': self.cities.count()}
        
        
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
            
        return info
        
        
    def empty(self):
        """checks if list is empty"""
        return self.cities.count() == 0        

