from django.db import models



class City(models.Model):
    """Describes one city"""       
    name = models.CharField(max_length = 50, unique=True)
    xcoord = models.PositiveIntegerField()
    ycoord = models.PositiveIntegerField()
    
    #the coordinates of the city must be uniqe (we do not alow two cities in
    #one place)
    unique_together = ('xcoord', 'ycoord')
    
    def __unicode__(self):
        return self.name + '(' + xcoord + ',' + ycoord + ')'



class CityList(models.Model):  
    """describes list of the cities, which have to be visited by traveler"""    
    name = models.CharField(max_length = 50, unique=True)
    
    #one list can have multiple cities and every city can by included
    #in many lists. Relation described by 'CityInList' model
    cities = models.ManyToManyField(City, through='CityInList')
    
    def __unicode__(self):
        return self.name
    
    

    def addCity(self, city):
        """add previously created city to the list"""
        cil = CityInList(city = city, cityList = self)
        cil.save()
        
    
    def delCity(self, city):
        """remove city from the list"""
        cil = CityInList.objects.get(city = city, cityList = self)
        cil.delete()
        
    def getCities(self):
        """get all cities belonging to this city list
        
        cities returned are sorted by the position field, which means the first
        city in returned list will be a city marked as start point for traveler
        and the last one will be city marked as traveler's destination point
        """
        
        cities = CityInList.objects.order_by('position').filter(cityList = self)
        return cities

    
    

class CityInList(models.Model):
    """describes cities in lists memberships"""
    
    #the naming here (exactly the real, short names) is important since it allows
    #to easily sort some group of cities in order where first city is 'really'
    #first at the list, and last city is 'really' last one
    POSITION_CHOICES = (
        ('a', 'first'),
        ('b', 'middle'),        
        ('c', 'last'),
    )
    
    #we have to explicitly tell about foreign keys we will use
    city = models.ForeignKey(City)
    cityList = models.ForeignKey(CityList)
    
    #whether we should threat city as start / finish point in list or just 
    #a city that can be somewhere in the middle of any path
    position = models.CharField(max_length=1, choices=POSITION_CHOICES, default='middle')
    
    def __unicode__(self):
        return self.city.name + ' in ' + self.cityList.name


