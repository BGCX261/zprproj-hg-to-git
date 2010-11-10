from pyamf.remoting.gateway.django import DjangoGateway
import iface


def echo(data):
    'simple echo function, for basic testing purpose'
    return data

   
   
#available services
services = {
    'traveler.echo'             : echo,
    'traveler.addCity'          : iface.addCity,
    'traveler.addCityList'      : iface.addCityList,
    'traveler.addCityToList'    : iface.addCityToList,
    'traveler.delCity'          : iface.delCity,
    'traveler.delCityList'      : iface.delCityList,
    'traveler.delCityFromList'  : iface.delCityFromList,
    'traveler.getCities'        : iface.getCities,
    'traveler.getCitiesLists'   : iface.getCitiesLists,
    'traveler.getCitiesInList'  : iface.getCitiesInList,
    'traveler.setFirstCity'     : iface.setFirstCity,
    'traveler.setLastCity'      : iface.setLastCity,
}
    

#open pyamf gateway, discard 'request' argument in service - handling functions    
gateway = DjangoGateway(services, expose_request = False)
