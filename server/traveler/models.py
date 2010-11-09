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



class CityList(models.Model):  
    """describes list of the cities, which have to be visited by traveler"""    
    name        = models.CharField(max_length = 50, unique=True)
    
    #one list can have multiple cities and every city can by included
    #in many lists.
    cities     = models.ManyToManyField(City)
    firstCity  = models.ForeignKey(City, related_name = 'firstCity', null=True)
    lastCity   = models.ForeignKey(City, related_name = 'lastCity', null=True)
    
    
    def __unicode__(self):
        return self.name

        
    def addCity(self, city):
        """add previously created city to the list
        
        If list was empty this city is automaticaly set as first city
        (start point for traveler)
        """
        self.cities.add(city)
        if self.firstCity is None:
            self.firstCity = city
       
            
    def delCity(self, city):
        """remove city from the list"""
        self.cities.get(city).delete()

        
    def getCities(self):
        """get all cities belonging to this city list"""     
        return self.cities.all()
        
        
    @property
    def first(self):
        """start point for traveler"""
        return self.firstCity
       
        
    @first.setter
    def first(self, city):
        self.firstCity = city
       
        
    @property
    def last(self):
        """destination point for traveler"""
        if self.lastCity is not None:
            return self.lastCity
        else:
            #if last city was not set assume that start point is also a finish
            #point
            return self.firstCity
       
            
    @last.setter
    def last(self, city):
        self.lastCity = city
        
        
    def empty(self):
        """checks if list is empty"""
        return self.cities.count() == 0


