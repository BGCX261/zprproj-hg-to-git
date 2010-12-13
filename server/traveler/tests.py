"""
This file demonstrates two different styles of tests (one doctest and one
unittest). These will both pass when you run "manage.py test".

Replace these with more appropriate tests for your application.
"""

from django.test import TestCase
from django.db import IntegrityError
from django.core.exceptions import ObjectDoesNotExist
import unittest
from iface import *

class CityTest(TestCase):
    """Class used to test city's methods and properties"""
    warsaw = City()
    
    def setUp(self):
        self.warsaw = City(name = 'Warsaw', xcoord = 30, ycoord = 40)
        
    def testPrintingMethods(self):
        """
        tests all City's methods
        """

        self.assertEqual(self.warsaw.__unicode__(), 'Warsaw(30,40)')
        self.assertEqual(self.warsaw.getInfo(), {'y': 40, 'x': 30, 'name': 'Warsaw'})

        
    def testCityNameUniqueness(self):
        """
        tests if cities' names are unique
        """

        badCity = City(name = 'Warsaw', xcoord = 2, ycoord = 2)

        #cities' names must be unique
        with self.assertRaises(IntegrityError):
            self.warsaw.save()
            badCity.save()

            
    def testCityCoordsUniqueness(self):
        """
        tests if cities' coordinates are unique
        """

        badCity = City(name = 'badCity', xcoord = 30, ycoord = 40)

        #cities' positions must be unique
        with self.assertRaises(IntegrityError):
            self.warsaw.save()
            badCity.save()



class CityListTest(TestCase):
    """Class used to test CityList methods"""
    warsaw = City()
    krakow = City()
    lodz = City()
    clist = CityList()

    def setUp(self):
        self.warsaw = City(name = 'Warsaw', xcoord = 30, ycoord = 40)
        self.krakow = City(name = 'Krakow', xcoord = 25, ycoord = 30)
        self.lodz = City(name = 'Lodz', xcoord = 25, ycoord = 35)
        self.clist = CityList(name = 'clist')

        self.warsaw.save()
        self.krakow.save()
        self.lodz.save()
        self.clist.save()


    def testAddCity(self):
        """
        tests CityList's adding City method
        """

        #adds first city and checks if it becomes home
        self.clist.addCity(self.warsaw)
        self.assertEqual(self.warsaw, self.clist.home)

        #adds another city and makes sure it doesn't become home
        self.clist.addCity(self.krakow)
        self.assertNotEqual(self.krakow, self.clist.home)


    def testDelCity(self):
        """
        tests CityList's deleting City method
        """

        self.clist.addCity(self.warsaw)
        self.clist.addCity(self.krakow)
        self.clist.addCity(self.lodz)

        #the last city is deleted from the list, home shouldn't change
        self.clist.delCity(self.lodz)
        self.assertFalse(self.clist.empty())
        self.assertEqual(self.clist.home, self.warsaw)

        #the first city is deleted from the list, home should change
        self.clist.delCity(self.warsaw)
        self.assertEqual(self.clist.home, self.krakow)

        #the list is empty, home should be None
        self.clist.delCity(self.krakow)
        self.assertTrue(self.clist.empty())
        self.assertIsNone(self.clist.homeCity)


    def testGetCities(self):
        """
        tests CityList's getCiities method
        """

        #checks if a list if cities can be properly obtained from
        #an empty and a nonempty lists
        self.assertItemsEqual(self.clist.getCities(), [])
        self.clist.addCity(self.warsaw)
        self.assertItemsEqual(self.clist.getCities(), [self.warsaw])
        

    def testHome(self):
        """
        tests CityList's home method
        """

        #checks if homeCity is appropriate for an empty and a nonempty lists
        self.assertEqual(self.clist.home, self.clist.homeCity)
        self.clist.addCity(self.warsaw)
        self.assertEqual(self.clist.home, self.clist.homeCity)


    def testInfo(self):
        """
        tests CityList's info methods and __unicode__ method
        """

        #test for an empty list
        self.assertEqual(self.clist.__unicode__(), 'clist')
        info = self.clist.getInfo()
        self.assertEqual(info['name'], 'clist')
        self.assertEqual(info['count'], 0)
        self.assertItemsEqual(self.clist.getCitiesInfo(), [])

        #test for a list with one city
        self.clist.addCity(self.warsaw)
        info = self.clist.getInfo()
        self.assertEqual(info['name'], 'clist')
        self.assertEqual(info['count'], 1)

        #checks if first city's info is OK
        firstCity = self.clist.getCitiesInfo()[0]
        self.assertEqual(firstCity['name'], 'Warsaw')
        self.assertEqual(firstCity['x'], 30)
        self.assertEqual(firstCity['y'], 40)
        self.assertEqual(firstCity['position'], 'home')

        #adds another city and checks if list's info is OK
        self.clist.addCity(self.krakow)
        info = self.clist.getInfo()
        self.assertEqual(info['name'], 'clist')
        self.assertEqual(info['count'], 2)

        #checks correctness of info of both cities
        self.assertDictEqual(firstCity, self.clist.getCitiesInfo()[0])
        secondCity = self.clist.getCitiesInfo()[1]
        self.assertEqual(secondCity['name'], 'Krakow')
        self.assertEqual(secondCity['x'], 25)
        self.assertEqual(secondCity['y'], 30)
        self.assertEqual(secondCity['position'], 'middle')



class InterfaceTest(TestCase):
    """Class used to test interface methods"""

    def testAddMethods(self):
        """
        tests adding methods from interface
        """

        #checks City's uniqueness
        cid = addCity('Warsaw', 30, 40)
        with self.assertRaises(IntegrityError):
            addCity('Warsaw', 30, 40)

        #checks if added City has proper attributes    
        warsaw = City.objects.get(id = cid)
        info = warsaw.getInfo()
        self.assertEqual(info['name'], 'Warsaw')
        self.assertEqual(info['x'], 30)
        self.assertEqual(info['y'], 40)

        #checks CityList's uniqueness
        clid = addCityList('clist')
        with self.assertRaises(IntegrityError):
            addCityList('clist')

        #checks if an added list has proper attributes
        clist = CityList.objects.get(id = clid)
        clistInfo = clist.getInfo()
        self.assertEqual(clistInfo['name'], 'clist')
        self.assertEqual(clistInfo['count'], 0)

        #checks if the list has proper attributes
        #after adding a city to the list
        addCityToList(cid, clid)
        clistInfo = clist.getInfo()
        self.assertEqual(clistInfo['name'], 'clist')
        self.assertEqual(clistInfo['count'], 1)

        clist = CityList.objects.get(id = clid)
        #checks if the added city is home
        self.assertEqual(clist.home, warsaw)

        #checks if next added city is not home
        cid2 = addCity('Krakow', 25, 30)
        addCityToList(clid, cid2)
        krakow = City.objects.get(id = cid2)
        self.assertNotEqual(clist.home, krakow)

    def testDelMethods(self):
        """
        tests deleting methods from interface
        """

        #checks if a deleted city is 'ungettable'
        cid = 1
        warsaw = City(name = 'Warsaw', xcoord = 30, ycoord = 40, id = cid)
        warsaw.save()
        delCity(cid)
        with self.assertRaises(ObjectDoesNotExist):
            deletedCity = City.objects.get(id = cid)

        #checks if a deleted citylist is 'ungettable'
        clid = 1
        clist = CityList(name = 'clist', id = clid)
        clist.save()
        delCityList(clid)
        with self.assertRaises(ObjectDoesNotExist):
            deletedList = CityList.objects.get(id = clid)

        #checks if a deleted city from a list doesn't belong to it anymore
        warsaw = City(name = 'Warsaw', xcoord = 30, ycoord = 40, id = cid)
        warsaw.save()
        clist = CityList(name = 'clist', id = clid)
        clist.save()
        clist.addCity(warsaw)
        delCityFromList(cid, clid)
        
        clist = CityList.objects.get(id = clid)
        self.assertTrue(clist.empty())

        #checks if empty list's home is None
        self.assertIsNone(clist.home)
        

    #something's wrong with getCitiesInList method!!
    def testGetMethods(self):
        """
        tests getters from interface
        """

        #checks if value returned by getCities() mtethod is correct
        #with no cities and with some cities
        self.assertListEqual(getCities(), [])
        cid1 = addCity('Warsaw', 30, 40)
        cid2 = addCity('Krakow', 25, 30)
        cities = [City.objects.get(id = cid1).getInfo(),
                   City.objects.get(id = cid2).getInfo()]
        self.assertListEqual(getCities(), cities)

        #checks if citylists returned by getCitiesLists() are correct
        #for an empty citylist and a nonempty city list
        self.assertItemsEqual(getCitiesLists(), [])
        clid1 = addCityList('clist1')
        clid2 = addCityList('clist2')
        citiesLists = [CityList.objects.get(id = clid1).getInfo(),
                       CityList.objects.get(id = clid2).getInfo()]
        self.assertListEqual(getCitiesLists(), citiesLists)

        #checks if a list of cities returned by getCitiesInList()
        #is correct when citylist is empty and when it contains some cities
        self.assertListEqual(getCitiesInList(clid1), [])
        
        addCityToList(clid1, cid1)
        addCityToList(clid1, cid2)

        warsawInfo = City.objects.get(id = cid1).getInfo()
        warsawInfo['position'] = 'home'
        krakowInfo = City.objects.get(id = cid2).getInfo()
        krakowInfo['position'] = 'middle'
        cities = [warsawInfo, krakowInfo]
        self.assertListEqual(getCitiesInList(clid1), cities)

        #checks if a list of cities is still correct after deleting one city
        delCityFromList(clid1, cid1)
        cities = [krakowInfo]
        self.assertListEqual(getCitiesInList(clid1), cities)


    def testSetHome(self):
        """
        tests setHomeCity function
        """

        cid1 = addCity('Warsaw', 30, 40)
        cid2 = addCity('Krakow', 25, 30)
        clid = addCityList('clist')
        
        clist = CityList.objects.get(id = clid)
        warsaw = City.objects.get(id = cid1)
        krakow = City.objects.get(id = cid2)

        #checks if the first added city becomes home
        setHomeCity(clid, cid1)
        clist = CityList.objects.get(id = clid)
                
        self.assertEqual(warsaw, clist.home)

        #checks if the next added city becomes home and
        #the recent home still belongs to the list
        setHomeCity(clid, cid2)
        
        clist = CityList.objects.get(id = clid)        
        self.assertEqual(krakow, clist.home)
        warsawInfo = warsaw.getInfo()
        warsawInfo['position'] = 'middle'
        self.assertIn(warsawInfo, getCitiesInList(clid))

        

if __name__=='__main__':
    unittest.main()
